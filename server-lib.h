/*! 
*\file server-lib.h
*\author Anonymous
*\version 1.0
*\date 21 avril 2014
*\brief Bibliothèque des fonctions relatives serveur
*\details Contient l'ensemble des déclarations de fonctions relatives aux actions des clients
*/

#ifndef SERVER_LIB_H_INCLUDED
#define SERVER_LIB_H_INCLUDED

struct _server_connection;
typedef struct _server_connection *server_connection;
/* [ client_connection ] represente une connection avec le client. */

server_connection server_open_connection(int port);
/* [ server_open_connection(port) ] ouvre le port [ port ] sur la machine
   locale sur laquelle un client pourra se connecter. */

void server_send_message(server_connection sc, const char *msg);
/* [ server_send_message (sc, msg) ] envoie le message [ msg ] au
   client via la connection [ sc ]. */

void server_receive_message(server_connection sc, char *buf, int len);
/* [ server_receive_message(sc, buf, len) ] recoit un message du client
   via la connection [ sc ]. Stocke le resultat dans le buffer [ buf ]
   de longueur [ len ]. */

void server_close_connection(server_connection sc);
/* [ server_close_connection(sc) ] ferme la connection [ sc ] et desalloue
   toutes les ressources qui lui sont affectees. */

#endif
