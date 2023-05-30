#pragma once

#include <stdint.h>
#include "util_csrs.h"

class FPGA_CSRs : public Util_CSRs<uint64_t, uint32_t>
{
   public:
    virtual void write(uint64_t offset, uint32_t rval) { *(uint32_t*)(this->m_base + offset) = rval; }
    virtual uint32_t read(uint64_t offset) { return *(uint32_t*)(this->m_base + offset); }
    virtual void print(uint64_t offset) {
        uint32_t rval = read(offset);
        printf("FPGA+%x: 0x%08X\n", (uint32_t)offset, (uint32_t)rval); 
    }
} FPGA;


class Dagger_CSRs : public Util_CSRs<uint32_t, uint16_t>
{
   public:
    virtual void write(uint32_t offset, uint16_t rval)
    {
        FPGA.write(0x18, offset);
        FPGA.write(0x1C, rval);
        FPGA.write(0x10, 1);
        FPGA.waitFor(0x14, 1, 1);
    }
    virtual uint16_t read(uint32_t offset)
    {
        FPGA.write(0x18, offset);
        FPGA.write(0x10, 2);
        FPGA.waitFor(0x14, 2, 2);
        return (uint16_t)(FPGA.read(0x1C));
    }
    virtual void print(uint32_t offset) {
        uint16_t rval = this->read(offset);
        printf("Dagger+%x: 0x%04X\n", (uint32_t)offset, (uint16_t)rval); 
    }
} Dagger;

