/*! 
*\file fonctions.h
*\brief Bibliothèque des fonctions
*\details Ce fichier .h est la bibliothèque des fonctions utilisées dans le 
*projet, écrites dans des fichiers .c éponymes séparés
*/

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include"struct.h"

/* Fonctions relatives à la grille */
grid create_grid(void) ;
int put_token(grid, int, token) ;
void print_grid(grid);
int winner(grid) ;
void erase_token(grid, int) ;
token play(player, player) ;

/* Fonctions relatives à la création de joueurs */
player create_keyboard(token) ;
player create_client(token, char*, int) ;
player create_server(token, int) ;
player create_ia(token,depth) ;


/* Fonctions de jeu */
int input(grid, player) ;
void output(player, int) ;

/* Fonctions de gestion de détection des joueurs */
void detect(int,char**,player*) ;
void deconnexion(player, player) ;

/* Fonctions concernant l'IA */
int pond(grid) ;
int alphabeta(grid, int, int, int, token) ;
int where_play(grid ,int ,token) ; 
int winner3(grid) ;

void help(void) ;

#endif