#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>

int currentFib(int amount)
{
	int fib1, fib2, fibNext;
	fib1 = 0;
	fib2 = 1;
	if(amount == 2 || amount == 1)
	{
		fibNext =1;
		return fibNext;
	}
	else
	{
		for(int i = 2; i < amount; i++)
		{

		fibNext = fib1 + fib2;
		fib1 = fib2;
		fib2 = fibNext;

		}
		return fibNext;
	}
}


int main()
{
	char buffer[2];
	buffer[0] = 0;
	buffer[1] = 0;
	int file=0;
	int pos=0;
	int count=0;
	if((file = open("fib.txt", O_RDONLY)) <-1) return 1;
	while(read(file,buffer,1) == 1)
	{
		pos=currentFib(count);
		if(lseek(file, pos, SEEK_SET) < 0) return 1;
		if(read(file,buffer,1) != 1) return 1;
		buffer[1] = 0;
		printf("%s",buffer);
		count++;
	}
	
	return 0;
}