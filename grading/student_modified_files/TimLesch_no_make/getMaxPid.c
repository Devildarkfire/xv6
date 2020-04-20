#include "types.h" 
#include "stat.h" 
#include "user.h" 
#include "fcntl.h"

int main(int argc, char *args[]) {
	printf(1, "%d\n", getMaxPid());
	exit();
}
