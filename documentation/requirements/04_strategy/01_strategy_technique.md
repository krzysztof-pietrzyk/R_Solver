\page Requirements Requirements

\anchor req-strategy-technique
|\ref req-strategy-technique "Strategy: Technique" &emsp; Version: 1 &emsp; \ref tp-strategy-technique "Test Plan"|
|:-|
|Due to complexity, Strategy shall be divided into small, managable parts, called \ref def-technique "Techniques". A technique is an abstraction for a single analysis method a human player would perform when playing Minesweeper.|
|\anchor req-strategy-technique-a \ref req-strategy-technique-a "a." Techniques have access to the Grid via the View component, on the basis defined in \ref req-grid-data-access "grid data access" and \ref req-view-functionality "view functionality".|
|\anchor req-strategy-technique-b \ref req-strategy-technique-b "b." Techniques are allowed to store internal data, as well as share external data with other Techniques. Techniques shall not access each others' internal data.|
|\anchor req-strategy-technique-c \ref req-strategy-technique-c "c." A Technique only has one publicly available functionality, which is to be "activated". Any other functionality shall be done by other components (like for example retrieving statistics shall be done via \ref req-statistics "Statistics Component").|
|\anchor req-strategy-technique-d \ref req-strategy-technique-d "d." When activated, a Technique is applied to the entire \ref def-board "board" and a result is returned. The result indicates whether the Technique successfully performed moves, won or lost the game, or resulted in a forseen error. Techniques may add their own, unique result statuses if needed.|
|\anchor req-strategy-technique-e \ref req-strategy-technique-e "e." One activation shall be sufficient at any given time. In other words, there shall be no reason to apply the same Technique twice in a row.|
|\anchor req-strategy-technique-f \ref req-strategy-technique-f "f." Techniques shall be as small as possible. If a Technique can be split into smaller parts, it should be split, even if the resulting smaller Techniques will have to be applied together, one after another. The general rules to apply this requirement shall be as follows: If a Technique can be split into smaller parts that can be uniquely named, strongly consider splitting it (no "part1, part2" Technique names). If the resulting smaller Techniques would use the exact same internal data for operation, weakly consider not splitting it.|


\page Test_Plan Test Plan

\anchor tp-strategy-technique
|\ref req-strategy-technique "Strategy: Technique"|Test Category|Test Link|Comment|
|-|-|-|-|
|\anchor tp-strategy-technique-a \ref req-strategy-technique-a "req-strategy-technique-a"| | | |
|\anchor tp-strategy-technique-b \ref req-strategy-technique-b "req-strategy-technique-b"| | | |
|\anchor tp-strategy-technique-c \ref req-strategy-technique-c "req-strategy-technique-c"| | | |
|\anchor tp-strategy-technique-d \ref req-strategy-technique-d "req-strategy-technique-d"| | | |
|\anchor tp-strategy-technique-e \ref req-strategy-technique-e "req-strategy-technique-e"| | | |
|\anchor tp-strategy-technique-f \ref req-strategy-technique-f "req-strategy-technique-f"| | | |
