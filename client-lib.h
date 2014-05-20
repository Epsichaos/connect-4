/*! 
*\file client-lib.h
*\author Anonymous
*\version 1.0
*\date 21 avril 2014
*\brief Bibliothèque des fonctions relatives au client
*\details Contient l'ensemble des déclarations de fonctions relatives aux actions des clients
*/


#ifndef CLIENT_LIB_H_INCLUDED
#define CLIENT_LIB_H_INCLUDED

struct _client_connection;
typedef struct _client_connection *client_connection;
/* [ client_connection ] represente une connection avec le serveur. */

client_connection client_open_connection(const char* host, int port);
/* [ client_open_connection(host, port) ] ouvre une connection avec le
   serveur sur la machine [ host ] et le port [ port ]. */

void client_send_message(client_connection cc, const char *msg);
/* [ client_send_message(cc, msg) ] envoie le message [ msg ] au
   serveur via la connection [ cc ]. */

void client_receive_message(client_connection cc, char *buf, int len);
/* [ client_receive_message(cc, buf, len) ] recoit un message du serveur
   via la connection [ cc ]. Stocke le resultat dans le buffer [ buf ]
   de longueur [ len ]. */

void client_close_connection(client_connection cc);
/* [ client_close_connection(cc) ] ferme la connection [ cc ] et desalloue
   toutes les ressources qui lui sont affectees . */

#endif
