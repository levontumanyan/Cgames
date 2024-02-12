# Block breaker

## How to run the game
Clone the repository. Change directory into the repo then run make to build the executable. Finally run it and enjoy!
```
git clone itfibonacci/Cgames
cd Cgames/blockbreaker
make
./bin/blockbreaker
```

## How to play the game

## Todos
- create a game loop
- create a block struct - coordinate member, unsigned char length, unsigned char health (0..3)
- create levels when all the blocks are broken proceed to next level - function name constructlevel
	- accepts the level number
	- creates the appropriate number of blocks
	- displays the blocks on the screen
- Have a ball that moves to crush the blocks
- make sure blocks are not generated on top of each other
- add diagonal directions for the ball to move as well

## Done
- create a coordinate struct
- create a ncurses screen
- create the bottom bar - have it be moved with keyboard arrows first then later maybe with mouse
- add user input handling for the bottom bar to move
- check that the bottom bar doesn't run over the boundaries

## Current Bugs

## Resolved bugs

