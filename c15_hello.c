/* ============================================================================
 * C15 · 命令行参数 + Makefile + 调试（工程化的最后一课）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c15_hello.c -o c15_hello.exe
 * 运行：c15_hello.exe 28 62.5
 *      c15_hello.exe --help
 * 中文乱码先在终端敲一次：chcp 65001
 * ==========================================================================*/

/* ---------------- 模范示例 1：argc / argv ---------------------------------
 * main 的完整写法其实是：
 *     int main(int argc, char *argv[])
 *
 *   argc  —— 命令行参数的个数（程序名自己算第一个）
 *   argv  —— 参数字符串数组，argv[0] 是程序名
 *
 * 运行 c15_hello.exe 28 62.5 时：
 *     argc = 3
 *     argv[0] = "c15_hello.exe"
 *     argv[1] = "28"
 *     argv[2] = "62.5"
 *
 * ⚠️ 所有取到的都是字符串！数字要自己用 sscanf / atoi 转换。
 *
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("参数个数 argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：字符串转数字 --------------------------------
 *     int    x = atoi("28");         // ASCII to int，stdlib.h
 *     double d = atof("62.5");       // ASCII to double，stdlib.h
 *     double d = strtod("62.5", NULL);   // 更严谨的版本，能检测转换失败
 *
 * Python 里 input() 拿到的也是字符串，规则一样，只是 C 要你自己调函数转。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：Makefile 长什么样 ---------------------------
 * 没有 Makefile 时，四五个文件要敲一长串命令；有了之后只敲一个 make。
 * 新建一个文件叫 Makefile（无扩展名），内容示例：
 *
 * ┌──────────────────────────────────────────────────────────┐
 * │ CC      = gcc                                            │
 * │ CFLAGS  = -Wall -g                                       │
 * │ TARGET  = app.exe                                        │
 * │ OBJS    = main.o sensor.o motor.o                        │
 * │                                                          │
 * │ $(TARGET): $(OBJS)                                       │
 * │ <TAB>$(CC) $(OBJS) -o $(TARGET)                          │
 * │                                                          │
 * │ main.o: main.c sensor.h motor.h                          │
 * │ <TAB>$(CC) $(CFLAGS) -c main.c                           │
 * │                                                          │
 * │ sensor.o: sensor.c sensor.h                              │
 * │ <TAB>$(CC) $(CFLAGS) -c sensor.c                         │
 * │                                                          │
 * │ clean:                                                   │
 * │ <TAB>del *.o *.exe                                       │
 * └──────────────────────────────────────────────────────────┘
 *
 * ⚠️ 每条命令前面必须是 **Tab 键**，不能用空格代替 —— 这是 Makefile 的死规矩。
 * 在 VSCode 里写 Makefile 时留意右下角是不是显示「空格: 4」，必要时手动敲 Tab。
 * 用法：make 编译、make clean 清理、make 之后再 make 只重编改动过的文件。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：调试 —— 段错误怎么查 ------------------------
 * 段错误（Segmentation fault）三大常见元凶：
 *     ① 解引用空指针 / 野指针
 *     ② 数组越界写入
 *     ③ 重复释放或访问已释放的内存
 *
 * 定位手段，按成本从低到高：
 *   A. printf 大法：在可疑位置前后插 printf，看程序死在哪两行之间
 *   B. gdb 官方写法：
 *          gcc -Wall -g xxx.c -o xxx.exe        （必须有 -g）
 *          gdb xxx.exe
 *          (gdb) run                      ← 跑起来
 *          (gdb) bt                       ← 崩了之后看调用栈，直接告诉你在第几行
 *          (gdb) print 变量名              ← 看变量当前的值
 *          (gdb) quit
 *   C. 注释二分法：注释掉一半代码，看还崩不崩，逐步缩小范围
 *
 * 初学推荐 A 和 C，等看 gdb 顺眼了再用 B。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    /* 没有参数时给个友好提示 */
    if (argc < 3) {
        printf("用法：%s <温度> <湿度>\n", argv[0]);
        printf("示例：%s 28 62.5\n", argv[0]);
        printf("可选：再加 --verbose 打印详细信息\n");
        return 1;
    }

    /* 字符串转数字 */
    int   temp = atoi(argv[1]);
    float humi = (float)atof(argv[2]);

    /* 是否带了 --verbose */
    int verbose = 0;
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--verbose") == 0) { verbose = 1; }
    }

    if (verbose) {
        printf("[调试] argc = %d\n", argc);
        for (int i = 0; i < argc; i++) {
            printf("[调试] argv[%d] = %s\n", i, argv[i]);
        }
    }

    printf("\n---- 巡检结论 ----\n");
    printf("温度 %d 度，湿度 %.1f%%\n", temp, humi);

    if (temp >= 35) {
        printf("判定：高温，加强通风\n");
    } else if (temp < 10) {
        printf("判定：低温，关闭风口保温\n");
    } else if (temp > 25 && humi < 40.0f) {
        printf("判定：偏干，启动灌溉\n");
    } else if (humi > 85.0f) {
        printf("判定：过湿，停止灌溉\n");
    } else {
        printf("判定：维持现状\n");
    }

    return 0;
}
