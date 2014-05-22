/**
*\file client-lib.c
*\brief Corps des fonctions relatives au client
*\details Contient l'ensemble du corps des fonctions relatives aux actions des clients
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client-lib.h"

#define error(args...) do { fprintf(stderr, args); exit(1); } while(0);

/**
*\struct _client_connection
*/
struct _client_connection {
  int socket_desc;
};

/**
*\details Fonction de connexion d'un client au serveur
*\param host paramètre de type \a char* donnant le nom de l'hôte
*\param port paramètre de type \a int , qui est le numéro du port sur lequel on souhaite se connecter
*\return renvoit un objet de type \a client_connection, alias d'une struct définie dans struct.h
*/
client_connection client_open_connection(const char* host, int port){
  struct hostent *he;
  struct sockaddr_in server;
  int socket_desc;
  client_connection sc;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_desc == 0)
    error("Error: failed to create socket\n");

  he = gethostbyname(host);
  if(he == NULL)
    error("Error: cannot resolve host: '%s'\n", host);

  memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if(connect(socket_desc, (struct sockaddr*) &server, sizeof(server)))
    error("Error: connection to server '%s' failed\n", host);

  sc = malloc(sizeof(struct _client_connection));
  sc->socket_desc = socket_desc;

  return sc;
}

/**
*\details Fonction d'envoi de message d'un client au serveur
*\param cc paramètre de type \a client_connection , représentant la connexion avec le serveur
*\param msg paramètre de type \a char* qui contient le message à envoyer au serveur
*\return Cette fonction ne renvoie rien (type \a void)
*/
void client_send_message(client_connection cc, const char *msg){
  send(cc->socket_desc, msg, strlen(msg), 0);
  send(cc->socket_desc, "\n", 1, 0);
}

/**
*\details Fonction de réception d'un message du serveur
*\param cc paramètre de type \a client_connection , représentant la connexion avec le serveur
*\param buf paramètre de type \a char* buffer dans lequel on va stocker le message du serveur
*\param len paramètre de type \a int , représente la longueur maximale du message reçu
*\return Cette fonction ne renvoie rien (type \a void)
*/
void client_receive_message(client_connection cc, char *buf, int len){
  char c = 'x';
  int i = 0, n = 1;
  while(n != 0 && c != '\n' && c != '\0'){
    if(i >= len) error("Error: client receive message: buffer overflow\n");
    n = recv(cc->socket_desc, &c, 1, 0);
    if(n == -1) error("Error: client receive message\n");
    buf[i] = c;
    i ++;
  }
  buf[i-1] = '\0';
}

/**
*\details Fonction de fermeture de la connexion du client au serveur
*\param cc paramètre de type \a client_connection , représentant la connexion avec le serveur
*\return Cette fonction ne renvoie rien (type \a void)
*/
void client_close_connection(client_connection cc){
  close(cc->socket_desc);
  free(cc);
}
