#ifndef AlgorithmFirstMove_hpp
#define AlgorithmFirstMove_hpp

#include "AlgorithmAction.hpp"

class AlgorithmFirstMove : public AlgorithmAction
{
    public:

    AlgorithmFirstMove(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmFirstMove();

    protected:

    unsigned int first_move_field;

    void RunInternal();

    private:

    static const unsigned int default_first_move_field;
};

#endif
