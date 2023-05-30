
#include <stdio.h>
#include "test_csrs.h"

extern "C" void __cxa_pure_virtual() { while (1); }

static uint32_t regs[8] = {0};

uint64_t get_base() { return (uint64_t)regs; }

void reg_print_all()
{
    for (int i = 0; i < sizeof(regs) / sizeof(regs[0]); ++i)
    {
        printf("REG%d: %08X\n", i, regs[i]);
    }
}

int main()
{
    FPGA.init(get_base());
    FPGA.trace_switch(true);
    reg_write(FPGA,ID,0x1234567);
    reg_print(FPGA,ID);
    reg_write(FPGA,SR,3);
    reg_print(FPGA,SR);
    reg_decant(FPGA,SR,wr);
    reg_decant(FPGA,SR,rd);

    Dagger.trace_switch(true);
    Dagger.print(0);
    Dagger.write(0xaabbccdd, 0x0102);
    Dagger.print(0xaabbccdd);
    Dagger.print(0x11223344);

    return 0;
}
