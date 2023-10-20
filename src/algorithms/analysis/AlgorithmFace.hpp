#ifndef ALGORITHM_FACE_HPP
#define ALGORITHM_FACE_HPP

#include "AlgorithmAnalysis.hpp"

class AlgorithmFace : public AlgorithmAnalysis
{
    public:

    AlgorithmFace(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmFace();

    protected:

    AlgorithmStatus Execution() override;

    private:

    void Clear();
};

#endif
