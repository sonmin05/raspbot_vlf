#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <termio.h>
#include <softPwm.h>

#define GPIO0  0 // Physical 11
#define GPIO3  3 // Physical 15

#define ENA  6 // Physical
#define IN1  4 // Physical
#define IN2  5 // Physical
#define ENB  0 // Physical
#define IN3  2 // Physical
#define IN4  3 // Physical

#define MAX_PWM_DUTY 100
#define baud_rate 115200

void sig_Handler(int sig);

int getch(void)
{
    int ch;
    struct termios buf;
    struct termios save;

    tcgetattr(0 ,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME]  = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}

int motor_control_setup(void)
{
    if(wiringPiSetup() == -1)
    {
        printf("wiringPi Setup error!\n");
        return -1;
    }

    signal(SIGINT, sig_Handler);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    softPwmCreate(ENA, 1, MAX_PWM_DUTY);
    softPwmCreate(ENB, 1, MAX_PWM_DUTY);

    softPwmWrite(ENA, 0);
    softPwmWrite(ENB, 0);
    return 0;
}

void motor_control_r(int pwm)
{
    if(pwm > 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        softPwmWrite(ENA, pwm);
    }
    else if(pwm == 0)
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        softPwmWrite(ENA, 0);
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        softPwmWrite(ENA, -pwm);
    }
}

void motor_control_l(int pwm)
{
    if(pwm > 0)
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        softPwmWrite(ENB, pwm);
    }
    else if(pwm == 0)
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, LOW);
        softPwmWrite(ENB, 0);
    }
    else
    {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        softPwmWrite(ENB, -pwm);
    }
}

int main(void)
{
    int fd;
    int pwm_r = 0;
    int pwm_l = 0;
    unsigned char test = 'B', receive_char;

    if(motor_control_setup() == -1)
    {
        return -1;
    }

    while(1)
    {
        test = getch();
         
        switch(test)
        {
           case 'w':
               motor_control_r(pwm_r);
               motor_control_l(pwm_l);
               pwm_r++;
               pwm_l++;
               break;
         
           case 's':
               motor_control_r(0);
               motor_control_l(0);
               break;
               
           case 'x':
               motor_control_r(-pwm_r);
               motor_control_l(-pwm_l);
               pwm_r--;
               pwm_l--;
               break;
        }
        motor_control_r(-30);
        motor_control_l(-30);
        delay(500);
    }

    return 0;
}

void sig_Handler(int sig)
{
    printf("\n\n\n\n\nProgram and Motor Stop!\n\n\n\n");
    motor_control_r(0);
    motor_control_l(0);
    exit(0);
}
