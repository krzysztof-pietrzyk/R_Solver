\page Requirements Requirements

\anchor req-statistics-element-types
|\ref req-statistics-element-types "Statistics: Element Types"|
|:-|
|Statistics can be gathered into the following types of objects.|
|\anchor req-statistics-element-types-a \ref req-statistics-element-types-a "a." Unsigned 64-bit integer. For example number of wins.|
|\anchor req-statistics-element-types-b \ref req-statistics-element-types-b "b." Unsigned 64-bit integer maximum. For example best win streak.|
|\anchor req-statistics-element-types-c \ref req-statistics-element-types-c "c." Unsigned 64-bit integer minimum. For example smallest number of openings on the Grid.|
|\anchor req-statistics-element-types-d \ref req-statistics-element-types-d "d." Unsigned 64-bit integer average, represented as a double precision floating point value. For example win/played ratio.|
|\anchor req-statistics-element-types-e \ref req-statistics-element-types-e "e." Double precision floating point maximum. For example largest cumulative risk of a won game.|
|\anchor req-statistics-element-types-f \ref req-statistics-element-types-f "f." Double precision floating point minimum. For example smallest probability of a mine.|
|\anchor req-statistics-element-types-g \ref req-statistics-element-types-g "g." Circular buffer of \ref req-grid-state "Grid States". For example last 100 Grid States, which contained an "8" \ref def-clue "Clue".|
|\anchor req-statistics-element-types-h \ref req-statistics-element-types-h "h." Unsigned 64-bit integer histogram. For example a distribution of clue values on the Grid.|
