#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#include "spinlock.h"
#include "processInfo.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

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


//system call code (new)
int
hello(void)
{
	cprintf("hello\n");
	return 0;
}

int
helloYou(char *name)
{
	argstr(0, &name);
	cprintf("%s\n",name);
	return 0;
}

int
getNumProc(void)
{

	int total = 0;

	// find total number of processes and
	// store it as integer to be printed

	struct proc *p;
	acquire(&ptable.lock);
	for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
		if(p->state > 0){
			total++;
		}
	}
	release(&ptable.lock);

	return total;
}

int
getMaxPid(void)
{
	int maxId=0;

	struct proc *p;
	acquire(&ptable.lock);
	for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
		if(p->state >= 0){
			if(p->pid > maxId){
				maxId = p->pid;
			}
		}
	}
	release(&ptable.lock);
	return maxId;
}

int
getProcInfo(int pid, struct processInfo* Info)
{
	argint(0, &pid);
	argptr(1,(void*)&Info,sizeof(Info));
	struct proc *p;
	acquire(&ptable.lock);
	for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
			if(p->pid == pid){
				Info->pid = p -> pid;
				Info->psize = p -> sz;
				Info->numberContextSwitches = p -> switchn;

				release(&ptable.lock);
				return 0;
			}
	}
	release(&ptable.lock);
	return -1;
}

int
setprio(int n)
{
	argint(0, &n);
	myproc() -> prio = n;
	return 0;
}

int
getprio(void)
{
	return myproc() -> prio;
}
