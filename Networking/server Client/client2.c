#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>


int getch (void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &newattr);

	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldattr);
	return ch;


}




void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{

	int sockfd, portnumber, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[20];
	char buffer2[11];
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portnumber = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd <  0)
		error("ERROR opening socket");
		
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char*) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portnumber);
	
	
	if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		error("ERROR connecting \n Only for ESU CPSC Students taking CPSC445 \n You are not yet invited yet");
	}
	
	printf("Welcome to Computer Science Department\n\n\n");
	printf("Username: ");
	bzero(buffer,20);
	fgets(buffer,12,stdin);
	n = write(sockfd,buffer,8);
	
	
	printf("Password: ");
	bzero(buffer2,11);
	int k = 0;
	while( k<=9)
	{
	
	if(buffer2[k] == 13)
		{
			break;
		}
		else
		{
			buffer2[k] = getch();
			printf("*");
		}
		k++;
	}
	//fgets(buffer2,10,stdin);
	n = write(sockfd,buffer2,sizeof(buffer2));
		
	//printf("Enter message:");
	n = write(sockfd,buffer,sizeof(buffer));
	if (n < 0)
		error("ERROR writing to socket");
	bzero(buffer,sizeof(buffer));
	
	n = read(sockfd,buffer,sizeof(buffer));
	printf("%s\n",buffer);
	if (n < 0)
		error("ERROR reading from socket");
	n = read(sockfd,buffer,255);
	printf("%s\n",buffer);
	//printf("%s\n",buffer);
	return 0;
}

