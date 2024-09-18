#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "modbus_pdu.h"

    void 
stuff_bits(uint8_t *const byte_arr,
        const uint8_t *const bits,
        const uint8_t bit_count)
{
    assert(byte_arr);
    assert(bits);

    for(uint8_t i = 0, j = 0; i < bit_count; ++i) {
        assert(bits[i] == 0 || bits[i] == 1);
        if(i != 0 && i % 8 == 0)
            ++j;
        byte_arr[j] |= bits[i] << (i % 8);
    }
}

    uint8_t 
get_req_pdu_datalen(const uint8_t *const serial_pdu)
{
    assert(serial_pdu);
    const uint8_t function = serial_pdu[0];
    const uint8_t *data = serial_pdu + 1;
    uint8_t pdu_datalen = 0;

    switch(function) {
        case MODBUS_FUNC_READ_COILS:
        case MODBUS_FUNC_READ_DISCRETE_INPUTS:
        case MODBUS_FUNC_READ_HOLDING_REGISTERS:
        case MODBUS_FUNC_READ_INPUT_REGISTERS:
        case MODBUS_FUNC_WRITE_SINGLE_COIL:
        case MODBUS_FUNC_WRITE_SINGLE_REGISTER:
        case MODBUS_FUNC_DIAGNOSTICS:
            pdu_datalen = 4;
            break;

        case MODBUS_FUNC_WRITE_MULTIPLE_COILS:
        case MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS:
            pdu_datalen = 4 + 1 + data[4];
            break;

        case MODBUS_FUNC_RW_MULTIPLE_REGISTERS:
            pdu_datalen = 8 + 1 + data[8];
            break;

        default:
            break;
    }

    if(pdu_datalen > MODBUS_DATALEN_MAX)
        pdu_datalen = 0;
    return pdu_datalen;
}

    uint8_t
get_excp_pdu_datalen(const uint8_t *const serial_pdu)
{
    assert(serial_pdu);
    const uint8_t function = serial_pdu[0] & 0x7F;
    uint8_t pdu_datalen = 0;

    switch(function) {
        case MODBUS_FUNC_READ_COILS:
        case MODBUS_FUNC_READ_DISCRETE_INPUTS:
        case MODBUS_FUNC_READ_HOLDING_REGISTERS:
        case MODBUS_FUNC_READ_INPUT_REGISTERS:
        case MODBUS_FUNC_RW_MULTIPLE_REGISTERS:
        case MODBUS_FUNC_WRITE_SINGLE_COIL:
        case MODBUS_FUNC_WRITE_SINGLE_REGISTER:
        case MODBUS_FUNC_DIAGNOSTICS:
        case MODBUS_FUNC_WRITE_MULTIPLE_COILS:
        case MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS:
            pdu_datalen = 1;
            break;

        default:
            break;
    }

    return pdu_datalen;

}

    uint8_t 
get_rsp_pdu_datalen(const uint8_t *const serial_pdu)
{
    assert(serial_pdu);
    const uint8_t function = serial_pdu[0];
    const uint8_t *data = serial_pdu + 1;
    uint8_t pdu_datalen = 0;

    if(function & 0x80)
        return get_excp_pdu_datalen(serial_pdu);

    switch(function) {
        case MODBUS_FUNC_READ_COILS:
        case MODBUS_FUNC_READ_DISCRETE_INPUTS:
        case MODBUS_FUNC_READ_HOLDING_REGISTERS:
        case MODBUS_FUNC_READ_INPUT_REGISTERS:
        case MODBUS_FUNC_RW_MULTIPLE_REGISTERS:
            pdu_datalen = 1 + data[0];
            break;

        case MODBUS_FUNC_WRITE_SINGLE_COIL:
        case MODBUS_FUNC_WRITE_SINGLE_REGISTER:
        case MODBUS_FUNC_DIAGNOSTICS:
        case MODBUS_FUNC_WRITE_MULTIPLE_COILS:
        case MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS:
            pdu_datalen = 4;
            break;

        default:
            break;
    }

    if(pdu_datalen > MODBUS_DATALEN_MAX)
        pdu_datalen = 0;
    return pdu_datalen;
}

    uint8_t
get_req_pdu_len(const uint8_t *const serial_pdu)
{
    assert(serial_pdu);
    uint8_t pdu_datalen = get_req_pdu_datalen(serial_pdu);
    if(pdu_datalen > 0)
        return 1 + pdu_datalen;
    return 0;
}

    uint8_t
