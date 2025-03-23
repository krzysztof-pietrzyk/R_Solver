\page Requirements Requirements

\anchor req-game-states
|\ref req-game-states "Game: States" &emsp; Version: 1 &emsp; \ref tp-game-states "Test Plan"|
|:-|
|Operation of Game is described as transitioning between states.|
|\anchor req-game-states-a \ref req-game-states-a "a." Game's default state after creation is Unconfigured. In this state, the Game can be \ref req-game-configuration "Configured".|
|\anchor req-game-states-b \ref req-game-states-b "b." Once Game is configured, it can be commanded to Start. Starting the Game begins the loop of Grid generation, playing until finish and then generating again.|
|\anchor req-game-states-c \ref req-game-states-c "c." Once Game is Started, it can be Paused. Pausing the Game temporarily stops the execution of the loop before the next Technique is applied.|
|\anchor req-game-states-d \ref req-game-states-d "d." Once the Game is Paused, it can be Resumed. Resuming a paused game results in continuing the execution of the loop from the same state as when it was paused.|
|\anchor req-game-states-e \ref req-game-states-e "e." Once the Game is Paused, it can be Stopped. Stopping a Game clears its internal state reverts it to an Unconfigured state.|


\page Test_Plan Test Plan

\anchor tp-game-states
|\ref req-game-states "Game: States"|Test Category|Test Link|Comment|
|-|-|-|-|
|\anchor tp-game-states-a \ref req-game-states-a "req-game-states-a"| | | |
|\anchor tp-game-states-b \ref req-game-states-b "req-game-states-b"| | | |
|\anchor tp-game-states-c \ref req-game-states-c "req-game-states-c"| | | |
|\anchor tp-game-states-d \ref req-game-states-d "req-game-states-d"| | | |
|\anchor tp-game-states-e \ref req-game-states-e "req-game-states-e"| | | |
