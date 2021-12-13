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