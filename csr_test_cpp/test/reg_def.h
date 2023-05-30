#ifndef _FPGA_DEF_H_
#define _FPGA_DEF_H_

#include <stdint.h>

typedef uint64_t FPGA_addr_t;
typedef uint32_t FPGA_data_t;

typedef uint32_t DAGGER_addr_t;
typedef uint16_t DAGGER_data_t;

// offset
#define FPGA_ID_OFFSET 0x0
#define FPGA_CR_OFFSET 0x10
#define FPGA_SR_OFFSET 0x14
#define FPGA_ADR_OFFSET 0x18
#define FPGA_DAT_OFFSET 0x1C

// type
typedef union {
    FPGA_data_t value;
    struct {
        FPGA_data_t id;
    };
}typedef_FPGA_ID_t;

typedef union {
    FPGA_data_t value;
    struct {
        FPGA_data_t wr : 1;
        FPGA_data_t rd : 1;
        FPGA_data_t rsvd : 30;
    };
}typedef_FPGA_CR_t,typedef_FPGA_SR_t;
typedef union {
    FPGA_data_t value;
    struct {
        FPGA_data_t adr;
    };
}typedef_FPGA_ADR_t;

typedef union {
    FPGA_data_t value;
    struct {
        FPGA_data_t dat : 16;
        FPGA_data_t rsvd : 16;
    };
}typedef_FPGA_DAT_t;

// mask
#define FPGA_ID_id_MASK 0xFFFFFFFF
#define FPGA_CR_wr_MASK 0x00000001
#define FPGA_CR_rd_MASK 0x00000002
#define FPGA_SR_wr_MASK 0x00000001
#define FPGA_SR_rd_MASK 0x00000002
#define FPGA_ADR_adr_MASK 0xFFFFFFFF
#define FPGA_DAT_dat_MASK 0xFFFF

// shift
#define FPGA_ID_id_SHIFT 0
#define FPGA_CR_wr_SHIFT 0
#define FPGA_CR_rd_SHIFT 1
#define FPGA_SR_wr_SHIFT 0
#define FPGA_SR_rd_SHIFT 1
#define FPGA_ADR_adr_SHIFT 0
#define FPGA_DAT_dat_SHIFT 0

#endif
