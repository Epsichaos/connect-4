/**
*\file create_something.c
*\brief Contient l'ensemble des fonctions de création de joueur
*\details Ce fichier contient les trois fonctions de base de création de joueur : \a create_keyboard , 
*\a create_client , \a create_server 
*/

#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include"fonctions.h"
#include"client-lib.h"
#include"server-lib.h"

/**
*\brief Fonction create_keyboard, utilisée pour créer un joueur au clavier, sur la machine même
*\details Cette fonction permet au main de créer un joueur de type \a keyboard , qui joue sur la 
*machine où le programme est lancé
*\param t paramètre de type \a token (lui-même type \a enum) pouvant prendre 3 valeurs : 
*\a NOTHING , \a RED ou \a YELLOW (couleur des jetons)
*\return Objet de type player, définit dans struct.h
*/
player create_keyboard(token t) {
	/* On "créé" le joueur + allocation dynamique avec malloc */
	player player_key=malloc(sizeof(player_type)) ;
	/* On teste le succès de l'allocation */
	if(player_key==NULL) {
		printf("Erreur d'allocation dans create_keyboard !\n") ;
		exit(EXIT_FAILURE) ;
	} 
	/* On initialise le joueur de type player pour que tout corresponde à un type de jeu clavier */
	player_key->player_kind=KEYBOARD ; 
	player_key->player_token = t ;
	player_key->player_data.player_keyboard = 1 ;
	return(player_key) ;
}

player create_ia(token t,depth d) {
	/* On "créé" et on alloue le joueur */
	player player_ia=malloc(sizeof(player_type)) ; 
	/* Test de l'allocation */
	if(player_ia==NULL) {
		printf("Erreur d'allocation dans create_ia !\n") ;
		exit(EXIT_FAILURE) ;
	}
	/* On initialise le joueur de type player pour que tout corresponde à un type de jeu IA */
	player_ia->player_kind=IA ; 
	player_ia->player_token = t ;
	player_ia->player_data.player_ia = d ;
	return(player_ia) ;
}

/**
*\version 1.0
*\date 21 avril 2014
*\brief Fonction create_server, utilisée pour créer un joueur de type server
*\details Cette fonction permet au main de créer un joueur de type \a server , 
*à l'aide des arguments passés dans la ligne de commande
*\param t paramètre de type \a token (lui-même type \a enum) pouvant prendre 3 valeurs : 
*\a NOTHING , \a RED ou \a YELLOW (couleur des jetons)
*\param port paramètre de type \a int , numéro du port du serveur ouvert, par lequel le client se connectera
*\return Objet de type player, définit dans struct.h
*/
player create_server(token t, int port) {
	/* On "créé" et on alloue le joueur */
	player player_srv=malloc(sizeof(player_type)) ;
	/* Test de l'allocation */
	if(player_srv==NULL) {
		printf("Erreur d'allocation dans create_server !\n") ;
		exit(EXIT_FAILURE) ;
	}
	/* On initialise le joueur de type player pour que tout corresponde à un type de jeu server */
	player_srv->player_kind=SERVER ;
	player_srv->player_token = t ;
	player_srv->player_data.player_server.server_port=port ;
	player_srv->player_data.player_server.server_connection=server_open_connection(port) ;
	return(player_srv) ;
}

/**
*\brief Fonction create_client, utilisée pour créer un joueur de type client
*\details Cette fonction permet au main de créer un joueur de type \a client , grâce aux 
*arguments passés en ligne de commande
*\param t paramètre de type \a token (lui-même type \a enum) pouvant prendre 3 valeurs : \a NOTHING , 
*\a RED ou \a YELLOW (couleur des jetons)
*\param host paramètre de type \a char* , nom de la machine hôte
*\param port paramètre de type \a int , numéro du port de connexion au serveur
*\return Objet de type player, définit dans struct.h
*/
player create_client(token t, char *host, int port) {
	/* On "créé" et on alloue le joueur */
	player player_cli=malloc(sizeof(player_type)) ;
	/* Test de l'allocation */
	if(player_cli==NULL) {
		printf("Erreur d'allocation dans create_client !\n") ;
		exit(EXIT_FAILURE) ;
	}
	/* On initialise le joueur de type player pour que tout corresponde à un type de jeu client */
	player_cli->player_kind=CLIENT ;
	player_cli->player_token = t ;
	player_cli->player_data.player_client.client_host=host ;
	player_cli->player_data.player_client.client_port=port ;
	player_cli->player_data.player_client.client_connection=client_open_connection(host,port);
	return(player_cli) ;
}
