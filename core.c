/** 
*\file core.c
*\author Epsichaos
*\version 2.0
*\date 25 avril 2014
*\brief Ensemble des fonctions de base
*\details Contient l'ensemble des fonctions utiles au déroulement d'une partie, comme la génération et l'affichage de grille, l'algorithme d'analyse de grille pour 
déterminer la victoire, ...etc.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h> /* Pour strcmp */
#include<ctype.h> /* Pour isdigit */
#include"fonctions.h"
#include"struct.h"

/**
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Fonction create_grid, utilisée pour générer une grille de Puissance 4
*\details Cette fonction permet au main, ou a posteriori à la fonction play{} de créer une grille de jeu
*/
grid create_grid() {
    grid grille=malloc(sizeof(grid_content)); /* On crée une grille, de type grid, et pour éviter une erreur de segmentation, on utilise malloc */
    if(grille==NULL) {
        printf("Erreur d'allocation dans create_grid\n") ;
        exit(EXIT_FAILURE) ;
    }
    int i ;
    int j ;
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) {
            grille->table[i][j]=NOTHING ; /* On initialise toute la grille à 0, en la parcourant avec la double boucle for. */
        }
    }
    int k;
    for(k=0;k<COLUMN_NB;k++) {
        grille->heights[k]=0; /* On initialise le nombre de jetons par colonne à 0, pour chaque colonne, car toute la grille est vide. */
    }
    return(grille); /* On retourne la grille ainsi créé, de type grid, qui est entièrement vide pour le moment */
}

/**
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Fonction print_grid, utilisée pour afficher une grille de Puissance 4
*\details Cette fonction permet au main, ou a posteriori à la fonction \a play{} d'afficher une grille de jeu dans le terminal
*\param g grille (\a grid) que l'on souhaite afficher
*/
void print_grid(grid g) {
    couleur("36") ;
    printf(" 1  2  3  4  5  6  7 \n");
    couleur("0") ;  
    int i ;
    int j ;
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) { /* On parcourt toute la grille, et selon ce que contiennent les cases, on affiche " ", "x" ou "o" */
            couleur("36") ;
            printf("|") ;
            couleur("0") ;
            if(g->table[i][j]==NOTHING) {
                couleur("37") ;
                printf(".") ;
                couleur("0") ;
            }
            if(g->table[i][j]==RED) {
                couleur("31") ;
                printf("x") ;
                couleur("0") ;
            }   
            if(g->table[i][j]==YELLOW){
                couleur("33") ;
                printf("o");
                couleur("0") ;
            }  
            couleur("36") ;
            printf("|");
            couleur("0") ;
        }   
       printf("\n");
    }
    couleur("36") ;
    printf(" _  _  _  _  _  _  _ \n");
    couleur("0") ;
    printf("\n");
} 
/**
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Fonction put_token, utilisée pour mettre un jeton dans la grille
*\details Cette fonction permet au main, ou a posteriori à la fonction play{} de déposer un jeton \a t (t=RED ou t=YELLOW) dans la colonne \a column de la 
grille \a g
*\param g grille (\a grid) dans laquelle on joue
*\param column entier (\a int) désignant la colonne dans laquelle le jeton est lâché
*\param t paramètre de type \a token pouvant prendre trois valeurs : \a RED , \a YELLOW ou \a NOTHING, désignant la couleur des jetons (\a RED , \a YELLOW et \a
NOTHING sont des alias de type \a int)
*/
int put_token(grid g, int column, token t) {
    if(column<1 || column>7) {
        printf("Tu viens de poser un jeton par terre, tocard...\n");
        exit(EXIT_FAILURE) ;
    }
    if((t!=RED)&&(t!=YELLOW)) {
        printf("Met un jeton officiel acheté à 10000€ sur le site web de l'Empire\n");
        exit(EXIT_FAILURE);
    }
    column=column-1;
    int nb ;
    nb = g->heights[column] ;
    if(nb==6) {
        printf("La colonne est pleine !\n");
        exit(EXIT_FAILURE) ;
    }
    if(nb>6 || nb<0) {
        printf("Cas en théorie impossible, mais on est trop super prudents\n");
        exit(EXIT_FAILURE) ;
    }
    g->heights[column]=g->heights[column] +1 ;
    g->table[5-nb][column]=t;
    return(0);
}

void erase_token(grid g, int column) {
    column=column-1;
    int nb ;
    nb = g->heights[column] ;
    if(nb==0) {
        printf("La colonne est vide !\n") ;
        exit(EXIT_FAILURE) ;
    }
    g->table[6-nb][column]=NOTHING ;
    g->heights[column]=g->heights[column] - 1 ;
}

/**
*\author Epsichaos
*\version 1.0
*\date 15 avril 2014
*\brief Fonction winner, utilisée pour tester si une grille est gagnante
*\details Cette fonction permet, en prenant une grille en fonction, de savoir si une configuration gagnante est présente ou non (respectant les normes de victoire)
relatives aux règles en vigueur dans le puissance 4
\param g grille de type \a grid 
*/

