/* ============================================================================
 * sensor.c —— Sensor 模块的实现（配套 c13）
 * ----------------------------------------------------------------------------
 * 规矩：
 *   1. 必须 #include "sensor.h"（双引号表示「本项目的头文件」）
 *   2. 只实现 .h 里声明过的函数
 *   3. 设有 module 内部辅助函数的习惯：不想对外暴露的函数加 static
 * ==========================================================================*/

#include <stdio.h>
#include "sensor.h"

/* 构造一个 Sensor 并返回（返回结构体拷贝，调用方拿到的是副本） */
Sensor make_sensor(char shed, int temp, float humi) {
    Sensor s;
    s.shed = shed;
    s.temp = temp;
    s.humi = humi;
    return s;
}

/* 打印单条记录 */
void print_sensor(const Sensor *ps) {
    printf("%c棚  温度 %2d 度  湿度 %5.1f%%\n", ps->shed, ps->temp, ps->humi);
}

/* 打印整张台账 */
void print_all(const Sensor *arr, int len) {
    for (int i = 0; i < len; i++) {
        print_sensor(&arr[i]);
    }
}

/* 又热又干才需要灌溉 */
int need_irrigation(const Sensor *ps) {
    return ps->temp > 25 && ps->humi < 40.0f;
}

/* 温度越界就是异常 */
int is_abnormal(const Sensor *ps) {
    return ps->temp >= 35 || ps->temp < 10;
}

/* 找出温度最高的元素下标（注意 len<=0 的保护） */
int hottest_index(const Sensor *arr, int len) {
    if (len <= 0) { return -1; }
    int idx = 0;
    for (int i = 1; i < len; i++) {
        if (arr[i].temp > arr[idx].temp) { idx = i; }
    }
    return idx;
}
