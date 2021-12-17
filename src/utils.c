#include "utils.h"

/*  
* Taken from:
* https://www.cplusplus.com/reference/cstdio/vsnprintf/
*/
int run_cmd(const char * cmd, ... ) {
  char buffer[256];
  va_list args;
  va_start(args, cmd);
  vsnprintf(buffer, 256, cmd, args);
  va_end(args);

  return system(buffer);
}

/* Calcaulte the checksum for an ip header */
uint16_t checksum(void *addr, int count) {
  uint32_t sum = 0;
  uint16_t * ptr = addr;

  while (count > 1) {
    /* Inner loop */
    sum += * ptr++;
    count -= 2;
  }

  /* Add the remaing byte if required */
  if (count > 0) {
    sum += * (uint8_t *) ptr;
  }

  /* Fold the 32 bits into 16 bits */
  while (sum >> 16) {
    sum = (sum & 0xffff) + (sum >> 16);
  }

  // Return the one's complement of the sum
  return ~sum;
}

/* Used to print the contents of an ethernet frame */
void print_hexdump(char *str, int len) {
  printf("Printing hexdump:");
  for (int i = 0; i < len; i ++) {
    if (i % 8 == 0) printf("\n");
    printf("%02x ", (unsigned char)str[i]);
  }
  printf("\n");
}