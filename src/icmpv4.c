#include "icmpv4.h"

void icmpv4_incoming(struct netdev *dev, struct eth_hdr *hdr)  {
  // Extract the icmp packet from the ethernet data
  struct ipv4_hdr *iphdr = (struct ipv4_hdr *) hdr->payload;
  struct icmp_v4_hdr *icmphdr = (struct icmp_v4_hdr *) iphdr->data;

  // Check that the checksum is valid
  if (checksum(icmphdr, iphdr->len - (iphdr->ihl * 4))) {
    printf("Invalid checksum received in ICMP packet\n");
    return;
  }

  // Process the packet
  switch (icmphdr->type) {
    case ICMP_V4_ECHO:
      icmpv4_reply(dev, hdr);
      break;
    default:
      printf("\n");
      break;
  }
}

void icmpv4_reply(struct netdev *dev, struct eth_hdr *hdr) {
  // Extract the 
  struct ipv4_hdr *iphdr = (struct ipv4_hdr *) hdr->payload;
  struct icmp_v4_hdr *icmphdr = (struct icmp_v4_hdr *) iphdr->data;

  // Add the ICMP reply and checksum data to the packet
  icmphdr->type = ICMP_V4_REPLY;
  icmphdr->csum = 0;
  icmphdr->csum = checksum(icmphdr, iphdr->len - (iphdr->ihl * 4));

  // Transmit the packet
  ipv4_transmit(dev, hdr);
}