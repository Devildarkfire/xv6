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

// This method prints hello
int sys_hello(void){
  cprintf("Hello\n");
  return 0;
}

// This method prints the given name on the console.
int sys_helloYou(void){
  char *name;
  if(argstr(0, &name) < 0)
    return -1;
  cprintf("%s\n", name);
  return 0;
}

// This method returns the number of processes in the process table.
int sys_getNumProc(void){
  return getProcNum();

int sys_getMaxPid(void){
  return getProcMax();
}

// This method returns information about the given process.
int sys_getProcInfo(void){
  int pid;
  struct processInfo *procInfo;
  if(argint(0, &pid) < 0)
    return -1;
  if(argptr(1, (void*)&procInfo, sizeof(*procInfo))  < 0)
    return -1;
  int status = getProcessInfo(pid, procInfo);
  return status;
}
// This method sets the priority of the current process.
int sys_setprio(void){
  int priority;
  if(argint(0, &priority) < 0)
    return -1;
  myproc()->priority = priority;
  return 0;
}

// This method gets the priority of the current process.
int sys_getprio(void){
  return myproc()->priority;
}
