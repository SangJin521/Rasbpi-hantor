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

#include "spi.h"

#define DEVICE_MAX 32

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

const u_int8_t MODE = SPI_MODE_0;
const u_int8_t BITS = 8;
const u_int32_t CLOCK = 1000000;
const u_int16_t DELAY = 5;

int spi_init(int spi)
{
    char device[DEVICE_MAX];

    snprintf(device, DEVICE_MAX, "/dev/spidev0.%d", spi);

    int fd = open(device, O_RDWR);

    if (fd < 0)
    {
        perror("SPI Error: Can't open device.");
        return -1;
    }

    return fd;
}

int spi_set(int fd)
{
    if (ioctl(fd, SPI_IOC_WR_MODE, &MODE) == -1)
    {
        perror("SPI_IOC_WR_MODE");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &BITS) == -1)
    {
        perror("SPI_IOC_WR_BITS_PER_WORD");
        return -1;
    }

    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &CLOCK) == -1)
    {
        perror("SPI_IOC_WR_MAX_SPEED_HZ");
        return -1;
    }

    return 0;
}

uint8_t control_bits_differential(uint8_t channel)
{
    return ((channel & 0x7) << 4);
}

uint8_t control_bits(uint8_t channel)
{
    return (0x8 | control_bits_differential(channel));
}

int read_adc(int fd, uint8_t channel)
{
    uint8_t tx[] = {1, control_bits(channel), 0};
    uint8_t rx[3];

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = ARRAY_SIZE(tx),
        .delay_usecs = DELAY,
        .speed_hz = CLOCK,
        .bits_per_word = BITS,
    };

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) == 1)
    {
        perror("SPI_IOC_MESSAGE");
        abort();
    }

    return ((rx[1] << 8) | rx[2]) & 0x3FF;
}

int spi_final(int fd)
{
    if (close(fd) == -1)
    {
        return -1;
    }
    
    return 0;
}