/**
*\file main.c
*\brief \a main, faisant la liaison entre toutes les fonctions pour permettre le jeu.
*\details Ce fichier permet la gestion d'une partie, à l'aide de toutes les fonctions implémentées
dans les fichiers précédents.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct.h"
#include"fonctions.h"

int main(int argc, char *argv[]) { 	
	int token_winner ;
    /* On alloue joueurs */
	player *joueurs=malloc(2*sizeof(player_type)) ;
    /* Test de l'allocation */
	if(joueurs == NULL) { 
		printf("Erreur d'allocation dans le main !\n");
		exit(EXIT_FAILURE) ;
	}
    /* Dans ce cas, il n'y a aucun paramètre de rentré */
    if(argc==1) {
        couleur("31") ;
        printf("Erreur dans les paramètres, si vous avez besoin d'aide : ./connect4.x --help\n") ;
        couleur("0") ;
        free(joueurs) ;
        exit(EXIT_FAILURE) ;
    }
    /* On détecte les paramètres entrés en ligne de commande */
	detect(argc,argv,joueurs) ; 
	player joueur1=joueurs[1] ;
	player joueur2=joueurs[2] ;
    /* On libère joueurs vu qu'on a plus besoin de lui */
	free(joueurs);
    /* On assigne les jetons à chaque joueur, puisque ils sont initialisés à NOTHING */
	joueur1->player_token=RED ;
	joueur2->player_token=YELLOW ;
    /* On lance la partie */
	token_winner = play(joueur1,joueur2) ; 
    /* On affiche le gagnant */
	if(token_winner!=0) {
		printf("Le joueur %d a gagné !\n",token_winner) ;
	}
	if(token_winner==0) {
		printf("Match Nul : Personne n'a gagné !\n") ;
	}
    /* On déconnecte proprement le client/serveur */
	deconnexion(joueur1,joueur2) ; 
    /* On finit par vider la mémoire */
	free(joueur1) ;
	free(joueur2) ;
	return(0) ;
}