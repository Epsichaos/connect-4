/**
*\file struct.h
*\details Ici sont défini les alias \a token , \a grid , \a player_kind , \a keyboard , 
*\a server , \a client , \a player
*/

#ifndef STRUCT_H
#define STRUCT_H

#include<stdio.h>
#include"client-lib.h"
#include"server-lib.h"

/* Macros pour afficher les couleurs dans le terminal */
#define clrscr() printf("\033[H\033[2J") /* fonction qui efface l'écran */
#define couleur(param) printf("\033[%sm",param)

/** Macro définissant le nombre de colonnes de la grille */
#define COLUMN_NB 7 

/** Macro définissant le nombre de lignes de la grille */
#define LINE_NB 6 

/**
*\enum token
*\details Désigne la couleur du jeton dans la case du tableau : Rouge ou Jaune 
*(Nothing si aucun jeton n'est à cette case)
*/
typedef enum { NOTHING, RED, YELLOW } token ;

/**
*\struct grid_content
*\brief Structure représentant une grille de jeu de manière générale
*/
typedef struct {
    token table[LINE_NB][COLUMN_NB] ;
    int heights[COLUMN_NB] ; 	
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
	int server_port ;
	server_connection server_connection ; 
} server;

/**
*\struct client
*\brief Structure représentant un client
*/
typedef struct {
	char *client_host ; 
	int client_port ; 
	client_connection client_connection ;
} client ;

/**
*\struct player
*\brief Structure représentant un joueur
*/
typedef struct {
	player_kind player_kind ; 
	token player_token ; 
	union {
		client player_client ;
		server player_server ;
		keyboard player_keyboard ;
		depth player_ia ;
	} player_data ;
} player_type,*player ;

#endif 
