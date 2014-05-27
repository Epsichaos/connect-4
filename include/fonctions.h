/*! 
*\file fonctions.h
*\brief Bibliothèque des fonctions
*\details Ce fichier .h est la bibliothèque des fonctions utilisées dans le 
*projet, écrites dans des fichiers .c éponymes séparés
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
player create_ia(token,depth) ;


int input(grid, player) ;
void output(player, int) ;

void detect(int,char**,player*) ;
void deconnexion(player, player) ;

int pond(grid) ;
int alphabeta(grid, int, int, int, token) ;
int where_play(grid ,int ,token) ; 
int winner3(grid) ;

void help(void) ;

#endif