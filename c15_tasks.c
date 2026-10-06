/* ============================================================================
 * C15 任务区 · 命令行参数 + Makefile + 调试
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c15_tasks.c -o c15_tasks.exe
 * 运行：c15_tasks.exe 28 62.5
 *
 * 【今天要记的规矩】
 *   1. argv 里全是字符串，数字要用 atoi / atof 转换
 *   2. 用之前先检查 argc 够不够，缺参数要给友好提示再退出
 *   3. Makefile 里命令前必须是 Tab，不能是空格
 *   4. 查段错误三板斧：printf 插桩 / gdb bt / 注释二分
 *   5. gcc 一定要带 -g，否则 gdb 看不到行号
 * ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 函数原型写在这 */


int main(int argc, char *argv[]) {

    /* 任务 1：先把 argv 打印清楚
     * 写一个循环打印 argc 和每个 argv[i]。
     * 分别这样运行，观察输出差异：
     *     c15_tasks.exe
     *     c15_tasks.exe 28
     *     c15_tasks.exe 28 62.5
     * 确认 argv[0] 是程序自己。
     */


    /* 任务 2：缺参数要给提示，不能崩
     * 加一段保护：
     *     if (argc < 3) {
     *         printf("用法：%s <温度> <湿度>\n", argv[0]);
     *         return 1;
     *     }
     * 不带参数跑一次，看是不是友好退出了。
     * 这条习惯很重要 —— 别人拿到你的程序，第一件事就是不带参数乱敲。
     */


    /* 任务 3：参数转换成数字
     *     int   temp = atoi(argv[1]);
     *     float humi = (float)atof(argv[2]);
     * 打印出来确认转对了。
     * 再试试传个非数字进去（c15_tasks.exe abc 62.5），
     * 观察 atoi("abc") 得到什么（0）—— 这就是为什么真实项目要用更严谨的 strtod。
     */


    /* 任务 4：加个开关参数
     * 支持可选参数 --verbose：出现时打印详细过程和全部 argv，不出现就只打印结论。
     *     scanf 思路：遍历 argv[3..argc-1]，用 strcmp 比对 "--verbose"
     * 运行两种并对比输出：
     *     c15_tasks.exe 28 62.5
     *     c15_tasks.exe 28 62.5 --verbose
     */


    /* 任务 5：写第一个 Makefile
     * 给 c13 的 sensor + 你自己写的模块建一个 Makefile（文件名就叫 Makefile，无后缀）：
     *     定义 CC / CFLAGS / TARGET / OBJS
     *     写 $(TARGET) 规则和每个 .o 的规则
     *     写 clean 规则
     * 然后依次执行：
     *     make            ← 应该一步编出来
     *     make            ← 第二次应该提示「已是最新」
     *     随便改一个 .c 里一个字符，再 make ← 只重编那个文件
     *     make clean      ← 清理干净
     * 踩坑提醒：命令前必须是 Tab 而不是空格。
     *     报错 missing separator ← 就是这条，检查一下是不是用了空格。
     */


    /* 任务 6（★）：gdb 找段错误
     * 先故意写一个会崩的程序（保存成 crash.c，别写在任务区里）：
     *     int *p = NULL;  printf("%d", *p);
     * 然后：
     *     gcc -Wall -g crash.c -o crash.exe
     *     gdb crash.exe
     *     (gdb) run
     *     (gdb) bt            ← 这一条会告诉你崩在第几行、哪个函数
     *     (gdb) quit
     * 对比一下：把 -g 去掉再编一次跑 gdb，看输出少了什么（没有行号了）。
     * 这就是编译命令里必须有 -g 的原因。
     */


    /* 任务 7（★★）：命令行版巡检工具（第三段的收官）
     * 做一个真正能从命令行用的程序，综合 c12 文件 + c13 多文件 + c15 参数：
     *
     *     patrol.exe stats <文件名>         读文件里的多行数据，打印统计报告
     *     patrol.exe add <文件> <棚号> <温度> <湿度>   追加一条记录到文件
     *     patrol.exe                        打印用法说明
     *
     * 示例：
     *     patrol.exe add data.txt A 28 62.5
     *     patrol.exe stats data.txt
     *     → 天数：3 / 最高：31 / 最低：19 / 平均：26.0 / 报警：1
     *
     * 工程要求：
     *     - 至少拆两个模块（建议 sensor.c/h 复用 c13 的）
     *     - 写 Makefile，make 之后能直接用
     *     - 每个 fopen 都判 NULL，每个 malloc 都配 free
     *     - 参数不够时打印用法而不是崩溃
     * 门槛：这个项目做完，你就具备了写 c16/c17/c18 的所有部件。
     *       剩下的差别只是「规模」和「不看笔记能不能写出来」。
     */


    return 0;
}
