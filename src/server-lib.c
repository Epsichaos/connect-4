/*! 
*\file server-lib.c
*\brief Corps des fonctions relatives au serveur
*\details Contient l'ensemble du corps des fonctions relatives aux actions du serveur
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server-lib.h"

#define error(args...) do { fprintf(stderr, args); exit(1); } while(0);

struct _server_connection {
  int socket_desc;
  int new_socket;
};

/*!
*\details Fonction d'ouverture de connexion du serveur
*\param port paramètre de type \a int , qui est le numéro du port que l'on ouvre pour le client
*\return renvoit un objet de type \a server_connection, alias d'une struct définie dans struct.h représentant la connexion ouverte du serveur
*/
server_connection server_open_connection(int port){
  int socket_desc;
  int new_socket;
  unsigned int addrlen;
  struct sockaddr_in address;
  server_connection sc;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_desc == 0)
    error("Error: failed to create socket\n");

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  address.sin_port = htons(port);
  if(bind(socket_desc, (struct sockaddr*) &address, sizeof(address)) < 0)
    error("Error: failed to bind socket\n");

  if(listen(socket_desc, 3) < 0)
    error("Error: failed to listen socket\n");

  addrlen = sizeof(address);

  new_socket = accept(socket_desc, (struct sockaddr*) &address, &addrlen);
  if(new_socket < 0)
    error("Error: failed to accept connection\n");

  sc = malloc(sizeof(struct _server_connection));
  sc->socket_desc = socket_desc;
  sc->new_socket = new_socket;

  return sc;
}

/*!
*\details Fonction d'envoi de message du serveur au client
*\param sc paramètre de type \a server_connection , représentant la connexion ouverte client/serveur
*\param msg paramètre de type \a char* qui contient le message à envoyer au serveur
*\return Cette fonction ne renvoie rien (type \a void)
*/
void server_send_message(server_connection sc, const char *msg){
  send(sc->new_socket, msg, strlen(msg), 0);
  send(sc->new_socket, "\n", 1, 0);
}

/*!
*\details Fonction de réception du message du client
*\param sc paramètre de type \a server_connection , représentant la connexion ouverte client/serveur
*\param buf paramètre de type \a char* buffer dans lequel on va stocker le message du serveur
*\param len paramètre de type \a int , représente la longueur maximale du message reçu
*\return Cette fonction ne renvoie rien (type \a void)
*/
void server_receive_message(server_connection sc, char *buf, int len){
  char c = 'x';
  int i = 0, n = 1;
  while(n != 0 && c != '\n' && c != '\0'){
    if(i >= len) error("Error: server receive message: buffer overflow\n");
    n = recv(sc->new_socket, &c, 1, 0);
    if(n == -1) error("Error: server receive message\n");
    buf[i] = c;
    i ++;
  }
  buf[i-1] = '\0';
}

/*!
*\details Fonction de fermeture de la connexion
*\param sc paramètre de type \a server_connection , représentant la connexion ouverte client/serveur
*\return Cette fonction ne renvoie rien (type \a void)
*/
void server_close_connection(server_connection sc){
  close(sc->socket_desc);
  close(sc->new_socket);
  free(sc);
}
