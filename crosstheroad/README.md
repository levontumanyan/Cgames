# Cross the road game

## How to run the game

Clone the repository. Change directory into the repo then run make to build the executable. Finally run it and enjoy!
```
git clone itfibonacci/Cgames
cd Cgames/crosstheroad
make
./bin/crosstheroad
```

## How to play the game

- Press the up arrow to attempt to cross a lane
- Press the down arrow to back down into a previous lane
- Avoid the cars as you cross the road

## Todos

- level
  - draw level
  - add levels to the game
  - add a time limit for each level
  - add speed of cars
  - number of cars (density of cars)
  - number of lanes
  - number of safe lanes in between
- cars
  - add the functionality for cars to whiz by
  - add collision between the cars and the chicken
  - add the images of cars
- chicken
  - make sure it is possible to have multiple chickens to cross at some point - start with single one
- add an option to quit the game without control c
- add a score
- add a pause/resume game functionality

## Order of development

1. Create the game loop: Start by creating a simple game loop in main.c that will control the flow of your game.

2. Implement the player (chicken): Implement the player's functionality in player.c and player.h. This includes the player's movement and rendering.

3. Implement the road: Implement the road's functionality in road.c and road.h. This includes the road's rendering and movement.

4. Implement the cars: Implement the cars' functionality in car.c and car.h. This includes the cars' rendering, movement, and collision detection with the player.

5. Implement the levels: Implement the levels' functionality in game.c and game.h. This includes drawing the level, adding multiple levels, and adding a time limit for each level.

6. Add additional features: Once the basic game is working, you can start adding additional features like score, pause/resume functionality, sound effects, etc.

7. Testing: Write unit tests for your game components in the test directory. Make sure to test your game thoroughly to catch any bugs.

## Done

## Bugs at the moment

## Bugs resolved
