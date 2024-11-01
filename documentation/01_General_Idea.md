\page DOC_GeneralIdea General Idea

\tableofcontents

# General idea

The main goal of R_Solver project is to create a program, which solves games of [Minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game)).

This task is notoriously difficult and so far a **perfect** algorithm to solve Minesweeper games has not been discovered. While the rules of the game are simple and a high-level algorithm can easily be formulated, a naive implementation will often not be able to find a solution to the more difficult games. At the same time, a more sophisticated approach may take a very long time to compute - sometimes longer than the age of the universe - due to the exponential nature of the problem.

It's not clear how to implement the solving program. Therefore, a kind of "prototyping engine" for the solver shall be prepared, to test different approaches and measure various aspects of the solver's performance. The "prototyping engine" shall be a base, on which the solver is built.

For the purpose of this project, a **perfect** algorithm is an algorithm that:
- **Achieves the highest possible win ratio.**
    - The actual highest possible win ratio<sup>**[1]**</sup><sup>**[2]**</sup> is unknown.
- **Computes solutions in a reasonable amount of time.**
    - Due to the exponential nature of the problem, some calculations will be quick and some will be slow. It's been proven that [Minesweeper is NP-complete](https://www.minesweeper.info/articles/MinesweeperIsNPComplete.pdf). In this context it means that it's always possible to reverse-engineer a game, which will take exceedingly long to analyze, no matter what algorithm is used. However, using clever approaches it's possible to [almost always](https://en.wikipedia.org/wiki/Almost_surely) calculate the solution relatively quickly.
    - For the purposes of this project, a reasonable amount of time means that beginner, intermediate and expert games are _almost always_ completed within one second. Preferably much faster.
    - The upper bound of the exceptionally complex games is expected to be within 1 second for beginner, 1 minute for intermediate and 1 hour for expert.
- **Performs the same moves when ran multiple times on the same board.**
    - Removing randomness from the algorithm allows for making concrete statements about the algorithm's performance<sup>**[3]**</sup><sup>**[4]**</sup>.

---
<sup>**[1]**</sup> It's expected to be between 91% - 93% for beginner, 78% - 82% for intermediate and 40% - 43% for expert.

<sup>**[2]**</sup> For a given size and number of mines, the number of possible boards is always finite. Therefore a true win ratio of an algorithm must be a rational number. For example, the number of possible beginner boards is 81!/(71!*10!) = 1 878 392 407 320. Consider an experiment where you run a solver algorithm on every single one of those boards. Let's say it wins 1 690 553 166 588 times. The win ratio is exactly 90%. Now consider all possible algorithms capable of solving beginner boards. Some will be worse and some will be better but there must also be an algorithm or a family of algorithms that achieve the highest win ratio of all.

<sup>**[3]**</sup> If an algorithm uses randomness for decision making, each time you conduct the experiment<sup>**[2]**</sup>, the result will be slightly better or slightly worse. The presence of luck is not good for comparing performance of different algorithms between each other. In principle, an algorithm could even get lucky billions of times in a row and achieve 100% win ratio. It doesn't make it the best algorithm.

<sup>**[4]**</sup> This constraint implies that non-exhaustive brute force methods shall not be used.
