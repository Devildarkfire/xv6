#include "types.h" 
#include "stat.h" 
#include "user.h" 
#include "fcntl.h"
int main(int argc, char *args[]) {
	int prio = atoi(args[1]);
	setprio(prio);
	exit();
}
