
#include <stdio.h>
#include "fpga_csrs.h"

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
    FPGA.write(0,0x1234567);
    FPGA.print(0);
    FPGA.write(0x14,3);
    FPGA.print(0x14);

    Dagger.print(0);
    Dagger.write(0xaabbccdd, 0x0102);
    Dagger.print(0xaabbccdd);
    Dagger.print(0x11223344);
    
    return 0;
}
