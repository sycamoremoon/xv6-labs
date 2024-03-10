#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(const char * filename, const char * path)
{
	struct stat st;
	struct dirent de;
	int fd;
	char buf[512] = {0};			//why if I dont initalize this buf, it will go wrong
   	char * p;	
	
	//printf("for the begin the path is %s\nthe buf is %s\n",path,buf);
	if ((fd = open(path,O_RDONLY)) < 0)
	{
		fprintf(2, "find: cannot open current path\n");
		return;
	}
	
	memmove(buf,path,strlen(path));
	p = buf + strlen(buf);
	//printf("before loop the buf is %s\n",buf);
	while(read(fd,&de,sizeof(de)) == sizeof(de))
	{
		if(de.inum == 0)
			continue;
		*p = '/';					// p point to where the '/' is
		memmove(p+1,de.name,DIRSIZ);			//when it copys, the position where p point to is not change
		p[DIRSIZ] = 0;
		if (stat(buf,&st) < 0)
		{
			fprintf(2,"find: cannot stat %s \n",buf);
			continue;
		}
		switch (st.type){
		case T_DEVICE:
		case T_FILE:
			if (strcmp(de.name,filename) == 0)
			{
				char ret= '\n';
				write(1,buf,strlen(buf));
				write(1,&ret,1);
			}
			break;
		case T_DIR:
			if(strcmp(de.name,".") == 0 || strcmp(de.name,"..") == 0)
				break;
			//printf("before recsive the buf is %s ,filename is %s\n",buf ,filename);
			find(filename,buf);
			break;
		default:
			break;

		}
	}
	close(fd);
}
int main(int argc , const char * argv[])
{
	int i;
	if (argc < 2 )
	{
		fprintf(2,"Please input at least one target\n");
		exit(0);
	}
	for(i = 2;i < argc; i++)
	{
		find(argv[i],argv[1]);
	}
	exit(0);	
}
