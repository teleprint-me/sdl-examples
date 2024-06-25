#ifndef PRECISION_H
#define PRECISION_H

#include <assert.h>
#include <stdint.h>

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

// 8-bit quarter-precision (placeholder)
// typedef uint8_t quant8_t;
#define QK8_0 32

typedef struct {
    float16_t delta;
    uint8_t   quants[QK8_0];
} quant8_t;

static_assert(sizeof(quant8_t) == sizeof(float16_t) + QK8_0, "wrong K8 block size/padding");

// 4-bit eighth-precision (placeholder)
// Here we might need to think differently as there's no native 4-bit type
// and we might want to store two 4-bit values in one 8-bit variable.
// typedef uint8_t quant4_t;
#define QK4_0 16

typedef struct {
    float16_t delta;
    uint8_t   quants[QK4_0]; // nibbles
} quant4_t;

static_assert(sizeof(quant4_t) == sizeof(float16_t) + QK4_0, "wrong K4 block size/padding");

bfloat16_t float_to_bfloat16(float value);
float      bfloat16_to_float(bfloat16_t value);

float16_t float_to_float16(float value);
float     float16_to_float(float16_t value);

quant8_t float_to_quant8(float value);
float    quant8_to_float(quant8_t value);

quant4_t float_to_quant4(float value);
float    quant4_to_float(quant4_t value);

#endif // PRECISION_H
