#include "tun_if.h"

// tun file descriptor
static int tun_fd;

/*
 * Taken from Kernel Documentation/networking/tuntap.txt
 */
static int tun_alloc(char *dev) {
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tap", O_RDWR)) < 0 ) {
    perror("Cannot open TUN/TAP dev\n"
            "Make sure one exists with " 
            "'$ mknod /dev/net/tap c 10 200'");
    exit(1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
  if( *dev ) {
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }

  strcpy(dev, ifr.ifr_name);
  return fd;
}

/* Read a packet from the tap (just a file access) */
int tun_read(char *buf, int len) {
  return read(tun_fd, buf, len);
}

/* Write a packet tp the tap (just a file access) */
int tun_write(char *buf, int len) {
  return write(tun_fd, buf, len);
}

/* Initialize and bring up the tun interface */
void tun_init(char *dev) {
  // Allocate the tun file descriptor
  tun_fd = tun_alloc(dev);

  // Bring up the interface
  if (run_cmd("ip link set up dev %s", dev) != 0) {
    perror("Couldn't bring up the tun interface");
    exit(1);
  }

  if (run_cmd("ip addr add %s dev %s", IP_ADDR, dev) != 0) {
    perror("Couldn't assign ip address to tun");
    exit(1);
  };

}