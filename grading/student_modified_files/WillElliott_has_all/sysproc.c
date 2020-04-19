#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "processInfo.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// print "Hello"
int
sys_hello(void)
{
  cprintf("Hello\n");
  return 0;
}

// print "<user input name>"
int
sys_helloYou(void)
{
 char *n;
 if(argstr(0, &n) < 0)
    return -1;
 cprintf("%s\n", n);
 return 0;
} 

//calls func in proc.c
//returns the total number
//of active processes
int
sys_getNumProc(void)
{
  return(getNumProc());
}

//calls func in proc.c
//returns max pid
int
sys_getMaxPid(void)
{
  return(getMaxPid());
}

// calls getProcInfo in proc.c
// populates given processInfo struct with
// info from given process
int
sys_getProcInfo(void)
{
  int pid;
  struct processInfo *PI;
  if(argint(0, &pid) < 0)
    return -1;
  if(argptr(1, (void*)&PI, sizeof(*PI)) < 0)
    return -1;
  if(getProcInfo(pid, PI) == 0){
    return 0;
  }
  return -1;
}

// calls getPrio in proc.c
// returns priority of given pid
int
sys_getprio(void)
{
  return(getPrio());
}

// calls setPrio in proc.c
// sets priority of proces of 
// given PID to given priority
int
sys_setprio(void)
{
  int prio;
  if(argint(0, &prio) < 0)
    return -1;
  setPrio(prio);
  return 0;
}

// for debugging.  call procdump
int
sys_procdump(void)
{
  procdump();
  return 0;
}
