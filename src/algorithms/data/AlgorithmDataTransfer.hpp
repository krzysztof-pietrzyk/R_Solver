#ifndef ALGORITHM_DATA_TRANSFER_HPP
#define ALGORITHM_DATA_TRANSFER_HPP

// project includes
#include "ActionsDTO.hpp"
#include "BorderDTO.hpp"
#include "CombinationsDTO.hpp"
#include "FaceDTO.hpp"
#include "FactorialsDTO.hpp"
#include "SectionsDTO.hpp"
#include "SegmentsDTO.hpp"
#include "SubsegmentsDTO.hpp"

// std includes

// forward declarations


struct AlgorithmDataTransfer
{
    ActionsDTO actions_dto;
    BorderDTO border_dto;
    SectionsDTO sections_dto;
    SegmentsDTO segments_dto;
    SubsegmentsDTO subsegments_dto;
    FaceDTO face_dto;
    CombinationsDTO combinations_dto;
    FactorialsDTO factorials_dto;

    AlgorithmDataTransfer(GridDimensions grid_dim);

    void Clear();
};

#endif
