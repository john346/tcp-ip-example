#ifndef ICMPV4_H_
#define ICMPV4_H_

/* System headers */
#include <stdint.h>

/* Application headers */
#include "ethernet.h"
#include "netdev.h"
#include "ipv4.h"

#define ICMP_V4_ECHO 0x08
#define ICMP_V4_REPLY 0x00

/* Struct to hold header information */
struct icmp_v4_hdr {
  uint8_t type;
  uint8_t code;
  uint16_t csum;
  uint8_t data[];
} __attribute__((packed));

/* Struct to hold pcaket information for an echp */
struct icmp_v4_echo {
    uint16_t id;
    uint16_t seq;
    uint8_t data[];
} __attribute__((packed));

/* Struct to hold packet information for an unreachable message */
struct icmp_v4_dst_unreachable {
    uint8_t unused;
    uint8_t len;
    uint16_t var;
    uint8_t data[];
} __attribute__((packed));

void icmpv4_incoming(struct netdev *dev, struct eth_hdr * hdr);
void icmpv4_reply(struct netdev *dev, struct eth_hdr *hdr);

#endif