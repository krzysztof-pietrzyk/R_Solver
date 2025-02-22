\page Requirements_Generator Requirements: Generator

\anchor req-generator-functionality
|\ref req-generator-functionality "Generator: Functionality"|
|:-|
|Generator produces contents of a Grid.|
|\anchor req-generator-functionality-a \ref req-generator-functionality-a "a." Generator produces placement of mines on the Grid. The placement may be random, predetermined, or follow some specific rules.|
|\anchor req-generator-functionality-b \ref req-generator-functionality-b "b." Generator calculates values of \ref def-clue "Clues", after the placement of mines is already determined.|
|\anchor req-generator-functionality-c \ref req-generator-functionality-c "c." Generator can uncover some \ref def-field "Fields" if necessary (for example restoring state of the \ref def-board "Board" to a known state).|
|\anchor req-generator-functionality-d \ref req-generator-functionality-d "d." Generator can place flags on some fields if necessary (for example restoring state of the board to a known state).|
|\anchor req-generator-functionality-e \ref req-generator-functionality-e "e." Generator does not allow for producing defective grids, with incorrect clues or incorrect number of mines.|
