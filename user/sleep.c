#include "kernel/types.h"
#include "user/user.h"

int 
main (int argc, char const * argv[])
{
	if(argc > 2)
	{
		fprintf(2,"error of using sleep function");
		exit(1);
	}
	else if(argc == 2)
	{
		sleep(atoi(argv[1]));
	}
	else
		sleep(1);
	exit(0);

}

