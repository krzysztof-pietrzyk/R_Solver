#ifndef GENERATOR_RANDOM_HPP
#define GENERATOR_RANDOM_HPP

#include "GeneratorInternal.hpp"
#include "RandomNumberGenerator.hpp"

enum GeneratorRandomType
{
    UNSAFE,
    GUARANTEED_SAFE,
    GUARANTEED_OPENING
};

class GeneratorRandom : public GeneratorInternal
{
    public:

    GeneratorRandom(GridAccessGeneratorIf& grid_, GeneratorRandomType type);

    ~GeneratorRandom();

    virtual void SetStartingField(uint32_t new_starting_field) override;

    protected:

    std::vector<uint32_t> current_template;
    uint32_t current_max;

    virtual void GenerateMinePositions() override;

    void CreateTemplate();

    void CopyTemplateToWorkingVector();

    private:

    GeneratorRandomType generator_type;
    uint32_t previous_starting_field;

    void ValidateGridDimensions();

    void CreateUnsafeTemplate();
    void CreateSafeTemplate();
    void CreateGuaranteedOpeningTemplate();
};

#endif
