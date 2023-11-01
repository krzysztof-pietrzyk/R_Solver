#ifndef LAYER_ONE_FIELD_SIGNATURE_HPP
#define LAYER_ONE_FIELD_SIGNATURE_HPP

// project includes

// std includes
#include <cstdint>

// forward declarations


struct LayerOneFieldSignature
{
    uint32_t field = 0;
    uint8_t flags_count = 0;
    uint8_t not_visible_count = 0;
    uint8_t field_value = 0;
};

#endif
