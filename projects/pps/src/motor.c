#include "motor.h"
#include "os.h"
#include "ciaak.h"

//int Paso[8]={1000,1100,0100,0110,0010,0011,0001,1001};
uint16_t Paso[8]={0x040,0x0C0,0x080,0x180,0x100,0x300,0x200,0x240};

void Encender_Led(int32_t fd_out)
{
	uint16_t outputs;
	ciaaPOSIX_read(fd_out, &outputs, 2);
	outputs ^= 0x400 ;
	ciaaPOSIX_write(fd_out, &outputs, 2);
}

void TurnOff(int32_t fd_out)
{
	uint16_t outputs;
	ciaaPOSIX_read(fd_out, &outputs, 2);
	outputs = outputs & 0x03F ;
	ciaaPOSIX_write(fd_out, &outputs, 2);
}
void Stepper(int *Direction, int *Steps,int32_t fd_out)
{
	uint16_t outputs;
	outputs=Paso[*Steps];
	ciaaPOSIX_write(fd_out, &outputs, 2);
	SetDirection(Direction,Steps);
}

void SetDirection(int *Direction,int *Steps)
{
   if(*Direction)
      (*Steps)++;
   else
      (*Steps)--;
   if ((*Steps)>7) (*Steps)=0;
   if ((*Steps)<0) (*Steps)=7;
}
