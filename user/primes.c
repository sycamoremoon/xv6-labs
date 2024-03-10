#include "kernel/types.h"
#include "user/user.h"
#define MAXNUMBER 80
int main(int argc , const char * argv[])
{
	int pid;
	char print_num;
	char buffer_num = MAXNUMBER;
	int count;
	char buf[MAXNUMBER] = {0};
	char number;
	int pip[2];
	int pip2[2];
	for (count = 2; count < MAXNUMBER+2; count++)
		buf[count-2] = count;
	while(buffer_num > 1)
	{
		pipe(pip2);
		pipe(pip);
		if((pid = fork()) > 0)
		{
			close(pip[0]);
			close(pip2[1]);
			//printf("length of parent's buff is %d\n",buffer_num);
			if(write(pip[1],buf,buffer_num)!=buffer_num)
				fprintf(2,"write error at %d lines\n",__LINE__);
			close(pip[1]);
			//wait(0);
			read(pip2[0],&buffer_num,1);
			//printf("next get %d nums from pipe\n",buffer_num);
			read(pip2[0],buf,buffer_num);
			close(pip2[0]);				//very important to close this fd 
		}
		else if (pid == 0)
		{
			close(pip[1]);
			close(pip2[0]);
			buffer_num = 0;
			read(pip[0],&print_num,1);
			printf("prime %d\n",print_num);
			while(read(pip[0],&number,1) != 0)
			{
				//printf("read status is %d\n",status);
				//sleep(1);
				//fprintf(2,"read number as %d, at %d lines\n",number,__LINE__);
				if(((int)number % (int)print_num)!= 0)
				{
					buf[(int)(buffer_num)++] = number;
				}	
			}
			if (buffer_num == 1)
				printf("prime %d\n",number);
			close(pip[0]);
			//printf("length of child's buff is %d\n",buffer_num);
			write(pip2[1],&buffer_num,1);
			if (write(pip2[1],buf,buffer_num) != buffer_num)
				fprintf(2,"error at %d lines\n",__LINE__);
			close(pip2[1]);
			exit(0);
		}
	}
	exit(0);
}
