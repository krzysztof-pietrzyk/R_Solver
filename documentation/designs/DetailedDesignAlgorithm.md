\page Detailed_Design_Algorithm Detailed Design: Algorithm

\tableofcontents

# Overview

Playing a game of Minesweeper requires the use of many different techniques. Those techniques are represented in code by various Algorithm classes. Those classes expose one public method, which is called to apply the technique to the current state of the Grid. This implementation allows the Algorithms to be arranged in different orders and configurations (strategies), to achieve different results.

# Terminology

**Technique** - A technique used to play a Minesweeper game, implemented in an Algorithm class. There are many techniques for different types of situations encountered in the game.

**Strategy** - An arrangement of techniques, defining their order and transitions between them. It defines how to play a game of Minesweeper from start to finish. Different strategies may be used to achieve different desired effects (win ratio, speed, efficiency, etc.).

# Algorithm types

Minesweeper techniques are divided into 3 functional groups.

## Analysis

Those are techniques, which <b>only observe the Grid</b>. The purpose of analysis Algorithms is to gather some specific information about the Grid. This information is then used by other Algorithms to make decisions. Some analysis Algorithms rely on other information provided by other analysis Algorithms, which forces a certain order of execution.

## Decision

Those are techniques, which <b>decide which fields should be left-clicked or right-clicked</b>. Those decisions are made based on information provided by analysis Algorithms, which must be executed beforehand. A given decision Algorithm is usually coupled with one or more analysis Algorithms, which provide the information necessary for making the decision.

## Action (TODO)

Those are techniques, which <b>perform clicks on the Grid</b>. Having the information about safe and unsafe fields from preceding decision Algorithms, the action Algorithm may choose which clicks to perform, and in what order. This is useful for imitating the way a human plays the game or for achieving desired efficiency of clicks.

# Algorithm component design

```plantuml
@startuml diagram_algorithm_component_design

title Algorithm component design

abstract class Algorithm #PaleGreen {
    - GridAccessPlayerReadIf& _grid
    - AlgorithmDataTransfer& _data
    + AlgorithmStatus Run()
    # {abstract} AlgorithmStatus Execution()
} 
note bottom of Algorithm: \
calling <b>Run()</b> applies the Algorithm to current state of <b>Grid</b>. \n\
The actual "technique" is implemented inside of specific \n\
<b>Algorithm</b> implementations, in <b>Execution()</b>.

class "[specific Algorithm implementations]" as AlgorithmImpls #PaleGreen {
    # AlgorithmStatus Execution() override
}
note bottom of AlgorithmImpls: \
This is where the Minesweeper solving \n\
techniques are implemented. The techniques \n\
are divided into 3 categories: Analysis, \n\
Decision and Action.

class AlgorithmDataTransfer #PaleGreen {
    + [intermittent data used by algorithms]
    + void Clear()
}
note bottom of AlgorithmDataTransfer: \
Contains all data generated and used by <b>Algorithms</b>. \n\
Serves as a Data Transfer Object between <b>Algorithms</b>.

class AlgorithmExecutor #PaleGreen {
    + bool RunAll()
    + const std::map<AlgorithmType, Algorithm*>& GetAlgorithmsMap()
    - GridAccessPlayerReadIf* grid
    - AlgorithmDataTransfer* data
    - AlgorithmTransitionManager transitions
    - std::map<AlgorithmType, Algorithm*> algorithms
    - void CreateAlgorithms()
}
note top of AlgorithmExecutor: \
Contains one <b>AlgorithmTransitionManager</b>. \n\
Owns one <b>AlgorithmDataTransfer</b>. Owns many <b>Algorithms</b>. \n\
Is responsible for calling <b>Run()</b> on <b>Algorithms</b> \n\
in the order dictated by <b>AlgorithmTransitionManager</b>. \n\n\
<b>GetAlgorithmsMap</b> is used outside, to register \n\
<b>Algorithms</b> as <b>StatisticsProducers</b>.

class AlgorithmTransitionManager #PaleGreen {
    + void AddTransition(AlgorithmType type, AlgorithmStatus status, AlgorithmType next_type)
    + void DeleteTransition(AlgorithmType type, AlgorithmStatus status)
    + AlgorithmType GetNext(AlgorithmType type, AlgorithmStatus status)
    + void SetStartingAlgorithm(AlgorithmType new_starting_algorithm)
    + AlgorithmType GetStartingAlgorithm()
    - std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>> transitions
    - AlgorithmType starting_algorithm
    - {static} const AlgorithmType default_starting_algorithm
    - void ConfigureDefaultTransitions()
}
note bottom of AlgorithmTransitionManager: \
Manages and provides the order of execution \n\
of <b>Algorithms</b> to <b>AlgorithmExecutor</b>

class StatisticsProducer {
    + const StatisticsProducerStruct& GetStatisticsCollectors()
    # StatisticsProducerStruct statistics_collectors
}

class Solver {
    - AlgorithmExecutor*
}

interface GridAccessPlayerReadIf

AlgorithmImpls "many" --|> Algorithm
Algorithm --> AlgorithmDataTransfer : uses
Algorithm --|> StatisticsProducer : is
Algorithm --> GridAccessPlayerReadIf : uses
AlgorithmExecutor *-up-> AlgorithmTransitionManager : contains >
AlgorithmExecutor o--> AlgorithmDataTransfer : owns
AlgorithmExecutor o--> "many" Algorithm : owns
Solver o-up-> AlgorithmExecutor : owns

@enduml
```

