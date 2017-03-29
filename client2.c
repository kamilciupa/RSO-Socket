#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void pInt(char* buf, int val, int offset);
void pDouble(char* buf, double val, int offset);
int uInt(char* buf, int offset);
double uDouble(char* buf, int offset);
void makeSqrt(char* buf, double val);
void makeTime(char* buf);
int isBigEndian();
void changeEndianess(char* buf, int size);

int main (int agrc, char *argv[]) {
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result; int choice = 0;
	int id ; int rqid ; double val = 0;

	char *ch;


	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (atoi(argv[1]));
	len = sizeof (address);

	/*  Now connect our socket to the server's socket.  */

	result = connect (sockfd, (struct sockaddr *) &address, len);
		if (result == -1)
		{
			perror ("oops: netclient");
			exit (1);
		}
	/*  We can now read/write via sockfd.  */
	printf("Which operation \n 1 - Square Root \n 2 - Time \n");
	scanf("%d", &choice);

	if(choice == 1) {
	ch = malloc((2*sizeof(int)+sizeof(double)));
	printf("Type number to square\n");
	scanf("%lg", &val);
	makeSqrt(ch, val);
//	makeTime(ch);

	if(write (sockfd, ch, 16) == -1) {
    perror ("oops: fail write");
    exit (1);
  }
	read (sockfd, ch, 16);

	id = uInt(ch, 0);
	rqid = uInt(ch,sizeof(int));
	val = uDouble(ch, sizeof(double));
	printf("\n %d \n", rqid);
	printf(" %f \n", val);
} else if (choice == 2) {
		ch = malloc(2*sizeof(int));
		makeTime(ch);
		write(sockfd, ch, 8);
		read(sockfd, ch, 12);
		printf("%d\n", uInt(ch,sizeof(int)) );
		printf("%d\n", uInt(ch, sizeof(int)*2));
}

	close (sockfd);
	exit (0);
}

void pInt(char* buf, int val, int offset) {

	int i = 0;
		for(i = 0 ; i < sizeof(int) ; i++){
			buf[i+offset] = ((char*)&val)[i];
		}
}

void pDouble(char* buf, double val, int offset) {

	int i = 0;
		for(i = 0 ; i < sizeof(double) ; i++){
			buf[i+offset] = ((char*)&val)[i];
		}
}

int uInt(char* buf, int offset) {

	int i = 0; int res = 0;
	for(i = 0 ; i < sizeof(int) ; i++){
		((char*)&res)[i] = buf[i+offset];
		}
		return res;
}


double uDouble(char* buf, int offset) {

	int i = 0; double res = 0;
	for(i = 0 ; i < sizeof(double) ; i++){
		((char*)&res)[i] = buf[i+offset];
		}
		return res;
}

void makeSqrt(char* buf, double val) {

		srand(time(NULL));
		int id = 1;
		int rqid = rand () % 2000;
		pInt(buf, id, 0);
		pInt(buf, rqid, sizeof(int));
		pDouble(buf, val, 2*sizeof(int));
		//changeEndianess(buf, 16);
}

void makeTime(char* buf) {

	srand(time(NULL));
	int id = 2;
	int rqid = rand () % 2000;
	pInt(buf, id, 0);
	pInt(buf, rqid, sizeof(int));
//	changeEndianess(buf, 8);
}

int isBigEndian() {

	int i = 1;
	char buf[sizeof(int)];
	char *bufptr;
	bufptr = buf;
	pInt(bufptr, i, 0);
	if((int)(((char*)&buf)[0]) == 1)
			//printf("Little\n");
			return 0;
		else
			//printf("Big\n");
			return 1;
}

void changeEndianess(char* buf, int size) {

		int i = 0;
		char tmp;

		for(i = 0 ; i < size ; i++){
			tmp = buf[i];
			buf[i] = buf[size] ;
			buf[size] = tmp;
		}

}
