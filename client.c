/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


void pac(char* buf, int val, int offset);
int unpac(char* buf, int offset);



int main (int agrc, char *argv[]) {
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;
	double tosqrt = 4;

char* ch;
	ch = (char*)malloc(sizeof(int));

	pac(ch, 5, 0);
	result = unpac(ch, 0);
	printf("\n %d \n" , result);

	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (9877);
	len = sizeof (address);

	/*  Now connect our socket to the server's socket.  */

	result = connect (sockfd, (struct sockaddr *) &address, len);
		if (result == -1)
		{
			perror ("oops: netclient");
			exit (1);
		}
	/*  We can now read/write via sockfd.  */
	write (sockfd, &ch, 16);
	//read (sockfd, &ch, 1);
	//printf ("char from server = %s\n", ch);
	close (sockfd);
	exit (0);
}



void pac(char *buf, int val, int offset) {

	int i = 0;
	int s = sizeof(val);	
	for(i = 0 ; i < s ; i++) {
		buf[i+offset] = ((char*)&val)[i];	
	}
	
}

int unpac(char *buf, int offset) {
	
	int i = 0 ; int j = 0 ;
	int s = sizeof(j);
	for( i = 0 ; i < s ; i++ ) {
		((char*)&j)[i] = buf[i+offset];
	}
	return j;
}

