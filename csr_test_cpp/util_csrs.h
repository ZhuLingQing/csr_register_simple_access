#pragma once

#include <stdio.h>

constexpr int timeout_count = 100;

template <class addr_t, class data_t>
class Util_CSRs
{
   public:
    Util_CSRs() : n_timeout(timeout_count), m_base(0) {}
    void init(addr_t base) { m_base = base; }
    void get_base() { return m_base; }
    virtual void print(addr_t offset) = 0;

    virtual void write(addr_t offset, data_t rval) = 0;
    virtual data_t read(addr_t offset) = 0;

    int waitFor(addr_t offset, data_t rval, data_t mask)
    {
        for (int n = 0; n < n_timeout; ++n)
        {
            if ((read(offset) & mask) == (rval & mask)) return 0;
        }
        return -1;
    }
    void composeModify(addr_t offset, data_t rval, data_t mask)
    {
        data_t rv = (_reg_read(offset) & (~mask)) | rval;
        write(offset, rv);
    }

   protected:
    int n_timeout;
    addr_t m_base;
};

// init the register group, input the base_address
#define reg_init(obj, base) obj.init(base)

// write register: value into label with reg_data_t width.
#define reg_write(obj, label, value) obj.write(label##_OFFSET, value)

// read register: value from label with reg_data_t width.
#define reg_read(obj, label) obj.read(label##_OFFSET)

// print register: value from label and only print the field.
#define reg_decant_f(obj, label, field)                                                \
    do                                                                                 \
    {                                                                                  \
        typedef_##label##_t __##label;                                                 \
        __##label.value = obj.read(label);                                             \
        printf("%s.%s: %d<0x%X>\n", #label, #field, __##label.field, __##label.field); \
    } while (0)

// print register: value from label and only print the whole register.
#define reg_decant(obj, label)                     \
    do                                             \
    {                                              \
        obj##_data_t __##label = obj.read(label);  \
        printf("%s: 0x%08X\n", #label, __##label); \
    } while (0)

// read register and compare. read register and only compare the masked fields.
#define reg_waitFor(obj, label, value, mask) obj.waitFor(label##_OFFSET, value, mask)

// write register only the identified field, others keep zero.
#define reg_writeCompose(obj, label, field, fv)                   \
    do                                                            \
    {                                                             \
        obj##_data_t __##label = REG_COMPOSE_V(label, field, fv); \
        obj.write(label, __##label);                              \
    } while (0)

// read register, modify the field with fv, then write back the whole value.
#define reg_writeComposeModify(obj, label, field, fv) \
    do                                                \
    {                                                 \
        typedef_##label##_t __##label;                \
        __##label.value = obj.read(label);            \
        __##label.field = (fv);                       \
        obj.write(label, __##label.value);            \
    } while (0)
#define reg_writeComposeModify2(obj, label, f1, v1, f2, v2) \
    do                                                      \
    {                                                       \
        typedef_##label##_t __##label;                      \
        __##label.value = obj.read(label);                  \
        __##label.f1 = (v1);                                \
        __##label.f2 = (v2);                                \
        obj.write(label, __##label.value);                  \
    } while (0)

// read register, clear the mask, plus the rv, then write back the whole value.
#define reg_composeModify(obj, label, rv, mask) obj.composeModify(label##_OFFSET, rv, mask)

// compose the value with field.
#define REG_COMPOSE_V(label, field, fv) (((fv) << label##_##field##_SHIFT) & label##_##field##_MASK)
// get the field mask.
#define REG_COMPOSE_M(label, field) (label##_##field##_MASK)
