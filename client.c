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
unsigned char* AskSqrt(double number);
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

	//unsigned char ch[8] = AskDate();// = "a";
	unsigned char *ch;
	ch = (unsigned char*)malloc(8*sizeof(unsigned char));
	ch = AskSqrt(40.0);
	//ch = AskDate();
	//


	//memcpy(&ch,&tosqrt,sizeof(tosqrt));
	//sprintf(ch,"%f",tosqrt);

	// printf("%s",ch);


	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (9879);
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



unsigned char* AskSqrt(double number)	{
	int j = 0;
	unsigned int i = 0001;
	unsigned	char *id ;
	unsigned char *numberToSqrt;
	unsigned char *idrq;
	unsigned char *Request;
	id = (unsigned char*)malloc(sizeof(unsigned int));
	numberToSqrt = (unsigned char*)malloc(sizeof(double));
	idrq = (unsigned char*)malloc(sizeof(unsigned int));
	Request = (unsigned char*)malloc(2*(sizeof(unsigned int)) + sizeof(double));

	numberToSqrt = ConvertDoubleTochar(number);
	id = ToBigEndian(ConvertIntToChar(i));
	idrq = GenerateIdRq();
	memcpy(Request, id, 4);
	memcpy(&Request[4], idrq, 4);
	memcpy(&Request[8], numberToSqrt, 8);

	for (j = 0; j < 16; j++) {
		printf(" %d ", Request[j]);
	}

	free(id);
	free(numberToSqrt);
	free(idrq);

	return Request;
}

unsigned char* AskDate() {
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

	free(id);
	free(rqid);

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

unsigned char* ConvertDoubleTochar(double i) {
	unsigned char *result;
	result = (unsigned char*)malloc(sizeof(double));
	memcpy(result, &i, sizeof(i));
	return result;
}

unsigned char* ToBigEndian(unsigned char* j) {

	int i = 0;
	unsigned char *result;
	result = (unsigned char*)malloc(sizeof(4));
	for(i = 0 ; i <= 3 ; i++){
		result[i] = j[3 - i];
	}
	return result;
}
