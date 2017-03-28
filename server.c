#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

  int i;
  int server_sock, client_sock;
  socklen_t server_len, client_len;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  //config
  server_sock = socket( AF_INET, SOCK_STREAM, 0);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl (INADDR_ANY);
  server_address.sin_port = htons (9877);
  server_len = sizeof(server_address);
  //bind
  bind (server_sock, (struct sockaddr *) &server_address, server_len);
  //listen
  listen(server_sock, 5);

  char *ch;
  ch = (char*)malloc(sizeof(16));

  while(1) {
    printf ("\nserver waiting\n");
    //accept
    client_len = sizeof (client_address);
    client_sock = accept (server_sock, (struct sockaddr *) &client_address, &client_len);
    //read
		int how = read (client_sock, ch, 16);
    printf("\n");
		for(i = 0 ; i <= 15 ; i++){
      printf(" %d " , ch[i]);
    }

		//write (client_sock, &ch, 1);
		close (client_sock);
  }
}
