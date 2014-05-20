/**
*\file struct.h
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Structures et création des alias
*\details Ici sont défini les alias \a token , \a grid , \a player_kind , \a keyboard , \a server , \a client , \a player
*/

#ifndef STRUCT_H
#define STRUCT_H

#include"client-lib.h"
#include"server-lib.h"

/** Macro définissant le nombre de colonnes de la grille */
#define COLUMN_NB 7 

/** Macro définissant le nombre de lignes de la grille */
#define LINE_NB 6 

/**
*\enum token
*\details Désigne la couleur du jeton dans la case du tableau : Rouge ou Jaune (Nothing si aucun jeton n'est à cette case)
*/
typedef enum { NOTHING, RED, YELLOW } token ;

/**
*\struct grid_content
*\brief Structure représentant une grille de jeu de manière générale
*/
typedef struct {
    token table[LINE_NB][COLUMN_NB] ; /** Tableau à deux dimensions (LINE_NB * COLUMN_NB) représentant la grille en elle-même */
    int heights[COLUMN_NB] ; /** Tableau à une dimension (COLUMN_NB), donnant le nombre de jetons par colonne de la grille */
} grid_content, *grid ;

/**
*\enum player_kind
*\details Désigne le type de joueur que l'on considère : ordinateur, client, ou serveur
*/
typedef enum {KEYBOARD, CLIENT, SERVER, IA} player_kind ;

typedef int keyboard;
typedef int depth;

/**
*\struct server
*\brief Structure représentant un serveur
*/
typedef struct {
	int server_port ; /** Numéro du port du serveur sur lequel doivent se connecter les clients */
	server_connection server_connection ; /** Variable de type server_connection, définie dans server-lib.c et représentant la connexion ouverte du serveur */
} server;

/**
*\struct client
*\brief Structure représentant un client
*/
typedef struct {
	char *client_host ; /** Nom de l'hôte auquel doit se connecter le client */
	int client_port ; /** Nom du port de l'host auquel le client doit se connecter */
	client_connection client_connection ; /** Variable de type client_connection, définie dans client-lib.c et représentant la connexion du client au serveur */
} client ;

/**
*\struct player
*\brief Structure représentant un joueur
*/
typedef struct {
	player_kind player_kind ; /** Variable indiquant quel est le type du joueur : client, server, ou joue-t-il sur la machine ? */
	token player_token ; /** Indique la couleur de jeton du joueur */
	union {
		client player_client ;
		server player_server ;
		keyboard player_keyboard ;
		depth player_ia ;
	} player_data ; /** Cette union nous permet de choisir le type du joueur et donc les caractériques à savoir pour le définir correctement */
} *player ;

#endif 
