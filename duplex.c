#include "util.h"

#define CHANNEL_THRESHOLD 100
#include <pthread.h>

int CSTATE = CSTATE_IDENT;
int READY = 0;
char SND_BUF[129];
char RECV_BUF[128];
const char frame_start_seq = '\xab';

void*
read_from_stdin()
{
    while (true) {
        fflush(stdout);
        printf("\nSend < ");
        SND_BUF[0] = frame_start_seq;
        fgets(SND_BUF + 1, sizeof(SND_BUF), stdin);
        READY = 1;

        while (READY) {
        };
    }
}

int
main(int argc, char** argv)
{
    // Initialize config and local variables
    struct config config;
    init_config(&config, argc, argv);

    char* msg = NULL;
    size_t msg_len = 0;

    ADDR_PTR addr = config.addr;

    // Iterator/index into the send and recv buffers.
    int send_iter = 0, recv_iter = 0;

    CYCLES access_time;
    uint8_t bit_sequence = 0;
    int receiving = 0;
    int sync = 0;
    char cur_char = 0;
    pthread_t reader_thread;

    pthread_create(&reader_thread, NULL, read_from_stdin, NULL);

    while (true) {
        CYCLES start_t = cc_sync();
        // Choose the granularity of 1 epoch and extract the nth bit to
        // alternate between modes.
        int misses = 0, hits = 0;
        int mode = ((start_t >> 21) & 1) ^ CSTATE;
        bool bit;

        fflush(stdout);

        switch (mode) {
            case 0:
                // We're in send mode, there are a couple of things to do
                // here:
                //  1. Check if we have a pending message to send.
                //  2. If, there is a pending message, we're in one of two
                //     states:
                //     2.a. We've send a part of the message, therefore, the
                //          iterator and current buffer and non-zero.
                //     2.b. We have a brand new message!
                if (!READY)
                    continue;

                if (send_iter == 0) {
                    msg = string_to_binary(SND_BUF);
                    msg_len = strlen(msg);
                }

                if (msg[send_iter] == '1') {
                    // Repeatedly flush addr
                    while ((get_time() - start_t) < config.interval) {
                        clflush(addr);
                    }
                } else {
                    // Do Nothing
                    while (get_time() - start_t < config.interval) {
                    }
                }

                send_iter += 1;
                if (send_iter == (msg_len * 8)) {
                    /* Reset and get ready for new input from commandline */
                    READY = 0;
                    send_iter = 0;
                    msg = NULL;
                    msg_len = 0;
                }
                break;
            case 1:
                // We're in receive mode, there are multiple things to do here:
                // 1. receive a bit.
                // 2. Check if frame_start_seq was received, if it is, then
                //    this bit is a part of the message, so add it.
                // 3. Else, append it to the sequence, compare to
                //    frame_start_seq, and set the state appropriately.
                while ((get_time() - start_t) < config.interval) {
                    access_time = mem_access(config.addr);
                    // Check if detected 1 or 0
                    if (access_time > CHANNEL_THRESHOLD) {
                        misses++;
                    } else {
                        hits++;
                    }
                }

                bit = misses >= hits;

                if (bit_sequence == (uint8_t)frame_start_seq) {
                    // Add the bit to the message being assembled
                    cur_char = ((uint8_t)cur_char << 1) | bit;
                    recv_iter += 1;
                    if (recv_iter % 8 != 0) {
                        // We haven't assembled a full byte just yet.
                        continue;
                    }

                    // We have a full character worth of bytes now!
                    RECV_BUF[(recv_iter / 8) - 1] = (char)cur_char;
                    if (cur_char == '\0') {
                        // NULL byte, end-of-message
                        bit_sequence = 0;
                        recv_iter = 0;
                        printf("\nReceived > %s\n", RECV_BUF);
                    }

                    cur_char = (char)0;
                } else {
                    // Detect frame start
                    bit_sequence = ((uint8_t)bit_sequence << 1) | bit;
                    cur_char = 0;
                }
                break;
        }
    }

    return 0;
}
