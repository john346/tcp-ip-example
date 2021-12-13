#include "arp.h"

static struct arp_cache_entry arp_cache[ARP_CACHE_LEN];

/* Insert a new table entry into the next free slot */
static int insert_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data) {
  struct arp_cache_entry *entry;

  // Loop over the table until a free entry is found
  for (int i=0; i < ARP_CACHE_LEN; i++) {
    entry = &arp_cache[i];

    if (entry->state == ARP_FREE) {
      // Update the state to show it is 
      entry->state = ARP_RESOLVED;

      // Copy the relevant fields into the table
      entry->hwtype = hdr->hwtype;
      entry->sip = data->sip;
      memcpy(entry->smac, data->dmac, 6);

      return 0;
    }
  }

  // If we get here then something has gone wrong
  return -1;
}

/* Update an the MAC address of an entry in the translation table */
static int update_translation_table(struct arp_hdr *hdr, struct arp_ipv4 *data) {
  struct arp_cache_entry *entry;

  // Loop over the table until the entry is found, then update it
  for (int i=0; i < ARP_CACHE_LEN; i++) {
    entry = &arp_cache[i];

    if (entry->hwtype == hdr->hwtype && entry->sip == data->sip) {
      memcpy(entry->smac, data->smac, 6);
      return 1;
    }
  }

  // Couldn't find this entry in the table
  return 0;
}

/* Initialise the cahce memory to nulls */
void arp_init() {
  memset(arp_cache, 0, ARP_CACHE_LEN * sizeof(struct arp_cache_entry));
}

/* Handle incoming ARP packets */
void arp_incoming(struct netdev *netdev, struct eth_hdr *hdr) {
  struct arp_hdr *arphdr;
  struct arp_ipv4 *arpipv4;

  // Extract the ARP data from the ethernet payload
  arphdr = (struct arp_hdr *) hdr->payload;

  if (arphdr->hwtype != ARP_ETHERNET) {
    // We only allow ethernet based pacets
    printf("Only ethernet hardware connections are supported\n");
    return;
  }

  if (arphdr->protype != ARP_IPV4) {
    // We only talk over ipv4 protocol
    printf("Only ipv4 protocol is supported\n");
    return;
  }

  // Extract the ipv4 data from the arp packet
  arpipv4 = (struct arp_ipv4 *) arphdr->data;

  // Smash the data into the table
  update_translation_table(arphdr, arpipv4);

  // Report if we are the intended destination or not
  if (netdev->addr != arpipv4->dip) {
    printf("This packet is not for us\n");
  }

  // Insert the entry into the cache
  insert_translation_table(arphdr, arpipv4);

  // Handle the ARP opcode (only requests at the moment)
  switch (arphdr->opcode) {
    case ARP_REQUEST:
      arp_reply(netdev, hdr, arphdr);
      break;
    default:
      printf("Opcode not supported\n");
      break;
  }

}

/* Reply to an arp request */
void arp_reply(struct netdev *dev, struct eth_hdr *hdr, struct arp_hdr *arp) {
  struct arp_ipv4 * arp_ip4_hdr;
  int len;

  // Cast the contents to the c
  arp_ip4_hdr = (struct arp_ipv4 *) arp->data;

  // Add the source and destination addresses to the reply
  memcpy(arp_ip4_hdr->dmac, arp_ip4_hdr->smac, 6);
  arp_ip4_hdr->dip = arp_ip4_hdr->sip;
  memcpy(arp_ip4_hdr->smac, dev->hwaddr, 6);
  arp_ip4_hdr->sip = dev->addr;

  // Reply type packet
  arp->opcode = ARP_REPLY;

  // Correct the byte order to account for the network byte order
  arp->opcode = htons(arp->opcode);
  arp->hwtype = htons(arp->hwtype);
  arp->protype = htons(arp->protype);

  // Send the reply packet
  len = sizeof(struct arp_hdr) + sizeof(struct arp_ipv4);
  netdev_tx(dev, hdr, ETH_P_ARP, len, arp_ip4_hdr->dmac);
}