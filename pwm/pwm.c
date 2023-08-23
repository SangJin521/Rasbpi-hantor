#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> 

#include "pwm.h"

#define BUZZER_OUT_PWM 0

#define INTERVAL 1

void (*breakCapture)(int);

void signalingHandler(int signo) 
{
    PWMUnexport(BUZZER_OUT_PWM);
    exit(1);
}

int main() {

    setsid();
    umask(0);

    breakCapture = signal(SIGINT, signalingHandler);

    /*
     * Enable PMW pins
     */
    if (-1 == PWMExport(BUZZER_OUT_PWM)) {
        return (1);
    }

    /*
     * Set PWM Write Period
     */
    if (-1 == PWMWritePeriod(BUZZER_OUT_PWM, 2000000)) {
        return (2);
    }

    /*
     * Set PMW Write Duty Cycle
     */
    if (-1 == PWMWriteDutyCycle(BUZZER_OUT_PWM, 0)) {
        return (3);
    }   

    /*
     * Set PWM Enable
     */
    if (-1 == PWMEnable(BUZZER_OUT_PWM)) {
        return (4);
    }   

    int count = 0;

    do
    {
        for (int i = 150; i < 3000; i+=2) {
            if (-1 == PWMWriteDutyCycle(BUZZER_OUT_PWM, i * 1000)) { 
                return (5);
            }
            usleep(2);
        }
        for (int i = 3000; i > 150; i-=2) {
            if (-1 == PWMWriteDutyCycle(BUZZER_OUT_PWM, i * 1000)) { 
                return (5);
            }
            usleep(2);
        }

        PWMWriteDutyCycle(BUZZER_OUT_PWM, 0);

        sleep(INTERVAL);
    } while (count++ < 10);

    /*
     * Disable PWM pins
     */
    if (-1 == PWMUnexport(BUZZER_OUT_PWM)) {
        return (6);
    }

    return (0);
}