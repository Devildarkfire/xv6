#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "processInfo.h"

int main(void)
{
  int pid = 1;
  struct processInfo * PI = (struct processInfo*) malloc(sizeof(struct processInfo));
  getProcInfo(pid, PI);
  printf(1, "PID: %d\n", PI->pid);
  printf(1, "Process size: %d bytes\n", PI->psize);
  printf(1, "Number of context switches: %d\n", PI->numberContextSwitches);

  pid = 2;
  getProcInfo(pid, PI);
  printf(1, "PID: %d\n", PI->pid);
  printf(1, "Process size: %d bytes\n", PI->psize);
  printf(1, "Number of context switches: %d\n", PI->numberContextSwitches);

  pid = getpid();
  getProcInfo(pid, PI);
  printf(1, "PID: %d\n", PI->pid);
  printf(1, "Process size: %d bytes\n", PI->psize);
  printf(1, "Number of context switches: %d\n", PI->numberContextSwitches);
  free(PI);
  exit();
}
