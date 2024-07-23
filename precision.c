/**
 * Copyright © 2024 Austin Berrio
 *
 * @file precision.h
 *
 * @brief A simple and easy to use floating-point API
 *
 * Only use pure C.
 * Only use libraries when absolutely necessary.
 *
 * @note Prefixing related objects, functions, etc. assists with autocomplete.
 *
 * arxiv:2212.09720:The-case-for-4-bit-precision-k-bit-Inference-Scaling-Laws.pdf
 * arxiv:2110.02861:8-bit-Optimizers-via-Block-wise-Quantization.pdf
 * arxiv:2208.07339:LLM.int8-8-bit-Matrix-Multiplication-for-Transformers-at-Scale.pdf
 * arxiv:1805.11046:Scalable-Methods-for-8-bit-Training-of-Neural-Networks.pdf
 * arxiv:2310.13513:Exploring-the-Potential-of-Flexible-8-bit-Format-Design-and-Algorithm.pdf
 */

#include "precision.h"

#include <stdint.h>

/**
 * Converts float32 to bfloat16.
 */
bfloat16_t float_to_bfloat16(float value) {
    float32_t f32;
    f32.as_value = value;

    // Take the higher 16 bits of the float32 representation
    uint32_t bits = f32.as_bits;

    // Handle NaN: force to quiet NaN
    if ((bits & 0x7fffffff) > 0x7f800000) {
        return (bits >> 16) | 0x0040;
    }

    // Handle subnormals: flush to zero
    if ((bits & 0x7f800000) == 0) {
        return (bits >> 16) & 0x8000;
    }

    // Rounding: round to nearest even
    uint32_t rounding_bias = (bits & 0x0000ffff) > 0x00007fff    ? 1
                             : (bits & 0x00018000) == 0x00018000 ? 1
                                                                 : 0;
    return (bits + rounding_bias) >> 16;
}

/**
 * Converts bfloat16 to float32.
 */
float bfloat16_to_float(bfloat16_t bf16) {
    float32_t f32;
    f32.as_bits = (uint32_t) bf16 << 16;
    return f32.as_value;
}

// Conversion functions between float and float16

/**
 * Converts a 32-bit float to a 16-bit half-precision float.
 */
float16_t float_to_float16(float value) {
    float32_t f32;
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

// Example implementation for quant8 and quant4 types
quant8_t float_to_quant8(float value, size_t size) {
    quant8_t quant;
    quant.delta  = float_to_float16(value / (float) size);
    quant.quants = (int8_t*) malloc(size * sizeof(int8_t));
    quant.size   = size;

    // Example quantization process (uniform quantization)
    for (size_t i = 0; i < size; ++i) {
        quant.quants[i] = (int8_t) (value / quant.delta);
    }

    return quant;
}

float quant8_to_float(const quant8_t* quant) {
    float16_t delta = quant->delta;
    float     sum   = 0.0f;

    for (size_t i = 0; i < quant->size; ++i) {
        sum += quant->quants[i] * delta;
    }

    return sum;
}

quant4_t float_to_quant4(float value, size_t size) {
    quant4_t quant;
    quant.delta  = float_to_float16(value / (float) size);
    quant.quants = (uint8_t*) malloc(size * sizeof(uint8_t));
    quant.size   = size;

    // Example quantization process (uniform quantization)
    for (size_t i = 0; i < size; ++i) {
        quant.quants[i] = (uint8_t) (value / quant.delta);
    }

    return quant;
}

float quant4_to_float(const quant4_t* quant) {
    float16_t delta = quant->delta;
    float     sum   = 0.0f;

    for (size_t i = 0; i < quant->size; ++i) {
        sum += quant->quants[i] * delta;
    }

    return sum;
}

void free_quant8(quant8_t* quant) {
    free(quant->quants);
}

void free_quant4(quant4_t* quant) {
    free(quant->quants);
}
