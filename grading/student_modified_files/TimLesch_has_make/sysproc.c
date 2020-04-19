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

//Prints hello
int sys_hello(void)
{
//	hello();
	cprintf("Hello\n");
	return 1;
}

//Prints name
int sys_helloYou(void)
{
	char *name;
	argstr(0, &name);
//	cprintf("%s\n", name);
	helloYou(name);
	return 0;
}

//gets total num of processes 
//getNumProc() is located in proc.c
int sys_getNumProc(void)
{
	return getNumProc();	
	
}

//gets highest PID among processes
//getMaxPid is located in proc.c
int sys_getMaxPid(void)
{
	return getMaxPid();
	
}

//returns infor about process
//num of context switches, size, and PID
//getProcInfo is located in proc.c
int sys_getProcInfo(void)
{
	int pid;
	argint(0, &pid);
	struct processInfo *ptr;
	//char *ptr;
	argptr(1,(void*)&ptr, sizeof(int)*3);
	cprintf("%p sys\n", ptr);
	return getProcInfo(pid, (struct processInfo*) ptr);
	
}

int sys_getInt(void)
{
	int val;
	argint(0, &val);
	//cprintf("%d\n", val);
	getInt(val);
	return 0;
}

int sys_setprio(void)
{
	int prio;
	argint(0, &prio);
	return setprio(prio);
}

int sys_getprio(void)
{
//	int prio;
//	prio = myproc()->priority;
	//cprintf("%d\n", prio);
	return getprio();
	
}
