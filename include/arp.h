#ifndef ARP_H_
#define ARP_H_

#define ARP_ETHERNET    0x0001
#define ARP_IPV4        0x0800
#define ARP_REQUEST     0x0001
#define ARP_REPLY       0x0002

#define ARP_CACHE_LEN   32
#define ARP_FREE        0
#define ARP_WAITING     1
#define ARP_RESOLVED    2

/* System headers */
#include <stdint.h>
#include <string.h>

/* Application ehaders */
#include "ethernet.h"
#include "netdev.h"

struct arp_hdr {
  uint16_t hwtype;
  uint16_t protype;
  unsigned char hwsize;
  unsigned char prosize;
  uint16_t opcode;
  unsigned char data[];
} __attribute__((packed));

struct arp_ipv4 {
  unsigned char smac[6];
  uint32_t sip;
  unsigned char dmac[6];
  uint32_t dip; 
} __attribute__((packed));

/* Struct to store a single entry in the ARP table */
struct arp_cache_entry{
  uint16_t hwtype;
  uint32_t sip;
  unsigned char smac[6];
  unsigned int state;
};

void arp_init();
void arp_incoming(struct netdev *netdev, struct eth_hdr *hdr);
void arp_reply(struct netdev *netdev, struct eth_hdr *hdr, struct arp_hdr *arphdr);

#endif