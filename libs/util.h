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

#define CHANNEL_SENDING_INTERVAL        0x00008000
#define CHANNEL_SYNC_TIMEMASK           0x000FFFFF
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
