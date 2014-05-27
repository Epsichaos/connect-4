/*! 
*\file server-lib.h
*\brief Bibliothèque des fonctions relatives serveur
*\details Contient l'ensemble des déclarations de fonctions relatives aux actions des clients
*/

#ifndef NETWORK_LIB_H_INCLUDED
#define NETWORK_LIB_H_INCLUDED

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
