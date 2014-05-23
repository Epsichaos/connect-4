#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
#include"fonctions.h"

token play(player p1, player p2) {
	if(p1->player_kind==KEYBOARD) {
		grid g ;
	    g=create_grid() ;
	    print_grid(g);
	    /* Compteur qui s'incrémente à chaque tour de jeu, et qui sert à déterminer si la grille est pleine */
	    int compteur=0 ; 
	    /* Retourner le jeton du vainqueur */
	    int token_winner=0 ; 
	    while(winner(g)==0&&compteur<42) {
	    	int a ;
			a = input(g,p1) ;
			while(a<1||a>7) {
				print_grid(g) ;
				printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
				a = input(g,p1) ;
			}
       		if(a>0&&a<8) {
            	while(g->heights[a-1]==6) {
            		print_grid(g) ;
                	printf("Colonne pleine, choisissez en une autre !\n");
                	a = input(g,p1) ;
            	}
        	}
			put_token(g, a, p1->player_token) ;
			output(p2,a) ;
			compteur = compteur + 1 ;
			print_grid(g) ;
	        if(winner(g)==1) {
	            token_winner=p1->player_token ;
	        }
	        if(compteur==42) {
	            token_winner=NOTHING ;
	        }
	        if(winner(g)==0&&compteur<42) {
		        int b;
		        b = input(g,p2) ; /* Vérification de saisie ci dessous*/
		        //b = where_play(g,1,p2->player_token) ;
		        while(b<1||b>7) {
		        	print_grid(g) ;
		        	printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
		        	b = input(g,p2) ;
		        }
	       		if(b>0&&b<8) {
	            	while(g->heights[b-1]==6) {
	            		print_grid(g) ;
	                	printf("Colonne pleine, choisissez en une autre !\n");
	                	b = input(g,p2) ;
	            	}
	        	}
		        put_token(g, b, p2->player_token) ;
				output(p1,b) ;
				compteur = compteur + 1 ;
				print_grid(g);
		        if(winner(g)==1) {
		            token_winner=p2->player_token ;
		        }
		        if(compteur==42) {
		            token_winner=NOTHING ;
		        }		        
	        }
	    }
	    free(g) ;
	    return(token_winner) ;
	}
	if(p1->player_kind==SERVER) {
		grid g ;
	    g=create_grid() ;
	    print_grid(g);
	    int compteur=0 ;
	    int token_winner ;
	    while(winner(g)==0&&compteur<42) {
	    	int a ;
			a = input(g,p1) ; //ne pas oublier la vérif
			while(a<1||a>7) {
				print_grid(g) ;
				printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
				a = input(g,p1) ;
			}
       		if(a>0&&a<8) {
            	while(g->heights[a-1]==6) {
            		print_grid(g) ;
                	printf("Colonne pleine, choisissez en une autre !\n");
                	a = input(g,p1) ;
            	}
        	}
			put_token(g, a, p1->player_token) ;
			output(p2,a) ;
			compteur = compteur + 1 ;
			print_grid(g) ;
	        if(winner(g)==1) {
	            token_winner=p1->player_token ;
	        }
	        if(compteur==42) {
	            token_winner=NOTHING ;
	        }
	        if(winner(g)==0&&compteur<42) {
		        int b;
		        b = input(g,p2) ;
		        while(b<1||b>7) {
		        	print_grid(g) ;
		        	printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
		        	b = input(g,p2) ;
		        }
	       		if(b>0&&b<8) {
	            	while(g->heights[b-1]==6) {
	            		print_grid(g) ;
	                	printf("Colonne pleine, choisissez en une autre !\n");
	                	b = input(g,p2) ;
	            	}
	        	}
		        put_token(g, b, p2->player_token) ;
				output(p1,b) ;
				compteur = compteur + 1 ;
				print_grid(g);
		        if(winner(g)==1) {
		            token_winner=p2->player_token ;
		        }
		        if(compteur==42) {
		            token_winner=NOTHING ;
		        }		        
	        }
	    }
	    free(g) ;
	    return(token_winner) ;
	}
	if(p1->player_kind==CLIENT) {
		grid g ;
	    g=create_grid() ;
	    print_grid(g);
	    int compteur=0 ;
	    int token_winner ;
	    while(winner(g)==0&&compteur<42) {
	    	int a ;
			a = input(g,p1) ; //ne pas oublier la vérif
			while(a<1||a>7) {
				print_grid(g) ;
				printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
				a = input(g,p1) ;
			}
       		if(a>0&&a<8) {
            	while(g->heights[a-1]==6) {
            		print_grid(g) ;
                	printf("Colonne pleine, choisissez en une autre !\n");
                	a = input(g,p1) ;
            	}
        	}
			put_token(g, a, p1->player_token) ;
			output(p2,a) ;
			compteur = compteur + 1 ;
			print_grid(g) ;
	        if(winner(g)==1) {
	            token_winner=p1->player_token ;
	        }
	        if(compteur==42) {
	            token_winner=NOTHING ;
	        }
	        if(winner(g)==0&&compteur<42) {
		        int b;
		        b = input(g,p2) ;
		        while(b<1||b>7) {
		        	print_grid(g) ;
		        	printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
		        	b = input(g,p2) ;
		        }
	       		if(b>0&&b<8) {
	            	while(g->heights[b-1]==6) {
	            		print_grid(g) ;
	                	printf("Colonne pleine, choisissez en une autre !\n");
	                	b = input(g,p2) ;
	            	}
	        	}
		        put_token(g, b, p2->player_token) ;
				output(p1,b) ;
				compteur = compteur + 1 ;
				print_grid(g);
		        if(winner(g)==1) {
		            token_winner=p2->player_token ;
		        }
		        if(compteur==42) {
		            token_winner=NOTHING ;
		        }		        
	        }
	    }
	    free(g) ;
	    return(token_winner) ;
	}
	if(p1->player_kind==IA) {
		grid g ;
	    g=create_grid() ;
	    print_grid(g);
	    int compteur=0 ;
	    int token_winner ;
	    while(winner(g)==0&&compteur<42) {
	    	int a ;
			a = input(g,p1) ;
			while(a<1||a>7) {
				print_grid(g) ;
				printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
				a = input(g,p1) ;
			}
       		if(a>0&&a<8) {
            	while(g->heights[a-1]==6) {
            		print_grid(g) ;
                	printf("Colonne pleine, choisissez en une autre !\n");
                	a = input(g,p1) ;
            	}
        	}
			put_token(g, a, p1->player_token) ;
			output(p2,a) ;
			compteur = compteur + 1 ;
			print_grid(g) ;
	        if(winner(g)==1) {
	            token_winner=p1->player_token ;
	        }
	        if(compteur==42) {
	            token_winner=NOTHING ;
	        }
	        if(winner(g)==0&&compteur<42) {
		        int b;
		        b = input(g,p2) ;
		        while(b<1||b>7) {
		        	print_grid(g) ;
		        	printf("Choix hors colonne ou caractère incorrect, merci de recommencer\n") ;
		        	b = input(g,p2) ;
		        }
	       		if(b>0&&b<8) {
	            	while(g->heights[b-1]==6) {
	            		print_grid(g) ;
	                	printf("Colonne pleine, choisissez en une autre !\n");
	                	b = input(g,p2) ;
	            	}
	        	}
		        put_token(g, b, p2->player_token) ;
				output(p1,b) ;
				compteur = compteur + 1 ;
				print_grid(g);
		        if(winner(g)==1) {
		            token_winner=p2->player_token ;
		        }
		        if(compteur==42) {
		            token_winner=NOTHING ;
		        }		        
	        }
	    }
	    free(g) ;
	    return(token_winner) ;
	}
	else {
		return(0) ;
	}
}
	
