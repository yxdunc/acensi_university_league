# Conway's battle

##Goal

The goal is to code a player for the conway's battle which is a variant of famous conway game of life.

The only rule changed is: "When an empty case is dead and has 3 neighbours it become alive and take the color of the majority of the neighbours."

The players play turn by turn to position their cells and once each player has ~40 cells on the board the game of life simulation is launched. The player with the most cells alive after 500 iterations of the game of life, win.

Also the player has to compute in less than 2 seconds.
