#ifndef AlgorithmRefreshFace_hpp
#define AlgorithmRefreshFace_hpp

#include "../Algorithm.hpp"

class AlgorithmRefreshFace : public Algorithm
{
    public:

    AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshFace();

    AlgorithmStatus Run();

    protected:

    void Clear();

    private:

    unsigned int& D_face_index;
    std::vector<unsigned int>& D_face;
    std::vector<bool>& D_is_face;
    std::vector<std::vector<unsigned int>>& D_segments_face;
};

#endif
