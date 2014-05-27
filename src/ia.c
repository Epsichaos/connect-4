/**
*\file ia.c
*\brief Contient les fonctions relatives à l'IA
*\details Ce fichier contient les 3 fonctions permettant à l'IA de fonctionner : \a pont(), \a alphabeta() et \a where_play
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"
#include"fonctions.h"

#define INFINI 1000
#define NEUTRAL 0
#define COLUMN_NB 7
#define LINE_NB 6

/**
*\brief Fonction pond, heuristique qui détermine la valeur d'une grille.
*\details Cette fonction permet au main, ou a posteriori à la fonction play{} de créer une grille de jeu. Elle est relativement naïve :
elle renvoit moins l'INFINI si elle détecte une victoire, et moins l'INFINI sur deux, si elle détecte que 3 pièces sont alignées et
qu'il y a une place pour rajouter un jeton (que la case "suivante" est vide) (implémenté par la fonction \a winner3).
*\return g de type grid : c'est la grille créé par create_grid.
*/
int pond(grid g) { 
	if(winner(g)==1) {
		return(-INFINI) ;
	}
	else if(winner3(g)==1) {
		return(-INFINI/2) ;
	}
	else {
		return(NEUTRAL) ;
	}
}

/**
*\brief Fonction alphabeta, qui est l'implémentation de l'algorithme alpha/beta.
*\details Cette fonction permet de générer l'arbre (détruit au fur et à mesure) de l'ensemble des coups et des
grilles possibles. Note pour l'utilisation pratique : Il faut alpha < beta, typiquement alpha = -INFINI et beta = INFINI.
*\return best de type \a int : c'est la valeur de la pondération affectée à une grille.
*/
int alphabeta(grid g, int alpha, int beta, int depth, token t) { 
	if(winner(g)==1||depth==1) {								
		return(pond(g)) ;
	}
	else {
		int best ;
		int column ;
		best = -INFINI ;
		for(column=1; column<=COLUMN_NB; column++) {
			if(g->heights[column-1]!=LINE_NB) {
				int val ;
				/* On joue le coup */
				put_token(g, column, t) ; 
				if(t==RED) {
					/* On alterne les coups */
					val = - alphabeta(g, -beta, -alpha, depth-1, YELLOW) ; 
				}
				if(t==YELLOW) {
					/* On alterne les coups */
					val = - alphabeta(g, -beta, -alpha, depth-1, RED) ; 
				}
				/* On annule le coup -> Parcours destructif de l'arbre */
				erase_token(g, column) ; 
				/* Coupures Alpha et Beta */
				if(val > best) { 
					best = val ;
					if(best > alpha) {
						alpha = best ;
						if(alpha >= beta) {
							return(best) ;
						}
					}
				}
			}
		}
		return(best) ;
	}
}

/**
*\brief Fonction where_play, utilisée pour savoir où l'IA doit jouer.
*\details Cette fonction permet à l'IA (modulo sa profondeur) de savoir dans quelle colonne jouer, en se basant sur les
fonctions alphabeta et pond.
*\return a de type \a int, c'est le numéro de colonne (entre 1 et 7 donc) dans lequel l'IA doit jouer.
*/
int where_play(grid g,int depth,token t) {
	int i;
	int BestMove=1000 ;
	int tmp=1000 ;
	/* On initialise buf, mais Valgrind râle quand même, cf ligne 105 */
	char buf[7] = { 0 } ;
	int j=0 ;
	int z ;
	for(i=1;i<8;i++) {
		if(g->heights[i-1] != LINE_NB) {
			/* On pose un jeton */
			put_token(g,i,t) ;
			/* Si on est RED ... */
			if(t==RED) { 
				/* ... On lance alphabeta en indiquant que le prochain joueur à joueur joue les YELLOW */
				tmp=alphabeta(g,-1000,1000,depth,YELLOW) ; 
			}
			/* Si on est YELLOW ... */
			if(t==YELLOW) { 
				/* ... On lance alphabeta en indiquant que le prochain joueur à joueur joue les RED */
				tmp=alphabeta(g,-1000,1000,depth,RED) ; 
			}
			/* En cas d'égalité, on stocke à la suite dans un tableau, en vue de décider du choix aléatoirement : 
			permet de gérer le cas où quel que soit la colonne dans laquelle on joue " le cas est le même " */
			if(tmp==BestMove) { 
				buf[j]=i ;
				j = j+1 ;
			}
			/* Si une valeur renvoyée est < BestMove, alors on remet les indices à 0, et on écrase le tableau, pour
			favoriser les pondérations " faibles " */
			if(tmp<BestMove) { 
				j=0 ;
				for(z=0;z<7;z++) {
					buf[z] = 0 ;
				} 
				BestMove = tmp ;
				buf[j]=i ;
				j = j + 1 ;
			}
			/* On enlève le jeton : parcours destructif de l'arbre */
			erase_token(g,i) ;
		}
	}
	int k=0 ;
	int l=0 ;
	/* On compte le nombre de valeurs non nulles dans le tableau. La ligne suivante est source d'erreur avec Valgrind,
	qui nous dit 'Conditional jump or move depends on uninitialised value(s)', alors que buf est initialisé ligne 66... Nous 
	n'avons pas réussi à trouver la source de l'erreur.  */
	while(buf[k]!=0&&k<7) { 
		l = l + 1 ;
		k = k + 1 ;
	}
	/* On balance une fonction aléatoire, avec une seed horaire */
  	srand (time (NULL)); 
  	/* On module modulo le nombre de valeurs non nulle qu'il faut considérer dans buf[]
  	-> permet de choisir aléatoirement en cas d'égalité !*/
   	int a = rand()%l; 
	return(buf[a]) ; 
}

