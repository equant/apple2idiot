/**
 * FujiNet CONFIG for #Apple2
 *
 * SmartPort MLI Routines
 */

#ifndef SP_H
#define SP_H

#include <stdint.h>

extern uint8_t sp_payload[1024];
extern uint16_t sp_count, sp_dispatch;
extern uint8_t sp_dest;
extern uint8_t sp_error;

int8_t sp_status(uint8_t dest, uint8_t statcode);
int8_t sp_control(uint8_t dest, uint8_t ctrlcode);
int8_t sp_open(uint8_t dest);
int8_t sp_close(uint8_t dest);
int8_t sp_read(uint8_t dest, uint16_t len);
int8_t sp_write(uint8_t dest, uint16_t len);
int8_t sp_find_fuji(void);
int8_t sp_find_network(void);
uint8_t sp_find_slot(void);
uint16_t sp_dispatch_address(uint8_t slot);
void sp_init(void);

#endif /* SP_H */

