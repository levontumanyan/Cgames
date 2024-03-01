# How to run the game
Clone the repository. Change directory into the repo then run make to build the executable. Finally run it and enjoy!
```
git clone itfibonacci/Cgames
cd Cgames/tictactoe
make
./bin/tictactoe
```

# How to play the game
Regular tictactoe rules

## Todos
- add a way for the player to choose the dimensions of the board once the game starts (add some limits to this)
- add a score and implement player 1, player 2
- add a computer option to play vs bot

## Done
- add a condition for the game to end in draw if all the boxes have been filled and no winner so far

## Bugs at the moment
- when trying to display a winning banner in the screen, right before a game is over. The last move that results in a win, gets shown for an instant then disappears (commented out display_winner_banner(display) in the file game.c line:77 until the bug is identified and fixed).

## Bugs resolved
