#ifndef SENSOR_H
#define SENSOR_H

/* ============================================================================
 * sensor.h —— Sensor 模块的对外接口（配套 c13）
 * ----------------------------------------------------------------------------
 * 规矩：
 *   1. 只放「类型定义」和「函数声明」，不放函数体
 *   2. 前三行 #ifndef/#define/#endif 是 include guard，照抄别删
 *   3. 需要 stdio.h 的功能请放进 .c 里 include，头文件尽量干净
 * ==========================================================================*/

/* --- 类型定义 --- */
typedef struct {
    char  shed;      // 棚号
    int   temp;      // 温度
    float humi;      // 湿度
} Sensor;

/* --- 函数声明：外部可调用的接口 --- */

// 构造一个 Sensor（相当于 Python 的构造函数）
Sensor make_sensor(char shed, int temp, float humi);

// 打印单个传感器的信息
void   print_sensor(const Sensor *ps);

// 打印一组传感器台账
void   print_all(const Sensor *arr, int len);

// 是否需要灌溉：温度>25 且 湿度<40
int    need_irrigation(const Sensor *ps);

// 是否温度异常：>=35 或 <10
int    is_abnormal(const Sensor *ps);

// 返回温度最高的那个元素的下标
int    hottest_index(const Sensor *arr, int len);

#endif
