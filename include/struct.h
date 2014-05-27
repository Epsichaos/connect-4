/**
*\file struct.h
*\brief Structures globales introduites pour implémenter le jeu.
*\details Ici sont défini les alias, enum et structures \a token , \a grid , \a player_kind , \a keyboard , 
*\a server , \a client , \a player
*/

#ifndef STRUCT_H
#define STRUCT_H

#include<stdio.h>
#include"network-lib.h"

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
	/**> Grille de jeu : tableau à deux dimensions */
    token table[LINE_NB][COLUMN_NB] ; 
    /**> Tableau à une dimension servant à savoir si une colonne est pleine ou non */
    int heights[COLUMN_NB] ; 
} grid_content, *grid ;

/**
*\enum player_kind
*\details Désigne le type de joueur que l'on considère : ordinateur, client, ou serveur
*/
typedef enum { KEYBOARD, CLIENT, SERVER, IA } player_kind ;

/** Typedef pour désigner un clavier */
typedef int keyboard;
/** Typedef pour désigner la profondeur de l'IA */
typedef int depth;

/**
*\struct server
*\brief Structure représentant un serveur
*/
typedef struct {
	/**> Entier, désignant le port d'entré du serveur, auquel pourront se connecter les clients */
	int server_port ;
	/**> Quantité de type server_connection , désignant la connexion du serveur (définie dans la librairie serveur) */
	server_connection server_connection ; 
} server;

/**
*\struct client
*\brief Structure représentant un client
*/
typedef struct {
	/**> Nom du serveur auquel le client va se connecter */
	char *client_host ; 
	/**> Port du serveur auquel le client va se connecter */
	int client_port ; 
	/**> Quantité de type client_connection, désignant la connexion du client */
	client_connection client_connection ;
} client ;

/**
*\struct player_type
*\brief Structure représentant un joueur
*/
typedef struct {
	/**> Alias de type \a int, désignant le type de joueur, grace à l'ennum player_kind */
	player_kind player_kind ; 
	/**> Désigne le jeton joué par le joueur (NOTHING, RED, ou YELLOW) */
	token player_token ; 
	/**> Cette union représente le fait qu'un joueur puisse avoir plusieurs types. Dans ce cas, 
	* on choisit le type adapté pour le joueur : un seul possible */
	union {
		client player_client ;
		server player_server ;
		keyboard player_keyboard ;
		depth player_ia ;
	} player_data ;
} player_type, *player ;

#endif 
