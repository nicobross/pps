#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */
#include "pps.h"              /* <= own header */
#include "motor.h"

static int32_t fd_out;
int steps_left=4095;
int Direction = 1;
int Steps = 0; // Define el paso actual de la secuencia
int cont = 0;

int main(void)
{
   StartOS(AppMode1); /* Starts the operating system in the Application Mode 1 */
   return 0; /* StartOs shall never returns, but to avoid compiler warnings or errors 0 is returned */
}
void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

TASK(InitTask)/** \brief Initial task. This task is started automatically in the application mode 1.*/
{
   ciaak_start(); /* init CIAA kernel and devices */
   ciaaPOSIX_printf("Init Task...\n"); /* print message (only on x86) */
   fd_out = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR); /* open CIAA digital outputs */

   while(1){
   		/*while(steps_left>0){
   			Stepper(&Direction,&Steps,fd_out); //Avanza un paso
   		   	steps_left--; //Un paso menos
   		   	SetRelAlarm(WaitSleep, 1, 1); // sleep 1 milisecond
   		   	WaitEvent(Finish);
   		   	CancelAlarm(WaitSleep);
   		}
   		TurnOff(fd_out);*/
	   	Encender_Led(fd_out);
	   	SetRelAlarm(WaitSleep, 1000, 0); // sleep 300 milisecond
   		WaitEvent(Finish);
   		CancelAlarm(WaitSleep);
   		/*TurnOff(fd_out);
   		SetRelAlarm(WaitSleep, 300, 0); // sleep 300 milisecond
   		WaitEvent(Finish);*/
   		/*Direction = Direction%1;  //Invertimos la direceccion de giro
   		steps_left = 4095;*/
   	}
   TerminateTask();
}
/*==================[end of file]=====================*/
