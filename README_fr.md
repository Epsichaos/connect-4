Puissance 4 en C 
=================
Projet 
-----------------

Implémentation d'un jeu de type puissance 4 en C, proposant de multiples facettes du jeu : jouer sur une même machine, avec une architecture
client/serveur, ou contre une IA (MinMax avec coupures Alpha/Beta).

Jeu
-----------------

Différent type de joueurs sont prévus : 

* type KEYBOARD
* type SERVER
* type CLIENT
* type IA

Pour jouer (après avoir compilé avec make), lancez juste: ./connect4.x [player1] [player2], 
où [player] est :

* '-keyboard' si le type est KEYBOARD,
* '-client -hostname -hostport' if the type est CLIENT,
* '-server -port' si le type est SERVER,
* '-ia -depth' si le type est IA.

Exemples : 
-------------

	./connect4.x -keyboard -keyboard
	./connect4.x -keyboard -server -1200
	./connect4.x -client tesseract -1200 -keyboard
	./connect4.x -keyboard -ia 4

Aide :
-------------

Pour toute autre information :

	./connect4.x --help