/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/* 
 * File:   lsm303_sensor.h
 * Author: ankit
 *
 * Created on March 1, 2016, 4:04 PM
 */

#ifndef LSM303_SENSOR_H
#define LSM303_SENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

    
#include <linux/i2c-dev.h>
#include <linux/i2c.h>


struct lsm303
{
    char *dev; 	// device file i.e. /dev/i2c-N
    int addr;	// i2c address
    int fd;		// file descriptor
};

/*
 * opens the device at [dev_fqn] (i.e. /dev/i2c-N)
 */
int lsm303_open(char *dev_fqn, int addr, struct lsm303*);
/*
 * closees the device [e] 
 */
int lsm303_close(struct lsm303 *e);
/*
 * read and returns the eeprom byte at memory address [mem_addr] 
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int lsm303_read_byte(struct lsm303* e, __u16 mem_addr);
/*
 * read the current byte
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int lsm303_read_current_byte(struct lsm303 *e);
/*
 * writes [data] at memory address [mem_addr] 
 * Note: eeprom must have been selected by ioctl(fd,I2C_SLAVE,address) 
 */
int lsm303_write_byte(struct lsm303 *e, __u16 mem_addr, __u8 data);




#ifdef __cplusplus
}
#endif

#endif /* LSM303_SENSOR_H */

