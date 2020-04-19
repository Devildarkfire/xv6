#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
  printf(1, "Number of Processes: %d\n", getNumProc());
  exit();
}
