#include "reg_api.h"

#define waitfor_count 10

static uint64_t reg_base = 0;

void _reg_init(void* base) { reg_base = (uint64_t)base; }

void _reg_write(int label, reg_data_t value) { *(reg_data_t*)(reg_base + label) = value; }

reg_data_t _reg_read(int label) { return *(reg_data_t*)(reg_base + label); }

// void reg_decant(int label)

int _reg_waitFor(int label, reg_data_t value, reg_data_t mask)
{
    for (int n = 0; n < waitfor_count; ++n)
    {
        if ((_reg_read(label) & mask) == (value & mask)) return 0;
    }
    return -1;
}

// void reg_writeCompose(int label, reg_data_t value)

void _reg_composeModify(int label, reg_data_t value, reg_data_t mask)
{
    reg_data_t rv = (_reg_read(label) & (~mask)) | value;
    _reg_write(label, rv);
}
