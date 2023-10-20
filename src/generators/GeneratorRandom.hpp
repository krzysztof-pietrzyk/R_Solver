#ifndef GENERATOR_RANDOM_HPP
#define GENERATOR_RANDOM_HPP

#include "GeneratorInternal.hpp"
#include "RandomNumberGenerator.hpp"

class GeneratorRandom : public GeneratorInternal
{
    public:

    GeneratorRandom(GridGeneratorIf& grid_);

    ~GeneratorRandom();

    virtual void SetStartingField(uint32_t new_starting_field) override;

    protected:

    std::vector<uint32_t> current_template;
    uint32_t current_max;

    virtual void GenerateMinePositions() override;

    void CopyTemplateToWorkingVector();

    virtual void ValidateGridDimensions() = 0;

    virtual void CreateTemplate() = 0;

    private:

    uint32_t previous_starting_field;
};

#endif
