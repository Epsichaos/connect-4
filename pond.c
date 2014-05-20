#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"struct.h"
#include"fonctions.h"

#define INFINI 1000
#define NEUTRAL 0
#define COLUMN_NB 7
#define LINE_NB 6

int pond(grid g) { /* Fonction Naïve pour le moment */
	if(winner(g)==1) {
		return(-INFINI) ;
	}
	else {
		return(NEUTRAL) ;
	}
}

int alphabeta(grid g, int alpha, int beta, int depth, token t) { /* Il faut alpha < beta // t_var est le token qui varira // t_fix est le token */
	if(winner(g)==1||depth==1) {													/* qui permet de dire si on renvoit +INFINI ou -INFINI */
		return(pond(g)) ;
	}
	else {
		int best ;
		int column ;
		best = -INFINI ;
		for(column=1; column<=COLUMN_NB; column++) {
			if(g->heights[column-1]!=LINE_NB) {
				int val ;
				put_token(g, column, t) ; /* On joue le coup */
				if(t==RED) {
					val = - alphabeta(g, -beta, -alpha, depth-1, YELLOW) ; /* On alterne les coups */
				}
				if(t==YELLOW) {
					val = - alphabeta(g, -beta, -alpha, depth-1, RED) ; /* On alterne les coups */
				}
				erase_token(g, column) ; /* On annule le coup -> Parcours destructif de l'arbre */
				if(val > best) { /* Coupures Alpha et Beta */
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
	char buf[7] ;
	int j=0 ;
	int z ;
	for(i=0;i<7;i++) {
		buf[i] = 0 ;
	}
	for(i=1;i<8;i++) {
		if(g->heights[i-1] != LINE_NB) {
			put_token(g,i,t) ;
			if(t==RED) { /* Si on est rouge ... */
				tmp=alphabeta(g,-1000,1000,depth,YELLOW) ; /* ... On lance alphabeta en indiquant que le prochain joueur à joueur joue les YELLOW */
			}
			if(t==YELLOW) { /* Si on est YELLOW ... */
				tmp=alphabeta(g,-1000,1000,depth,RED) ; /* ... On lance alphabeta en indiquant que le prochain joueur à joueur joue les RED */
			}
			if(tmp==BestMove) { /* En cas d'égalité, on stocke à la suite dans un tableau, en vu de décider du choix aléatoirement */
				buf[j]=i ;
				j = j+1 ;
				printf("tmp = %d et buf[%d]=%d \n",tmp,j,i) ;
			}
			if(tmp<BestMove) { /* Si une valeur renvoyée est > BestMove, alors on remet les indices à 0, et on écrase le tableau */
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
	while(buf[k]!=0&&k<7) { /* On compte le nombre de valeurs non nulles dans le tableau */
		l = l + 1 ;
		k = k + 1 ;
		//printf("buf[%d]=%d \n",k-1,buf[k-1]) ;
	}
  	srand (time (NULL)); /* On balance une fonction aléatoire, avec une seed horaire */
   	int a = rand()%l; /* On module modulo le nombre de valeurs non nulle qu'il faut considérer dans buf[]->permet de choisir aléatoirement en cas d'égalité !*/
	//printf("l = %d et Je joue en %d\n",l, buf[a]);
	return(buf[a]) ; 
}