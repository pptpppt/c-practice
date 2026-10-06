/* ============================================================================
 * C11 任务区 · 结构体数组 + 指针（台账 / 排序 / 查找）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c11_tasks.c -o c11_tasks.exe
 * 运行：c11_tasks.exe
 *
 * 模范示例在 c11_hello.c 里，写之前先看一遍。
 *
 * 【今天要记的坑，按踩中频率排序】
 *   1. 遍历结构体数组一律传指针 const Sensor *arr，别拷贝整个数组
 *   2. 查找不到就返回 NULL，调用方必须判 NULL 再用
 *   3. 排序会打乱原顺序，需要溯源就先备份或多存一个序号字段
 *   4. 交换两个结构体用整体赋值，不用逐个成员搬
 *   5. 返回结构体 vs 返回指针：前者安全（拷贝），后者高效（要小心悬垂）
 * ==========================================================================*/

#include <stdio.h>

/* 在这片区域定义 Sensor 类型和函数原型 */


int main(void) {

    /* 任务 1：建台账
     * 定义 Sensor（shed / temp / humi），用数组存 5 个棚的数据。
     * 用 for + 下标打印一遍，再用 for + 指针偏移 (arr+i)->shed 打印一遍。
     * 两种输出必须一模一样 —— 这是在确认「下标和指针等价」。
     */


    /* 任务 2：把遍历抽成函数
     * 写 void print_all(const Sensor *arr, int len)，注意参数是 const Sensor*。
     * 在函数体里试着写一行 arr[0].temp = 99; —— 应该编译不过，这就是 const 的作用。
     * main 里调用它打印整张台账。
     */


    /* 任务 3：排序（按温度从高到低）
     * 写 void sort_by_temp(Sensor arr[], int len)，用 c04 的冒泡排序改造：
     *     比较条件改成比较 arr[j].temp 和 arr[j+1].temp
     *     交换时直接 Sensor t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
     * 排完打印，确认顺序真的变了。
     * 思考：这个函数**必须**传 Sensor arr[] 而不是 const Sensor*，为什么？
     *       （因为要改内容，加了 const 就没法改了）
     */


    /* 任务 4：返回指针的查找函数
     * 写 const Sensor* find_by_shed(const Sensor arr[], int len, char shed)：
     *     找到了就 return &arr[i];
     *     找不到就 return NULL;
     * main 里测两个 case：找一个存在的棚、找一个不存在的棚（'Z'）。
     * **必须**写 if (p != NULL) 才能解引用，否则段错误等着你。
     */


    /* 任务 5：找出最热的棚（两种返回方式对比）
     * 版本 A：Sensor  hottest_value(const Sensor arr[], int len)   返回拷贝
     * 版本 B：const Sensor* hottest_ptr(const Sensor arr[], int len) 返回地址
     * 两个都实现，在 main 里分别调用并打印结果。
     * 对比：
     *     版本 A 拿到的是副本，改它不影响原数组（安全但多一次拷贝）
     *     版本 B 拿到的是地址，能直接改到原数组（高效但要小心）
     * 初学推荐用 A，等项目大了再考虑 B。
     */


    /* 任务 6（★）：故意写错，认识三种雷
     * 一次只试一处：
     *     const Sensor *p = find_by_shed(list, len, 'Z');
     *     printf("%d", p->temp);               // 没判 NULL 就解引用，段错误
     *     void f(const Sensor *arr) { arr[0].temp = 99; }   // 编译不过，这才是好的
     *     Sensor *p = NULL; printf("%zu", sizeof(p));       // 8，指针大小与内容无关
     * 第一条是实际项目里崩溃的头号原因之一：
     * 「这个函数可能返回 NULL」这件事，必须写在调用者的意识里。
     */


    /* 任务 7（★★）：大棚巡检台账（今天的收官）
     * 数据：5 个棚 {A,28,62.5} {B,31,35.0} {C,19,88.0} {D,36,30.0} {E,24,55.0}
     * 要求实现并依次调用这些函数：
     *     void print_all(const Sensor *arr, int len);
     *     void sort_by_temp(Sensor arr[], int len);
     *     Sensor hottest(const Sensor arr[], int len);
     *     const Sensor* wettest(const Sensor arr[], int len);     // 湿度最高的
     *     int  count_alarm(const Sensor arr[], int len);          // temp>=35 或 temp<10 的个数
     *     void print_report(...)                                   // 汇总打印
     * 最后打印一份完整日报：
     *     全部台账 → 按温度排序后的名次 → 最热/最湿 → 报警棚数
     * 结构要求：main 里只做「准备数据 + 依次调用」，所有细节都在函数里。
     * 门槛：这是 c17 项目（传感器数据管线）的直接练手，今天写顺了，c17 就不难。
     */


    return 0;
}
