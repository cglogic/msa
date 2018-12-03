#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "common.h"

struct url_t
{
	int s;
	struct sockaddr_in a;
};

bool url_parse(/*const char *addr, struct url_t *url*/);
bool url_open(struct url_t *url);
bool url_receive(struct url_t *url);
bool url_close(struct url_t *url);

#endif // NETWORK_H
