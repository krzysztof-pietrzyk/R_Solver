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

    std::vector<unsigned int>& face;
    std::vector<bool>& is_face;
    std::vector<std::vector<unsigned int>>& segments_face;
    std::vector<unsigned int>& segments;
    std::vector<unsigned int>& segments_starting_indexes;
    std::vector<unsigned int>& segments_l;
    std::vector<Section>& sections;

    void Clear();
};

#endif
