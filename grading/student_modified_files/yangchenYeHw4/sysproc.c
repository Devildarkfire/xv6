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
  int r = fork();
  return r;
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
  int r = wait();
  return r;
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  int result = kill(pid);
  return result;
}

int
sys_getpid(void)
{
  int pid = myproc()->pid;
  return pid;
}

/**
 * Implement lazy allocation
 * sys_sbrk will only increment the
 * process's size, return the old size
 * but not allocate any memory
 * TODO: remember: this version
 * DOES NOT WORK on instcuctor's machine
 * change everything back before submitting!!!!!!
 * New change: only do lazy implementation if 
 * the process is asking for more memory.
 * If it is freeing memory, free it right away
 */
int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  //new version
  /*if (n < 0)
  {
      if (growproc(n) < 0) return -1;
  } else  myproc()->sz += n;*/
  if (growproc(n) < 0)
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

int
sys_hello(void)
{
    return hello();
}

int
sys_helloYou(void)
{
    char *name;
    if (argstr(0, &name) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }
    return helloYou(name);
}

int
sys_halt(void)
{
    return halt();
}

int
sys_getNumProc(void)
{
    return getNumProc();
}


int
sys_getMaxPid(void)
{
    return getMaxPid();
}

int
sys_getProcInfo(void)
{
    int pid;
    char *pinfo;
    //fetch argument
    if (argint(0, &pid) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }
    if (argptr(1, &pinfo, sizeof (struct processInfo)) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }
    return getProcInfo(pid, (struct processInfo *)pinfo);
}

int
sys_setprio(void)
{
    int p;
    if (argint(0, &p) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }
    return setprio(p);
}

int
sys_getprio(void)
{
    return getprio();
}

/*TODO: comment out before submitting!*/
/*int
sys_alarm(void)
{
    int ticks;
    void (*handler)();

    if (argint(0, &ticks) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }
    if (argptr(1, (char **)&handler, 1) == -1)
    {
        cprintf("Argument Error\n");
        return -1;
    }

    myproc()->ticks = ticks;
    myproc()->handler = handler;

    cprintf("%d, %d, %d\n", myproc()->ticks, myproc()->cticks, (int)myproc()->handler);
    return 0;
}*/
