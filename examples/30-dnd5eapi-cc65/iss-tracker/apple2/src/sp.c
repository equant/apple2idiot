#ifdef BUILD_APPLE2
/**
 * FujiNet CONFIG for #Apple2
 *
 * SmartPort MLI Routines
 */

#ifdef __INTELLISENSE__
// 18, expect closing parenthses - needed to use cc65 inline asm command with agruments.
  #pragma diag_suppress 18 
#endif


#include "sp.h"
#include <conio.h>
#include <stdio.h>
#include <apple2.h>
#include <peekpoke.h>

#define SP_CMD_STATUS 0
#define SP_CMD_CONTROL 4
#define SP_CMD_OPEN 6
#define SP_CMD_CLOSE 7
#define SP_CMD_READ 8
#define SP_CMD_WRITE 9
#define SP_STATUS_PARAM_COUNT 3
#define SP_CONTROL_PARAM_COUNT 3
#define SP_OPEN_PARAM_COUNT 1
#define SP_CLOSE_PARAM_COUNT 1
#define SP_READ_PARAM_COUNT 4
#define SP_WRITE_PARAM_COUNT 4

// extern globals:
uint8_t sp_payload[1024];
uint16_t sp_count;
uint8_t sp_dest;
uint16_t sp_dispatch;
uint8_t sp_error;

static uint8_t sp_cmdlist[10];
static uint8_t sp_cmdlist_low, sp_cmdlist_high;
static uint8_t sp_err, sp_rtn_low, sp_rtn_high;

int8_t sp_status(uint8_t dest, uint8_t statcode)
{
  sp_error = 0;
  // build the command list
  sp_cmdlist[0] = SP_STATUS_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();
  sp_cmdlist[2] = (uint8_t)((uint16_t)&sp_payload & 0x00FF);
  sp_cmdlist[3] = (uint8_t)((uint16_t)&sp_payload >> 8) & 0xFF;
  sp_cmdlist[4] = statcode;

  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;


  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_STATUS);
  __asm__ volatile ("sta %g", spCmd); // store status command # 
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find SP entry point using algorithm from firmware reference
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("stx %v", sp_rtn_low);
  __asm__ volatile ("sty %v", sp_rtn_high);
  __asm__ volatile ("sta %v", sp_err);
  
  sp_count = ((uint16_t)sp_rtn_high << 8) | (uint16_t)sp_rtn_low;
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_control(uint8_t dest, uint8_t ctrlcode)
{
  sp_error = 0;
  // sp_dest = 5; // need to search
  // build the command list
  sp_cmdlist[0] = SP_CONTROL_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();
  sp_cmdlist[2] = (uint8_t)((uint16_t)&sp_payload & 0x00FF);
  sp_cmdlist[3] = (uint8_t)((uint16_t)&sp_payload >> 8) & 0xFF;
  sp_cmdlist[4] = ctrlcode;

  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;

  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_CONTROL);
  __asm__ volatile ("sta %g", spCmd); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find entry point and used it instead of hardcoded address
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("sta %v", sp_err);
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_open(uint8_t dest)
{
  sp_error = 0;
  // sp_dest = 5; // need to search
  // build the command list
  sp_cmdlist[0] = SP_OPEN_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();

  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;

  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_OPEN);
  __asm__ volatile ("sta %g", spCmd); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find entry point and used it instead of hardcoded address
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("sta %v", sp_err);
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_close(uint8_t dest)
{
  sp_error = 0;
  // sp_dest = 5; // need to search
  // build the command list
  sp_cmdlist[0] = SP_CLOSE_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();

  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;

  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_CLOSE);
  __asm__ volatile ("sta %g", spCmd); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find entry point and used it instead of hardcoded address
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("sta %v", sp_err);
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_read(uint8_t dest, uint16_t len)
{
  sp_error = 0;
  // sp_dest = 5; // need to search
  // build the command list
  sp_cmdlist[0] = SP_READ_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();
  sp_cmdlist[2] = (uint8_t)((uint16_t)&sp_payload & 0x00FF);
  sp_cmdlist[3] = (uint8_t)((uint16_t)&sp_payload >> 8) & 0xFF;
  sp_cmdlist[4] = len & 0xFF;
  sp_cmdlist[5] = len >> 8;
  
  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;

  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_READ);
  __asm__ volatile ("sta %g", spCmd); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find entry point and used it instead of hardcoded address
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("sta %v", sp_err);
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_write(uint8_t dest, uint16_t len)
{
  sp_error = 0;
  // build the command list
  sp_cmdlist[0] = SP_READ_PARAM_COUNT; 
  sp_cmdlist[1] = dest; // set before calling sp_status();
  sp_cmdlist[2] = (uint8_t)((uint16_t)&sp_payload & 0x00FF);
  sp_cmdlist[3] = (uint8_t)((uint16_t)&sp_payload >> 8) & 0xFF;
  sp_cmdlist[4] = len & 0xFF;
  sp_cmdlist[5] = len >> 8;
  
  sp_cmdlist_low = (uint8_t)((uint16_t)&sp_cmdlist & 0x00FF);
  sp_cmdlist_high = (uint8_t)((uint16_t)&sp_cmdlist >> 8) & 0xFF;

  // store cmd list
  __asm__ volatile ("lda #%b", SP_CMD_WRITE);
  __asm__ volatile ("sta %g", spCmd); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_low);
  __asm__ volatile ("sta %g", spCmdListLow); // store status command #
  __asm__ volatile ("lda %v", sp_cmdlist_high);
  __asm__ volatile ("sta %g", spCmdListHigh); // store status command #
  
  __asm__ volatile ("jsr $C50D"); // to do - find entry point and used it instead of hardcoded address
