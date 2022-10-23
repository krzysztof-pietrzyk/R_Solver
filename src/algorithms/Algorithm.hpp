#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "../grid/GridManager.hpp"
#include "AlgorithmDataStorage.hpp"
#include "AlgorithmStatus.hpp"

class Algorithm
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataStorage and GridManager
    */
    public:
    
    Algorithm(GridManager& grid_, AlgorithmDataStorage& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run() = 0;

    protected:

    const GridManager& grid;

    const AlgorithmDataStorage& data;

    void LeftClick(const unsigned int field) const;

    void RightClick(const unsigned int field) const;

    unsigned char FieldValue(const unsigned int field) const;

    GridManager& GetModifiableGridManagerReference() const;

    AlgorithmDataStorage& GetModifiableAlgorithmDataStorageReference() const;

    private:

    GridManager& _grid;

    AlgorithmDataStorage& _data;
};

#endif
