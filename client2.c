#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

char* AskSqrt(double number);
char* ToBigEndian(char* buf, int i);

int main (int agrc, char *argv[]) {
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;

	//unsigned char ch[8] = AskDate();// = "a";
	char *ch;
	ch = (char*)malloc(16);
	ch = AskSqrt(40.0);
	//ch = AskDate();
	//memcpy(&ch,&tosqrt,sizeof(tosqrt));
	//sprintf(ch,"%f",tosqrt);
	// printf("%s",ch);
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

	if(write (sockfd, &ch, 16) == -1) {
    perror ("oops: fail write");
    exit (1);
  }

	//read (sockfd, &ch, 1);
	//printf ("char from server = %s\n", ch);
	close (sockfd);
	exit (0);
}


char* AskSqrt(double number) {

    srand(time(NULL));
    int j = 0;
//  char buf[16];
  char* buf;
  buf = (char*)malloc((2*sizeof(int))+sizeof(double));
  // char id[4];
  char* id;
  id = (char*)malloc(sizeof(int));
  //char rqid[4];
  char* rqid;
  rqid = (char*)malloc(sizeof(int));
//  char numb[8];
  char* numb;
  numb = (char*)malloc(sizeof(double));
  int i = 0001;
  int rq = rand() % 2564;

  snprintf(id, sizeof(id), "%d", i);
  snprintf(rqid, sizeof(rqid), "%d", rq);
  snprintf(numb, sizeof(numb), "%f", number);


  memcpy(buf, numb, 8);
  memcpy(&buf[8], rqid, 4);
  memcpy(&buf[11],id, 4);

  buf = ToBigEndian(buf, 16);
  for(j = 0 ; j <= 15 ; j++) {
    printf(" %d ", buf[j]);
  }


  return buf;

}

char* ToBigEndian(char* buf, int i) {
  int j = 0 ;
  char* tmp;
  tmp = (char*)malloc(i);
  for(j = 0 ; j <= i ; j++ ){
    tmp[j] = buf[i-j];
  }

  return tmp;
}
