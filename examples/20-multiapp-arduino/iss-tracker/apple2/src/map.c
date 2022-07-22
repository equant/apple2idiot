/**
 * ISS Tracker
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE.md for details.
 */
#include <apple2.h>
#include <6502.h>
#include <peekpoke.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void map(void)
{
  int f = open("MAP.HGR",O_RDONLY);

  if (f==-1)
    {
      perror("map open");
      cgetc();
      exit(1);
    }

  read(f,(void *)0x2000,0x2000);
  close(f);
}