get_rsp_pdu_len(const uint8_t *const serial_pdu)
{
    assert(serial_pdu);
    uint8_t pdu_datalen = get_rsp_pdu_datalen(serial_pdu);
    if(pdu_datalen > 0)
        return 1 + pdu_datalen;
    return 0;
}

    uint8_t
serialize_words(uint8_t *const data,
        const uint16_t *const words,
        const uint8_t wordlen)
{
    assert(data);
    assert(words);
    assert(wordlen > 0);

    uint8_t i;
    for(i = 0; i < wordlen; ++i) {
        data[2 * i] = BYTE_HI(words[i]);
        data[2 * i + 1] = BYTE_LO(words[i]);
    }
    return (2 * i + 1);
}

    void 
build_f1_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_coil_addr, 
        const uint16_t coil_count) 
{
    assert(serial_pdu);

    uint16_t words[] = { start_coil_addr, coil_count };

    serial_pdu[0] = MODBUS_FUNC_READ_COILS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void
build_f1_rsp_pdu(uint8_t *const serial_pdu,
        const uint8_t *const coil_vals,
        const uint8_t coil_count)
{
    assert(serial_pdu);
    assert(coil_vals);

    uint8_t byte_count = 0;

    byte_count = coil_count / 8;
    if(coil_count % 8 != 0)
        ++byte_count;

    serial_pdu[0] = MODBUS_FUNC_READ_COILS;
    serial_pdu[1] = byte_count;
    stuff_bits(serial_pdu + 2, coil_vals, coil_count);
}

    void 
build_f2_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_disc_input_addr, 
        const uint16_t disc_input_count) 
{
    assert(serial_pdu);

    uint16_t words[] = { start_disc_input_addr, disc_input_count };

    serial_pdu[0] = MODBUS_FUNC_READ_DISCRETE_INPUTS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void
build_f2_rsp_pdu(uint8_t *const serial_pdu,
        const uint8_t *const disc_input_vals,
        const uint8_t disc_input_count)
{
    assert(serial_pdu);
    assert(disc_input_vals);

    uint8_t byte_count = 0;

    byte_count = disc_input_count / 8;
    if(disc_input_count % 8 != 0)
        ++byte_count;

    serial_pdu[0] = MODBUS_FUNC_READ_DISCRETE_INPUTS;
    serial_pdu[1] = byte_count;
    stuff_bits(serial_pdu + 2, disc_input_vals, disc_input_count);
}

    void 
build_f3_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_reg_addr, 
        const uint16_t reg_count) 
{
    assert(serial_pdu);

    uint16_t words[] = { start_reg_addr, reg_count };

    serial_pdu[0] = MODBUS_FUNC_READ_HOLDING_REGISTERS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void 
build_f3_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count) 
{
    assert(serial_pdu);
    assert(reg_vals);

    serial_pdu[0] = MODBUS_FUNC_READ_HOLDING_REGISTERS;
    serial_pdu[1] = serialize_words(serial_pdu + 2, 
            reg_vals, reg_count) - 1;
}

    void 
build_f4_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_reg_addr, 
        const uint16_t reg_count) 
{
    assert(serial_pdu);

    uint16_t words[] = { start_reg_addr, reg_count };

    serial_pdu[0] = MODBUS_FUNC_READ_INPUT_REGISTERS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void 
build_f4_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count) 
{
    assert(serial_pdu);
    assert(reg_vals);

    serial_pdu[0] = MODBUS_FUNC_READ_INPUT_REGISTERS;
    serial_pdu[1] = serialize_words(serial_pdu + 2, 
            reg_vals, reg_count) - 1;
}

    void 
build_f5_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t coil_addr, 
        const uint8_t coil_status) 
{
    assert(serial_pdu);
    assert(coil_status == 0 || coil_status == 1);

    uint16_t words[] = { coil_addr };
    uint8_t nxt = 0;

    serial_pdu[nxt++] = MODBUS_FUNC_WRITE_SINGLE_COIL;
    nxt = serialize_words(serial_pdu + nxt, words, ARR_LEN(words));

    if(coil_status == 1) {
        serial_pdu[nxt++] = 0xFF;
        serial_pdu[nxt++] = 0x00;
    } else {
        serial_pdu[nxt++] = 0x00;
        serial_pdu[nxt++] = 0x00;
    }
}

    void 