int winner(grid g) {
    int i;
    int j;
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) {
            if(g->table[i][j]!=NOTHING) {
                int caase;
                caase=g->table[i][j];
                int win1=0 ;
                int k=j ;
                int increment=0 ;
                while(k!=6&&increment<3) { /* test de l'horizontale droite */
                    k=k+1 ;
                    increment=increment+1 ;
                    if(g->table[i][k]==caase) {
                    win1=win1+1 ;
                    }
                    if(win1==3) {
                        return(1);
                    }
                }
                int win2=0 ;
                k=j ;
                increment=0 ;
                while(k!=0&&increment<3) { /* test de l'horizontale gauche */
                    k=k-1 ;
                    increment=increment+1 ;
                    if(g->table[i][k]==caase) {
                    win2=win2+1 ;
                    }
                    if(win2==3) {
                        return(1);
                    }
                }
                int win3=0 ; /* test de la verticale basse */
                k=i ;
                increment=0 ;
                while(k!=5&&increment<3) {
                    k=k+1 ;
                    increment=increment+1 ;
                    if(g->table[k][j]==caase) {
                    win3=win3+1 ;
                    }
                    if(win3==3) {
                        return(1);
                    }
                }
                int win4=0 ; /* test de la verticale haute */
                k=i ;
                increment=0 ;
                while(k!=0&&increment<3) {
                    k=k-1 ;
                    increment=increment+1 ;
                    if(g->table[k][j]==caase) {
                    win4=win4+1 ;
                    }
                    if(win4==3) {
                        return(1);
                    }
                }
                int win5=0 ; /* test de la diagonale supérieure droite */
                k=i ;
                int l=j;
                increment=0 ;
                while(k!=0&&l!=6&&increment<3) {
                    k=k-1 ;
                    l=l+1 ;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win5=win5+1 ;
                    }
                    if(win5==3) {
                        return(1);
                    }
                }
                int win6=0 ; /* test de la diagonale inférieure droite */
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=5&&l!=6&&increment<3) {
                    k=k+1 ;
                    l=l+1;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win6=win6+1 ;
                    }
                    if(win6==3) {
                        return(1);
                    }
                }
                int win7=0 ; /* test de la diagonale supérieure gauche */
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=0&&l!=0&&increment<3) {
                    k=k-1 ;
                    l=l-1 ;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win7=win7+1 ;
                    }
                    if(win7==3) {
                        return(1);
                    }
                }
                int win8=0 ; /* test de la diagonale inférieure gauche */
                k=i ;
                l=j ;
                increment=0 ;
                while(k!=5&&l!=0&&increment<3) {
                    k=k+1 ;
                    l=l-1;
                    increment=increment+1 ;
                    if(g->table[k][l]==caase) {
                    win8=win8+1 ;
                    }
                    if(win8==3) {
                        return(1);
                    }
                }
            }
        }
    }
    return(0);
}


#define LENGTH 100

/**
*\author Epsichaos
*\version 1.0
*\date 28 avril 2014
*\brief Fonction \a input , utlisée pour recevoir l'action de jeu de l'autre joueur.
*\details Cette fonction permet de recevoir un message du client (ou du serveur, selon le type de joueur en entrée), correspondant au coup que celui-ci veut
jouer.
*\param p paramètre de type \a player , structure définie dans struct.h.
*\return Un entier, correspondant au numéro de colonne dans laquelle le joueur souhaite déposer un jeton
*/
int input(grid g, player p) {
    if(p->player_kind==KEYBOARD) {
        char nombre[100] ;
        printf("Joueur %d, indique ton numéro de colonne :\n",p->player_token);
        fgets(nombre,100,stdin) ;
        int a = atoi(nombre) ;
        return(a) ;
    }
    if(p->player_kind==CLIENT) {
        int a ;
        char buf[LENGTH] ;
        printf("L'autre joueur est en train de réfléchir... \n") ;
        client_receive_message(p->player_data.player_client.client_connection, buf, LENGTH) ;
        a=atoi(buf) ;
        return(a) ;
    }
    if(p->player_kind==SERVER) {
        int a ;
        char buf[LENGTH] ;
        printf("L'autre joueur est en train de réfléchir... \n") ;
        server_receive_message(p->player_data.player_server.server_connection, buf, LENGTH) ;
        a=atoi(buf) ;
        return(a) ;
    }
    if(p->player_kind==IA) {
        int a ;
        a = where_play(g,p->player_data.player_ia,p->player_token) ;
        return(a) ;
    }
    else {
        return(0) ;
    }
}

