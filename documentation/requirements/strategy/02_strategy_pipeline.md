\page Requirements_Strategy Requirements: Strategy

\anchor req-strategy-pipeline
|\ref req-strategy-pipeline "Strategy: Pipeline"|
|:-|
|Strategy component arranges \ref def-technique "Techniques" into a Strategy Pipeline.|
|\anchor req-strategy-pipeline-a \ref req-strategy-pipeline-a "a." Strategy Pipeline decides which Technique shall be applied next, based on the result of the previous applied Technique.|
|\anchor req-strategy-pipeline-b \ref req-strategy-pipeline-b "b." For a Strategy Pipeline to be valid, every possible result of each used Technique shall have an assigned next Technique. The next Technique can't be the same one as the previous one (see \ref req-strategy-technique-e "Strategy: Technique e."). Validity of the Strategy Pipeline shall be verified once, upon creation, before it is used.|
|\anchor req-strategy-pipeline-c \ref req-strategy-pipeline-c "c." Multiple Strategy Pipelines may exist. In other words, Techniques can be arranged in different ways by the Strategy component. A Technique itself doesn't define which Technique is executed next.|
|\anchor req-strategy-pipeline-d \ref req-strategy-pipeline-d "d." Strategy Pipeline finishes execution when the game is won or lost.|
|\anchor req-strategy-pipeline-e \ref req-strategy-pipeline-e "e." Strategy Pipeline can be slowed down (delay after each Technique is applied) or paused entirely.|
