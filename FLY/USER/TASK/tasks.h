#include "./TASK/task.h"
#ifdef __cplusplus
       extern "C" {
#endif
extern int task_bmp085(void);
extern int task_ultrasonic(void);
extern int task_pwm_ex(void);
extern int task_led(void);
extern int task_hmc5883l(void);
extern int task_cap_rc(void);
extern int loop_fast(void);//500hz
extern int task_6050(void);
extern int task_fast(void);//500hz
extern int task_gps(void);
extern int task_gsm(void);
#ifdef __cplusplus
        }
#endif

