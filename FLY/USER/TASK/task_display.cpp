#include "./TASK/task.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "../../GLIB/PERIPHERAL/GSM/SIM900A/SIM900A.h"
int task_gsm(void)
{
    _SS
    WaitX(20);
    while (1)
    {
        WaitX(10);
    }
    _EE
}

#ifdef __cplusplus
}
#endif
