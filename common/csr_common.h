#ifndef _CSR_COMMON_H_
#define _CSR_COMMON_H_

#include <byteswap.h>
#include <stdint.h>
#include <stdio.h>

// Local datatypes....
typedef uint32_t fpgaAddr_t;  // Both FPGA address & data values are Bits32
typedef uint32_t fpgaData_t;

const int byteOrder = __BYTE_ORDER;

// -------------------------
// _htoll
// -------------------------
// Convert from Host byte order to Little Endian order used by FPGA.
static inline uint32_t _htoll(uint32_t value)
{
    if (byteOrder == __LITTLE_ENDIAN)
    {
        return (value);
    }
    else
    {  // __BIG_ENDIAN
        return (__bswap_32(value));
    }
}

// -------------------------
// _ltohl
// -------------------------
// Convert from Little Endian order used by FPGA to Host byte order.
static inline uint32_t _ltohl(uint32_t value)
{
    if (byteOrder == __LITTLE_ENDIAN)
    {
        return (value);
    }
    else
    {  // __BIG_ENDIAN
        return (__bswap_32(value));
    }
}

// -------------------------
// _toVirtualAddr
// -------------------------
// Convert the logical `addr` into a Linux Vitual Address. You must use
// virtual addresses to access Linux controlled physical facilities.
static inline void *_toVirtualAddr(void *reg_base, fpgaAddr_t addr)
{
    void *virt_addr;

    virt_addr = reg_base + (off_t)(addr + REG_BASE);
    return (virt_addr);
}

// -------------------------
// _readReg
// -------------------------
// DJAK This is the CSR_READ from the FPGA's perspective. In essence, the
//     Agent_read_reg should just call this routine.
static inline fpgaData_t _readReg(void *reg_base, fpgaAddr_t addr)
{
    return (_ltohl(*((volatile fpgaData_t *)_toVirtualAddr(reg_base, addr))));
}

// -------------------------
// _writeReg
// -------------------------
static inline void _writeReg(void *reg_base, fpgaAddr_t addr, fpgaData_t value)
{
    *((volatile fpgaData_t *)_toVirtualAddr(reg_base, addr)) = _htoll(value);
}

#endif
