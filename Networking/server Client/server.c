/* A simple server in the internet domain using TCP The port number is passed as an argument */ 
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

 
void error(const char *msg) 
{ 
perror(msg);
 exit(1); 
} 

struct parameter
{
	int socket, threadno;
};

void *run(void *parameters)
{
	int n;
	FILE *file;
	char line[64];
	char *user;
	char *pass;
	char *name;
	char buffer[9]; 
	char buffer2[11];
	struct parameter *param = parameters;
	int newsockfd = param->socket;
	int thredno = param->threadno;
	
	
	file = fopen ("passwd.txt", "rt");  
	if(file == NULL) 
	{
		error("Error opening file");
	}
	
	const char delimeter[2]= " ";
	const char delimeter2[2] = ",";
	


	bzero(buffer,sizeof(buffer));
	n = read(newsockfd,buffer,sizeof(buffer));
	if (n < 0) error("ERROR reading from socket");
	
	bzero(buffer2,256);
	n = read(newsockfd,buffer2,sizeof(buffer));

	int logon = 0;
	int validUsername = 0;
	int i;
	int lineNo = 0;
		while(!validUsername && (fgets(line, sizeof(line), file) != NULL)) {
			user = strtok(line, delimeter);
		
			while(buffer[i] != '\n') {

				if(buffer[i] != user[i]) {
					validUsername = 0;
					break;
				} else {
					validUsername = 1;
				}

				i++;
			}
			lineNo++;
		}
	rewind(file);
	int validPass = 0, j = 0;

	if(validUsername) { //if valid, grab the password from the file
		for (j = 0; j < lineNo; j++)
			fgets(line, sizeof(line), file);

		pass = strtok(line, delimeter);
		pass = strtok(NULL, delimeter);
		name = strtok(NULL, delimeter);
		i = 0;
		while(buffer2[i] != '\n') {

				if(buffer2[i] != pass[i]) {
					validPass = 0;
					break;
				} else {
					validPass = 1;
				}

				i++;
			}
	} 
	
	if(validUsername && validPass)
	{
		n = write(newsockfd,"Welcome to CPSC445-Comp Networking class",40); 
		n = write(newsockfd,"You are invited to use Your Own Machine",39);
	}
	else
	{
		n = write(newsockfd,"Only for ESU CPSC Students taking CPSC445",41);
		n = write(newsockfd,"You are not invited yet",23);
	}


 if (newsockfd < 0) 
	error("ERROR on accept"); 
	
	bzero(buffer,256); 
	//n = read(newsockfd,buffer,255); 
	if (n < 0)
		error("ERROR reading from socket"); 
	
	if (n < 0) 
	error("ERROR writing to socket"); 
	return 0;
	
}


int main(int argc, char *argv[]) { 
	
	int sockfd, newsockfd, portno; 
	socklen_t clilen; 
	int threadno = 1;
	
	struct sockaddr_in serv_addr, cli_addr;
	int n; 
	if (argc < 2) 
	{ 
		fprintf(stderr,"ERROR, no port provided\n"); 
		exit(1); 
	} 
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd < 0)
		error("ERROR opening socket"); 
	 
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	portno = atoi(argv[1]);
	 
	serv_addr.sin_family = AF_INET;  
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	 
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	 
	listen(sockfd,5);
	// place code in method for threading below here
	clilen = sizeof(cli_addr);
	
	
	while((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)))
	{
		pthread_t tid;
		
		
		struct parameter *parameters;
		(*parameters).socket = newsockfd;
		(*parameters).threadno = threadno;
		threadno++;
		
		if(pthread_create(&tid, NULL, run, parameters) < 0)
		{
			perror("Failed to create thread");
			return 1;
		}
	}
	pthread_exit(0);
	if(newsockfd < 0)
	{
		perror("Connection lost to client");
	}
	close(newsockfd); 
	close(sockfd); 
	return 0; 
} 
