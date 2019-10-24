#include "util.h"
#include "sender.h"

/*
 * For a clock length of config->interval,
 * - Sends a bit 1 to the receiver by ...
 * - Sends a bit 0 by doing nothing
 */
void send_bit(bool one, struct config *config)
{
	// Synchronize with receiver
	CYCLES start_t = cc_sync();
	if (one) {
		// Repeatedly flush addr
		ADDR_PTR addr = config->addr;
		while ((get_time() - start_t) < config->interval) {
				clflush(addr);
		}	

	} else {
		// Do Nothing
		while (get_time() - start_t < config->interval) {}
	}
}

int main(int argc, char **argv) {
	// Initialize config and local variables
	struct config config;
	init_config(&config, argc, argv);
	int sending = 1;

    clock_t start_t, end_t;

	bool sequence[8] = {1,0,1,0,1,0,1,1};

	printf("Please type a message (exit to stop).\n");
	while (sending) {
        /*cc_sync();*/
        /*clflush(config.addr);*/
        /*continue;*/

		// Get a message to send from the user
		printf("< ");
		char text_buf[128];
		fgets(text_buf, sizeof(text_buf), stdin);

		// Indicate termination if input message is "exit"
		if (strcmp(text_buf, "exit\n") == 0) {
			sending = 0;
		}

		// Convert that message to binary
		char *msg = string_to_binary(text_buf);

		// Send a '10101011' bit sequence tell the receiver
		// a message is going to be sent
		for (int i = 0; i < 8; i++) {
			send_bit(sequence[i], &config);
		}

		// Send the message bit by bit
		size_t msg_len = strlen(msg);
        start_t = clock();
		for (int ind = 0; ind < msg_len; ind++) {
			if (msg[ind] == '0') {
				send_bit(false, &config);
			} else {
				send_bit(true, &config);
			}
		}
        end_t = clock();

        printf("Bitrate: %.2f Bytes/second\n", ((double) msg_len) / ((double) (end_t - start_t) / CLOCKS_PER_SEC));
	}

	printf("Sender finished\n");
	return 0;
}
