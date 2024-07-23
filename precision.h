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

#ifndef PRECISION_H
#define PRECISION_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum DataType {
    TYPE_FLOAT_F32,
    TYPE_FLOAT_F16,
    TYPE_FLOAT_BF16,
    TYPE_QUANT_K8, // k-bit precision
    TYPE_QUANT_K4,
    TYPE_MAX_COUNT, // number of data types
} data_t;

// 32-bit floating point (standard float)
typedef union Float32 {
    uint32_t as_bits;
    float    as_value;
} float32_t;

// Google Brain half-precision bfloat16
typedef uint16_t bfloat16_t;

// Standard half-precision (IEEE 754)
typedef uint16_t float16_t;

// 8-bit quarter-precision
typedef struct {
    float16_t delta;
    uint8_t*  quants; // Dynamically allocated array for quantized values
    size_t    size;   // Number of quantized values (default to 32)
} quant8_t;

// 4-bit eighth-precision
typedef struct {
    float16_t delta;
    uint8_t*  quants; // Dynamically allocated array for quantized nibbles
    size_t    size;   // Number of quantized nibbles (default to 16)
} quant4_t;

bfloat16_t float_to_bfloat16(float value);
float      bfloat16_to_float(bfloat16_t value);

float16_t float_to_float16(float value);
float     float16_to_float(float16_t value);

quant8_t* float_to_quant8(float value, size_t size);
float     quant8_to_float(const quant8_t* quant);

quant4_t* float_to_quant4(float value, size_t size);
float     quant4_to_float(const quant4_t* quant);

quant8_t* malloc_quant8(float16_t delta, size_t size, uint8_t* quants);
void      free_quant8(quant8_t* quant);

quant4_t* malloc_quant4(float16_t delta, size_t size, uint8_t* quants);
void      free_quant4(quant4_t* quant);

#endif // PRECISION_H
