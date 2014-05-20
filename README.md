Connect 4 in C
===============
Project
---------------
Implementation of the game "Connect 4" in C, where players can play on a same computer (keyboard/keyboard), or on differente ones (server/client). An IA (alpha/
beta algorithm) is also implemented.

Play
--------------

Different types of players are implemented : 

	* type KEYBOARD
	* type SERVER
	* type CLIENT
	* type IA

When you want to play, (after using the Makefile), juste try : ./connect4.x [player1] [player2], where [player] is :

	* '-keyboard' if the type is KEYBOARD,
	* '-client -hostname -hostport' if the type is CLIENT,
	* '-server -port' if the type is SERVER,
	* '-ia -depth' if the type is IA.

Exemples : 

	* 1 VS 1 on the same computer : ./connect4.x -keyboard -keyboard,
	* launch a server (and play as player 1) : ./connect4.x -keyboard -server -port_number,
	* launch a client (and play as player 2) : ./connect4.x -client -hostname -hostport -keyboard,
	* play against an IA : ./connect4.x -keyboard -ia 5,
	* ...

Issues
-------------

Until now, the IA isn't really efficient, as the heuristic remains really basic. You can find IA's dependancies in the file pond.c