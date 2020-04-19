#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  int pid = getpid();
  printf(1, "%d priority is %d\n", pid, getprio());
  setprio(8);
  printf(1, "set priority to 8");
  printf(1, "%d priority is %d\n", pid, getprio());
  exit();
}
