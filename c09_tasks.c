/* ============================================================================
 * C09 任务区 · 指针作参数（swap / 输出参数 / const）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c09_tasks.c -o c09_tasks.exe
 * 运行：c09_tasks.exe
 *
 * 模范示例在 c09_hello.c 里，写之前先看一遍。
 *
 * 【今天要记的三步】
 *   1. 形参写成 int *px
 *   2. 函数内用 *px 取值 / 赋值
 *   3. 调用时实参加 & → f(&a)
 *
 * 【坑】
 *   1. 忘了在实参加 & → -Wall 警告，运行时崩
 *   2. 函数里忘了写 *（直接用 px = 5）→ 改的是指针本身，不是外面的变量
 *   3. 传 NULL 进去还解引用 → 段错误
 *   4. 想「返回多个值」时，别硬凑结构体，指针输出参数最直接
 * ==========================================================================*/

#include <stdio.h>

/* 函数原型写在这 */


int main(void) {

    /* 任务 1：先把失败版本写一遍
     * 写 void swap_wrong(int x, int y)，里面老老实实交换 x 和 y。
     * main 里 int a=3, b=5; swap_wrong(a,b); 打印 a 和 b。
     * 结果是没换过来 —— 这是 c05 任务 5 的重演，先看清楚失败的样子。
     */


    /* 任务 2：真正的 swap
     * 写 void swap(int *px, int *py)：
     *     用临时变量中转，通过 *px 和 *py 完成交换
     * main 里调用必须是 swap(&a, &b) —— 那个 & 是整个的关键。
     * 打印交换前后的值确认成功。
     * 再试一次故意错：调用时写成 swap(a, b)，看 gcc 给什么警告（记下来）。
     */


    /* 任务 3：一次算出三个结果（输出参数）
     * 写 void analyze(int arr[], int len, int *pmax, int *pmin, double *pavg)
     * 在 main 里声明 int max, min; double avg; 然后 analyze(a, len, &max, &min, &avg);
     * 打印三个结果。
     * 注意：max/min/avg 在 main 里可以不初始化 —— 因为值是由 analyze 写回去的。
     * 对比「return 只能返回一个值」，体会输出参数解决了什么问题。
     */


    /* 任务 4：用指针修正「除零」问题
     * 写 int safe_avg(int arr[], int len, double *out)：
     *     len <= 0 时什么都不写，返回 0 表示失败
     *     正常时把平均值写进 *out，返回 1 表示成功
     * main 里根据返回值决定要不要打印结果：
     *     if (safe_avg(a, len, &avg)) { printf("%.1f\n", avg); }
     * 这是 C 里最常见的错误处理套路：返回值表状态，结果走指针。
     * 这套思路以后做文件操作（c12）还会再见。
     */


    /* 任务 5：const 保护数据
     * 把任务 3 里的打印函数写成 void print_arr(const int *arr, int len)。
     * 然后在函数体里偷偷加一行 arr[0] = 99; —— 编译会直接报错。
     * 把它改成 int* 版本再编译，就能通过。体会 const 的价值：
     * 它把「不小心改了别人的数据」从运行时崩溃变成编译期报错。
     */


    /* 任务 6（★）：故意写错，认识四种报错
     * 一次只试一处：
     *     swap(a, b);                    // 漏了 &：警告 + 运行崩
     *     swap(int *px, int *py) { px = py; }        // 忘了 *，只改指针自己
     *     void f(int *p) { *p = 5; }  f(NULL);       // 空指针写入，段错误
     *     int *p = &a;  p = 5;           // 给指针赋整数，-Wall 警告
     * 第二条最阴：编译完全通过，但 a 不变，很难查。
     */


    /* 任务 7（★★）：指针版的完整统计工具
     * 对一周温度 {22,25,28,26,24,31,19}，写一个完整程序：
     *     void read_all(...)      不需要，数据写死就行
     *     void analyze(int arr[], int len, int *pmax, int *pmin, double *pavg, int *pcount)
     *            一次性算出：最高、最低、平均、超过 28 度的天数
     *     void print_report(const int *arr, int len, int max, int min, double avg, int hot_days)
     *            打印一份整齐的日报
     * main 里只负责：准备数据 → 调 analyze → 调 print_report。
     * 门槛：main 函数应该很短（十几行），脏活都在函数里 —— 这就是好的结构。
     */


    return 0;
}
