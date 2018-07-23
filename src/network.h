#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

struct url_t
{
	int network;	// Internet version
	int protocol;	// Protocol
	int address;	// Address
	int port;	// Port

	int socket;	// Created socket
};

bool url_parse(const char *addr, struct url_t *url);
bool url_open(struct url_t *url);
bool url_close(struct url_t *url);

#endif // NETWORK_H
