#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  printf(1, "Hello, world!\n");

  
  hello();
  
  helloYou("xv6 lab\n");
  
  printf(1, "%d\n", getNumProc());
  
  printf(1, "%d\n", getMaxPid());
  
  exit();
}
