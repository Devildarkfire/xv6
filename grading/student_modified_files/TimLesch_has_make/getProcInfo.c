#include "types.h"
#include "stat.h" 
#include "user.h" 
#include "fcntl.h"


int main(int argc, char *args[]) {
//	struct processInfo p = *(struct processInfo*)args[2];
	struct processInfo *ptr = (void*)args[2];
	//(&p) = (void*)args[2];
	//int pid;
	//int i = 0;
	//p = (void*) args[2];
	//pid = args[1];
	ptr-> psize = 10;
	ptr-> pid = 20;
	ptr-> numberContextSwitches = 30;
	int pid = atoi(args[1]);
	int check = getProcInfo(pid, ptr);
	printf(1, "pointer c  %p \n", ptr);
	if(check == -1)
		printf(1, "Invaid pid");
	else
		printf(1, "Pid %d\nSize in Bytes %d\nContext Switches %d\n", ptr->pid, ptr->psize, ptr->numberContextSwitches);

	ptr-> psize = 40;
        ptr-> pid = 50;
        ptr-> numberContextSwitches = 60;
//	printf(1, "Pid %d\nSize in Bytes %d\nContext Switches %d\n", ptr->pid, ptr->psize, ptr->numberContextSwitches);


	exit();
}
