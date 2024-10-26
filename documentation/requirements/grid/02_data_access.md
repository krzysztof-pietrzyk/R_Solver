\page Requirements_Grid Requirements: Grid

\anchor req-grid-data-access
|Grid Data Access|
|-|
|Player can only access data, which the rules of the game permit the player to access.|
|\anchor req-grid-data-access-a **a.** Width and Height of the board (size) is always available to the player.|
|\anchor req-grid-data-access-b **b.** Total number of mines is always available to the player.|
|\anchor req-grid-data-access-c **c.** Information which squares contain mines is only available to the player if the game is finished.|
|\anchor req-grid-data-access-d **d.** Information which squares are visible to the player and how many visible squares there are is always available to the player.|
|\anchor req-grid-data-access-e **e.** Information which squares are flagged by the player and how many flagged squares there are is always available to the player.|
|\anchor req-grid-data-access-f **f.** Number of mines in the neighbourhood of a square is only available to the player if that square is visible.|
