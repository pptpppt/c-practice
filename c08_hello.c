/* ============================================================================
 * C08 · 指针与数组（数组名即地址 / 指针算术 / 退化）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c08_hello.c -o c08_hello.exe
 * 运行：c08_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 *
 * ⚠️ 这一课会把 c05 留下的那个「矛盾」解释清楚：
 *    为什么普通变量传进函数改不动，数组传进去却能改？
 * ==========================================================================*/

/* ---------------- 模范示例 1：数组名就是首元素地址 ------------------------
#include <stdio.h>

int main(void) {
    int a[] = {10, 20, 30, 40, 50};
    printf("a       = %p\n", (void *)a);
    printf("&a[0]   = %p\n", (void *)&a[0]);      // 跟上面一样！
    printf("*a      = %d\n", *a);                  // 10，等价于 a[0]
    printf("*(a+1)  = %d\n", *(a + 1));            // 20，等价于 a[1]
    printf("*(a+3)  = %d\n", *(a + 3));            // 40
    return 0;
}
 *
 * 核心事实：a[i] 就是 *(a + i) 的语法糖。两者完全等价，编译器都这么翻译。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：指针算术 —— 步长由类型决定 ------------------
 * p + 1 不是「地址值加 1」，而是「往后挪一个元素的距离」。
 *
 *     int    *pi = ...;     pi + 1  → 地址 + 4（int 占 4 字节）
 *     double *pd = ...;     pd + 1  → 地址 + 8（double 占 8 字节）
 *     char   *pc = ...;     pc + 1  → 地址 + 1
 *
 * 这就是为什么指针必须带类型 —— 不知道元素多大，就不知道该走多远。
 *
#include <stdio.h>

int main(void) {
    int a[] = {10, 20, 30};
    int *p = a;
    printf("%p → %d\n", (void *)p, *p);
    p++;                              // 往后挪一个 int
    printf("%p → %d\n", (void *)p, *p);
    p += 1;
    printf("%p → %d\n", (void *)p, *p);
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：用指针遍历数组 ------------------------------
#include <stdio.h>

int main(void) {
    int temps[] = {22, 25, 28, 26, 24};
    int len = sizeof(temps) / sizeof(temps[0]);

    for (int *p = temps; p < temps + len; p++) {
        printf("%d ", *p);
    }
    printf("\n");
    return 0;
}
 *
 * 传统写法 vs 指针写法，两者都可以，看懂别人的代码更重要。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：数组传参的真相 —— 退化 ----------------------
 * 这行：void f(int arr[], int len)
 * 等价于：void f(int *arr, int len)
 *
 * 传进去的只是首元素地址，**不是整个数组的副本**！
 * 所以函数里 arr[0] = 99 改的就是外面那个真数组 —— 这就是 c05 矛盾的答案。
 *
 * 附带后果：函数里 sizeof(arr) 得到的是指针大小（8），不是数组字节数。
 * 所以长度必须在外面算好传进来。这条 c05 提过，现在知道根因了。
 *
#include <stdio.h>

void change(int arr[], int len) {
    arr[0] = 99;
    printf("函数里 sizeof(arr) = %zu  ← 是指针大小，不是数组大小\n", sizeof(arr));
}

int main(void) {
    int a[] = {1, 2, 3};
    change(a, 3);
    printf("回到 main：a[0] = %d\n", a[0]);     // 99，真的被改了
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

void print_at(int arr[], int len);

int main(void) {
    int temps[] = {22, 25, 28, 26, 24};
    int len = sizeof(temps) / sizeof(temps[0]);

    printf("---- 数组名的本质 ----\n");
    printf("temps     = %p\n", (void *)temps);
    printf("&temps[0] = %p\n", (void *)&temps[0]);
    printf("*temps    = %d\n", *temps);

    printf("\n---- a[i] 等价于 *(a+i) ----\n");
    for (int i = 0; i < len; i++) {
        printf("temps[%d]=%d  *(temps+%d)=%d\n", i, temps[i], i, *(temps + i));
    }

    printf("\n---- 指针算术的步长 ----\n");
    int    *pi = temps;
    double d[] = {1.0, 2.0};
    printf("int*    p   = %p\n", (void *)pi);
    printf("int*    p+1 = %p   （差 %d 字节）\n",
           (void *)(pi + 1), (int)((char *)(pi + 1) - (char *)pi));
    printf("sizeof(int) = %zu\n", sizeof(int));

    printf("\n---- 传参后能改原数组 ----\n");
    print_at(temps, len);
    return 0;
}

// 验证：传进来的是地址，改了会影响外面
void print_at(int arr[], int len) {
    printf("函数里 sizeof(arr) = %zu  ← 8，退化成指针了\n", sizeof(arr));
    printf("改前 arr[0] = %d\n", arr[0]);
    arr[0] = 99;
    printf("改后 arr[0] = %d\n", arr[0]);
}
