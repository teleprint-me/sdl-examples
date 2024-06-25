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

// Conversion functions between float and float16

/**
 * Converts a 32-bit float to a 16-bit half-precision float.
 */
float16_t float_to_float16(float value) {
    union Float32 f32;
    f32.as_value = value;
    uint32_t f   = f32.as_bits;

    // Extract components
    uint32_t sign     = (f >> 16) & 0x8000;            // mask: 32768
    int32_t  exponent = ((f >> 23) & 0xFF) - 127 + 15; // mask: 255
    uint32_t mantissa = (f >> 13) & 0x3FF;             // mask: 1023

    if (exponent <= 0) {
        if (exponent < -10) {
            // Too small to be represented as a normalized half-float
            return sign;
        }
        // Subnormal half-float
        mantissa = (mantissa | 0x400) >> (1 - exponent); // flip: 1024
        return sign | mantissa;
    } else if (exponent == 0xFF - (127 - 15)) {
        if (mantissa == 0) {
            return sign | 0x7C00; // Inf
        } else {
            return sign | 0x7C00 | (mantissa >> 13); // NaN
        }
    } else if (exponent > 30) {
        // Overflow to Inf
        return sign | 0x7C00; // flip: 31744
    }

    // Normalized half-float
    return sign | (exponent << 10) | mantissa;
}

/**
 * Converts a 16-bit half-precision float to a 32-bit float.
 */
float float16_to_float(float16_t value) {
    uint32_t sign     = (value >> 15) & 0x00000001;
    uint32_t exponent = (value >> 10) & 0x0000001F;
    uint32_t mantissa = value & 0x000003FF;

    uint32_t f;

    if (exponent == 0) {
        if (mantissa == 0) {
            // Zero
            f = sign << 31;
        } else {
            // Subnormal number
            exponent = 1;
            while ((mantissa & 0x00000400) == 0) {
                mantissa <<= 1;
                exponent--;
            }
            mantissa  &= ~0x00000400;
            exponent   = exponent - 1 + 127;
            mantissa <<= 13;
            f          = (sign << 31) | (exponent << 23) | mantissa;
        }
    } else if (exponent == 31) {
        // Inf or NaN
        f = (sign << 31) | 0x7F800000 | (mantissa << 13);
    } else {
        // Normalized number
        exponent = exponent - 15 + 127;
        mantissa = mantissa << 13;
        f        = (sign << 31) | (exponent << 23) | mantissa;
    }

    union Float32 f32;
    f32.as_bits = f;
    return f32.as_value;
}
