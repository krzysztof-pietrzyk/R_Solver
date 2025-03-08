\page Requirements Requirements: Statistics

\anchor req-statistics-functionality
|\ref req-statistics-functionality "Statistics: Functionality"|
|:-|
|\anchor req-statistics-functionality-a \ref req-statistics-functionality-a "a." Statistics data is gathered from one or multiple \ref req-game "Game" instances into a single common collection.|
|\anchor req-statistics-functionality-b \ref req-statistics-functionality-b "b." Each distinct value that is being collected as statistics data is its own separate "Element" object. The Element object knows its own name (description string) and how to handle the data it represents. See also \ref req-statistics-element-types "Element Types".|
|\anchor req-statistics-functionality-c \ref req-statistics-functionality-c "c." The logic of when and how to gather the data is located in the owner (producer) of the Element object. The producer knows its name (description string) and a list of Elements it owns. Statistics data can be produced by \ref req-strategy-technique "Techniques", \ref req-generator "Generators" and \ref req-game "Games".|
|\anchor req-statistics-functionality-d \ref req-statistics-functionality-d "d." Statistics data can be generated at any point during Game runtime, but can only be gathered (accessed from outside) after the Game is finished.|
|\anchor req-statistics-functionality-e \ref req-statistics-functionality-e "e." Most statistics data is aggregated: not associated with a specific loop of a Game. For example, the number of flags placed in all Game loops is added together into a single number, instead of keeping track how many flags were placed in each Game loop separately. See also \ref req-statistics-functionality-f "point f.".|
|\anchor req-statistics-functionality-f \ref req-statistics-functionality-f "f." In some cases, statistics data can be associated with a specific Game loop or Grid State. For example, data collected this way may be related to rarely occurring game situations. See also \ref req-statistics-element-types-g "Circular Buffer of Grid States".|
|\anchor req-statistics-functionality-g \ref req-statistics-functionality-g "g." Some statistics data may be time-expensive to gather, for example calculating 3BV metric of a Grid. It shall be configurable by the user whether those statistics data are gathered or not.|
|\anchor req-statistics-functionality-h \ref req-statistics-functionality-h "h." Statistics data can be collected (from producers to common collection) upon a trigger from the outside, or after every finished game. User chooses which of those two modes is used.|
