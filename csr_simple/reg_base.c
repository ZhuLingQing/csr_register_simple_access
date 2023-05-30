#include <stdint.h>
#include <stdio.h>
#include "reg_base.h"

static reg_data_t regs[4] = {0};

void *get_base() { return (void *)regs; }

void reg_print_all()
{
    for (int i = 0; i < sizeof(regs) / sizeof(regs[0]); ++i)
    {
        printf("REG%d: %08X\n", i, regs[i]);
    }
}
