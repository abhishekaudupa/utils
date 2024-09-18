#ifndef MODBUS_PDU_H
#define MODBUS_PDU_H

#include <stdint.h>

#define MODBUS_FUNC_READ_COILS					0x01
#define MODBUS_FUNC_READ_DISCRETE_INPUTS		0x02
#define MODBUS_FUNC_READ_HOLDING_REGISTERS		0x03
#define MODBUS_FUNC_READ_INPUT_REGISTERS		0x04
#define MODBUS_FUNC_WRITE_SINGLE_COIL			0x05
#define MODBUS_FUNC_WRITE_SINGLE_REGISTER		0x06
#define MODBUS_FUNC_DIAGNOSTICS					0x08
#define MODBUS_FUNC_WRITE_MULTIPLE_COILS		0x0F
#define MODBUS_FUNC_WRITE_MULTIPLE_REGISTERS	0x10
#define MODBUS_FUNC_RW_MULTIPLE_REGISTERS		0x17

#define MODBUS_DATALEN_MAX						252
#define MODBUS_PDULEN_MAX						(MODBUS_DATALEN_MAX + 1)

#define BYTE_HI(uint16_word)					(uint16_word >> 8)
#define BYTE_LO(uint16_word)					(uint16_word & 0x00FF)
#define COMBINE(byte_hi, byte_lo)				((byte_hi << 8) | (byte_lo))
#define ARR_LEN(arr)							(sizeof(arr) / sizeof(arr[0]))

void 
stuff_bits(uint8_t *const byte_arr,
        const uint8_t *const bits,
        const uint8_t bit_count);

uint8_t 
get_req_pdu_datalen(const uint8_t *const serial_pdu);

uint8_t
get_excp_pdu_datalen(const uint8_t *const serial_pdu);

uint8_t 
get_rsp_pdu_datalen(const uint8_t *const serial_pdu);

uint8_t
get_req_pdu_len(const uint8_t *const serial_pdu);

uint8_t
get_rsp_pdu_len(const uint8_t *const serial_pdu);

uint8_t
serialize_words(uint8_t *const data,
        const uint16_t *const words,
        const uint8_t wordlen);

void 
build_f1_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_coil_addr, 
        const uint16_t coil_count); 

void
build_f1_rsp_pdu(uint8_t *const serial_pdu,
        const uint8_t *const coil_vals,
        const uint8_t coil_count);

void 
build_f2_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_disc_input_addr, 
        const uint16_t disc_input_count);

void
build_f2_rsp_pdu(uint8_t *const serial_pdu,
        const uint8_t *const disc_input_vals,
        const uint8_t disc_input_count);

void 
build_f3_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_reg_addr, 
        const uint16_t reg_count);

void 
build_f3_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count);

void 
build_f4_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t start_reg_addr, 
        const uint16_t reg_count);

void 
build_f4_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count);

void 
build_f5_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t coil_addr, 
        const uint8_t coil_status);

void 
build_f5_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t coil_addr, 
        const uint8_t coil_status);

void 
build_f6_req_pdu(uint8_t *const serial_pdu, 
        const uint16_t reg_addr, 
        const uint16_t write_val);

void 
build_f6_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t reg_addr, 
        const uint16_t write_val);

void
build_f15_req_pdu(uint8_t *const serial_pdu,
        const uint16_t start_coil_addr,
        const uint16_t coil_count,
        const uint8_t *const coil_vals);

void
build_f15_rsp_pdu(uint8_t *const serial_pdu,
        const uint16_t start_coil_addr,
        const uint16_t coil_count);

void
build_f16_req_pdu(uint8_t *const serial_pdu,
        const uint16_t start_reg_addr,
        const uint16_t reg_count,
        const uint16_t *const write_vals);

void
build_f16_rsp_pdu(uint8_t *const serial_pdu,
        const uint16_t start_reg_addr,
        const uint16_t reg_count);

void
build_f23_req_pdu(uint8_t *const serial_pdu,
        const uint16_t read_start_addr,
        const uint16_t read_count,
        const uint16_t write_start_addr,
        const uint16_t write_count,
        const uint16_t *const vals);

void 
build_f23_rsp_pdu(uint8_t *const serial_pdu, 
        const uint16_t *const reg_vals, 
        const uint8_t reg_count);

void
build_excp_pdu(uint8_t *const serial_pdu,
        const uint8_t function_code,
        const uint8_t exception_code);

#endif
