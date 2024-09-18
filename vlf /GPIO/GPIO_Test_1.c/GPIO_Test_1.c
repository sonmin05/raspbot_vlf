#include <stdio.h>  
#include <string.h>  
#include <wiringPi.h>
#include <wiringSerial.h>

#define GPIO0 0
#define GPIO3 3

#define baud_rate 115200

int main(void)
{ 
   
   int fd;
   unsigned char test;
   
   if(wiringPiSetup() == -1)
   {
      printf("wiringPi setup error !\n");
      return -1;
   }
   
   if((fd= serialOpen("/dev/ttys0",baud_rate))< 0)
   {
      printf("UART open error !\n");
      return -1;
   }
      
   pinMode(GPIO0,INPUT);
   pinMode(GPIO3,OUTPUT);
   
   // printf("GPIO PIN3 : Low \n");
   //digitalWrite(GPIO3, LOW);
   //delay*(1000);
   
   while(1)
   {
      printf("GPIO Pin Read : %ld \n",digitalRead(GPIO0));
      delay(1000);
   }
   return 0;
}
