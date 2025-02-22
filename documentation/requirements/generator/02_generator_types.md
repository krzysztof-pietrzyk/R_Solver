\page Requirements_Generator Requirements: Generator

\anchor req-generator-types
|\ref req-generator-types "Generator: Types"|
|:-|
|Generator allows for providing Grid data according to different desired rules. The following are the examples of functional rules that the generator can follow.|
|\anchor req-generator-types-a \ref req-generator-types-a "a." Random mine distribution.|
|\anchor req-generator-types-b \ref req-generator-types-b "b." Random mine distribution, except the first left-clicked \ref def-field "Field" of the game can never be a mine. This assures that the game can't be lost on first click.|
|\anchor req-generator-types-c \ref req-generator-types-c "c." Random mine distribution, except the first left-clicked \ref def-field "Field" of the game has its \ref def-clue "Clue" equal to zero. This assures that the game starts with an \ref req-grid-zero-chain-reaction "Opening".|
|\anchor req-generator-types-d \ref req-generator-types-d "d." Random mine distribution, except some specific fields can't contain mines (i.e. no mines on the edges of the board).|
|\anchor req-generator-types-e \ref req-generator-types-e "e." Predetermined mine distribution, based on a previous state, past game, preset, or player's choosing. In this case, Generator may also place flags and uncover fields, to recreate any state of the board. See also \ref req-grid-state "Grid State".|
|\anchor req-generator-types-f \ref req-generator-types-f "f." Next combination. This rule allows the generator to iterate through all possible combinations of mines on the board, one at a time.|
