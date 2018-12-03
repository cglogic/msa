#ifndef STREAM_H
#define STREAM_H

#include "common.h"

#define TS_SIZE 188
#define TS_PID_NP 0x1fff
#define TS_CC_NE 0xff

struct ts_pid_cc
{
	uint16_t pid;
	uint8_t cc;
};

struct ts_stream_stat
{
	struct ts_pid_cc *pc;
	size_t size;
} sstat;

void ts_init();
void ts_destroy();
uint8_t tr_get_cc(uint16_t pid);
void ts_add_pid(uint16_t pid, uint8_t cc);
void ts_set_cc(uint16_t pid, uint8_t cc);

void tr_analize(void *buff, size_t size);

#endif // STREAM_H
