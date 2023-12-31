#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1

int GPIOExport(int pin);

int GPIOUnexport(int pin);

int GPIODirection(int pin, int dir);

int GPIORead(int pin);

int GPIOWrite(int pin, int value);

#endif