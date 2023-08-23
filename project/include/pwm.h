#ifndef __PWM_H__
#define __PWM_H__

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1

int PWMExport(int pwmnum);

int PWMUnexport(int pwmnum);

int PWMEnable(int pwmnum);

int PWMWritePeriod(int pwmnum, int value);

int PWMWriteDutyCycle(int pwmnum, int value);

#endif