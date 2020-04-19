#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "processInfo.h"

int main(void)
{
  printf(1, "Test:\n");
  hello();
  printf(1, "\n");
  char *str = "HelloYou";
  helloYou(str);
  printf(1, "\n");
  int n = getNumProc();
  printf(1, "The number of process is %d.\n", n);
  int pid = getMaxPid();
  printf(1, "The max pid is %d. \n", pid);
  if(pid>0){
    struct processInfo pi;
    getProcInfo(1, &pi);
    printf(1, "The number of context switch is %d. \n", pi.numberContextSwitches);
  }
  setprio(5);
  printf(1, "Current prio is %d. \n", getprio());
  exit();
}
