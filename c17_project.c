/* ============================================================================
 * C17 项目② · 传感器数据管线（多文件 + 动态内存 + 完整流程）
 * ----------------------------------------------------------------------------
 * 目标：把 c16 的单文件版本改造成「工程级多文件 + 动态扩容」
 * 预计：4 个源文件 + 2 个头文件，约 400 行
 *
 * ⚠️ 这一课的关键词是「管线」：数据从一端进，经过几道工序，从另一端出报告。
 *    工业软件基本都是这个形状（传感器采集 → 清洗 → 分析 → 输出）。
 * ==========================================================================*/

/*
 * ┌────────────────────── 文件结构（自己建）──────────────────────────┐
 * │ record.h / record.c     数据结构 + 单条记录的读写处理              │
 * │ pipeline.h / pipeline.c 整批数据的流程：加载、清洗、统计、输出      │
 * │ c17_project.c           main：串起整条流水线                       │
 * │ Makefile                一键编译                                   │
 * └──────────────────────────────────────────────────────────────────┘
 *
 * 编译（写完 Makefile 之后就只用 make）：
 *     gcc -Wall -g c17_project.c record.c pipeline.c -o c17.exe
 */

/*
 * ┌──────────────────────── 需求 ────────────────────────────────────┐
 * │ 一个命令行工具，处理 CSV 格式的传感器数据文件：                     │
 * │                                                                  │
 * │     输入文件格式（data.csv，可用记事本手写几行）：                  │
 * │         shed,temp,humi                                           │
 * │         A,28,62.5                                                │
 * │         B,31,35.0                                                │
 * │         C,19,88.0                                                │
 * │         D,-999,50.0        ← -999 是常见的「传感器故障」哨兵值      │
 * │         E,36,30.0                                                │
 * │                                                                  │
 * │ 程序要做完这条流水线：                                             │
 * │     ① load   读文件，动态申请内存（数据量编译时不知道）            │
 * │     ② clean  剔除故障记录（temp == -999）和明显离谱的值            │
 * │     ③ stat   统计最高温/最低温/平均温/平均湿/报警数                │
 * │     ④ report 生成 report.txt，带表头和判定建议                     │
 * │                                                                  │
 * │ 命令行用法：                                                      │
 * │     c17.exe run <数据文件>        跑完整条流水线，输出 report.txt   │
 * │     c17.exe check <数据文件>      只做 ①②，打印「清洗掉了几条」    │
 * └──────────────────────────────────────────────────────────────────┘
 *
 * ┌────────────────── 分步建议（每步编译一次）────────────────────────┐
 * │ 第 1 步：record.h 定义结构体 + 三个最小函数，跑通 hello world 级调用 │
 * │ 第 2 步：pipeline.c 实现 load_xxx，先固定申请 100 个，能读进数据     │
 * │ 第 3 步：把固定 100 改成动态扩容（realloc 翻倍）                    │
 * │ 第 4 步：实现 clean_xxx，剔除 -999，返回剔除条数                    │
 * │ 第 5 步：实现 stat_xxx，用输出参数返回多个统计值                    │
 * │ 第 6 步：实现 write_report，生成带表头的 report.txt                 │
 * │ 第 7 步：main 里接 argc/argv，实现 run / check 两个子命令           │
 * │ 第 8 步：写 Makefile，make 一次通过                                 │
 * └──────────────────────────────────────────────────────────────────┘
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>          // strcmp 在这里

/* ======================== record.h 该写什么 ======================== */
/* （把下面这段复制进你新建的 record.h）
 *
 * typedef struct {
 *     char  shed;
 *     int   temp;
 *     float humi;
 * } Record;
 *
 * Record  make_record(char shed, int temp, float humi);
 * const char *judge(const Record *r);          // 沿用 c16 的判定逻辑
 * void    print_record(const Record *r);
 * int     is_valid(const Record *r);           // temp != -999 且 在合理范围
 * int     parse_line(const char *line, Record *out);   // 拆一行 CSV
 */

/* ======================== pipeline.h 该写什么 ====================== */
/* （把下面这段复制进你新建的 pipeline.h）
 *
 * #include "record.h"
 *
 * // 从文件加载，返回新数组的地址，条数写进 *pcount；失败返回 NULL
 * Record *load_records(const char *path, int *pcount);
 *
 * // 清洗：把无效记录剔掉，返回保留下来的条数
 * int     clean_records(Record *arr, int count);
 *
 * // 统计：结果通过输出参数带回来
 * void    stat_records(const Record *arr, int count,
 *                      int *pmax, int *pmin, double *pavg_temp,
 *                      double *pavg_humi, int *palarm);
 *
 * // 排序：按温度从高到低
 * void    sort_by_temp(Record *arr, int count);
 *
 * // 生成报告文件，成功返回 1
 * int     write_report(const Record *arr, int count, const char *path);
 */

int main(int argc, char *argv[]) {
    /* 先做一件事：确认参数够不够 */
    if (argc < 3) {
        printf("用法：%s <run|check> <数据文件>\n", argv[0]);
        printf("  run    跑完整流水线，生成 report.txt\n");
        printf("  check  只做加载和清洗，打印清洗情况\n");
        return 1;
    }

    if (strcmp(argv[1], "check") == 0) {
        /* 练习 1：加载 + 清洗，打印「原始 N 条，有效 M 条，剔除 N-M 条」 */
        printf("TODO: 实现 check 分支\n");
    } else if (strcmp(argv[1], "run") == 0) {
        /* 练习 2：完整流水线 */
        printf("TODO: 实现 run 分支\n");
    } else {
        printf("未知子命令：%s\n", argv[1]);
        return 1;
    }

    return 0;
}

/* ┌────────────────── 验收标准（逐条打勾）────────────────────────────┐
 * │ □ make 一次编译通过，零警告                                        │
 * │ □ 数据文件有多少行都能读（不会因为超过 100 条就崩）                 │
 * │ □ -999 的记录被正确剔除，且打印剔除了几条                           │
 * │ □ report.txt 有表头，每条记录带判定建议                             │
 * │ □ 传不存在的文件名时给出友好提示，不崩溃                            │
 * │ □ 用 valgrind 或手动检查：所有 malloc 都有对应的 free               │
 * │ □ main 函数里的脏活都挪进了 record.c / pipeline.c                   │
 * │ □ 换个同事看你的 record.h，不用读 .c 就知道怎么用这个模块           │
 * └──────────────────────────────────────────────────────────────────┘ */
