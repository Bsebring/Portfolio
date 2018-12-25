#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
int main()
{
	char buffer[1];
	int file=0;
	int pos=4;
	if((file = open("test.txt", O_RDONLY)) <-1) return 1;
	while(read(file,buffer,1) == 1)
	{
		if(lseek(file, pos, SEEK_SET) < 0) return 1;
		if(read(file,buffer,1) != 1) return 1;
		printf("%s\n",buffer);
		pos+=5;
	}
	
	return 0;
}
