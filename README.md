# How to run the game
Clone the repository. Change directory into the repo then run make to build the executable. Finally run it and enjoy!
```
git clone https://github.com/itfibonacci/snake
cd snake
make
./bin/snake
```

# Todos
- add emoji support ( utf-8 ) - lncursesw looks like is a bit more complicated in terms of dependencies. Users will have to install it separately and I am not happy with that approach.

# Done
- We need a game loop
- Need a function that is responsible for outputting random food on the screen
- Need to keep track of the snake's body, direction, (speed)
- Collision detection
- Input handling to change the snake's direction
- need to properly remove the tail from the screen as the snake moves
- add to the collision the case where the snake collides with its own body
- when the snake collides and the game over banner is printed. if the player quickly presses buttons it exits too quickly without the player having time to see the score - just add a one second delay then wait for a user input to exit 
- add a feature where if u press the space bar it moves faster
- when the snake is going in a certain direction dont allow key press of 180 degrees direction - example: if up no down

## Bugs at the moment
- The game only finishes when the snake collides with the top and left corners not left and bottom. - done
