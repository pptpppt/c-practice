/* ============================================================================
 * C13 任务区 · 多文件与头文件
 * ----------------------------------------------------------------------------
 * 这一课不再是单文件！请按下面顺序建文件：
 *
 *     ① motor.h       类型定义 + 函数声明（自己写）
 *     ② motor.c       函数实现（自己写）
 *     ③ c13_tasks.c   main：调用上面模块（就是本文件）
 *
 * 编译命令（必须把所有 .c 都列上）：
 *     gcc -Wall -g c13_tasks.c motor.c -o c13_tasks.exe
 * 运行：c13_tasks.exe
 *
 * ⚠️ 忘了把 motor.c 写进命令 → undefined reference to 'xxx'
 *    这是多文件编译最常见的报错，见到它就查命令里是不是漏了文件。
 *
 * 【今天要记的规矩】
 *   1. .h 放类型定义和函数声明，.c 放实现
 *   2. .h 必须有 include guard（#ifndef/#define/#endif）
 *   3. .c 里要 #include "自己的.h"，双引号表示本项目文件
 *   4. 编译要把所有 .c 一起给 gcc
 *   5. 不想对外暴露的函数加 static
 * ==========================================================================*/

#include <stdio.h>
#include "motor.h"          // ← 这一行引用你自己写的 motor.h

int main(void) {

    /* 任务 1：先让编译跑起来
     * 按 c13_hello.c 顶部的说明，对照 sensor.h / sensor.c 的格式，
     * 自己写 motor.h 和 motor.c，实现最基础的两个函数：
     *     Motor make_motor(int rpm, float current, char status);
     *     void  print_motor(const Motor *m);
     * main 里构造一台电机并打印。
     * 关键：确认你能用多文件命令编译通过 —— 这是今天的第一道坎。
     */


    /* 任务 2：故意制造 undefined reference
     * 编译时故意只写 gcc -Wall -g c13_tasks.c -o x.exe（漏掉 motor.c）
     * 记下报错长什么样：undefined reference to `print_motor'
     * 这个报错以后每周都会见到，先认熟它的样子。
     */


    /* 任务 3：给模块加功能
     * 在 motor.h/motor.c 里继续加这些函数，main 里逐个调用测试：
     *     int   is_overload(const Motor *m);        // 电流 > 5.0 或 status=='F'
     *     void  set_target(Motor *m, int target);   // 改目标转速（注意没有 const！）
     *     float load_ratio(const Motor *m);         // 当前转速 / 目标转速
     * 想一想为什么有的参数加 const 有的不加 —— 答案写进注释。
     */


    /* 任务 4：体会 include guard 的作用
     * 在 main 里连写两行：
     *     #include "motor.h"
     *     #include "motor.h"
     * 有 include guard 时一切正常。把 motor.h 的 #ifndef/#define/#endif 三行删掉再编译，
     * 会看到「redefinition」类报错。看完记得加回去。
     */


    /* 任务 5：static 隐藏内部函数
     * 在 motor.c 里写一个辅助函数：
     *     static int clamp_rpm(int rpm) { ... }     // 把转速限制在 0~3000
     * 试着从 main 里直接调用 clamp_rpm —— 编译会报「未声明」。
     * 这就是 static 的作用：模块私有的工具函数，外面看不见。
     * 然后让 motor.c 内部自己的函数（set_target）去用它。
     */


    /* 任务 6（★）：三种编译姿势都走一遍
     * ① 一次性：gcc -Wall -g c13_tasks.c motor.c -o t1.exe
     * ② 分开编：gcc -Wall -g -c motor.c        → 看是不是多了 motor.o
     *           gcc -Wall -g -c c13_tasks.c    → 多了 c13_tasks.o
     *           gcc motor.o c13_tasks.o -o t2.exe
     * ③ 只改 motor.c 里一个数字，只重编 motor.o 再链接，看是不是快了。
     * 体会：文件多了以后，分开编译能省大量时间 —— 这也是 c15 Makefile 存在的理由。
     */


    /* 任务 7（★★）：把 c11 的台账拆成多文件（今天的收官）
     * 把 c11 任务 7 做过的「大棚巡检台账」改造成模块化版本：
     *     sensor.h / sensor.c    已经有了，直接复用！编译时加上它即可：
     *         gcc -Wall -g c13_tasks.c sensor.c motor.c -o app.exe
     *     patrol.h / patrol.c    新写一个「巡检」模块，负责：
     *         int  count_abnormal(const Sensor arr[], int len);
     *         void sort_by_temp(Sensor arr[], int len);
     *         void print_report(const Sensor arr[], int len);
     *     main 里：造 5 个 Sensor → print_report → sort_by_temp → print_report
     * 体会一件事：sensor.c 这种「通用模块」写好之后是可以反复复用的，
     *           下次要用，只要 #include + 编译时带上 .c，不用再抄一遍代码。
     *           这就是工程化的第一步，也是 c17/c18 的基础。
     */


    return 0;
}
