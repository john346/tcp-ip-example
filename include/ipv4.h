#ifndef IPV4_H_
#define IPV4_H_

/* System headers */
#include <stdint.h>
#include <arpa/inet.h>

/* Application headers */
#include "netdev.h"
#include "ethernet.h"
#include "utils.h"
#include "icmpv4.h"

#define IPV4 0x04

#define ICMPV4 0x01

/* Struct which describes an ipv4 header */
struct ipv4_hdr {
  uint8_t ihl : 4,
          version : 4;
  uint8_t tos;
  uint16_t len;
  uint16_t id;
  uint16_t  flags : 3,
            frag_offset : 13;
  uint8_t ttl;
  uint8_t protocol;
  uint16_t csum;
  uint32_t saddr;
  uint32_t daddr;
  uint8_t data[];
} __attribute((packed))__;

void ipv4_incoming(struct netdev *dev, struct eth_hdr *hdr);
void ipv4_transmit(struct netdev *dev, struct eth_hdr *hdr);

#endif