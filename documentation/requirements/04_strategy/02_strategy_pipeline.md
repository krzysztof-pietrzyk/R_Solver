\page Requirements Requirements

\anchor req-strategy-pipeline
|\ref req-strategy-pipeline "Strategy: Pipeline" &emsp; Version: 1 &emsp; \ref tp-strategy-pipeline "Test Plan"|
|:-|
|Strategy component arranges \ref def-technique "Techniques" into a Strategy Pipeline.|
|\anchor req-strategy-pipeline-a \ref req-strategy-pipeline-a "a." Strategy Pipeline decides which Technique shall be applied next, based on the result of the previous applied Technique.|
|\anchor req-strategy-pipeline-b \ref req-strategy-pipeline-b "b." For a Strategy Pipeline to be valid, every possible result of each used Technique shall have an assigned next Technique. The next Technique can't be the same one as the previous one (see \ref req-strategy-technique-e "Strategy: Technique e."). Validity of the Strategy Pipeline shall be verified once, upon creation, before it is used.|
|\anchor req-strategy-pipeline-c \ref req-strategy-pipeline-c "c." Multiple Strategy Pipelines may exist. In other words, Techniques can be arranged in different ways by the Strategy component. A Technique itself doesn't define which Technique is executed next.|
|\anchor req-strategy-pipeline-d \ref req-strategy-pipeline-d "d." Strategy Pipeline finishes execution when the game is won or lost.|
|\anchor req-strategy-pipeline-e \ref req-strategy-pipeline-e "e." Strategy Pipeline can be slowed down (delay after each Technique is applied) or paused entirely.|


\page Test_Plan Test Plan

\anchor tp-strategy-pipeline
|\ref req-strategy-pipeline "Strategy: Pipeline"|Test Category|Test Link|Comment|
|-|-|-|-|
|\anchor tp-strategy-pipeline-a \ref req-strategy-pipeline-a "req-strategy-pipeline-a"| | | |
|\anchor tp-strategy-pipeline-b \ref req-strategy-pipeline-b "req-strategy-pipeline-b"| | | |
|\anchor tp-strategy-pipeline-c \ref req-strategy-pipeline-c "req-strategy-pipeline-c"| | | |
|\anchor tp-strategy-pipeline-d \ref req-strategy-pipeline-d "req-strategy-pipeline-d"| | | |
|\anchor tp-strategy-pipeline-e \ref req-strategy-pipeline-e "req-strategy-pipeline-e"| | | |
