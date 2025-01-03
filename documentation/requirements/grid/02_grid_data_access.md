\page Requirements_Grid Requirements: Grid

\anchor req-grid-data-access
|\ref req-grid-data-access "Grid Data Access"|
|:-|
|Player can only access data, which the rules of the game permit the player to access.|
|\anchor req-grid-data-access-a \ref req-grid-data-access-a "a." Width and Height of the board (size) is always available to the player.|
|\anchor req-grid-data-access-b \ref req-grid-data-access-b "b." Total number of mines is always available to the player.|
|\anchor req-grid-data-access-c \ref req-grid-data-access-c "c." Information which fields contain mines is only available to the player if the game is finished.|
|\anchor req-grid-data-access-d \ref req-grid-data-access-d "d." Information which fields are visible to the player and how many visible fields there are is always available to the player.|
|\anchor req-grid-data-access-e \ref req-grid-data-access-e "e." Information which fields are flagged by the player and how many flagged fields there are is always available to the player.|
|\anchor req-grid-data-access-f \ref req-grid-data-access-f "f." \ref def-clue "Clue" of a field is only available to the player if that field is visible.|
|\anchor req-grid-data-access-g \ref req-grid-data-access-g "g." Information about \ref req-grid-data-contents-g "field neighbours" is always available to the player.|
