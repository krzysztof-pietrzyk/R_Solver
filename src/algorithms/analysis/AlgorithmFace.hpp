#ifndef ALGORITHM_FACE_HPP
#define ALGORITHM_FACE_HPP

// project includes
#include "AlgorithmAnalysis.hpp"

// std includes

// forward declarations


class AlgorithmFace : public AlgorithmAnalysis
{
    public:

    AlgorithmFace(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmFace();

    protected:

    AlgorithmStatus Execution() override;

    private:

    SectionsDTO& sections_dto;
    SegmentsDTO& segments_dto;
    FaceDTO& face_dto;

    void Clear();
};

#endif
