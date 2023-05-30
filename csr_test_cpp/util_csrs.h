#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string>

constexpr int timeout_count = 100;

template <class addr_t, class data_t>
class Util_CSRs
{
   public:
    Util_CSRs(const char name[]) : n_timeout(timeout_count), m_base(0), b_trace(false), m_name(name) {}
    void init(addr_t base) { m_base = base; }
    void trace_switch(bool on_off) { b_trace = on_off; }
    void get_base() { return m_base; }

    virtual void print_reg(addr_t offset, data_t rval, bool is_wr)
    {
        if (b_trace) printf("%s+%x %s 0x%X\n", m_name.c_str(), (uint32_t)offset, is_wr ? "wr" : "rd", (uint32_t)rval);
    }
    virtual void print(addr_t offset)
    {
        data_t rval = read(offset);
        printf("%s+%x == 0x%08X\n", m_name.c_str(), (uint32_t)offset, (uint32_t)rval);
    }

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
        data_t rv = (read(offset) & (~mask)) | rval;
        write(offset, rv);
    }

   protected:
    bool b_trace;
    int n_timeout;
    addr_t m_base;
    std::string m_name;
};

// init the register group, input the base_address
#define reg_init(obj, base) obj.init(base)

// write register: value into label with reg_data_t width.
#define reg_write(obj, label, value) obj.write(obj##_##label##_OFFSET, value)

// read register: value from label with reg_data_t width.
#define reg_read(obj, label) obj.read(obj##_##label##_OFFSET)

// print register: value from label and only print the field.
#define reg_decant(obj, label, field)                                                           \
    do                                                                                          \
    {                                                                                           \
        typedef_##obj##_##label##_t _v_##label;                                                         \
        _v_##label.value = reg_read(obj, label);                                                 \
        printf("%s_%s.%s: %d<0x%X>\n", #obj, #label, #field, _v_##label.field, _v_##label.field); \
    } while (0)

// print register: value from label and only print the whole register.
#define reg_print(obj, label)                               \
    do                                                      \
    {                                                       \
        obj##_data_t _v_##label = reg_read(obj, label);      \
        printf("%s_%s: 0x%08X\n", #obj, #label, _v_##label); \
    } while (0)

// read register and compare. read register and only compare the masked fields.
#define reg_waitFor(obj, label, value, mask) obj.waitFor(obj##_##label##_OFFSET, value, mask)
#define reg_waitForCompose(obj, label, field, value) \
    obj.waitFor(obj##_##label##_OFFSET, REG_COMPOSE_V(obj, label, field, value), REG_COMPOSE_M(obj, label, field))

// write register only the identified field, others keep zero.
#define reg_writeCompose(obj, label, field, fv)                         \
    do                                                                  \
    {                                                                   \
        obj##_data_t _v_##label = REG_COMPOSE_V(obj, label, field, fv); \
        reg_write(obj, label, _v_##label);                              \
    } while (0)

// read register, modify the field with fv, then write back the whole value.
#define reg_writeComposeModify(obj, label, field, fv) \
    do                                                \
    {                                                 \
        typedef_##label##_t __##label;                \
        __##label.value = reg_read(obj, label);       \
        __##label.field = (fv);                       \
        reg_write(obj, label, __##label.value);       \
    } while (0)
#define reg_writeComposeModify2(obj, label, f1, v1, f2, v2) \
    do                                                      \
    {                                                       \
        typedef_##label##_t __##label;                      \
        __##label.value = reg_read(obj, label);             \
        __##label.f1 = (v1);                                \
        __##label.f2 = (v2);                                \
        reg_write(obj, label, __##label.value);             \
    } while (0)

// read register, clear the mask, plus the rv, then write back the whole value.
#define reg_composeModify(obj, label, rv, mask) obj.composeModify(obj##_##label##_OFFSET, rv, mask)

// compose the value with field.
#define REG_COMPOSE_V(obj, label, field, fv) \
    (((fv) << obj##_##label##_##field##_SHIFT) & obj##_##label##_##field##_MASK)
// get the field mask.
#define REG_COMPOSE_M(obj, label, field) (obj##_##label##_##field##_MASK)
