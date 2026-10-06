/* ============================================================================
 * C12 · 文件 I/O（fopen / fclose / fprintf / fscanf / fgets）
 *                                          （对应 Python day07 / day18）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c12_hello.c -o c12_hello.exe
 * 运行：c12_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 *
 * ⚠️ 到这一课，你的程序终于能「记住东西」了 —— 数据不再随窗口关闭而消失。
 * ==========================================================================*/

/* ---------------- 模范示例 1：文件指针与四种模式 --------------------------
 * FILE *fp = fopen("路径", "模式");
 *
 * 模式速查：
 *     "r"    读（文件必须已存在，否则返回 NULL）
 *     "w"    写（不存在就新建，存在就**清空**！）
 *     "a"    追加写（不存在就新建，写到末尾）
 *     "r+"   读写
 * 二进制再加 b，如 "rb" "wb"（STM32 和 later 做数据块会用到）
 *
 * 用完必须 fclose(fp); —— 不关，缓冲区里的数据可能没落盘，而且泄漏文件句柄。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：写文件 fprintf ------------------------------
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("report.txt", "w");
    if (fp == NULL) {                       // 永远检查这一步！
        printf("打开失败\n");
        return 1;
    }

    fprintf(fp, "%c棚 温度%d度 湿度%.1f%%\n", 'A', 28, 62.5);
    fprintf(fp, "%c棚 温度%d度 湿度%.1f%%\n", 'B', 31, 35.0);

    fclose(fp);
    printf("已写入 report.txt\n");
    return 0;
}
 *
 * fprintf 的用法跟 printf 一模一样，只是多一个 fp 参数在前面。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：读文件 fscanf -------------------------------
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("report.txt", "r");
    if (fp == NULL) { printf("打开失败\n"); return 1; }

    char shed;
    int temp;
    float humi;

    // fscanf 成功时返回「读到的项数」，读到文件尾就不等于 3 了
    while (fscanf(fp, " %c棚 温度%d度 湿度%f%%", &shed, &temp, &humi) == 3) {
        printf("读到了：%c %d %.1f\n", shed, temp, humi);
    }

    fclose(fp);
    return 0;
}
 *
 * 跟 scanf 一样用 &（同一套套路：要往你变量里写就得给地址）。
 * 循环条件用返回值控制，这是读文件的标准写法。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：整行读 fgets（比 fscanf 常用）---------------
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("data.csv", "r");
    if (fp == NULL) { printf("打开失败\n"); return 1; }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {     // 每次读一整行
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
 *
 * fgets 的好处：不挑格式，整行拿回来，再用 sscanf（c06）慢慢拆。
 * 坏处：它会把行尾的 '\n' 一起读进来，打印时不用额外加换行。
 * 这是处理 CSV 类文件的正路。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 5：feof 与常见误区 -----------------------------
 * 错误写法（新手常见）：
 *     while (!feof(fp)) { fscanf(fp, ...); 处理; }
 * ↑ 会多处理最后一次失败的数据，因为 feof 要读失败后才置位。
 *
 * 正确写法：用读取函数的返回值作为循环条件（如示例 3、4 所示）。
 * 结论：初学阶段干脆别用 feof。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

int main(void) {
    FILE *fp = NULL;

    /* 1. 写文件 */
    fp = fopen("c12_output.txt", "w");
    if (fp == NULL) { printf("写入打开失败\n"); return 1; }

    fprintf(fp, "A 28 62.5\n");
    fprintf(fp, "B 31 35.0\n");
    fprintf(fp, "C 19 88.0\n");
    fclose(fp);
    printf("已写入 3 条记录到 c12_output.txt\n\n");

    /* 2. 用 fscanf 读回来 */
    fp = fopen("c12_output.txt", "r");
    if (fp == NULL) { printf("读取打开失败\n"); return 1; }

    printf("---- fscanf 解析结果 ----\n");
    char shed;
    int temp;
    float humi;
    while (fscanf(fp, " %c %d %f", &shed, &temp, &humi) == 3) {
        printf("%c棚 温度%2d度 湿度%5.1f%%\n", shed, temp, humi);
    }
    fclose(fp);

    /* 3. 用 fgets + sscanf 读同一份文件 */
    fp = fopen("c12_output.txt", "r");
    if (fp == NULL) { printf("读取打开失败\n"); return 1; }

    printf("\n---- fgets + sscanf 解析结果 ----\n");
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char s2;
        int t2;
        float h2;
        if (sscanf(line, " %c %d %f", &s2, &t2, &h2) == 3) {
            printf("行内容是[%s] → 拆出 %c %d %.1f\n", line, s2, t2, h2);
        }
    }
    fclose(fp);

    /* 4. 追加写 */
    fp = fopen("c12_output.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "D 36 30.0\n");
        fclose(fp);
        printf("\n已追加一条 D 棚记录\n");
    }

    return 0;
}
