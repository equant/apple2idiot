/**
 * ISS Tracker
 *
 * @author Thomas Cherryhomes
 * @email thom dot cherryhomes at gmail dot com
 * @license gpl v. 3, see LICENSE.md for details.
 */

#ifndef SATELLITE_H
#define SATELLITE_H

void satellite(int lon, int lat);
bool satellite_fetch(int *lon, int *lat, char *lon_s, char *lat_s, unsigned long *ts);

#endif /* SATELLITE_H */
