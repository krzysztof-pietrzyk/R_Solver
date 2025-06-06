\page Detailed_Design_Grid Detailed Design: Grid

\tableofcontents

# Overview

Grid represents the functionalities of the Minesweeper board and is used via interfaces:
- GridViewIf - for display/GUI
- GridAccessPlayerReadIf - for clicking and analyzing the Grid in any way a human player should be allowed
- GridGeneratorIf - for feeding the Grid with newly generated games
- GridCommonIf - for reading general information about the Grid. This interface is included in all interfaces above

# Grid component design

```plantuml
@startuml diagram_grid_component_design

title Grid component design

interface GridCommonIf #PaleGreen {
    + {abstract} GridDimensions GetDimensions() const
    + {abstract} const std::vector<uint32_t>& GetNeighbors(uint32_t) const
    + {abstract} GridHash GetHash() const
}
interface GridGeneratorIf #PaleGreen {
    + {abstract} void SetMineFields(const CachedVector&)
    + {abstract} void SetFlaggedFields(const CachedVector&)
    + {abstract} void SetVisibleFields(const CachedVector&)
    + {abstract} void SetFieldValues(const std::vector<uint8_t>&)
    + {abstract} void Reset()
}
interface GridAccessPlayerReadIf #PaleGreen {
    + {abstract} const CachedVector& GetVisibleFields() const
    + {abstract} const CachedVector& GetFlaggedFields() const
    + {abstract} uint8_t GetFieldValue(uint32_t field) const
    + {abstract} PlayerActionResult SetVisible(uint32_t)
    + {abstract} PlayerActionResult SetFlag(uint32_t)
    + {abstract} bool IsLost() const
    + {abstract} bool IsWon() const
    + {abstract} void GiveUp()
}
interface GridViewIf #PaleGreen {
    + {abstract} const std::vector<FieldType>& GetFieldTypesToDisplay()
}

abstract class Grid #PaleGreen {
    # const GridDimensions dimensions
    # CachedVector mine_fields
    # CachedVector flagged_fields
    # CachedVector visible_fields
    # std::vector<uint8_t> field_values
    # std::vector<std::vector<uint32_t>> neighbors
    # bool is_lost
    + GridDimensions GetDimensions() const
    + const std::vector<uint32_t>& GetNeighbors(uint32_t) const
    + const CachedVector& GetVisibleFields() const
    + const CachedVector& GetFlaggedFields() const
    + uint8_t GetFieldValue(uint32_t) const
    + bool IsLost() const
    + bool IsWon() const
    + void GiveUp()
    + void SetMineFields(const CachedVector&)
    + void SetFlaggedFields(const CachedVector&)
    + void SetVisibleFields(const CachedVector&)
    + void SetFieldValues(const std::vector<uint8_t>&)
    + void Reset()
    + const std::vector<FieldType>& GetFieldTypesToDisplay()
    # bool CheckVisible(uint32_t) const
}

class GridInternal #PaleGreen {
    GridHash GetHash() const
    PlayerActionResult SetVisible(uint32_t)
    PlayerActionResult SetFlag(uint32_t)
}

abstract class Generator {
    # GridGeneratorIf& grid
}

abstract class Algorithm {

}

abstract class View {

}

class Solver {

}

GridGeneratorIf -up-|> GridCommonIf
GridAccessPlayerReadIf -up-|> GridCommonIf
GridViewIf -up-|> GridCommonIf
Grid -up-|> GridGeneratorIf
Grid -up-|> GridAccessPlayerReadIf
Grid -up-|> GridViewIf
GridInternal -up-|> Grid

Generator --> GridGeneratorIf : uses
Algorithm --> GridAccessPlayerReadIf : uses
View --> GridViewIf : uses
Solver o--> Grid : owns

@enduml
```
