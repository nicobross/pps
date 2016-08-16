#include "os.h"
#include "ciaak.h"

void motor_run();
void TurnOff();
void Stepper(int *Direction, int *Steps,int32_t fd_out);
void SetDirection(int *Direction,int *Steps);
