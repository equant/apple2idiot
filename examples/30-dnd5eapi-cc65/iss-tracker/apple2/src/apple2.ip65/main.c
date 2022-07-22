/**
 * ISS Tracker
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE.md for details.
 */

#include <conio.h>
#include <tgi.h>
#include <apple2.h>
#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "map.h"
#include "satellite.h"
#include "osd.h"
#include "ip65.h"

unsigned char net = ETH_INIT_DEFAULT;
char lon_s[16], lat_s[16];
int lat, lon;
long timer;
unsigned long ts;

void error_exit(char *op)
{
  printf("%s:%s\n",op,ip65_strerror(ip65_error));
  cgetc();
  exit(1);
}

void main(void)
{
  int f;
  f = open("ethernet.slot",O_RDONLY);
  if (f!=-1)
    {
      read(f,&net,sizeof(net));
      close(f);
      net &= ~'0';
    }
  
  if (ip65_init(net))
    error_exit("ip65_init");

  if (dhcp_init())
    error_exit("dhcp_init");
  
  tgi_install(tgi_static_stddrv);
  tgi_init();
  tgi_apple2_mix(true);
  tgi_clear();

  while (1)
    {
      timer=524088;
      clrscr();
      satellite_fetch(&lon,&lat,lon_s,lat_s,&ts);
      map();
      osd(lon_s,lat_s,ts);
      satellite(lon,lat);

      while (timer>0)
	{
	  if (kbhit())
	    switch(cgetc())
	      {
	      case 0x1b:
		return;
	      case 0x0D:
	      case 0x0A:
		timer=0;
		break;
	      default:
		break;
	      }

	  timer--;
	}
    }
}
