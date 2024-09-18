#include <stdio.h>  
#include <string.h>  
#include <wiringPi.h>
#include <wiringSerial.h>
#include <termio.h>

#define GPIO0 0
#define GPIO3 3

#define baud_rate 115200
int getch(void) 
{
    int ch ;
    struct termios buf;
    struct termios save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN]=1;
    buf.c_cc[VTIME]=0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0,TCSAFLUSH, &save);
    return ch;
     }

int main(void)
{ 
   
   int fd;
   unsigned char test,receive_char;
   
   if(wiringPiSetup() == -1)
   {
      printf("wiringPi setup error !\n");
      return -1;
   }
   
   if((fd= serialOpen("/dev/ttyACM0",baud_rate))< 0)
   {
      printf("UART open error !\n");
      return -1;
   }
      
   pinMode(GPIO0,INPUT);
   pinMode(GPIO3,OUTPUT);
   
   // printf("GPIO PIN3 : Low \n");
   //digitalWrite(GPIO3, LOW);
   //delay*(1000);
      test = 'A';
      serialPutchar(fd,test);
      delay(100);
      
   while(1)
   {
      test = getch();
      
      if(test == 'A')
      {
         printf("Input A : %c\n",test);
         serialPutchar(fd,test);
      }
      else
      {
         printf("Input not A : %c\n",test);
         serialPutchar(fd,test);
      }
      delay(50);
         
      while(serialDataAvail(fd))
      {
         receive_char = serialGetchar(fd);
         printf("Received char : %d %c\n",receive_char,receive_char);
      }
      delay(2);
         //test = receive_char + 0;
         //if(test == 'Z') test = 'A'-1;
      
   }
   return 0;
}
