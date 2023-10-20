#ifndef ALGORITHM_FACE_HPP
#define ALGORITHM_FACE_HPP

#include "../Algorithm.hpp"

class AlgorithmFace : public Algorithm
{
    public:

    AlgorithmFace(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmFace();

    AlgorithmStatus Execution() override;

    protected:

    void Clear();

    private:

    uint32_t& D_face_index;
    std::vector<uint32_t>& D_face;
    std::vector<bool>& D_is_face;
    std::vector<std::vector<uint32_t>>& D_segments_face;
};

#endif
