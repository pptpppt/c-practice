/* ============================================================================
 * C05 · 函数（定义 / 声明 / 参数 / 返回值 / 作用域 / 值传递）
 *                                          （对应 Python day04_function）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c05_hello.c -o c05_hello.exe
 * 运行：c05_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 * ==========================================================================*/

/* ---------------- 模范示例 1：函数长什么样 --------------------------------
 * 语法：
 *     返回值类型 函数名(参数列表) {
 *         函数体
 *         return 返回值;          // 返回值类型是 void 时可以不写 return
 *     }
 *
#include <stdio.h>

// 求两个温度的较大者
int max_of(int a, int b) {
    if (a > b) { return a; }
    return b;
}

int main(void) {
    int x = 28, y = 31;
    printf("较高的是 %d\n", max_of(x, y));
    return 0;
}
 *
 * 要点：
 *   ① return 一执行，函数立刻结束，后面的代码不跑
 *   ② 有两个 return 不矛盾 —— 走到哪条算哪条
 *   ③ -Wall 会警告「某条路径没有返回值」，比如 if 里 return 了、else 里忘了
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：为什么要用函数（对应 Python day04）----------
 * 同样的逻辑写三遍，就该抽成函数。好处跟 Python 完全一样：
 *     起个名字让代码能读、改一处全生效、方便单独测试。
 *
 * C 额外多一条硬性理由：C 里没法像 Python 那样随手缩进组织代码块，
 * 函数几乎是唯一的「把代码装起来」的手段。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：函数声明（原型）和定义分离 ------------------
 * C 编译器从上往下读。写在后面的函数，前面要先用一句「原型」预告：
 *
 *     int add(int a, int b);        // 声明（可以放文件顶部）
 *
 *     int main(void) { printf("%d", add(1,2)); }   // 用
 *
 *     int add(int a, int b) { return a + b; }      // 定义（放后面也行）
 *
 * 这也正是后面 c13「头文件 .h」要做的事的雏形。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：值传递 —— C 的默认规则 ---------------------
 * 形参是实参的**副本**。在函数里改形参，外面那个变量纹丝不动。
 *
#include <stdio.h>

void try_change(int x) {
    x = 100;
    printf("函数里：x = %d\n", x);
}

int main(void) {
    int a = 10;
    try_change(a);
    printf("回到 main：a = %d\n", a);     // 还是 10！
    return 0;
}
 *
 * 这条你现在只能先记住：想在函数里改外面的变量，得传地址（c09 讲指针时解决）。
 * 这也是为什么 scanf 写的是 scanf("%d", &x) —— 那个 & 就是在传地址。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 5：数组作为参数 -------------------------------
 * 数组传进函数时，会退化成指针，**长度信息会丢**，所以必须额外传长度。
 *
#include <stdio.h>

int sum_of(int arr[], int len) {      // 也可以写成 int *arr，等价
    int s = 0;
    for (int i = 0; i < len; i++) { s += arr[i]; }
    return s;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int len = sizeof(a) / sizeof(a[0]);
    printf("和是 %d\n", sum_of(a, len));
    return 0;
}
 *
 * 坑：在函数内部对 arr 做 sizeof(arr) / sizeof(arr[0])，
 *     得到的不是数组长度，而是指针大小除以元素大小 —— 错的。
 *     所以长度必须在 main 里算好传进来。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

/* 函数原型：先预告，定义写在后面 */
int  temp_sum(int arr[], int len);
double temp_avg(int arr[], int len);
int  temp_max(int arr[], int len);
int  need_water(int temp, int humi);

int main(void) {
    int temps[] = {22, 25, 28, 26, 24, 31, 19};
    int len = sizeof(temps) / sizeof(temps[0]);

    printf("---- 一周统计 ----\n");
    printf("合计：%d\n", temp_sum(temps, len));
    printf("平均：%.1f\n", temp_avg(temps, len));
    printf("最高：%d\n", temp_max(temps, len));

    if (need_water(30, 35)) {
        printf("结论：需要灌溉\n");
    } else {
        printf("结论：暂不需要灌溉\n");
    }

    return 0;
}

/* --- 下面是各函数的实现 --- */

// 求和
int temp_sum(int arr[], int len) {
    int s = 0;
    for (int i = 0; i < len; i++) { s += arr[i]; }
    return s;
}

// 求平均（注意转 double）
double temp_avg(int arr[], int len) {
    if (len <= 0) { return 0.0; }
    return temp_sum(arr, len) / (double)len;      // 函数里调用函数
}

// 求最大值
int temp_max(int arr[], int len) {
    int m = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > m) { m = arr[i]; }
    }
    return m;
}

// 是否需要灌溉：又热又干才要（返回 1 表示需要，0 表示不需要）
int need_water(int temp, int humi) {
    return temp > 25 && humi < 40;
}
