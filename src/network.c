#include "network.h"

#include <sys/socket.h>
#include <stdlib.h>

bool url_parse(const char *addr, struct url_t *url)
{
	url = malloc(sizeof(struct url_t));
	url->network = PF_INET;
	url->protocol = SOCK_DGRAM;
	url->address = atoi("224.1.0.1");
	url->port = 11111;

	return true;
}

bool url_open(struct url_t *url)
{
	url->socket = socket(url->network, url->protocol, 0);

	return true;
}

bool url_close(struct url_t *url)
{
	close(url->socket);

	return true;
}
