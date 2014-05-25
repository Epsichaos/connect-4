#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"
#include"fonctions.h"

#define INFINI 1000
#define NEUTRAL 0
#define COLUMN_NB 7
#define LINE_NB 6

/* Fonction Naïve pour le moment */
int pond(grid g) { 
	if(winner(g)==1) {
		return(-INFINI) ;
	}
	else {
		return(NEUTRAL) ;
	}
}

/* Il faut alpha < beta, typiquement alpha = -INFINI et beta = INFINI */
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

int where_play(grid g,int depth,token t) {
	int i;
	int BestMove=1000 ;
	int tmp=1000 ;
	char buf[7] = { 0 } ;
	int j=0 ;
	int z ;
	for(i=1;i<8;i++) {
		if(g->heights[i-1] != LINE_NB) {
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
			/* En cas d'égalité, on stocke à la suite dans un tableau, en vu de décider du choix aléatoirement */
			if(tmp==BestMove) { 
				buf[j]=i ;
				j = j+1 ;
			}
			/* Si une valeur renvoyée est < BestMove, alors on remet les indices à 0, et on écrase le tableau */
			if(tmp<BestMove) { 
				j=0 ;
				for(z=0;z<7;z++) {
					buf[z] = 0 ;
				} 
				BestMove = tmp ;
				buf[j]=i ;
				j = j + 1 ;
			}
			erase_token(g,i) ;
		}
	}
	int k=0 ;
	int l=0 ;
	/* On compte le nombre de valeurs non nulles dans le tableau */
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