\page DOC_Requirements 02 Requirements

\tableofcontents

# Solver Engine Requirements

This section contains requirements for the Solver Engine.

## Component: Grid Requirements

Grid component is an abstraction for the Minesweeper game board, implementing features like left clicks, right clicks and access control to the squares data.

|Engine Grid Data Contents <a id="$~53b0466c"></a>|
|-|
|Grid contains information about state of the board.|
|**a.** <a id="$~e93d531d"></a> Width and Height of the board (size).|
|**b.** <a id="$~bab9887f"></a> Total number of mines.|
|**c.** <a id="$~544f0ab3"></a> Information which squares contain mines.|
|**d.** <a id="$~22f16924"></a> Information which squares are visible to the player and how many visible squares there are.|
|**e.** <a id="$~ede4812f"></a> Information which squares are flagged by the player and how many flagged squares there are.|
|**f.** <a id="$~174c1320"></a> [Clue](05_Dictionary_of_Concepts.md#$~80af1ada) of each square (number of mines in the neighbourhood of that square).|

|Engine Grid Data Access <a id="$~cb6545f1"></a>|
|-|
|Player can only access data, which the rules of the game permit the player to access.|
|**a.** <a id="$~34c19906"></a> Width and Height of the board (size) is always available to the player.|
|**b.** <a id="$~3452bee5"></a> Total number of mines is always available to the player.|
|**c.** <a id="$~e789ed4e"></a> Information which squares contain mines is only available to the player if the game is finished.|
|**d.** <a id="$~128fe573"></a> Information which squares are visible to the player and how many visible squares there are is always available to the player.|
|**e.** <a id="$~361bd967"></a> Information which squares are flagged by the player and how many flagged squares there are is always available to the player.|
|**f.** <a id="$~b196dd53"></a> Number of mines in the neighbourhood of a square is only available to the player if that square is visible.|

|Engine Grid Left Click Functionality <a id="$~7161862a"></a>|
|-|
|Player can left-click any square.|
|**a.** <a id="$~39ca2c9a"></a> If the player left-clicks a covered square, that square becomes visible. See also [Zero Chain Reaction](#$~7293c5bc).|
|**b.** <a id="$~b9dd5682"></a> If the player left-clicks a covered square, which contains a mine, the game immediately ends in a loss for the player.|
|**c.** <a id="$~78c5c6b6"></a> If the player left-clicks a flagged square, nothing happens.|
|**d.** <a id="$~707ea419"></a> If the player left-clicks a visible square, nothing happens or chording is used. See also [Chording](#$~961c88b1).|
|**e.** <a id="$~7c0354cf"></a> If the player left-clicks any field while the game is finished, nothing happens.|

|Engine Grid Right Click Functionality <a id="$~2ab18af2"></a>|
|-|
|The player can right-click any field.|
|**a.** <a id="$~077c330a"></a> If the player right-clicks a covered field, that field becomes flagged.|
|**b.** <a id="$~340c33a7"></a> If the player right-clicks a flagged field, that field stops being flagged and becomes covered.|
|**c.** <a id="$~f003796c"></a> If the player right-clicks a visible field, nothing happens.|
|**d.** <a id="$~46675b82"></a> If the player right-clicks any field while the game is finished, nothing happens.|

|Engine Grid Zero Chain Reaction <a id="$~7293c5bc"></a>|
|-|
|**a.** <a id="$~b9c080c6"></a> When a field is being uncovered and that field has no mines in its neighbourhood, the neighbourhood fields automatically become uncovered. This logic is then applied again to any fields that have been uncovered this way. If there are multiple adjacent fields, which don't have mines in their neighbourhood, this triggers a chain reaction, which uncovers them all.|
|**b.** <a id="$~de17fa41"></a> If the chain reaction encounters a flagged field, it first removes the flag and then uncovers the field. This can only happen if the player placed a flag on a field without a mine beforehand.|

|Engine Grid Chording <a id="$~961c88b1"></a>|
|-|
|Chording is an action performed by the player, which may uncover multiple fields with a single left click.|
|**a.** <a id="$~5484072c"></a> If the player left-clicks a visible field, consider fields in the neighbourhood of that field. If the number of flags is equal to the [Clue](05_Dictionary_of_Concepts.md#$~80af1ada) of that field, all covered fields become uncovered.|
|**b.** <a id="$~85c38ac5"></a> If this results in a mine being uncovered, the game is immediately lost, [as normal](#$~b9dd5682).|

## Component: Generator Requirements



## Component: View Requirements



## Component: Algorithm Requirements



## Component: Solver Requirements



## Component: Statistics Requirements



## Component: Configuration Manager Requirements



# Example Requirements Section Level 1



## Example Requirements Section Level 2



### Example Requirements Section Level 3

|Example Name <a id="$~00000000"></a>|
|-|
|Example description.|
