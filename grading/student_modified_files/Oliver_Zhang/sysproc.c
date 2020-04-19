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

// NEW
// print Hello
int
sys_hello(void)
{
  cprintf("Hello\n");
  return 0;
}

// print name specified by user program
int
sys_helloyou(void)
{
  char* name;
  if (argstr(0, &name) < 0)
    return -1;
  cprintf("%s\n", name);
  return 0;
}

// return number of active processes
int
sys_getnumproc(void)
{
  return getNumProc();
}

// return the max active pid
int
sys_getmaxpid(void)
{
  return getMaxPid();
}

// return 0 and print the fields of processInfo
// return -1 if PID is not present
// check sys_open() in sysfile.c for taking multiple args
// check sys_fstat() for using argptr()
int
sys_getprocinfo(void)
{
  int pid;
  struct processInfo *procInfo;

  if (argint(0, &pid) < 0 || 
      argptr(1, (void*)&procInfo, sizeof(struct processInfo)) < 0){
    return -1;
  }
  return getProcInfo(pid, procInfo);
}

// set the priority of the process
// input should be a positive integer as priority
int
sys_setprio(void)
{
  int prio;
  if (argint(0, &prio) < 0)
  {
    return -1;
  }
  myproc()->priority = prio;
  return 0;
}

// get the priority of the process
int
sys_getprio(void)
{
  return myproc()->priority;
}