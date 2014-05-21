/*! 
*\file fonctions.h
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Bibliothèque des fonctions
*\details Ce fichier .h est la bibliothèque des fonctions utilisées dans le projet, écrites dans des fichiers .c éponymes séparés
*/

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include"struct.h"

grid create_grid(void) ;
int put_token(grid, int, token) ;
void print_grid(grid);
int winner(grid) ;
void erase_token(grid, int) ;
token play(player, player) ;

player create_keyboard(token) ;
player create_client(token, char*, int) ;
player create_server(token, int) ;
player create_ia(token,depth) ; // Cours de DEV


int input(grid, player) ;
void output(player, int) ;

//player* detect(int, char**) ; //en cours de dev, mais semble terminée ON NE DOIT PAS RENVOYER DE PLAYER -> SINON MEMORY LOST
void detect(int,char**,player*) ;
void deconnexion(player, player) ; //en cours de dev, mais semble terminée

int pond(grid) ; // EN COURS DE DEV POUR L'ALPHA BETA
int alphabeta(grid, int, int, int, token) ; // EN COURS DE DEV POUR L'ALPHA BETA
int where_play(grid ,int ,token) ; // EN COURS DE DEV

#endif