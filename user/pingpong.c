#include "kernel/types.h"
#include "user/user.h"

int main(int argc , const char * argv[])
{
	int p[2];
	char buf[1];
	int pid;
	pipe(p);
	if((pid = fork())>0)
	{
		wait(0);
		read(p[0],buf,sizeof(buf));
		printf("%d: received pong\n",getpid());	
		exit(0);
	}
	else if (pid ==0)
	{
		write(p[1],buf,sizeof(buf));
		printf("%d: received ping\n",getpid());	
		exit(0);
	}
	fprintf(2,"fork failed");
	exit(1);
}
