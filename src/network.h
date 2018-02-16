#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>

struct url_t
{
	// Protocol
	// Address
	// Port
};

bool url_parse(const char *addr, struct url_t *url);
bool url_open(struct url_t *url);

#endif // NETWORK_H
