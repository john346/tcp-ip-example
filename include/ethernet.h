#ifndef ETHERNET_H_
#define ETHERNET_H_

/* System headers */
#include <stdint.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

struct eth_hdr {
  unsigned char dmac[6];
  unsigned char smac[6];
  uint16_t ethertype;
  unsigned char payload[];
} __attribute__((packed));

struct eth_hdr* init_eth_hdr(char *buf);

#endif