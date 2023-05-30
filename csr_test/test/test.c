#include <assert.h>
#include "reg_api.h"
#include "reg_def.h"


static reg_data_t regs[4] = {0};

void *get_base() { return (void *)regs; }

void reg_print_all()
{
    for (int i = 0; i < sizeof(regs) / sizeof(regs[0]); ++i)
    {
        printf("REG%d: %08X\n", i, regs[i]);
    }
}

int main()
{
    reg_init(get_base());

    reg_write(REG_ID, 0x12345678);
    reg_print(REG_ID);

    reg_writeCompose(REG_EN, en, 1);
    reg_print(REG_EN);

    reg_writeCompose(REG_CFG, b2, 0x33);
    reg_print(REG_CFG);
    reg_writeCompose(REG_CFG, b1, 0x44);
    reg_print(REG_CFG);

    reg_write(REG_CFG, 0xAAA55A55);
    reg_print(REG_CFG);
    reg_data_t v = REG_COMPOSE_V(REG_CFG, b2, 0x11) + REG_COMPOSE_V(REG_CFG, b1, 0x22);
    reg_data_t m = REG_COMPOSE_M(REG_CFG, b2) + REG_COMPOSE_M(REG_CFG, b1);
    reg_composeModify(REG_CFG, v, m);
    reg_print(REG_CFG);

    reg_writeComposeModify(REG_CFG,b3,0x77);
    reg_print(REG_CFG);
    reg_decant(REG_CFG,b0);
    reg_decant(REG_CFG,b1);
    reg_decant(REG_CFG,b2);
    reg_decant(REG_CFG,b3);

    return 0;
}
