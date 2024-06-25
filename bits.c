#include <stdint.h>

/**
 * Converts a floating-point number in bit representation to its equivalent
 * as a float value.
 */
float fp32_from_bits(uint32_t bits);

/**
 * Converts a floating-point number from the float format to its bit
 * representation.
 */
uint32_t fp32_to_bits(float value);

union FP32 {
    uint32_t as_bits;
    float    as_value;
};

/**
 * Converts a floating-point number in bit representation to its equivalent
 * as a float value.
 */
float fp32_from_bits(uint32_t bits) {
    union FP32 fp32 = {.as_bits = bits};
    return fp32.as_value;
}

/**
 * Converts a floating-point number from the float format to its bit
 * representation.
 */
uint32_t fp32_to_bits(float value) {
    union FP32 fp32 = {.as_value = value};
    return fp32.as_bits;
}
