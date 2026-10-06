/* ============================================================================
 * C04 · 数组（一维 / 二维 / 遍历 / 排序）
 *                                          （对应 Python day09_list_stats）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c04_hello.c -o c04_hello.exe
 * 运行：c04_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 * ==========================================================================*/

/* ---------------- 模范示例 1：声明、初始化、访问 --------------------------
 * 语法：类型 数组名[长度];
 *
 *     int temps[5] = {22, 25, 28, 26, 24};      // 全部初始化
 *     int temps[5] = {22, 25};                  // 剩下的自动补 0
 *     int temps[]  = {22, 25, 28, 26, 24};      // 长度由初值个数决定，得 5
 *
 * 下标从 0 开始！temps[0] 是第一个，temps[4] 是最后一个。
 *
#include <stdio.h>

int main(void) {
    int temps[5] = {22, 25, 28, 26, 24};
    printf("第 1 个：%d\n", temps[0]);
    printf("第 5 个：%d\n", temps[4]);

    temps[2] = 30;                       // 改第三个
    printf("改后第 3 个：%d\n", temps[2]);

    for (int i = 0; i < 5; i++) {
        printf("temps[%d] = %d\n", i, temps[i]);
    }
    return 0;
}
 *
 * 坑：temps[5] 是越界访问（合法下标只有 0~4）。
 *     C 完全不拦你，结果是「相邻内存里的随机值」，运行时才出乱子。
 *     这是 C 最危险的地方之一 —— 没有 Python 那种 IndexError 保护。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：求长度（sizeof 技巧）------------------------
 * 数组一旦传给函数，长度信息就丢了，所以要么传长度进去，要么在这里算：
 *
 *     int len = sizeof(temps) / sizeof(temps[0]);
 *              ↑ 整个数组的字节数     ↑ 一个元素的字节数
 *
 * 注意：这招只在同一个作用域内有效。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：遍历找最大 / 最小 / 求和 --------------------
#include <stdio.h>

int main(void) {
    int temps[] = {22, 25, 28, 26, 24};
    int len = sizeof(temps) / sizeof(temps[0]);

    int max = temps[0];         // 别初始化成 0！万一全是负数就错了
    int min = temps[0];
    int sum = 0;

    for (int i = 0; i < len; i++) {
        if (temps[i] > max) { max = temps[i]; }
        if (temps[i] < min) { min = temps[i]; }
        sum += temps[i];
    }
    printf("最高 %d  最低 %d  平均 %.1f\n", max, min, sum / (double)len);
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：二维数组（棚 × 时刻）------------------------
 *     int data[3][4] = {
 *         {20, 22, 25, 24},      // 1 棚四个时刻
 *         {21, 23, 26, 25},      // 2 棚
 *         {19, 21, 24, 23}       // 3 棚
 *     };
 *
 * 遍历要两层循环：行在外、列在内。
 *     for (int r = 0; r < 3; r++) {
 *         for (int c = 0; c < 4; c++) { printf("%d ", data[r][c]); }
 *         printf("\n");
 *     }
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 5：冒泡排序（先会用，原理后面再说）------------
#include <stdio.h>

int main(void) {
    int a[] = {28, 22, 31, 25, 19};
    int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {          // 大的往后挪
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    for (int i = 0; i < n; i++) { printf("%d ", a[i]); }
    printf("\n");
    return 0;
}
 * 交换三个变量值那三行是经典写法：先存一个，再覆盖，再放回。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

int main(void) {
    int temps[] = {22, 25, 28, 26, 24, 31, 19};
    int len = sizeof(temps) / sizeof(temps[0]);

    int max = temps[0];
    int min = temps[0];
    int sum = 0;

    for (int i = 0; i < len; i++) {
        if (temps[i] > max) { max = temps[i]; }
        if (temps[i] < min) { min = temps[i]; }
        sum += temps[i];
    }

    printf("---- 一周温度统计 ----\n");
    printf("天数：%d\n", len);
    printf("最高：%d 度\n", max);
    printf("最低：%d 度\n", min);
    printf("平均：%.1f 度\n", sum / (double)len);

    printf("\n高于平均的天：");
    double avg = sum / (double)len;
    for (int i = 0; i < len; i++) {
        if (temps[i] > avg) { printf("第%d天(%d) ", i + 1, temps[i]); }
    }
    printf("\n");

    return 0;
}
