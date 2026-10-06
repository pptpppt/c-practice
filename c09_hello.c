/* ============================================================================
 * C09 · 指针作参数（突破值传递 / swap / 传址返回多个结果）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c09_hello.c -o c09_hello.exe
 * 运行：c09_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 *
 * ⚠️ c05 任务 5 留下的那个「改不动」的遗憾，今天彻底翻案。
 * ==========================================================================*/

/* ---------------- 模范示例 1：值传递为什么改不动 --------------------------
#include <stdio.h>

void wrong(int x) { x = 100; }        // 形参是副本，改的是副本

int main(void) {
    int a = 10;
    wrong(a);
    printf("a = %d\n", a);            // 还是 10
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：传地址就能改（真正的 swap）------------------
#include <stdio.h>

void swap(int *px, int *py) {         // 参数是指针：接收地址
    int t = *px;                      // 取出 px 指向的值
    *px = *py;                        // 把 py 指向的值写进 px 指向的房间
    *py = t;
}

int main(void) {
    int a = 3, b = 5;
    printf("交换前：a=%d b=%d\n", a, b);
    swap(&a, &b);                     // 关键：实参要加 &
    printf("交换后：a=%d b=%d\n", a, b);
    return 0;
}
 *
 * 三步记住：
 *   ① 形参写成 int *px
 *   ② 函数内部用 *px 拿值/改值
 *   ③ 调用时实参加 &
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：用「输出参数」返回多个结果 ------------------
 * C 的函数只能 return 一个值。想返回多个，就让别人先把房间地址交出来：
 *
#include <stdio.h>

// 一次算出最高、最低、平均，通过指针写回三个变量
void analyze(int arr[], int len, int *pmax, int *pmin, double *pavg) {
    *pmax = arr[0];
    *pmin = arr[0];
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] > *pmax) { *pmax = arr[i]; }
        if (arr[i] < *pmin) { *pmin = arr[i]; }
        sum += arr[i];
    }
    *pavg = sum / (double)len;
}

int main(void) {
    int a[] = {22, 25, 28, 26, 24};
    int len = sizeof(a) / sizeof(a[0]);
    int max, min;
    double avg;

    analyze(a, len, &max, &min, &avg);
    printf("最高%d 最低%d 平均%.1f\n", max, min, avg);
    return 0;
}
 *
 * 实战经验：以后看到函数参数里有一堆 *xxx，
 * 基本就是「这参数是给你往外带结果的」。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：不想被改就用 const --------------------------
 *     void print_arr(const int *arr, int len) { ... }
 *
 * 加了 const，函数里写 arr[0] = 99 会直接编译报错。
 * 这是给自己和别人看的「只读声明」，工程代码里很常见。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

void swap(int *px, int *py);
void analyze(int arr[], int len, int *pmax, int *pmin, double *pavg);
void print_arr(const int *arr, int len);

int main(void) {
    printf("---- swap 演示 ----\n");
    int a = 3, b = 5;
    printf("交换前：a=%d b=%d\n", a, b);
    swap(&a, &b);
    printf("交换后：a=%d b=%d\n", a, b);

    printf("\n---- 一次算出三个结果 ----\n");
    int temps[] = {22, 25, 28, 26, 24};
    int len = sizeof(temps) / sizeof(temps[0]);
    int max = 0, min = 0;
    double avg = 0.0;

    analyze(temps, len, &max, &min, &avg);
    printf("数据：");
    print_arr(temps, len);
    printf("最高 %d 度\n", max);
    printf("最低 %d 度\n", min);
    printf("平均 %.1f 度\n", avg);

    return 0;
}

// 交换两个 int 变量的值
void swap(int *px, int *py) {
    int t = *px;
    *px = *py;
    *py = t;
}

// 通过指针把三个统计结果写回调用者
void analyze(int arr[], int len, int *pmax, int *pmin, double *pavg) {
    *pmax = arr[0];
    *pmin = arr[0];
    int sum = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] > *pmax) { *pmax = arr[i]; }
        if (arr[i] < *pmin) { *pmin = arr[i]; }
        sum += arr[i];
    }
    *pavg = sum / (double)len;
}

// const 保证不会误改数据
void print_arr(const int *arr, int len) {
    for (int i = 0; i < len; i++) { printf("%d ", arr[i]); }
    printf("\n");
}
