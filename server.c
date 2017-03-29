#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//KONPIJLUJ Z -lm
void pInt(char* buf, int val, int offset);
void pDouble(char* buf, double val, int offset);
int uInt(char* buf, int offset);
double uDouble(char* buf, int offset);
void makeSqrt(char* buf, int rqid, double val);
void makeTime(char* buf, int rqid);
void changeEndianess(char* buf, int size);

int main(int agrc, char *argv[]) {

  int i; int id ; int rqid; double val;
  int server_sock, client_sock;
  socklen_t server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  //config
  server_sock = socket( AF_INET, SOCK_STREAM, 0);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl (INADDR_ANY);
  server_address.sin_port = htons (atoi(argv[1]));
  server_len = sizeof(server_address);
  //bind
  bind (server_sock, (struct sockaddr *) &server_address, server_len);
  //listen
  listen(server_sock, 5);

  char *ch;
  ch = (char*)malloc((2*sizeof(int))+sizeof(double));

  while(1) {
    printf ("\nserver waiting\n");
    //accept
    client_len = sizeof (client_address);
    client_sock = accept (server_sock, (struct sockaddr *) &client_address, &client_len);
    //read

    read (client_sock, ch, ((2*sizeof(int))+sizeof(double)));
    //changeEndianess(ch, ((2*sizeof(int))+sizeof(double)));
    id = uInt(ch, 0);
    rqid = uInt(ch,sizeof(int));
    if(id == 1) {
      val = uDouble(ch, sizeof(int)*2);
      printf(" %f ", val);
      makeSqrt(ch, rqid, val);
      write (client_sock, ch,  ((2*sizeof(int))+sizeof(double)) );
    } else if(id == 2) {
      makeTime(ch, rqid);
      write (client_sock, ch,  ((3*sizeof(int))));
    }



		close (client_sock);
  }
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

void makeSqrt(char* buf, int rqid, double val) {

    int id = 1001;
    val = sqrt(val);
    pInt(buf, id, 0);
    pInt(buf, rqid, sizeof(int));
    pDouble(buf, val, 2*sizeof(int));
}

void makeTime(char* buf, int rqid) {

  int id = 1002;
  int tim = time(NULL);
  pInt(buf, id, 0);
  pInt(buf, rqid, sizeof(int));
  pInt(buf, tim, 2*sizeof(int));

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
