#ifndef __SPI_H__
#define __SPI_H__

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

int spi_init(int spi);  

int spi_set(int spi);

uint8_t control_bits_differential(uint8_t channel);

uint8_t control_bits(uint8_t channel);

int read_adc(int spi, uint8_t channel);

int spi_final(int fd);

#endif