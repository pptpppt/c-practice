/* ============================================================================
 * C05 任务区 · 函数（定义 / 声明 / 参数 / 返回值 / 值传递）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c05_tasks.c -o c05_tasks.exe
 * 运行：c05_tasks.exe
 *
 * 模范示例在 c05_hello.c 里，写之前先看一遍。
 *
 * 【今天要记的坑，按踩中频率排序】
 *   1. 形参是实参的副本，函数里改不动外面的变量（值传递）
 *   2. 忘了 return，-Wall 会警告「control reaches end of non-void function」
 *   3. 数组作参数会丢长度，必须把 len 一起传进去
 *   4. 在函数里对数组 sizeof 是错的，长度要在外面算
 *   5. 返回 0/1 表示真假时，-Wall 也救不了逻辑错误，自己测
 * ==========================================================================*/

#include <stdio.h>

/* 任务 0：先在上面这一片区域练习写「函数原型」
 * 下面 main 会调用这几个函数，请你：
 *   1. 在 main 上面写它们的原型（一行一个，以分号结尾）
 *   2. 在 main 下面写它们的实现
 * 函数名建议沿用模范示例：temp_sum / temp_avg / temp_max / need_water
 */


int main(void) {

    /* 任务 1：写一个最简单的函数
     * 写一个 void print_line(void)，打印一行 30 个减号分隔线，
     * 在 main 里调用三次，让输出分成三段。
     * 体会：没有返回值、没有参数的函数长什么样。
     */


    /* 任务 2：有参数有返回值（对应 Python day04）
     * 写一个 double c_to_f(double c)，把摄氏转华氏（f = c * 9 / 5 + 32）。
     * 在 main 里调用它，打印 0、25、37、100 度对应的华氏值。
     * 注意：参数形式是 (double c)，不要怕
     * 注意：公式里写 9.0/5.0 而不是 9/5（还记得整数除法吗）
     */


    /* 任务 3：返回「真假」的函数
     * 写一个 int is_high_temp(int temp)，temp >= 35 返回 1，否则返回 0。
     * 在 main 里测 4 个值：35 / 34 / 10 / 9，打印 X度 的判定结果。
     * 进阶：把函数体写成一行 return temp >= 35; ——关系运算的结果本来就是 1/0。
     */


    /* 任务 4：数组作参数
     * 把 c04 任务 3 的「求最高最低平均」改成函数版本：
     *     int   find_max(int arr[], int len);
     *     int   find_min(int arr[], int len);
     *     double find_avg(int arr[], int len);
     * 在 main 里调用这三个函数打印结果。
     * 关键记住：len 必须在 main 里用 sizeof 算好再传进来。
     */


    /* 任务 5：值传递实验（重点，为 c09 指针埋伏笔）
     * 写一个 void double_it(int x)，里面把 x 乘 2，并打印函数里的 x。
     * 在 main 里：int a = 10; double_it(a); 打印 a。
     * 看到什么？——函数里的改动的，出了函数就消失了，a 还是 10。
     * 别急着解决，先接受这个事实。c09 讲指针的时候，这里会被彻底翻案。
     */


    /* 任务 6（★）：故意写错，认识三种报错
     * 一次只改一处，编译看它报什么：
     *     int f(int a) { return a; }         // 忘了    return，但有返回值类型 int
     *     void g(int a) { return a; }        // void   函数里带了值 return
     *     double h(int a) { return 1/2; }    // 返回   0.0 而不是 0.5（整数除法又来了）
     * 第一条 -Wall 会警告 control reaches end of non-void function。
     * 第三条最阴：-Wall 不报任何错，但结果是错的。所以浮点一定要写 1.0/2.0。
     */


    /* 任务 7（★★）：把 c04 的一周日报函数化
     * 把 c04 任务 7 的「一周温度排行榜」拆成函数版本，要求至少抽 4 个函数：
     *     void print_array(int arr[], int len);      // 打印一行
     *     void bubble_sort(int arr[], int len);      // 冒泡排序（会真的改动原数组！）
     *     int  find_max(int arr[], int len);
     *     int  find_min(int arr[], int len);
     * 写完后测一件事：调用 bubble_sort 之后，main 里的原数组顺序变了吗？
     *   → 答案是变了。数组传进去能改，这跟任务 5 的「改不动」正好相反。
     *     先记下这个矛盾，c08/c09 会揭开谜底。
     */


    return 0;
}
