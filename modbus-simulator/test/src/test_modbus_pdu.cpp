#include <gtest/gtest.h>

extern "C" {
#include "modbus_pdu.h"
}

TEST(test_serialize_words, 
        test_serialize_words) 
{
    uint16_t words[] = { 0x0001, 0x0203, 0x0405 };
    uint8_t data[2 * ARR_LEN(words)];

    serialize_words(data, words, ARR_LEN(words));

    EXPECT_EQ(data[0], 0x00);
    EXPECT_EQ(data[1], 0x01);
    EXPECT_EQ(data[2], 0x02);
    EXPECT_EQ(data[3], 0x03);
    EXPECT_EQ(data[4], 0x04);
    EXPECT_EQ(data[5], 0x05);
}

TEST(test_md_req_pdu_fn1, 
        test_md_req_pdu_fn1)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f1_req_pdu(serial_pdu, start_addr, count);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_COILS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn2, 
        test_md_req_pdu_fn2)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f2_req_pdu(serial_pdu, start_addr, count);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_DISCRETE_INPUTS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn3, 
        test_md_req_pdu_fn3)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f3_req_pdu(serial_pdu, start_addr, count);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_HOLDING_REGISTERS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn4, 
        test_md_req_pdu_fn4)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f4_req_pdu(serial_pdu, start_addr, count);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_INPUT_REGISTERS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn5, 
        test_md_req_pdu_fn5)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234;
    uint8_t pdu_len, pdu_datalen;

    build_f5_req_pdu(serial_pdu, start_addr, 1);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_COIL);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], 0xFF);
    EXPECT_EQ(serial_pdu[4], 0x00);

    build_f5_req_pdu(serial_pdu, start_addr, 0);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_COIL);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], 0x00);
    EXPECT_EQ(serial_pdu[4], 0x00);

    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn6, 
        test_md_req_pdu_fn6)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t register_addr = 0x0234, write_val = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f6_req_pdu(serial_pdu, register_addr, write_val);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_REGISTER);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(register_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(register_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(write_val));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(write_val));
    
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn15, 
        test_md_req_pdu_fn15)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint8_t vals[] = { 1,0,1,0,1,0,1,0,1 };
    uint16_t start_addr = 0x0234, count = ARR_LEN(vals);
    uint8_t byte_count;
    uint8_t pdu_len, pdu_datalen;

    build_f15_req_pdu(serial_pdu, start_addr, count, vals);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    byte_count = count / 8;
    if(count % 8 != 0)
        ++byte_count;

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_MULTIPLE_COILS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(serial_pdu[5], byte_count);
    EXPECT_EQ(serial_pdu[6], 0x55);
    EXPECT_EQ(serial_pdu[7], 0x01);

    EXPECT_EQ(pdu_datalen, 4 + 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn16, 
        test_md_req_pdu_fn16)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0004;
    uint16_t vals[] = { 0x2354, 0x5498, 0xAF23, 0x0398 };
    uint8_t byte_count;
    uint8_t pdu_len, pdu_datalen;

    build_f16_req_pdu(serial_pdu, start_addr, count, vals);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    byte_count = count * 2;

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    EXPECT_EQ(serial_pdu[5], byte_count);

    for(uint8_t i = 0; i < count; ++i) {
        EXPECT_EQ(serial_pdu[2 * i + 6], BYTE_HI(vals[i]));
        EXPECT_EQ(serial_pdu[2 * i  + 1 + 6], BYTE_LO(vals[i]));
    }
    EXPECT_EQ(pdu_datalen, 4 + 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_req_pdu_fn23, 
        test_md_req_pdu_fn23)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t read_start_addr = 0x0234, read_count = 0x0004; 
    uint16_t write_start_addr = 0x01230, write_count = 0x0003;
    uint16_t write_vals[] = { 0x2354, 0x5498, 0xAF23 };
    uint8_t byte_count;
    uint8_t pdu_len, pdu_datalen;

    build_f23_req_pdu(serial_pdu, read_start_addr, read_count, 
            write_start_addr, write_count, write_vals);
    pdu_len = get_req_pdu_len(serial_pdu);
    pdu_datalen = get_req_pdu_datalen(serial_pdu);

    byte_count = write_count * 2;

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_RW_MULTIPLE_REGISTERS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(read_start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(read_start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(read_count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(read_count));
    EXPECT_EQ(serial_pdu[5], BYTE_HI(write_start_addr));
    EXPECT_EQ(serial_pdu[6], BYTE_LO(write_start_addr));
    EXPECT_EQ(serial_pdu[7], BYTE_HI(write_count));
    EXPECT_EQ(serial_pdu[8], BYTE_LO(write_count));
    EXPECT_EQ(serial_pdu[9], byte_count);

    for(uint8_t i = 0; i < write_count; ++i) {
        EXPECT_EQ(serial_pdu[2 * i + 10], BYTE_HI(write_vals[i]));
        EXPECT_EQ(serial_pdu[2 * i  + 1 + 10], BYTE_LO(write_vals[i]));
    }
    EXPECT_EQ(pdu_datalen, 8 + 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn1,
        test_md_rsp_pdu_fn1)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint8_t coils[] = { 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 };
    uint8_t count = ARR_LEN(coils);
    uint8_t pdu_len, pdu_datalen;
    uint8_t byte_count = count / 8;
    if(count % 8 != 0)
        ++byte_count;

    build_f1_rsp_pdu(serial_pdu, coils, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_COILS);
    EXPECT_EQ(serial_pdu[1], byte_count);
    EXPECT_EQ(serial_pdu[2], 0x55);
    EXPECT_EQ(serial_pdu[3], 0x02);
    
    EXPECT_EQ(pdu_datalen, 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn2,
        test_md_rsp_pdu_fn2)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint8_t discrete_inputs[] = { 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 };
    uint8_t count = ARR_LEN(discrete_inputs);
    uint8_t pdu_len, pdu_datalen;
    uint8_t byte_count = count / 8;
    if(count % 8 != 0)
        ++byte_count;

    build_f2_rsp_pdu(serial_pdu, discrete_inputs, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_DISCRETE_INPUTS);
    EXPECT_EQ(serial_pdu[1], byte_count);
    EXPECT_EQ(serial_pdu[2], 0x80);
    EXPECT_EQ(serial_pdu[3], 0x00);
    
    EXPECT_EQ(pdu_datalen, 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn3,
        test_md_rsp_pdu_fn3)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint16_t registers[] = { 0x1122, 0x3344 };
    uint8_t count = ARR_LEN(registers);
    uint8_t pdu_len, pdu_datalen;

    uint8_t byte_count = count * 2;

    build_f3_rsp_pdu(serial_pdu, registers, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_HOLDING_REGISTERS);
    EXPECT_EQ(serial_pdu[1], byte_count);
    EXPECT_EQ(serial_pdu[2], 0x11);
    EXPECT_EQ(serial_pdu[3], 0x22);
    EXPECT_EQ(serial_pdu[4], 0x33);
    EXPECT_EQ(serial_pdu[5], 0x44);
    
    EXPECT_EQ(pdu_datalen, 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn4,
        test_md_rsp_pdu_fn4)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint16_t registers[] = { 0x1234, 0x5678 };
    uint8_t count = ARR_LEN(registers);
    uint8_t pdu_len, pdu_datalen;

    uint8_t byte_count = count * 2;

    build_f4_rsp_pdu(serial_pdu, registers, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_INPUT_REGISTERS);
    EXPECT_EQ(serial_pdu[1], byte_count);
    EXPECT_EQ(serial_pdu[2], 0x12);
    EXPECT_EQ(serial_pdu[3], 0x34);
    EXPECT_EQ(serial_pdu[4], 0x56);
    EXPECT_EQ(serial_pdu[5], 0x78);
    
    EXPECT_EQ(pdu_datalen, 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn5, 
        test_md_rsp_pdu_fn5)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234;
    uint8_t pdu_len, pdu_datalen;

    build_f5_rsp_pdu(serial_pdu, start_addr, 1);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_COIL);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], 0xFF);
    EXPECT_EQ(serial_pdu[4], 0x00);
    
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);

    build_f5_rsp_pdu(serial_pdu, start_addr, 0);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_COIL);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], 0x00);
    EXPECT_EQ(serial_pdu[4], 0x00);

}

