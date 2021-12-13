#include "netdev.h"

/*  */
void init_netdev(struct netdev *netdev, char *addr, char *hwaddr) {
  // Clear the contents of the netdev struct
  memset(netdev, 0, sizeof(struct netdev));

  // Construct the IP address from the addr agrument
  if (inet_pton(AF_INET, addr, &netdev->addr) != 1) {
    perror("Unable to parse IP address");
    exit(1);
  }

  // Copy the MAC address to the netdev pointer (in correct format)
  sscanf(hwaddr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &netdev->hwaddr[0],
                                                  &netdev->hwaddr[1],
                                                  &netdev->hwaddr[2],
                                                  &netdev->hwaddr[3],
                                                  &netdev->hwaddr[4],
                                                  &netdev->hwaddr[5]);

}

/* Build an send an ethernet packet  */
void netdev_tx(struct netdev *dev, struct eth_hdr *hdr,
                uint16_t ethertype, int len, unsigned char *dest) {

  // Add the packet type to the 
  // htons converts the byte order to
  hdr->ethertype = ethertype;

  // Add the source and destination MAC addresses
  // Use memcpy prevents type errors
  memcpy(hdr->smac, dev->hwaddr, 6);
  memcpy(hdr->dmac, dest, 6);

  // Update the length of the packet to be sent to include header
  len += sizeof(struct eth_hdr);

  // Write the packet to the tun
  tun_write((char *) hdr, len);
}