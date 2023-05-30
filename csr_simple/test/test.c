#include <assert.h>
#include "reg_api.h"
#include "reg_base.h"
#include "reg_def.h"

void* reg_base;

int main()
{
    reg_init(get_base());

    reg_write(REG_ID, 0x12345678);
    reg_decant(REG_ID);

    reg_writeCompose(REG_EN, en, 1);
    reg_decant(REG_EN);

    reg_writeCompose(REG_CFG, b2, 0x33);
    reg_decant(REG_CFG);
    reg_writeCompose(REG_CFG, b1, 0x44);
    reg_decant(REG_CFG);

    reg_write(REG_CFG, 0xAAA55A55);
    reg_decant(REG_CFG);
    reg_data_t v = REG_COMPOSE_V(REG_CFG, b2, 0x11) + REG_COMPOSE_V(REG_CFG, b1, 0x22);
    reg_data_t m = REG_COMPOSE_M(REG_CFG, b2) + REG_COMPOSE_M(REG_CFG, b1);
    reg_composeModify(REG_CFG, v, m);
    reg_decant(REG_CFG);

    reg_writeComposeModify(REG_CFG,b3,0x77);
    reg_decant(REG_CFG);
    reg_decant_f(REG_CFG,b0);
    reg_decant_f(REG_CFG,b1);
    reg_decant_f(REG_CFG,b2);
    reg_decant_f(REG_CFG,b3);

    return 0;
}
