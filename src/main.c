#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"struct.h"
#include"fonctions.h"

//Vérifier les tests
//Finir de commenter les fonctions

int main(int argc, char *argv[]) { 	
	int token_winner ;
	player *joueurs=malloc(2*sizeof(player_type)) ;
	if(joueurs == NULL) { 
		printf("Erreur d'allocation !\n");
		exit(EXIT_FAILURE) ;
	}
    if(argc==1) {
        printf("Error in parameters, if you need help please run ./connect4.x --help\n") ;
        exit(EXIT_FAILURE) ;
    }
	detect(argc,argv,joueurs) ; 
	player joueur1=joueurs[1] ;
	player joueur2=joueurs[2] ;
	free(joueurs);
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
	free(joueur1) ;
	free(joueur2) ;
	return(0) ;
}

/**
*@mainpage
<h1>Projet</h1>
    <p> Dans le cadre du cours IN-104, proposé à l'ENSTA ParisTech en première année, nous devons programmer un jeu puissance 4 en C proposant de multiples
        fonctionnalités. Notre binôme est composé d'Achille Issenjou et de Camille Constant, sous la supervision de Benoît Vaugon.</p>
<h1>Objectifs</h1>
    <p> Les objectifs du projet suivi sont multiples :</p>
    <h2>Jeu fonctionnel puissance 4</h2>
        <p> La première partie consiste à programmer un jeu fonctionnel, permettant de jouer à deux sur la même machine, à tour de rôle.</p>
    <h2>Jeu en réseau, suivant l'architecture client/serveur</h2>
        <p> La deuxième partie consister à utiliser la base de la partie 1, pour développer un système permettant de jouer à 2 joueurs, mais sur 2 machines différentes.
        Il faudra alors mettre en place une communication client/serveur pour la gestion de la partie et des coups. Le serveur devant lire le coup que le client 
        souhaite jouer, pour ensuite appliquer la modification à la grille et renvoyer le résultat au client, puis lui-même jouer et renvoyer la grille au client 
        après modification et attendre alors l'action que celui-ci souhaite entreprendre, et ainsi de suite.</p>
        <p>La bibliothèque utilisée a été proposée par le  chargé de TD lui-même et est donc mise à notre disposition.</p>
    <h2>Développer une IA selon la méthode alpha-bêta</h2>
        <p>La dernière partie du projet consiste à coder une IA, qui puisse jouer seule au puissance 4 (contre elle-même), et qui puisse également permettre à un humain
        de jouer tout seul, contre l'ordinateur.<p>
    <h2>Ouvertures</h2>
        <p>De multiples ouvertures sont possibles : algorithmes génétiques pour améliorer l'IA, utilisation d'une interface graphique avec GTK, ... etc.</p>
    <hr>
<h1>Historique des modifications</h1>
    <h2>28 Avril 2014</h2>
        <h3>Description des modifications</h3>
            <p>Finalisation complète de la partie client / serveur. Les fonctions input(), output() sont créés et play() est mise à jour. Des vérifications 
            mineures restent toujours à faire dans certains cas, mais la base est posée, le programme est parfaitement fonctionnel pour un jeu en réseau.</p>
            <p>Poursuite des commentaires dans les nouvelles fonctions, corrections mineures (voir le repot git et la description des commits pour plus de
            détails).</p>
        <h3>Commentaires</h3>
            <p>L'écriture est restée assez basique. J'ai rencontré une erreur de segmentation, après avoir oublié d'initialiser quelques structures \a player
            dans le main. Problème réglé après l'initialisation avec \a malloc() .</p>
            <p>La fonction \a play() reste un peu compliquée... Peut être faudrait-il la simplifier. Les vérifications sont lourdes, et la disjonction de cas peut
            être un peu bancale. Mais celui ne nuit qu'à la lisibilité du code source, pas à l'exécution ni à la vitesse d'exécution du programme. A voir en cours, 
            pour savoir comment l'améliorer.</p>
            <p>La fonction \a play() , sera à terme transférée dans core.c, mais pour le moment, elle reste en construction (ce qui n'est pas le cas des autres
            fonctions situées dans core.c).</p>
            <p>Petit fait amusant : pour le transfert de string entre serveur/client, j'avais pris une longueur de string très limite (exactement égale à 1). Pour 
            des raisons pratiques, il y avait un buffer overflow, du à un terme de fin de string, je suppose (cf le commit correspondant dans le repot git). 
            Un changement de macro 1 -> 100 corrige le problème (j'ai pris 100 pour être vraiment large).</p>
            <p>A terme, il faudrait introduire des vérifications plus poussées quant à la chaîne de caractère envoyée : Que se passe-t-il si on envoie n'importe
            quoi ..?</p>
         <h3>Programmes modifiés</h3>
            <ul>
                <li>mise à jour de core.c, regroupant les fonctions de base, ainsi que les nouvelles fonctions \a input et \a output .</li>
                <li>mise à jour de play.c, pour convenir à tous les cas de figure (traités jusqu'à présent).</li>
                <li>mise à jour de main.c, pour convenir aux exécutions client/serveur du programme.</li>
            </ul>
    <h2>25 Avril 2014</h2>
        <h3>Description des modifications</h3>
            <p>Mise en forme du code pour la nouvelle version de la doc. Les fonctions essentielles sont regroupées dans core.c et create_something.c.</p>
            <p>Ajout d'un Makefile général, avec fonction de clean auto, de génération de documentation Doxygen (commande 'make doxy'), et de compilation de documentation
            latex.</p>
            <p>Ajout d'un repot git pour pouvoir travailler à plusieurs et pour synchroniser en live le code source sur mon ordinateur avec mon compte à l'ENSTA. Ce qui nous
            permet d'éviter une utilisation redondante de SCP.</p>
        <h3>Programmes créés</h3>
            <ul>
                <li>écriture de core.c, regroupant les fonctions de base : \a print_grid , \a create_grid , \a winner , \a put_token .</li>
                <li>écriture de create_something.c, regroupant les fonctions de base : \a create_keyboard , \a create_client et \a create_server . </li>
                <li>écriture du Makefile.</li>
            </ul>
        <h3>Programmes supprimés</h3>
            <p>Les programmes suivants sont désormais devenus obsolètes :</p>
            <ul>
                <li>print_grid.c</li>
                <li>create_grid.c</li>
                <li>put_token.c</li>
                <li>winner.c</li>
                <li>create_keyboard.c</li>
                <li>create_client.c</li>
                <li>create_server.c</li>
            </ul>
    <h2>21 Avril 2014</h2> 
        <h3>Description des modifications</h3>
            <p>Mise en forme du code : documentation complète avec Doxygen et écriture de quelques commentaires.</p>
            <p>Documentation des fonctions données par le chargé de TD.</p>
            <p>Début des fonctions de la partie 2 : \a create_keyboard , \a create_server et \a create_client .</p>
        <h3>Commentaires</h3>
            <p>Refonte totale du code qui était auparavant dans un unique <em>main.c</em>. Cette fois le code devient plus propre et plus lisible avec l'abstration dans 
            d'autres fichiers .c regroupant les fonctions, et dans des fichiers d'en-tête <em>headers</em> .h. Le problème qui nous empêchait de le faire auparavant a 
            été résolu en introduisant des : 
            <blockquote>#ifndef STRUCT_H<br>
                        #define STRUCT_H<br>
                        [...]<br>
                        #endif
            </blockquote></p>
            <p>Création ensuite d'autres fichiers pour la partie 2, qui semblent fonctionnels après avoir été testés dans le main. Affaire à suivre.</p>
            <p>Ecriture du programme play.c, totalement fonctionnel pour la partie du jeu à 2 sur une même machine. Compilation impeccable pour le moment.</p>
        <h3>Programmes créés</h3>
            <ul>
                <li>écriture de main2.c, pour tester les fonctions programmées</li>
                <li>écriture de create_keyboard.c</li>
                <li>écriture de create_client.c</li>
                <li>écriture de create_server.c</li>
                <li>écriture de play.c</li>
            </ul>
        <h3>Programmes mis à jour</h3>
            <ul>
                <li>mis à niveau de struct.h, pour y inclure les nouvelles structures</li>
            </ul>
        <h3>Programmes fournis</h3>
            <ul>
                <li>Fonctions relatives au serveur dans server-lib.c</li>
                <li>Bibliothèque des fonctions relatives au serveur dans server-lib.h</li>
                <li>Fonctions relatives au client dans client-lib.c</li>
                <li>Bibliothèque des fonctions relatives au client dans client-lib.h</li>
            </ul>
    <h2>15 Avril 2014</h2> 
        <h3>Description des modifications</h3>
            <p>Programmation complète de la partie 1, sans documentation, ni commentaire. Le jeu puissance 4 est parfaitement fonctionnel.</p>
        <h3>Commentaires</h3>
            <p>Le code est pour le moment regroupé dans un unique <em>main.c</em>. Nous avons eu des problèmes pour inclure un struct.h dans diverses fonctions (du à l'absence
            de <strong>ifndef</strong>), soucis qui sera réglé lors de la mise à jour du 21 Avril. Tout est fonctionnel, et les algorithmes semblent globalement assez
            performants.</p>
        <h3>Programmes créés</h3>
            <ul>
                <li>écriture de main.c, pour lancer le jeu et tester les fonctions</li>
                <li>écriture de print_grid.c, fonction d'affichage d'une grille</li>
                <li>écriture de create_grid.c, fonction de création d'une grille</li>
                <li>écriture de put_token.c, fonction pour ajouter un jeton</li>
                <li>écriture de winner.c, fonction pour déterminer la victoire sur une grille</li>
                <li>écriture de struct.h, rassemblant les structures et alias utilisés dans les fonctions</li>
                <li>écriture de fonctions.h, bibliothèque des fonctions</li>
            </ul>
*/