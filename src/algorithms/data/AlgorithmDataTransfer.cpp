#include "AlgorithmDataTransfer.hpp"

AlgorithmDataTransfer::AlgorithmDataTransfer(GridDimensions grid_dim)
    : border_dto(BorderDTO(grid_dim)),
    sections_dto(SectionsDTO(grid_dim)),
    segments_dto(SegmentsDTO(grid_dim)),
    subsegments_dto(SubsegmentsDTO(grid_dim)),
    face_dto(FaceDTO(grid_dim)),
    combinations_dto(CombinationsDTO(grid_dim)),
    factorials_dto(FactorialsDTO(grid_dim))
{
    LOGGER(LogLevel::INIT) << "AlgorithmDataTransfer";
    LOGGER(LogLevel::INIT) << "GridDimensions are: " <<
        int(grid_dim.width) << "x" << int(grid_dim.height) << ", size " << int(grid_dim.size) <<
        ", mines " << int(grid_dim.mines) << ", safe " << int(grid_dim.safe);
}

void AlgorithmDataTransfer::Clear()
{
    // Not all DTOs require something to be cleared
    border_dto.Clear();
    sections_dto.Clear();
    segments_dto.Clear();
}
