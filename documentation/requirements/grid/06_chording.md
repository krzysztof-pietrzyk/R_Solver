\page Requirements_Grid Requirements: Grid

\anchor req-grid-chording
|Grid Chording|
|-|
|Chording is an action performed by the player, which may uncover multiple fields with a single left click.|
|\anchor req-grid-chording-a **a.** If the player left-clicks a visible field, consider fields in the neighbourhood of that field. If the number of flags is equal to the \ref def-clue "Clue" of that field, all covered fields become uncovered.|
|\anchor req-grid-chording-b **b.** If this results in a mine being uncovered, the game is immediately lost, \ref req-grid-left-click-b "as normal".|
