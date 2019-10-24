#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


#ifndef UTIL_H_
#define UTIL_H_

#define CYCLES uint32_t
#define ADDR_PTR uint64_t

#ifdef DUPLEX_MODE
#define CHANNEL_SENDING_INTERVAL        0x00009FFFF
#define CHANNEL_SYNC_TIMEMASK           0x0000FFFFF
#else
#define CHANNEL_SENDING_INTERVAL        0x00009FFF
#define CHANNEL_SYNC_TIMEMASK           0x0000FFFF
#endif

#define CHANNEL_SYNC_JITTER             0x0100

#define MAX_BUFFER_LEN	1024


struct config {
	int interval;
	ADDR_PTR addr;
};

CYCLES mem_access(ADDR_PTR addr);
CYCLES rdtscp(void);
CYCLES get_time();
CYCLES cc_sync();


void clflush(ADDR_PTR addr);

char *string_to_binary(char *s);

char *conv_char(char *data, int size, char *msg);

void init_config(struct config *config, int argc, char **argv);




#endif
