#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *args[])
{
	char* name = args[1];
	//cprintf("%s\n", name);
	helloYou(name);
//	int i = 0;
//	for(i = 1; i < argc; i++)
//	{
	//	printf(1, "%s%s", args[i], i+1 < argc ? " " : "\n");
//		sprintf(name, "%s%s%s", name, i+1 < argc ? " " : "\n", args[i]);
//	}
//	helloYou(name);
	exit();
}

