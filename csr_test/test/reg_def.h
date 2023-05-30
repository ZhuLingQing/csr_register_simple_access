#ifndef _REG_DEF_H_
#define _REG_DEF_H_

#include "reg_base.h"

// offset
#define REG_ID_OFFSET 0x0
#define REG_EN_OFFSET 0x4
#define REG_CFG_OFFSET 0xC

// type
typedef union {
    reg_data_t value;
    struct {
        reg_data_t id;
    };
}typedef_REG_ID_t;

typedef union {
    reg_data_t value;
    struct {
        reg_data_t en : 1;
        reg_data_t rsvd : 31;
    };
}typedef_REG_EN_t;

typedef union {
    reg_data_t value;
    struct {
        reg_data_t b0 : 8;
        reg_data_t b1 : 8;
        reg_data_t b2 : 8;
        reg_data_t b3 : 8;
    };
}typedef_REG_CFG_t;

// mask
#define REG_ID_id_MASK 0xFFFFFFFF
#define REG_EN_en_MASK 0x00000001
#define REG_CFG_b0_MASK 0x000000FF
#define REG_CFG_b1_MASK 0x0000FF00
#define REG_CFG_b2_MASK 0x00FF0000
#define REG_CFG_b3_MASK 0xFF000000

// shift
#define REG_ID_id_SHIFT 0
#define REG_EN_en_SHIFT 0
#define REG_CFG_b0_SHIFT 0
#define REG_CFG_b1_SHIFT 8
#define REG_CFG_b2_SHIFT 16
#define REG_CFG_b3_SHIFT 24

#endif