/**
*\author Epsichaos
*\version 1.0
*\date 28 avril 2014
*\brief Fonction \a output , utlisée pour envoyer l'action de jeu à l'autre joueur.
*\details Cette fonction permet d'envoyer un message au client (ou au serveur), contenant un entier désignant la colonne dans lequel le joueur en argument (et
envoyant le message) souhaite lâcher un jeton.
*\param p paramètre de type \a player , structure définie dans struct.h.
*\param col_ind entier, désignant la colonne dans laquelle on souhaite lâcher le jeton.
*/
void output(player p, int col_ind) {
    if(p->player_kind==KEYBOARD) {
    }
    if(p->player_kind==CLIENT) {
        int a=col_ind ;
        char buf[LENGTH] ;
        if((a>0&&a<8))
        sprintf(buf,"%d",a) ;
        client_send_message(p->player_data.player_client.client_connection, buf) ;
    }
    if(p->player_kind==SERVER) {
        int a=col_ind ;
        char buf[LENGTH] ;
        sprintf(buf,"%d",a) ;
        server_send_message(p->player_data.player_server.server_connection, buf) ;
    }
}

void deconnexion(player p1, player p2) {
    if(p1->player_kind==CLIENT) {
        client_close_connection(p1->player_data.player_client.client_connection) ;
        printf("Client déconnecté\n") ;
    }
    if(p2->player_kind==CLIENT) {
        client_close_connection(p2->player_data.player_client.client_connection) ;
        printf("Client déconnecté\n") ;
    }
    if(p1->player_kind==SERVER) {
        server_close_connection(p1->player_data.player_server.server_connection) ;
        printf("Serveur déconnecté\n") ;
    }
    if(p2->player_kind==SERVER) {
        server_close_connection(p2->player_data.player_server.server_connection) ;
        printf("Serveur déconnecté\n") ;
    }
}
/*
player* detect(int argc, char *argv[]) {
    int i;
    player* joueurs=malloc(2*sizeof(player)) ;
    if(joueurs==NULL) {
        printf("Erreur d'allocation dans detect\n") ;
        exit(EXIT_FAILURE) ;
    }
    int nb_joueurs = 0 ;
    for(i=1; i<argc;i++) {
        if(strcmp(argv[i],"-ia")==0) { // Si on détecte l'IA, on crée un joueur de type IA avec la fonction correspondante 
            nb_joueurs = nb_joueurs + 1 ; // On incrémente le nombre de joueurs 
            if(i==argc-1) { // Condition pour gérer le cas où on ne met rien après l'IA 
                printf("Erreur, il manque la profondeur de l'IA\n") ; 
                exit(EXIT_FAILURE) ;
            }
            else if(isdigit(argv[i+1][0])!=0&&argv[i+1][0]!='0') { // Permet de vérifier si le paramètre entré après -ia est correct 
                if(argv[i+1][1]!='\0'&&isdigit(argv[i+1][1])!=0&&argv[i+1][2]=='\0') {
                joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
                else{
                    joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
            }
            else {
                printf("Erreur, le caractère entré après l'IA n'est pas un chiffre, ou est un chiffre > 99 ou < 1\n") ;
                exit(EXIT_FAILURE) ;
            }
        }
        if(strcmp(argv[i],"-keyboard")==0) {
            nb_joueurs = nb_joueurs + 1 ; // On incrémente le nombre de joueurs
            joueurs[nb_joueurs] = create_keyboard(NOTHING) ;
        }
        if(strcmp(argv[i],"-client")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] = create_client(NOTHING,argv[i+1],atoi(argv[i+2])) ;
        }
        if(strcmp(argv[i],"-server")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] =create_server(NOTHING, atoi(argv[i+1])) ;
        }   
    }
    if(nb_joueurs!=2) {
        printf("Erreur dans le nombre de joueur (ou leur synthaxe) passés en ligne de commande\n") ;
        exit(EXIT_FAILURE) ;
    }
    return(joueurs) ;
}
*/

void detect(int argc, char *argv[],player* joueurs) {
    int nb_joueurs = 0 ;
    int i ;
    for(i=1; i<argc;i++) {
        if(strcmp(argv[i],"-ia")==0) { // Si on détecte l'IA, on crée un joueur de type IA avec la fonction correspondante 
            nb_joueurs = nb_joueurs + 1 ; // On incrémente le nombre de joueurs 
            if(isdigit(argv[i+1][0])!=0&&argv[i+1][0]!='0') { // Permet de vérifier si le paramètre entré après -ia est correct 
                if(argv[i+1][1]!='\0'&&isdigit(argv[i+1][1])!=0&&argv[i+1][2]=='\0') {
                joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
                else{
                    joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
            }
            else {
                printf("Erreur, le caractère entré après l'IA n'est pas un chiffre, ou est un chiffre > 99 ou < 1\n") ;
                exit(EXIT_FAILURE) ;
            }
        }
        if(strcmp(argv[i],"-keyboard")==0) {
            nb_joueurs = nb_joueurs + 1 ; // On incrémente le nombre de joueurs
            joueurs[nb_joueurs] = create_keyboard(NOTHING) ;
        }
        if(strcmp(argv[i],"-client")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] = create_client(NOTHING,argv[i+1],atoi(argv[i+2])) ;
        }
        if(strcmp(argv[i],"-server")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] =create_server(NOTHING, atoi(argv[i+1])) ;
        }   
    }
    if(nb_joueurs!=2) {
        printf("Erreur dans le nombre de joueur (ou leur synthaxe) passés en ligne de commande\n") ;
        exit(EXIT_FAILURE) ;
    }
}