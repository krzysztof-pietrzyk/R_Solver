#ifndef AlgorithmAction_hpp
#define AlgorithmAction_hpp

#include "../Algorithm.hpp"

class AlgorithmAction : public Algorithm
{
    /* 
    Abstract class for algorithms which take an action, 
    meaning they perform left or right clicks.
    The main difference from other algorithms is that this type of algorithm
    automatically checks whether the game is won/lost at the end.
    */
    public:

    AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmAction();

    AlgorithmStatus Run();

    protected:

    virtual AlgorithmStatus RunInternal() = 0;

    private:

    AlgorithmStatus CheckGameOverConditions();
};

#endif
