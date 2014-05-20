#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct.h"
#include"fonctions.h"

//Vérifier les tests
//VIDER LES MALLOC BORDEL !
//Finir de commenter les fonctions
//fonction qui vérifie si le caractère entré est bien un chiffre entier ?

int main(int argc, char *argv[]) { 	
	int token_winner ;
	player *joueurs=malloc(2*sizeof(player)) ;
	if(joueurs == NULL) { 
		printf("Erreur d'allocation !\n");
		exit(EXIT_FAILURE) ;
	}
	joueurs=detect(argc,argv) ; 
	player joueur1=joueurs[1] ;
	player joueur2=joueurs[2] ;
	joueur1->player_token=RED ;
	joueur2->player_token=YELLOW ;
	token_winner = play(joueur1,joueur2) ; 
	if(token_winner!=0) {
		printf("Le joueur %d a gagné !\n",token_winner) ;
	}
	if(token_winner==0) {
		printf("Match Nul : Personne n'a gagné !\n") ;
	}
	deconnexion(joueur1,joueur2) ; 
	free(joueurs);
	return(0) ;
}