# Strategies

A **Strategy** may be thought of as a state machine of Algorithms, where each Algorithm is a state.

Different **Strategies** are implemented in AlgorithmTransitionManager by defining transitions between Algorithms. A **Transition** determines which Algorithm shall be executed next, based on which Algorithm was executed previously and what was its AlgorithmStatus. Each Algorithm may be used as a part of multiple **Strategies**. Within a single **Strategy**, each Algorithm may have multiple **Transitions** (maximum one per each possible **AlgorithmStatus** it may return).

<span style="color:LightBlue">**Analysis Algorithms** are coloured Blue.</span>

<span style="color:LightGreen">**Decision Algorithms** are coloured Green.</span>

<span style="color:Goldenrod">**Action Algorithms** are coloured Gold.</span>

## Max win ratio strategy (default)

This strategy maximizes win ratio. Second priority is fast execution time. Click efficiency and human similarity are not considered at all.

```plantuml
@startuml diagram_algorithm_state_machine

title AlgorithmTransitionManager default order of execution

hide empty description

state Border #LightBlue
state Combinations #LightBlue
state Face #LightBlue
state Sections #LightBlue
state Segments #LightBlue
state Subsegments #LightBlue

state CombinationsLeastRisky #LightGreen
state CombinationsSafeMoves #LightGreen
state FirstMove #LightGreen
state GiveUp #LightGreen
state LayerOne #LightGreen
state LayerTwo #LightGreen
state SimpleCorners #LightGreen

[*] -[#Black,bold]-> FirstMove
FirstMove -[#Green,bold]-> Border : Success

SimpleCorners -[#Green,bold]-> Border : Success
SimpleCorners -[#Red,bold]-> CombinationsLeastRisky : No_Moves

Border -[#Black,bold]-> LayerOne

LayerOne -[#Green,bold]-> Border : Success
LayerOne -[#Red,bold]-> Sections : No_Moves

Sections -[#Black,bold]-> LayerTwo

LayerTwo -[#Green,bold]-> Border : Success
LayerTwo -[#Red,bold]-> Segments : No_Moves

Segments -[#Black,bold]-> Subsegments

Subsegments -[#Black,bold]-> Face

Face -[#Black,bold]-> Combinations

Combinations -[#Black,bold]-> CombinationsSafeMoves
Combinations -[#Red,bold]-> GiveUp : Failure (too much data)

CombinationsSafeMoves -[#Green,bold]-> Border : Success
CombinationsSafeMoves -[#Red,bold]-> SimpleCorners : No_Moves

CombinationsLeastRisky -[#Green,bold]-> Border : Success
CombinationsLeastRisky -[#Red,bold]-> GiveUp : No_Moves

GiveUp -[#Black,bold]-> [*]

@enduml
```