build_f5_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t coil_addr, 
        const uint8_t coil_status) 
{
    build_f5_req_pdu(serial_pdu, coil_addr, coil_status);
}


    void 
build_f6_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t reg_addr, 
        const uint16_t write_val) 
{
    assert(serial_pdu);

    uint16_t words[] = { reg_addr, write_val };

    serial_pdu[0] = MODBUS_FUNC_WRITE_SINGLE_REGISTER;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void 
build_f6_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t reg_addr, 
        const uint16_t write_val) 
{
    build_f6_req_pdu(serial_pdu, reg_addr, write_val);
}

    void
build_f15_req_pdu(uint8_t *const serial_pdu,
        const uint16_t start_coil_addr,
        const uint16_t coil_count,
        const uint8_t *const coil_vals)
{
    assert(serial_pdu);
    assert(coil_vals);

    uint8_t byte_count = 0, nxt = 0;
    uint16_t words[] = { start_coil_addr, coil_count };

    serial_pdu[nxt++] = MODBUS_FUNC_WRITE_MULTIPLE_COILS;
    nxt = serialize_words(serial_pdu + nxt, words, ARR_LEN(words));

    byte_count = coil_count / 8;
    if(coil_count % 8 != 0)
        ++byte_count;

    serial_pdu[nxt++] = byte_count;
    stuff_bits(serial_pdu + nxt, coil_vals, coil_count);
}

    void
build_f15_rsp_pdu(uint8_t *const serial_pdu,
        const uint16_t start_coil_addr,
        const uint16_t coil_count)
{
    assert(serial_pdu);

    uint16_t words[] = { start_coil_addr, coil_count };

    serial_pdu[0] = MODBUS_FUNC_WRITE_MULTIPLE_COILS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void
build_f16_req_pdu(uint8_t *const serial_pdu,
        const uint16_t start_reg_addr,
        const uint16_t reg_count,
        const uint16_t *const write_vals)
{
    assert(serial_pdu);
    assert(write_vals);

    uint8_t byte_count = 0, nxt = 0;
    uint8_t ser_vals[MODBUS_DATALEN_MAX] = { 0 };
    uint16_t words[] = { start_reg_addr, reg_count };

    serial_pdu[nxt++] = MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS;
    nxt = serialize_words(serial_pdu + nxt, words, ARR_LEN(words));
    byte_count = serialize_words(ser_vals, write_vals, reg_count) - 1;

    serial_pdu[nxt++] = byte_count;
    memcpy(serial_pdu + nxt, ser_vals, byte_count);
}

    void
build_f16_rsp_pdu(uint8_t *const serial_pdu,
        const uint16_t start_reg_addr,
        const uint16_t reg_count)
{
    assert(serial_pdu);

    uint16_t words[] = { start_reg_addr, reg_count };

    serial_pdu[0] = MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS;
    serialize_words(serial_pdu + 1, words, ARR_LEN(words));
}

    void
build_f23_req_pdu(uint8_t *const serial_pdu,
        const uint16_t read_start_addr,
        const uint16_t read_count,
        const uint16_t write_start_addr,
        const uint16_t write_count,
        const uint16_t *const vals)
{
    assert(serial_pdu);
    assert(vals);

    uint8_t byte_count = 0, nxt = 0;
    uint8_t ser_vals[MODBUS_DATALEN_MAX] = { 0 };
    uint16_t words[] = { read_start_addr, read_count, 
        write_start_addr, write_count };

    serial_pdu[nxt++] = MODBUS_FUNC_RW_MULTIPLE_REGISTERS;
    nxt = serialize_words(serial_pdu + nxt, words, ARR_LEN(words));
    byte_count = serialize_words(ser_vals, vals, write_count) - 1;

    serial_pdu[nxt++] = byte_count;
    memcpy(serial_pdu + nxt, ser_vals, byte_count);
}

    void 
build_f23_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count) 
{
    assert(serial_pdu);
    assert(reg_vals);

    serial_pdu[0] = MODBUS_FUNC_RW_MULTIPLE_REGISTERS;
    serial_pdu[1] = serialize_words(serial_pdu + 2, 
            reg_vals, reg_count) - 1;
}

    void
build_excp_pdu(uint8_t *const serial_pdu,
        const uint8_t function_code,
        const uint8_t exception_code)
{
    assert(serial_pdu);
    serial_pdu[0] = function_code + 0x80;
    serial_pdu[1] = exception_code;
}
