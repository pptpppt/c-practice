/* ============================================================================
 * C13 · 多文件与头文件（声明放 .h / 实现放 .c / 一起编译）
 * ----------------------------------------------------------------------------
 * 这一课不只是一个文件 —— 请先建好配套的三个文件，再回来对照：
 *
 *     sensor.h        类型定义 + 函数声明（对外接口）
 *     sensor.c        函数实现
 *     c13_hello.c     main：调用上面那些函数
 *
 * 编译必须把所有 .c 一起给 gcc：
 *     gcc -Wall -g c13_hello.c sensor.c -o c13_hello.exe
 * 运行：c13_hello.exe
 * ==========================================================================*/

/* ---------------- 为什么非要拆文件 ----------------------------------------
 * 到现在为止你写的所有程序都在一个 .c 里。到了几百行就会出问题：
 *     找一个函数要翻半天、改一处要重编全部、没法两个人协作。
 *
 * C 的工程惯例是「一个功能模块一对文件」：
 *     xxx.h   放：类型定义、函数声明、宏、extern 全局变量
 *     xxx.c   放：函数的具体实现
 *
 * 谁想用这个功能，就 #include "xxx.h"。
 * ------------------------------------------------------------------------- */

/* ---------------- 示范：sensor.h 应该长这样（另建文件）------------------
#ifndef SENSOR_H            // ← include guard：防止重复包含
#define SENSOR_H

// 类型定义
typedef struct {
    char  shed;
    int   temp;
    float humi;
} Sensor;

// 函数声明（外面要用的才写在这里）
void print_sensor(const Sensor *ps);
int  need_irrigation(const Sensor *ps);
Sensor make_sensor(char shed, int temp, float humi);

#endif
 * ------------------------------------------------------------------------- */

/* ---------------- 示范：sensor.c 应该长这样（另建文件）------------------
#include <stdio.h>
#include "sensor.h"          // 自己的头文件用双引号，系统的用尖括号

void print_sensor(const Sensor *ps) {
    printf("%c棚 %2d度 %.1f%%\n", ps->shed, ps->temp, ps->humi);
}

int need_irrigation(const Sensor *ps) {
    return ps->temp > 25 && ps->humi < 40.0f;
}

Sensor make_sensor(char shed, int temp, float humi) {
    Sensor s;
    s.shed = shed;
    s.temp = temp;
    s.humi = humi;
    return s;
}
 * ------------------------------------------------------------------------- */

/* ---------------- include guard 是干嘛的 ----------------------------------
 * #ifndef / #define / #endif 这三行保证：同一个 .h 被 include 多次也只生效一次。
 * 少了它，一旦 a.h 包含 b.h、main.c 又同时包含两者，就会报「重复定义」。
 * 这是头文件里的固定开场白，照抄即可。
 * ------------------------------------------------------------------------- */

/* ---------------- 编译多文件的三种写法 ------------------------------------
 * ① 一次编译（文件少时用这个）
 *      gcc -Wall -g c13_hello.c sensor.c -o app.exe
 *
 * ② 分开编译再链接（文件多时省时间，只重编改动过的）
 *      gcc -Wall -g -c sensor.c        → 生成 sensor.o
 *      gcc -Wall -g -c c13_hello.c     → 生成 c13_hello.o
 *      gcc sensor.o c13_hello.o -o app.exe
 *
 * ③ 写 Makefile（c15 专门讲）
 *      make
 *
 * 常见报错 undefined reference to 'xxx'：
 *     九成是编译时漏了某个 .c 文件，链接器找不到实现。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是这一课的 main 文件 ===================== */
#include <stdio.h>
#include "sensor.h"          // 用自己写的功能模块

int main(void) {
    Sensor a = make_sensor('A', 28, 62.5f);
    Sensor b = make_sensor('B', 31, 35.0f);
    Sensor c = make_sensor('C', 19, 88.0f);

    Sensor list[3] = {a, b, c};

    printf("---- 调用 sensor.c 里的函数 ----\n");
    for (int i = 0; i < 3; i++) {
        print_sensor(&list[i]);
    }

    printf("\n---- 灌溉判定 ----\n");
    for (int i = 0; i < 3; i++) {
        if (need_irrigation(&list[i])) {
            printf("%c 棚：需要灌溉\n", list[i].shed);
        } else {
            printf("%c 棚：维持现状\n", list[i].shed);
        }
    }

    return 0;
}
