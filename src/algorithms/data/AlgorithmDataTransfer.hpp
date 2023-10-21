#ifndef ALGORITHM_DATA_TRANSFER_HPP
#define ALGORITHM_DATA_TRANSFER_HPP

#include "../../utils/Logger.hpp"
#include "../../grid/GridDimensions.hpp"

#include "ActionsDTO.hpp"
#include "BorderDTO.hpp"
#include "SectionsDTO.hpp"
#include "SegmentsDTO.hpp"
#include "SubsegmentsDTO.hpp"
#include "FaceDTO.hpp"
#include "CombinationsDTO.hpp"
#include "FactorialsDTO.hpp"

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
