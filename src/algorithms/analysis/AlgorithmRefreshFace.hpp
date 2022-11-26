#ifndef ALGORITHM_REFRESH_FACE_HPP
#define ALGORITHM_REFRESH_FACE_HPP

#include "../Algorithm.hpp"

class AlgorithmRefreshFace : public Algorithm
{
    public:

    AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshFace();

    AlgorithmStatus Run() override;

    protected:

    void Clear();

    private:

    uint32_t& D_face_index;
    std::vector<uint32_t>& D_face;
    std::vector<bool>& D_is_face;
    std::vector<std::vector<uint32_t>>& D_segments_face;
};

#endif
