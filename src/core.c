/** 
*\file core.c
*\brief Ensemble des fonctions de base
*\details Contient l'ensemble des fonctions utiles au déroulement d'une partie, comme la 
*génération et l'affichage de grille, l'algorithme d'analyse de grille pour 
déterminer la victoire, ...etc.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h> /* Pour strcmp */
#include<ctype.h> /* Pour isdigit */
#include<unistd.h> /* Pour Sleep */
#include"fonctions.h"
#include"struct.h"

/** Macro utilisée pour la longueur des tableaux dans input() */
#define LENGTH 100

/**
*\brief Fonction create_grid, utilisée pour générer une grille de Puissance 4
*\details Cette fonction permet au main, ou a posteriori à la fonction play{} de créer une grille de jeu.
*\return g de type grid : c'est la grille créé par create_grid.
*/
grid create_grid() {
    /* On crée une grille, de type grid_content, et pour éviter une erreur de segmentation, on utilise malloc */
    grid grille=malloc(sizeof(grid_content)); 
    /* On teste le succes de l'allocation */
    if(grille==NULL) {
        printf("Erreur d'allocation dans create_grid\n") ;
        exit(EXIT_FAILURE) ;
    }
    int i ;
    int j ;
    /* On initialise toute la grille à 0, en la parcourant avec la double boucle for. */
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) {
            grille->table[i][j]=NOTHING ; 
        }
    }
    int k;
    /* On initialise le nombre de jetons par colonne à 0, pour chaque colonne, car toute la grille est vide. */
    for(k=0;k<COLUMN_NB;k++) {
        grille->heights[k]=0; 
    }
    /* On retourne la grille ainsi créé, de type grid, qui est entièrement vide pour le moment */
    return(grille); 
}

