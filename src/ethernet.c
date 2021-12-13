#include "ethernet.h"

/* Initalise an ethernet header struct  */
struct eth_hdr* init_eth_hdr(char *buf) {
  // Cast the buf string to an ethernet head
  struct eth_hdr *hdr = (struct eth_hdr *) buf;

  // Convert the byte order of the ethertype identifier
  hdr->ethertype = htons(hdr->ethertype);

  return hdr;
}