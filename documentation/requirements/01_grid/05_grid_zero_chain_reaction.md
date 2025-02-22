\page Requirements Requirements

\anchor req-grid-zero-chain-reaction
|\ref req-grid-zero-chain-reaction "Grid: Zero Chain Reaction"|
|:-|
|\anchor req-grid-zero-chain-reaction-a \ref req-grid-zero-chain-reaction-a "a." When a field is being uncovered and that field has no mines in its neighbourhood (\ref def-clue "Clue" is equal to 0), the neighbourhood fields automatically become uncovered. This logic is then applied again to any fields that have been uncovered this way. If there are multiple adjacent fields, which don't have mines in their neighbourhood, this triggers a chain reaction, which uncovers them all.|
|\anchor req-grid-zero-chain-reaction-b \ref req-grid-zero-chain-reaction-b "b." If the chain reaction encounters a flagged field, it first removes the flag and then uncovers the field. This can happen if the player placed a flag incorrectly.|
