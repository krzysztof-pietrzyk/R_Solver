\page Requirements_Grid Requirements: Grid

\anchor req-grid-state
|\ref req-grid-state "Grid: State"|
|:-|
|State of Grid can be stored into text.|
|\anchor req-grid-state-a \ref req-grid-state-a "a." State of Grid can be stored into text, in form of printable characters. The text shall be as short as possible.|
|\anchor req-grid-state-b \ref req-grid-state-b "b." State of Grid can be restored from a provided text, including positions of mines, positions of flags and visible clues. See also \ref req-generator-types-e "Generator: Predetermined".|
|\anchor req-grid-state-c \ref req-grid-state-c "c." The text, which stores the state of Grid is not encrypted.|
|\anchor req-grid-state-d \ref req-grid-state-d "d." The text, which stores the state of Grid is not a simple RNG seed. See also \ref req-generator-randomness-b "generator randomness".|
