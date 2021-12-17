#include "ipv4.h"

/* Handle incoming ipv4 packets */
void ipv4_incoming(struct netdev *dev, struct eth_hdr *hdr) {
  // Cast the payload of the ethernet packet to the ipv4 header
  struct ipv4_hdr *ip_hdr = (struct ipv4_hdr *) hdr->payload;

  // Check that the packet uses ipv4 protocol
  if (ip_hdr->version != IPV4) {
    printf("Only ipv4 packets are supported\n");
    return;
  }

  // Check that the ihl length is at least 5 (minimun for ipv4)
  if (ip_hdr->ihl < 5) {
    printf("ipv4 header ihl field is less than 5\n");
    return;
  }

  // Check if the TTL has expired
  if (ip_hdr->ttl == 0) {
    printf("Packet ttl has expired\n");
    return;
  }

  // Calculate the checksum
  if (checksum(ip_hdr, ip_hdr->ihl * 4) != 0) {
    printf("Invalid checksum in ipv4 packet\n");
    return;
  }

  // Rebuild fragmented packets


  // Process the packets
  switch (ip_hdr->protocol) {
    case ICMPV4:
      icmpv4_incoming(dev, hdr);
      break;
    default:
      printf("Only icmpv4 protocol is supported\n");
      break;
  }
}

/* Send an ipv4 packet */
void ipv4_transmit(struct netdev *dev, struct eth_hdr *hdr) {
  struct ipv4_hdr *iphdr = (struct ipv4_hdr *) hdr;
  uint32_t temp_addr = iphdr->saddr;
  uint8_t len = iphdr->len;

  /* Simply swap the source and destiunation addresses
   * Proper arp lookup tables will be added later
   */
  iphdr->saddr = iphdr->daddr;
  iphdr->daddr = temp_addr;

  /* Reverse the byte order for the len field */
  iphdr->len = htons(len);

  /* Get the check sum field */
  iphdr->csum = checksum(iphdr, iphdr->ihl * 4);

  /* Send the packet */
  netdev_tx(dev, hdr, ETH_P_IP, len, hdr->smac);
}

