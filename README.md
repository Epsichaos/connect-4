Connect 4 in C
===============
Project
---------------

Implementation of the game "Connect 4" in C, where players can play on a same computer (keyboard/keyboard), or 
on differente ones (server/client). An IA (alpha/beta algorithm) is also implemented.

Play
--------------

Different types of players are implemented : 

* type KEYBOARD
* type SERVER
* type CLIENT
* type IA

When you want to play, (after using the Makefile), juste try : ./connect4.x [player1] [player2], 
where [player] is :

* '-keyboard' if the type is KEYBOARD,
* '-client -hostname -hostport' if the type is CLIENT,
* '-server -port' if the type is SERVER,
* '-ia -depth' if the type is IA.

Exemples : 
-------------

	./connect4.x -keyboard -keyboard
	./connect4.x -keyboard -server -host_port
	./connect4.x -client -host_name -host_port -keyboard
	./connect4.x -keyboard -ia -ia_depth

If you want any information on how to use the .x created, just run :

	./connect4.x --help


Issues
-------------

Until now, the IA isn't really efficient, as the heuristic remains really basic. 
You can find IA's dependancies in the file pond.c