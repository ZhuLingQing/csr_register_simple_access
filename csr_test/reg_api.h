#ifndef _REG_API_H_
#define _REG_API_H_

#include <stdio.h>
#include "reg_base.h"

void _reg_init(void* base);

void _reg_write(int label, reg_data_t value);

reg_data_t _reg_read(int label);

// void reg_decant(int label);

int _reg_waitFor(int label, reg_data_t value, reg_data_t mask);

// void reg_writeCompose(int label, reg_data_t value);

void _reg_composeModify(int label, reg_data_t value, reg_data_t mask);

/*
 * the macros are the real export virtual functions to the user
 */

// init the register group, input the base_address
#define reg_init(base) _reg_init(base)

// write register: value into label with reg_data_t width.
#define reg_write(label, value) _reg_write(label##_OFFSET, value)

// read register: value from label with reg_data_t width.
#define reg_read(label) _reg_read(label##_OFFSET)

// print register: value from label and only print the field.
#define reg_decant_f(label, field)                                                     \
    do                                                                                 \
    {                                                                                  \
        typedef_##label##_t __##label;                                                 \
        __##label.value = reg_read(label);                                             \
        printf("%s.%s: %d<0x%X>\n", #label, #field, __##label.field, __##label.field); \
    } while (0)

// print register: value from label and only print the whole register.
#define reg_decant(label)                          \
    do                                             \
    {                                              \
        reg_data_t __##label = reg_read(label);    \
        printf("%s: 0x%08X\n", #label, __##label); \
    } while (0)

// read register and compare. read register and only compare the masked fields.
#define reg_waitFor(label, value, mask) _reg_waitFor(label##_OFFSET, value, mask)

// write register only the identified field, others keep zero.
#define reg_writeCompose(label, field, fv)                      \
    do                                                          \
    {                                                           \
        reg_data_t __##label = REG_COMPOSE_V(label, field, fv); \
        reg_write(label, __##label);                            \
    } while (0)

// read register, modify the field with fv, then write back the whole value.
#define reg_writeComposeModify(label, field, fv) \
    do                                           \
    {                                            \
        typedef_##label##_t __##label;           \
        __##label.value = reg_read(label);       \
        __##label.field = (fv);                  \
        reg_write(label, __##label.value);       \
    } while (0)
#define reg_writeComposeModify2(label, f1, v1, f2, v2) \
    do                                                 \
    {                                                  \
        typedef_##label##_t __##label;                 \
        __##label.value = reg_read(label);             \
        __##label.f1 = (v1);                           \
        __##label.f2 = (v2);                           \
        reg_write(label, __##label.value);             \
    } while (0)

// read register, clear the mask, plus the rv, then write back the whole value.
#define reg_composeModify(label, rv, mask) _reg_composeModify(label##_OFFSET, rv, mask)

// compose the value with field.
#define REG_COMPOSE_V(label, field, fv) (((fv) << label##_##field##_SHIFT) & label##_##field##_MASK)
// get the field mask.
#define REG_COMPOSE_M(label, field) (label##_##field##_MASK)

#endif