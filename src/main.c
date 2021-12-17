/* System Headers */
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>

/* Application headers */
#include "arp.h"
#include "netdev.h"
#include "ethernet.h"
#include "ipv4.h"
#include "utils.h"

#define BUFLEN 100

/* Add IP address and MAC address here */
#define IP_ADDRESS "10.0.0.4"
#define MAC_ADDRESS "xxx"

/* Handle different ethernet packets as they are received */
void handle_frame(struct netdev *dev, struct eth_hdr *hdr) {
  switch (hdr->ethertype) {
    case ETH_P_ARP:
      arp_incoming(dev, hdr);
      break;
    case ETH_P_IP:
      ipv4_incoming(dev, hdr);
      break;
    default :
      printf("Unsupported packet type : 0x%x\n", hdr->ethertype);
      break;
  };
}

int main (int argc, char** argv) {
  char buf[BUFLEN];
  char *dev = calloc(10, 1);
  struct netdev netdev;

  memset(buf, 0, sizeof(buf));

  // Initialise the netdev, tun and arp modules
  init_netdev(&netdev, IP_ADDRESS, MAC_ADDRESS);
  tun_init(dev);
  arp_init();

  while (1) {
    // Read packet from the tun interface as they are received
    if (tun_read(buf, BUFLEN) < 0) {
      perror("Error reading from tun\n");
    } 

    // Create an ethernet header struct from the buffer
    struct eth_hdr *hdr = init_eth_hdr(buf);

    print_hexdump(buf, BUFLEN);

    // Handle the frame
    handle_frame(&netdev, hdr);
  }

}