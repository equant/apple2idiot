/**
 * ISS Tracker
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE.md for details.
 */

#include <conio.h>
#include <apple2.h>
#include <time.h>

void osd(char *lon, char *lat,unsigned long ts)
{
  cprintf("      ** CURRENT ISS POSITION **\r\n");
  cprintf(" LON: %-14s LAT: %-14s",lon,lat);
  cprintf("  AS OF: %s",ctime(&ts));
}
