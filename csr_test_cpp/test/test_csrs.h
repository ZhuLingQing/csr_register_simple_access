#pragma once

#include <stdint.h>
#include "reg_def.h"
#include "util_csrs.h"

class FPGA_CSRs : public Util_CSRs<FPGA_addr_t, FPGA_data_t>
{
   public:
    FPGA_CSRs(const char name[]) : Util_CSRs(name) {}
    virtual void write(FPGA_addr_t offset, FPGA_data_t rval)
    {
        *(FPGA_data_t*)(this->m_base + offset) = rval;
        print_reg(offset, rval, true);
    }
    virtual FPGA_data_t read(FPGA_addr_t offset)
    {
        FPGA_data_t rval = *(FPGA_data_t*)(this->m_base + offset);
        print_reg(offset, rval, false);
        return rval;
    }
} FPGA("FPGA");

class Dagger_CSRs : public Util_CSRs<DAGGER_addr_t, DAGGER_data_t>
{
   public:
    Dagger_CSRs(const char name[]) : Util_CSRs(name) {}
    virtual void write(DAGGER_addr_t offset, DAGGER_data_t rval)
    {
        /*
        FPGA.write(0x18, offset);
        FPGA.write(0x1C, rval);
        FPGA.write(0x10, 1);
        FPGA.waitFor(0x14, 1, 1);
        */
        reg_write(FPGA, ADR, offset);
        reg_write(FPGA, DAT, rval);
        reg_writeCompose(FPGA, CR, wr, 1);
        reg_waitForCompose(FPGA, SR, wr, 1);
        print_reg(offset, rval, true);
    }
    virtual DAGGER_data_t read(DAGGER_addr_t offset)
    {
        /*
        FPGA.write(0x18, offset);
        FPGA.write(0x10, 2);
        FPGA.waitFor(0x14, 2, 2);
        return (DAGGER_data_t)(FPGA.read(0x1C));
        */
        reg_write(FPGA, ADR, offset);
        reg_writeCompose(FPGA, CR, rd, 1);
        reg_waitForCompose(FPGA, SR, rd, 1);
        DAGGER_data_t rval = reg_read(FPGA, DAT);
        print_reg(offset, rval, false);
        return rval;
    }
} Dagger("Dagger");