/**
*\brief Fonction print_grid, utilisée pour afficher une grille de Puissance 4
*\details Cette fonction permet au main, ou a posteriori à la fonction \a play{} d'afficher une grille de jeu dans le terminal
*\param g grille (\a grid) que l'on souhaite afficher
*/
void print_grid(grid g) {
    /* Balise de couleur pour colorer la grille en cyan */
    couleur("36") ;
    printf(" 1  2  3  4  5  6  7 \n");
    couleur("0") ;  
    int i ;
    int j ;
    /* On parcourt toute la grille, et selon ce que contiennent les cases, on affiche " ", "x" ou "o" */
    for(i=0;i<LINE_NB;i++) {
        for(j=0;j<COLUMN_NB;j++) { 
            couleur("36") ;
            printf("|") ;
            couleur("0") ;
            if(g->table[i][j]==NOTHING) {
                /* Si la case est vide, on affiche un '.' blanc pour plus de visibilité/esthétique */
                couleur("37") ;
                printf(".") ;
                couleur("0") ;
            }
            if(g->table[i][j]==RED) {
                /* Si la case contient RED, on affiche une 'x' rouge ! */
                couleur("31") ;
                printf("x") ;
                couleur("0") ;
            }   
            if(g->table[i][j]==YELLOW){
                /* Si elle est YELLOW, on affiche un 'o' jaune */
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
*\brief Fonction put_token, utilisée pour mettre un jeton dans la grille
*\details Cette fonction permet au main, ou a posteriori à la fonction play{} de déposer 
*un jeton \a t (t=RED ou t=YELLOW) dans la colonne \a column de la 
grille \a g
*\param g grille (\a grid) dans laquelle on joue
*\param column entier (\a int) désignant la colonne dans laquelle le jeton est lâché
*\param t paramètre de type \a token pouvant prendre trois valeurs : \a RED , \a YELLOW ou \a NOTHING, 
*désignant la couleur des jetons (\a RED , \a YELLOW et \a
NOTHING sont des alias de type \a int)
*/
int put_token(grid g, int column, token t) {
    /* Il n'y a pas de test dans la fonction put_token(), ils sont situés dans les fonctions play()
    et input(). (Permet d'alléger le corps de put_token()) */
    column=column-1;
    int nb ;
    nb = g->heights[column] ;
    g->heights[column]=g->heights[column] +1 ;
    g->table[5-nb][column]=t ;
    return(0);
}

void erase_token(grid g, int column) {
    /* Pareil que pour put_token, erase_token ne contient aucun test, car elle est utilisée pour enlever un jeton 
    après qu'on l'ai posé avec la fonction where_play. Les colonnes ne seront donc jamais vides, donc inutile d'insérer des tests */
    column=column-1;
    int nb ;
    nb = g->heights[column] ;
    /* On efface le jeton en mettant NOTHING à la place */
    g->table[6-nb][column]=NOTHING ;
    /* On décrémente l'indice de nombre de jetons par colonne */
    g->heights[column]=g->heights[column] - 1 ;
}

/**
*\brief Fonction winner, utilisée pour tester si une grille est gagnante
*\details Cette fonction permet, en prenant une grille en fonction, de savoir si 
*une configuration gagnante est présente ou non (respectant les normes de victoire)
*relatives aux règles en vigueur dans le puissance 4. Cette fonction n'est pas optimale, puisque elle teste
*toute la grille, mais nous avons préféré simplifier son expression, plutôt qu'utiliser l'astuce : winner(grid g, int column), où column
*est la dernière colonne dans laquelle on a jouer. Dans ce cas, on aurait pu enlever la double boucle for, pour effectuer les mêmes conditions, 
*(toutes les 8), mais seulement sur une SEULE case, la dernière dans laquelle on a jouée. Faire cette modification est assez facile, mais le gain
*en temps de traitement sera imperceptible, nous avons donc décidé de garder celle-ci !
*\param g grille de type \a grid 
*/
int winner(grid g) {
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
                while(k!=6&&increment<3) { 
                    k=k+1 ;
                    increment=increment+1 ;
                    /* Si la case suivant est la même que celle d'origine, on compte */
                    if(g->table[i][k]==caase) {
                    win1=win1+1 ;
                    }
                    /* Si les 3 suivantes sont de la même couleur, c'est gagné !*/
                    if(win1==3) {
                        return(1);
                    }
                }
                int win2=0 ;
                k=j ;
                increment=0 ;
                /* test de l'horizontale gauche */
                while(k!=0&&increment<3) { 
                    k=k-1 ;
                    increment=increment+1 ;
                    if(g->table[i][k]==caase) {
                    win2=win2+1 ;
                    }
                    if(win2==3) {
                        return(1);
                    }
                }
                /* test de la verticale basse */
                int win3=0 ; 
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
                /* test de la verticale haute */
                int win4=0 ; 
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
                /* test de la diagonale supérieure droite */
                int win5=0 ; 
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
                /* test de la diagonale inférieure droite */
                int win6=0 ; 
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
                /* test de la diagonale supérieure gauche */
                int win7=0 ; 
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
                /* test de la diagonale inférieure gauche */
                int win8=0 ; 
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
    return(0) ;
}

/**
*\brief Fonction \a input , utlisée pour recevoir l'action de jeu de l'autre joueur.
*\details Cette fonction permet de recevoir un message du client (ou du serveur, 
*selon le type de joueur en entrée), correspondant au coup que celui-ci veut jouer.
*\param p paramètre de type \a player , structure définie dans struct.h.
*\return Un entier, correspondant au numéro de colonne dans laquelle le joueur souhaite déposer un jeton.
*/
int input(grid g, player p) {
    if(p->player_kind==KEYBOARD) {
        char nombre[LENGTH] ;
        printf("Joueur %d, indique ton numéro de colonne :\n",p->player_token);
        fgets(nombre,LENGTH,stdin) ;
        /* Test pour savoir si le caractère est bien un chiffre entre 0 et 9. Le cas chiffre = 0, 8, 9 ainsi que colonne pleine 
        est testé dans le corps de play() */
        while(strlen(nombre)>2||isdigit(nombre[0])==0) {
            print_grid(g) ;
            printf("Saisie incorrecte, Joueur %d, indique ton numéro de colonne :\n",p->player_token) ;
            fgets(nombre,LENGTH,stdin) ;
        }
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
*\brief Fonction \a output , utlisée pour envoyer l'action de jeu à l'autre joueur.
*\details Cette fonction permet d'envoyer un message au client (ou au serveur), contenant 
*un entier désignant la colonne dans lequel le joueur en argument (et envoyant le message) 
*souhaite lâcher un jeton.
*\param p paramètre de type \a player , structure définie dans struct.h.
*\param col_ind entier, désignant la colonne dans laquelle on souhaite lâcher le jeton.
*/
void output(player p, int col_ind) {
    if(p->player_kind==KEYBOARD||p->player_kind==IA) {
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

/**
*\brief Fonction \a deconnexion , utlisée pour fermer proprement la connexion client/server à la fin de la partie
*\details Cette fonction permet de déconnecter proprement en premier le client, puis le serveur.
*\param p1 paramètre de type \a player , structure définie dans struct.h.
*\param p2 paramètre de type \a player , structure définie dans struct.h.
*\return Cette fonction ne retourne rien, elle affiche juste les confirmations de déconnexion à l'écran.
*/
void deconnexion(player p1, player p2) {
    if(p1->player_kind==CLIENT) {
        client_close_connection(p1->player_data.player_client.client_connection) ;
        printf("Client déconnecté\n") ;
    }
    if(p2->player_kind==CLIENT) {
        client_close_connection(p2->player_data.player_client.client_connection) ;
        printf("Client déconnecté\n") ;
    }
    if(p1->player_kind==SERVER||p2->player_kind==SERVER) {
        printf("Merci d'attendre que le client se déconnecte \n") ;
    }
    /* On laisse le temps au client de se déconnecter */
    sleep(2) ;
    if(p1->player_kind==SERVER) {
        server_close_connection(p1->player_data.player_server.server_connection) ;
        printf("Serveur déconnecté\n") ;
    }
    if(p2->player_kind==SERVER) {
        server_close_connection(p2->player_data.player_server.server_connection) ;
        printf("Serveur déconnecté\n") ;
    }
}

/**
*\brief Fonction \a detect, qui sert à détecter les paramètres entrés sur la ligne de commande
*\details Cette fonction permet de gérer tous les cas de paramètres sur ligne de commande, et de réagir 
* en conséquence (fonction d'aide, message d'erreurs, ...etc).
*\param argc le paramètre de type \a int en argument du main() (donne le nombre de paramètres passés en ligne de commande).
*\param argv de type \a char** , tableau en argument du main() contenant tous les paramètres passés en lige de commande.
*\param joueurs de type \player* : structre pouvant contenir 2 player. On utilise le passage par adresse pour le remplir, 
* du coup, cette fonction ne renvoit rien (\a void).
*\return Cette fonction ne retourne rien, le passage par adresse permet de s'affranchir d'un retour de type \a player*
*/
void detect(int argc, char *argv[],player* joueurs) {
    int nb_joueurs = 0 ;
    int i ;
    /* Cas où la fonction --help est demandée, on affiche l'aide */
    if(strcmp(argv[1],"--help")==0) {
        help() ;
        /* On libère la mémoire, vu qu'on ne joue pas ! */
        free(joueurs) ;
        exit(EXIT_SUCCESS) ;
    }
    for(i=1; i<argc;i++) {
        /* Si on détecte l'IA, on crée un joueur de type IA avec la fonction correspondante */
        if(strcmp(argv[i],"-ia")==0) { 
            /* On incrémente le nombre de joueurs */
            nb_joueurs = nb_joueurs + 1 ; 
            /* Condition pour gérer le cas où on ne met rien après l'IA */
            if(i==argc-1) { 
                printf("Erreur, il manque la profondeur de l'IA\n") ; 
                /* On libère la mémoire, vu qu'on ne joue pas ! */
                free(joueurs) ;
                exit(EXIT_FAILURE) ;
            }
            /* Permet de vérifier si le paramètre entré après -ia est correct */
            else if(isdigit(argv[i+1][0])!=0&&argv[i+1][0]!='0') { 
                /* On autorise uniquement les nombres à moins de 3 chiffres strictement */
                if(argv[i+1][1]!='\0'&&isdigit(argv[i+1][1])!=0&&argv[i+1][2]=='\0') {
                joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
                /* Le else if n'est emprunté que lorsque le nombre n'a qu'un chiffre */
                else if(argv[i+1][1]=='\0'){
                    joueurs[nb_joueurs] = create_ia(NOTHING,atoi(argv[i+1])) ;
                }
                else {
                printf("Erreur, le caractère entré après l'IA est un chiffre > 99\n") ;
                /* On libère la mémoire, vu qu'on ne joue pas ! */
                free(joueurs) ;
                exit(EXIT_FAILURE) ;    
                }
            }
            /* Sinon, il y a une erreur de saisie */
            else {
                printf("Erreur, le caractère entré après l'IA n'est pas un chiffre, ou est un chiffre < 1\n") ;
                /* On libère la mémoire, vu qu'on ne joue pas ! */
                free(joueurs) ;
                exit(EXIT_FAILURE) ;
            }
        }
        /* Si on détecte un clavier, on créé un joueur de type clavier */
        if(strcmp(argv[i],"-keyboard")==0) {
            /* On incrémente le nombre de joueurs */
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] = create_keyboard(NOTHING) ;
        }
        /* Création d'un joueur de type client. Ici pas de vérification à faire, si le client entre mal les " coordonnées " 
        du serveur, c'est de sa faute, on ne peut contrôler cette variable (le numéro de port et nom d'hôte changeant en
        permanence*/
        if(strcmp(argv[i],"-client")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            joueurs[nb_joueurs] = create_client(NOTHING,argv[i+1],atoi(argv[i+2])) ;
        }
        /* Création d'un joueur de type serveur */
        if(strcmp(argv[i],"-server")==0) {
            nb_joueurs = nb_joueurs + 1 ; 
            if(i==argc-1) { 
                printf("Erreur, il manque le numéro de port du serveur !\n") ; 
                /* On libère la mémoire, vu qu'on ne joue pas ! */
                free(joueurs) ;
                exit(EXIT_FAILURE) ;
            }
            else if(isdigit(argv[i+1][0])!=0&&isdigit(argv[i+1][1])!=0&&isdigit(argv[i+1][2])!=0&&isdigit(argv[i+1][3])!=0) {
                joueurs[nb_joueurs] =create_server(NOTHING, atoi(argv[i+1])) ;
            }
            else {
                printf("Entrez un numéro de port compris à 4 chiffres, ou numéro de port incorrect\n") ;
                free(joueurs) ;
                exit(EXIT_FAILURE) ;
            }
        }   
    }
    if(nb_joueurs!=2) {
        printf("Erreur dans le nombre de joueurs (ou leur synthaxe) passés en ligne de commande\n") ;
        /* On libère la mémoire, vu qu'on ne joue pas ! */
        free(joueurs) ;
        exit(EXIT_FAILURE) ;
    }
}

/**
*\brief Fonction \a play, qui sert à jouer de manière générique
*\details Cette fonction permet de lancer une partie de manière totalement indépendante du type des joueurs passés
* en ligne de commande.
*\param p1 de type \a player, correspondant au premier joueur.
*\param p2 de type \a player, correspondant au second joueur.
*\return Cette fonction renvoit le token du joueur victorieux, ou NOTHING si personne n'a gagné.
*/
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
            /* Input renvoit forcément un seul chiffre, et un seul, mais la vérification
                >0 et <8 est inscrite ci après */
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
            /* On notifie le coup à l'autre joueur */
            output(p2,a) ;
            /* On incrémente le compteur de coups */
            compteur = compteur + 1 ;
            print_grid(g) ;
            if(winner(g)==1) {
                token_winner=p1->player_token ;
            }
            /* Cas où le nombre de coups maximal a été joué */
            if(compteur==42) {
                token_winner=NOTHING ;
            }
            if(winner(g)==0&&compteur<42) {
                int b;
                b = input(g,p2) ; 
                /* Vérification de saisie ci dessous*/
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
        /* On libère la mémoire ! */
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
            a = input(g,p1) ;
            /* Vérification de saisie ci dessous*/
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
                /* Vérification de saisie ci dessous*/
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
        /* On libère la mémoire ! */
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
            a = input(g,p1) ;
            /* Vérification de saisie ci dessous*/
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
                /* Vérification de saisie ci dessous*/
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
        /* On libère la mémoire ! */
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
            /* Vérification de saisie ci dessous*/
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
                /* Vérification de saisie ci dessous*/
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
        /* On libère la mémoire ! */
        free(g) ;
        return(token_winner) ;
    }
    else {
        return(0) ;
    }
}

/**
*\brief Fonction \a output , utlisée pour envoyer l'action de jeu à l'autre joueur.
*\details Cette fonction permet d'envoyer un message au client (ou au serveur), contenant 
*un entier désignant la colonne dans lequel le joueur en argument (et envoyant le message) 
*souhaite lâcher un jeton.
*\param p paramètre de type \a player , structure définie dans struct.h.
*\param col_ind entier, désignant la colonne dans laquelle on souhaite lâcher le jeton.
*/
void help(void) {
    printf("\n") ;
    couleur("31") ;
    printf("      ------------------------------------------\n") ;
    printf("      |     -------   Connect-4   -------      |\n") ;
    printf("      |       -- A game by Epsichaos --        |\n") ;
    printf("      ------------------------------------------\n") ;
    printf("\n") ;
    couleur("0") ;
    couleur("36") ;
    printf("     To play 1 VS 1 on the same computer, run :\n") ;
    couleur("0") ;
    couleur("33") ;
    printf("          ./connect4.x -keyboard -keyboard\n\n") ;
    couleur("0") ;
    couleur("36") ;
    printf("     To play as player 1 and launch a server, run :\n") ;
    couleur("0") ;
    couleur("33") ;
    printf("          ./connect4.x -keyboard -server -host_port\n\n") ;
    couleur("0") ;
    couleur("36") ;
    printf("     To play as player 2 and launch a server, run :\n") ;
    couleur("0") ;
    couleur("33") ;
    printf("          ./connect4.x -server -host_port -keyboard\n\n") ;
    couleur("0") ;
    couleur("36") ;
    printf("     To play as player 1 and connect to a server as a client, run :\n") ;
    couleur("0") ;
    couleur("33") ;
    printf("          ./connect4.x -keyboard -client -host_name -host_port\n\n") ;
    couleur("0") ;
    couleur("36") ;
    printf("     If you want an IA to play, just replace '-keyboard' by '-ia -ia_depth', for example :\n") ;
    couleur("0") ;
    couleur("33") ;
    printf("          ./connect4.x -keyboard -ia 8\n\n") ;
    couleur("0") ;
}
