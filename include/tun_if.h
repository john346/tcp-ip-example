#ifndef TUN_IF_H_
#define TUN_IF_H_

/* System Headers */
#include <stdlib.h>
#include <stdio.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* Application headers */
#include "utils.h"

// I am not sure why we have to use this address
#define IP_ADDR "10.0.0.0/24"

void tun_init(char *dev);
int tun_read(char *buf, int len);
int tun_write(char *buf, int len);

#endif