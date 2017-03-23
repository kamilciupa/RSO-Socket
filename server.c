#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int main() {
  
  int server_sock, client_sock;
  socklen_t server_len, client_len;
  struct sockaddr_in server_address;
   struct sockaddr_in client_address;

  //config
  server_sock = socket( AF_INET, SOCK_STREAM, 0);
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl (INADDR_ANY);
  server_address.sin_port = htons (9879);
  server_len = sizeof(server_address);
  
  //bind
  bind (server_sock, (struct sockaddr *) &server_address, server_len);
  
  //listen
  
  listen(server_sock, 5);
  
  while(1) {
    
    char ch[16];
  printf ("server waiting\n");    
    //accept
    
    client_len = sizeof (client_address);
    client_sock = accept (server_sock, (struct sockaddr *) &client_address, &client_len);
    
    
		read (client_sock, &ch, 1);
		printf("rozmiar%lu\n", sizeof(ch));
		printf("\n %s \n", ch);
		double a = *ch;
		printf("%f", a);
		//sqrt((double) a);
		write (client_sock, &ch, 1);
		close (client_sock);
  }
}