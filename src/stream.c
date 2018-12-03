#include "stream.h"

#include <netinet/in.h>

void ts_init()
{
	sstat.pc = NULL;
	sstat.size = 0;
}

void ts_destroy()
{
	free(sstat.pc);
	sstat.size = 0;
}

uint8_t ts_get_cc(uint16_t pid)
{
	if (sstat.size != 0)
		for (ssize_t i = 0; i < sstat.size; i++)
		{
			struct ts_pid_cc *npc = sstat.pc + i;

			if (npc->pid == pid)
				return npc->cc;
		}

	return TS_CC_NE;
}

void ts_add_pid(uint16_t pid, uint8_t cc)
{
	struct ts_pid_cc *npc = NULL;

	if (sstat.pc != NULL && sstat.size != 0)
	{
		realloc(sstat.pc, sizeof(struct ts_pid_cc) * (sstat.size + 1));
		npc = sstat.pc + sstat.size;
		sstat.size++;
	}
	else
	{
		sstat.pc = malloc(sizeof(struct ts_pid_cc));
		npc = sstat.pc;
		sstat.size = 1;
	}

	npc->pid = pid;
	npc->cc = cc;
}

void ts_set_cc(uint16_t pid, uint8_t cc)
{
	for (ssize_t i = 0; i < sstat.size; i++)
	{
		struct ts_pid_cc *npc = &sstat.pc[i];

		if (npc->pid == pid)
			npc->cc = cc;
	}
}

void tr_analize(void *buff, size_t size)
{
	if (size % TS_SIZE != 0)
		printf("UDP packet size not aligned to 188!\n");

	for (size_t i = 0; i < size / TS_SIZE; i++)
	{
		uint32_t header = ntohl(*((uint32_t*)buff + (i * TS_SIZE / 4)));
		
		uint8_t sb = header >> 24;
		uint8_t tei = (header & 0x800000) >> 23;
		uint8_t pusi = (header & 0x400000) >> 22;
		uint8_t tp = (header & 0x200000) >> 21;
		uint16_t pid = (header & 0x1fff00) >> 8;
		uint8_t tsc = (header & 0xc0) >> 6;
		uint8_t afc = (header & 0x30) >> 4;
		uint8_t cc = header & 0x0000000f;
#if defined DEBUG
		printf("SB: %02x ", sb);
		printf("TEI: %x ", tei);
		printf("PUSI: %x ", pusi);
		printf("TP: %x ", tp);
		printf("PID: %04x ", pid);
		printf("TSC: %x ", tsc);
		printf("AFC: %x ", afc);
		printf("CC: %02x", cc);
		printf("\n");
#endif
		if (sb != 0x47)
			printf("Sync byte incorrect!\n");

		// Skip packets without payload and null packets
		if (afc == 2 || pid == TS_PID_NP)
			continue;

		uint8_t occ = ts_get_cc(pid);
		if (occ != TS_CC_NE)
		{
			uint8_t ncc = ((occ < 15) ? occ + 1 : 0);
			if (ncc != cc)
				printf("Continuity sequence in PID: %04x broken! Expected: %02x, received: %02x\n", pid, ncc, cc);

			ts_set_cc(pid, cc);
		}
		else
			ts_add_pid(pid, cc);
	}
}
