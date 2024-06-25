#include <stdint.h>

typedef union Float32 {
    uint32_t as_bits;
    float    as_value;
} float32_t;

// google brain half-precision bfloat16
typedef struct BFloat16 {
    uint16_t bits;
} bfloat16_t;

typedef uint16_t float16_t;

bfloat16_t float_to_bfloat16(float value);
float      bfloat16_to_float(bfloat16_t bf16);

/**
 * Converts a floating-point number in bit representation to its equivalent
 * as a float value.
 */
float float_from_bits(uint32_t bits);

/**
 * Converts a floating-point number from the float format to its bit
 * representation.
 */
uint32_t float_to_bits(float value);

/**
 * Converts a floating-point number in bit representation to its equivalent
 * as a float value.
 */
float float_from_bits(uint32_t bits) {
    union Float32 fp32 = {.as_bits = bits};
    return fp32.as_value;
}

/**
 * Converts a floating-point number from the float format to its bit
 * representation.
 */
uint32_t float_to_bits(float value) {
    union Float32 fp32 = {.as_value = value};
    return fp32.as_bits;
}

bfloat16_t float_to_bfloat16(float value) {
    float32_t  f32;
    bfloat16_t bf16;

    // Take the higher 16 bits of the float32 representation
    f32.as_value = value;
    bf16.bits    = f32.as_bits >> 16;

    return bf16;
}

float bfloat16_to_float(bfloat16_t bf16) {
    float32_t f32;
    // Shift the bits back to their original position
    f32.as_bits = ((uint32_t) bf16.bits) << 16;
    return f32.as_value;
}
