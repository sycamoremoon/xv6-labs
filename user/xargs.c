#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXCMD 9
#define MAXNUM 8
	
void xargs( char * cmd , char * args)
{
	char * vargs[MAXNUM] = {0};
	char private_buf[MAXARG] = {0};
	char * pchar;
	//printf("before child the args is %s\n",args);
	if (fork() == 0 )		//child process
	{
		int v = 2;
		memmove(private_buf,args,MAXARG);
		vargs[0] = cmd;
		vargs[1] = pchar= private_buf;
		while((pchar = strchr(pchar,' '))!= 0 )
		{
			*pchar = 0;
			vargs[v++] = ++pchar;
		}
		vargs[v] = 0;
		//for(int i=0; i<=v;i++)
			//printf("VEC's num is %d\nthe vec[%d] is %s\n",v,i,vargs[i]);
		//printf("the cmd is %s\n",cmd);
		exec(cmd,vargs);
	}
	
	wait(0);

}
int main(int argc , const char * argv[])
{
	int i;
	char cmd[MAXCMD] = {0};
	char * begin;
	char argsbuf[MAXARG] = {0};
	char streambuf[MAXARG] = {0};
	char * p_argv , *p_stream;

	//printf("argc is %d\n",argc);
	for(i =0 ;i<argc ;i++)
	{
		//printf("argv[%d] is %s\n",i,argv[i]);
	}
	if (argc < 2)
	{
		fprintf(2,"xargs: missing argument\n");
		exit(0);
	}
	strcpy(cmd,argv[1]);
	p_stream = streambuf;
	for (i=2;i<argc;i++)
	{
		strcpy(p_stream,argv[i]);
		p_stream = p_stream + strlen(argv[i]);
		*(p_stream++)= ' ';
	}

	p_argv = argsbuf;
	int fnum;
	while ((fnum = read(0,p_argv,MAXARG)) > 0)			// read the data from standard input 
	{
		p_argv = p_argv+fnum;
	}
	//printf("read from pipe is %sthe argsbuf is %s",p_argv,argsbuf);
	begin = argsbuf;
	do{
	p_argv = strchr(begin,'\n');
	if(p_argv != 0)*p_argv = 0;
	strcpy(p_stream,begin);
	xargs(cmd,streambuf);
	begin = p_argv+1;
	}
	while((p_argv = strchr(begin,'\n')) != 0);
	exit(0);	
}
