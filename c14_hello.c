/* ============================================================================
 * C14 · 动态内存（malloc / calloc / realloc / free）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c14_hello.c -o c14_hello.exe
 * 运行：c14_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 *
 * ⚠️ 这一课最重要的不是「怎么申请」，而是「用完必须还」。
 *    C 没有垃圾回收 —— 你自己借的内存，自己负责还。
 * ==========================================================================*/

/* ---------------- 模范示例 0：为什么需要动态内存 --------------------------
 * 之前所有数组都是编译期就定好长度的：int a[10];
 * 但真实场景里，数据量往往运行时才知道：
 *     用户今天录入了多少条？文件里有多少行？
 *
 * 动态内存让你在程序运行过程中「按需申请」，用完还回去。
 * 代价：管理责任全在你身上。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 1：malloc 申请 + free 释放 ---------------------
#include <stdio.h>
#include <stdlib.h>          // malloc / free 在这里

int main(void) {
    int n = 0;
    printf("要录入几个数据？");
    if (scanf("%d", &n) != 1 || n <= 0) { printf("输入不合法\n"); return 1; }

    int *arr = (int *)malloc(n * sizeof(int));      // 申请 n 个 int 的空间
    if (arr == NULL) {                               // 永远检查！可能申请失败
        printf("内存申请失败\n");
        return 1;
    }

    for (int i = 0; i < n; i++) { arr[i] = i * 10; }
    for (int i = 0; i < n; i++) { printf("%d ", arr[i]); }
    printf("\n");

    free(arr);              // 还回去
    arr = NULL;             // 好习惯：防止变成野指针
    return 0;
}
 *
 * malloc(字节数)，返回 void*，要强转成你要的类型。
 * 申请到的是连续空间，可以当数组用：arr[i] 完全合法。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：calloc 与 malloc 的区别 ---------------------
 *     int *a = (int *)malloc(n * sizeof(int));      // 内容是垃圾值，未初始化
 *     int *b = (int *)calloc(n, sizeof(int));       // 内容全部清零，更安全
 *
 * calloc 参数写成（个数，每个多大），会自动乘起来，还顺手清零。
 * 初学推荐 calloc —— 少一个「忘了初始化」的坑。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：realloc 扩容（长度不够了怎么办）------------
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int cap = 2;                                     // 当前容量
    int cnt = 0;                                     // 当前个数
    int *arr = (int *)malloc(cap * sizeof(int));

    for (int i = 0; i < 5; i++) {
        if (cnt == cap) {                            // 满了就翻倍
            cap *= 2;
            int *tmp = (int *)realloc(arr, cap * sizeof(int));
            if (tmp == NULL) { free(arr); return 1; }
            arr = tmp;
        }
        arr[cnt++] = i * 100;
    }

    for (int i = 0; i < cnt; i++) { printf("%d ", arr[i]); }
    free(arr);
    return 0;
}
 *
 * realloc 可能「原地扩」，也可能「搬新家再拷过去」，所以用临时指针接收更安全。
 * 这个「满了就翻倍」的套路，是所有动态数组（Python 的 list 也是）的底层逻辑。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：三大内存事故 --------------------------------
 * ① 内存泄漏：malloc 了没 free。程序短时间没事，长时间跑会吃光内存。
 * ② 野指针：free 之后还用。free 还的是「使用权」，指针变量本身还留着旧地址。
 *     对策：free 之后立刻赋 NULL。
 * ③ 重复释放：同一块内存 free 两次 → 程序崩溃。
 *     对策：free(NULL) 是安全的，所以「free 后置 NULL」能顺带防住这条。
 *
 * 一句话总结：malloc / free 成对出现，free 之后马上 = NULL。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 0;
    printf("要录入几个温度值？");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入不合法\n");
        return 1;
    }

    /* calloc：申请并清零 */
    int *temps = (int *)calloc(n, sizeof(int));
    if (temps == NULL) {
        printf("内存申请失败\n");
        return 1;
    }

    printf("请依次输入 %d 个整数温度：\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &temps[i]) != 1) {
            printf("第 %d 个读取失败\n", i + 1);
            free(temps);
            return 1;
        }
    }

    int sum = 0;
    int max = temps[0];
    int min = temps[0];
    for (int i = 0; i < n; i++) {
        sum += temps[i];
        if (temps[i] > max) { max = temps[i]; }
        if (temps[i] < min) { min = temps[i]; }
    }

    printf("\n---- 统计结果 ----\n");
    printf("个数：%d\n", n);
    printf("最高：%d 度\n", max);
    printf("最低：%d 度\n", min);
    printf("平均：%.1f 度\n", sum / (double)n);

    free(temps);            // 用完还给系统
    temps = NULL;           // 防止野指针

    return 0;
}