TEST(test_md_rsp_pdu_fn6, 
        test_md_rsp_pdu_fn6)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t register_addr = 0x0234, write_val = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f6_rsp_pdu(serial_pdu, register_addr, write_val);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_SINGLE_REGISTER);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(register_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(register_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(write_val));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(write_val));
    
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn15, 
        test_md_rsp_pdu_fn15)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f15_rsp_pdu(serial_pdu, start_addr, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_MULTIPLE_COILS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn16, 
        test_md_rsp_pdu_fn16)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX];
    uint16_t start_addr = 0x0234, count = 0x0003;
    uint8_t pdu_len, pdu_datalen;

    build_f16_rsp_pdu(serial_pdu, start_addr, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS);
    EXPECT_EQ(serial_pdu[1], BYTE_HI(start_addr));
    EXPECT_EQ(serial_pdu[2], BYTE_LO(start_addr));
    EXPECT_EQ(serial_pdu[3], BYTE_HI(count));
    EXPECT_EQ(serial_pdu[4], BYTE_LO(count));
    
    EXPECT_EQ(pdu_datalen, 4);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_rsp_pdu_fn23,
        test_md_rsp_pdu_fn23)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint16_t registers[] = { 0x1122, 0x3344 };
    uint8_t count = ARR_LEN(registers);
    uint8_t pdu_len, pdu_datalen;

    uint8_t byte_count = count * 2;

    build_f23_rsp_pdu(serial_pdu, registers, count);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);

    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_RW_MULTIPLE_REGISTERS);
    EXPECT_EQ(serial_pdu[1], byte_count);
    EXPECT_EQ(serial_pdu[2], 0x11);
    EXPECT_EQ(serial_pdu[3], 0x22);
    EXPECT_EQ(serial_pdu[4], 0x33);
    EXPECT_EQ(serial_pdu[5], 0x44);
    
    EXPECT_EQ(pdu_datalen, 1 + byte_count);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}

TEST(test_md_excp_pdu,
        test_md_excp_pdu)
{
    uint8_t serial_pdu[MODBUS_PDULEN_MAX] = { 0 };
    uint8_t function = MODBUS_FUNC_READ_DISCRETE_INPUTS;
    uint8_t excp_code = 0x02;
    uint8_t pdu_len, pdu_datalen;

    build_excp_pdu(serial_pdu, function, excp_code);
    pdu_len = get_rsp_pdu_len(serial_pdu);
    pdu_datalen = get_rsp_pdu_datalen(serial_pdu);
    
    EXPECT_EQ(serial_pdu[0], MODBUS_FUNC_READ_DISCRETE_INPUTS | 0x80);
    EXPECT_EQ(serial_pdu[1], excp_code);
    
    EXPECT_EQ(pdu_datalen, 1);
    EXPECT_EQ(pdu_len, pdu_datalen + 1);
}
