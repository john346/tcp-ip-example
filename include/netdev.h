#ifndef NETDEV_H_
#define NETDEV_H_

/* System Headers */
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

/* Application headers */
#include "ethernet.h"
#include "tun_if.h"

/* Struct to describe the local network (IP, MAC) */
struct netdev {
  uint32_t addr;
  unsigned char hwaddr [6];
};

void init_netdev(struct netdev *netdev, char *addr, char *hwaddr);
void netdev_tx(struct netdev *dev, struct eth_hdr *hdr,
                uint16_t ethertype, int len, unsigned char *dest);

#endif