/**
*\brief Fonction winner3, utilisée pour déterminer la valeur d'une grille dans \a pond.
*\details Elle permet d'indiquer une "victoire" lorsque 3 jetons sont alignés, et que le 4ème est vide : sert à
rendre la fonction de pondération moins naïve.
*\return a de type \a int valant 0 si la grille est 'non gagnante' ou 1 si elle est 'gagnante' (un booléen donc...)
*/
int winner3(grid g) {
    int i;
    int j;
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) {
            /* On effectue le test que si la case est non vide */
            if(g->table[i][j]!=NOTHING) {
                int caase;
                caase=g->table[i][j];
                int win1=0 ;
                int k=j ;
                int increment=0 ;
                /* test de l'horizontale droite */
                while(k!=6&&increment<2) { 
                    k=k+1 ;
                    increment=increment+1 ;
                    /* Si la case suivant est la même que celle d'origine, on compte */
                    if(g->table[i][k]==caase) {
                    win1=win1+1 ;
                    }
                    /* Si les 3 suivantes sont de la même couleur, c'est gagné !*/
                    if(win1==2) {
                    	if(g->table[i][k+1]==NOTHING) {
                        	return(1);
                        }
                    }
                }
                int win2=0 ;
                k=j ;
                increment=0 ;
                /* test de l'horizontale gauche */
                while(k!=0&&increment<2) { 
                    k=k-1 ;
                    increment=increment+1 ;
                    if(g->table[i][k]==caase) {
                    win2=win2+1 ;
                    }
                    if(win2==2) {
                    	if(g->table[i][k-1]==NOTHING) {
                        	return(1);
                        }
                    }
                }
                /* test de la verticale basse */
                int win3=0 ; 
                k=i ;
                increment=0 ;
                while(k!=5&&increment<2) {
                    k=k+1 ;
                    increment=increment+1 ;
                    if(g->table[k][j]==caase) {
                    win3=win3+1 ;
                    }
                    if(win3==2) {
                    	if(g->table[k+1][j]==NOTHING) {
                    		return(1);
                    	}
                    }
                }
                /* test de la verticale haute */
                int win4=0 ; 
                k=i ;
                increment=0 ;
                while(k!=0&&increment<2) {
                    k=k-1 ;
                    increment=increment+1 ;
                    if(g->table[k][j]==caase) {
                    win4=win4+1 ;
                    }
                    if(win4==2) {
                    	if(g->table[k-1][j]==NOTHING) {
                    		return(1);
                    	}
                    }
                }
                /* test de la diagonale supérieure droite */
                int win5=0 ; 
                k=i ;
                int l=j;
                increment=0 ;
                while(k!=0&&l!=6&&increment<2) {
                    k=k-1 ;
                    l=l+1 ;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win5=win5+1 ;
                    }
                    if(win5==2) {
                        if(g->table[k-1][l+1]==NOTHING) {
                        	return(1) ;
                        }
                    }
                }
                /* test de la diagonale inférieure droite */
                int win6=0 ; 
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=5&&l!=6&&increment<2) {
                    k=k+1 ;
                    l=l+1;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win6=win6+1 ;
                    }
                    if(win6==2) {
                        if(g->table[k+1][l+1]==NOTHING) {
                        	return(1) ;
                        }
                    }
                }
                /* test de la diagonale supérieure gauche */
                int win7=0 ; 
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=0&&l!=0&&increment<2) {
                    k=k-1 ;
                    l=l-1 ;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win7=win7+1 ;
                    }
                    if(win7==2) {
                        if(g->table[k-1][l-1]==NOTHING) {
                        	return(1) ;
                        }
                    }
                }
                /* test de la diagonale inférieure gauche */
                int win8=0 ; 
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=5&&l!=0&&increment<2) {
                    k=k+1 ;
                    l=l-1;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win8=win8+1 ;
                    }
                    if(win8==2) {
                        if(g->table[k+1][l-1]==NOTHING) {
                        	return(1) ;
                        }
                    }
                }
            }
        }
    }
    return(0) ;
}