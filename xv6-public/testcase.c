#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  printf(1, "Hello, world!\n");

  
  hello();
  
  char name = "xv6\n";
  
  helloYou(name);
  
  exit();
}
