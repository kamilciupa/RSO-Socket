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

//bool IsBigEndian(char* package);
void AskSqrt(double number);
unsigned char* AskDate();
unsigned char* ConvertIntToChar(unsigned int i);
unsigned char* ToBigEndian(unsigned char* i);
unsigned char* GenerateIdRq();
unsigned char* ConvertDoubleTochar(double i) ;



int main (int agrc, char *argv[]) {
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;
	double tosqrt = 4;

	char ch[16];// = "a";

	//memcpy(&ch,&tosqrt,sizeof(tosqrt));
	//sprintf(ch,"%f",tosqrt);

	// printf("%s",ch);


	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (9878);
	len = sizeof (address);

	/*  Now connect our socket to the server's socket.  */

	result = connect (sockfd, (struct sockaddr *) &address, len);

	if (result == -1)
	{
		perror ("oops: netclient");
		exit (1);
	}

	/*  We can now read/write via sockfd.  */
	//AskSqrt(2.0);
	AskDate();
	write (sockfd, &ch, 1);
	read (sockfd, &ch, 1);
	//printf ("char from server = %s\n", ch);
	close (sockfd);
	exit (0);
}



void  AskSqrt(double number)	{

	unsigned int i = 012;
	unsigned	char *id ;
	id = (unsigned char*)malloc(i*sizeof(unsigned int));

	//id = ToBigEndian(ConvertToChar(i));
	id = GenerateIdRq();
	printf(" %d \n %d \n %d \n %d", id[0],id[1],id[2],id[3]);

}

unsigned char* AskDate() {
int j = 0;
	unsigned int i = 0002;
	unsigned	char *id ;
	unsigned char *rqid;
	unsigned char *Request;

	id = (unsigned char*)malloc(4*sizeof(unsigned char));
	rqid = (unsigned char*)malloc(4*sizeof(unsigned char));
	Request = (unsigned char*)malloc(sizeof(id)+sizeof(rqid));
	id = ToBigEndian(ConvertIntToChar(i));
	rqid = GenerateIdRq();
	memcpy(Request, id, 4);
	memcpy(&Request[4], rqid, 4);

	for(j = 0 ; j < 8 ; j++){
		printf(" %d ", Request[j]);
	}

	return Request;
}

unsigned char* GenerateIdRq() {

	srand(time(NULL));
	unsigned int id = rand() % 999999;
	unsigned char *result;
	result = (unsigned char*)malloc(4);
	result = ToBigEndian(ConvertIntToChar(id));
	return result;
}

unsigned char* ConvertIntToChar(unsigned int i) {

	unsigned char *result;
	result = (unsigned char*)malloc(4);
	result[0] = i & 0x000000ff;
	result[1] = (i & 0x0000ff00) >> 8;
	result[2] = (i & 0x00ff0000) >> 16;
	result[3] = (i & 0xff000000) >> 24;
	return result;
}
/*
unsigned char* ConvertDoubleTochar(double i) {
	result = (unsigned char*)malloc(i*sizeof(double));
	result[0] = i & 0x00000000000000ff;
	result[1] = (i & 0x000000f0) >> 8;
	result[2] = (i & 0x00000f00) >> 16;
	result[3] = (i & 0x0000f000) >> 24;
	result[4] = (i & 0x000f0000) >> 32;
	result[5] = (i & 0x00f00000) >> 40;
	result[6] = (i & 0x0f000000) >> 48;
	result[7] = (i & 0xf0000000) >> 56;
	return result;

}*/

unsigned char* ToBigEndian(unsigned char* i) {

	unsigned char *result;
	result = (unsigned char*)malloc(4);
	result[0] = i[3];
	result[1] = i[2];
	result[2] = i[1];
	result[3] = i[0];
	return result;

}