spCmd:
  __asm__ volatile ("nop");
spCmdListLow:
  __asm__ volatile ("nop");
spCmdListHigh:
  __asm__ volatile ("nop");
  __asm__ volatile ("sta %v", sp_err);
  sp_error = sp_err;
  return sp_err;
}

int8_t sp_find_fuji()
{
  // const char fuji[9] = "THE_FUJI";
  const char fuji[14] = "FUJINET_DISK_0";
  const uint8_t fuji_len = sizeof(fuji);
  int8_t err, num, i, j;

  err = sp_status(0x00, 0x00); // get number of devices
	if (err)
    return -err;
  num = sp_payload[0];
	num++;
	for (i = 1; i < num; i++)
	{
    //do
      err = sp_status(i, 0x03); // get DIB
    //while (err);
    if (sp_payload[4] == fuji_len)
    {
      for (j = 0; j < fuji_len; j++)
        if (fuji[j]!=sp_payload[5+j])
          return 0;
      sp_dest = i; // store the fuji unit #
      return i;
    }
	}
  return 0;
}

int8_t sp_find_network()
{
  const char net[7] = "NETWORK";
  const uint8_t net_len = sizeof(net);
  int8_t err, num, i, j;

  err = sp_status(0x00, 0x00); // get number of devices

  if (err)
    return -err;

  num = sp_payload[0];
  num+=2;

  for (i = 1; i < num; i++)
    {
      err = sp_status(i, 0x03); // get DIB

      if (sp_payload[4] == net_len)
	{
	  for (j = 0; j < net_len; j++)
	    if (net[j]!=sp_payload[5+j])
	      return 0;

	  return i;
	}
    }
  printf("NET NOT FOUND");
  cgetc();
  return 0;
}

/**
 * Apple // SmartPort routines for CC65
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 *
 */

/**
 * Check for SmartPort presence
 * @return slot #, or 0xFF if not present.
 */
uint8_t sp_find_slot(void)
{
  uint8_t s=0;

  for (s=7; s-- > 0;)
    {
      uint16_t a = 0xc000 + (s * 0x100);
      if ((PEEK(a+1) == 0x20) &&
          (PEEK(a+3) == 0x00) &&
          (PEEK(a+5) == 0x03) &&
          (PEEK(a+7) == 0x00))
        return s;
    }

  // Did not find.
  return 0;
}

/**
 * Return dispatch address for Smartport slot.
 * @param s Slot # (1-7)
 * @return smartport dispatch address
 */
uint16_t sp_dispatch_address(uint8_t slot)
{
  uint16_t a = (slot * 0x100) + 0xC000;
  uint8_t j = PEEK(a+0xFF);

  return a + j + 3;
}

void sp_init(void)
{
  uint8_t slot, f;
  slot = sp_find_slot();
  if (slot)
    sp_dispatch = sp_dispatch_address(slot);
  else
    cprintf("No SmartPort Firmware Found!");
  //sp_list_devs();
  f = sp_find_fuji();
  if (f < 1)
    cprintf("FujiNet Not Found!");
}

#endif /* BUILD_APPLE2 */
