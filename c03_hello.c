/* ============================================================================
 * C03 · 循环（while / for / do-while / break / continue）
 *                                          （对应 Python day03_loop）
 * ----------------------------------------------------------------------------
 * 编译：gcc -Wall -g c03_hello.c -o c03_hello.exe
 * 运行：c03_hello.exe
 * 中文乱码先在终端敲一次：chcp 65001
 * ==========================================================================*/

/* ---------------- 模范示例 1：while —— 不知道要转几圈时用 ------------------
 * 语法：while (条件) { 循环体 }
 * 条件为真才进去，每轮结束后回到条件处重新判断。
 *
 * 典型场景：一直采集，直到用户输入哨兵值（比如 -1）才停。
 *
#include <stdio.h>

int main(void) {
    int temp = 0;
    int count = 0;

    printf("请输入温度，输入 -1 结束：");
    if (scanf("%d", &temp) != 1) { printf("输入错误\n"); return 1; }

    while (temp != -1) {
        count++;
        printf("第 %d 次采样：%d 度\n", count, temp);

        printf("请输入温度，输入 -1 结束：");
        if (scanf("%d", &temp) != 1) { printf("输入错误\n"); return 1; }
    }
    printf("共采样 %d 次\n", count);
    return 0;
}
 *
 * 坑：循环体里必须有让条件走向假的语句。忘了更新 temp 就是死循环，
 *     Ctrl + C 才能救回来。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 2：for —— 知道转几圈时用 ------------------------
 * 语法：for (初始化; 条件; 更新) { 循环体 }
 *     ① 初始化只做一次    ② 条件为真才进    ③ 每轮结束做更新
 *
#include <stdio.h>

int main(void) {
    int sum = 0;
    for (int i = 1; i <= 10; i++) {
        sum += i;
        printf("i=%d  sum=%d\n", i, sum);
    }
    printf("1到10的和是 %d\n", sum);
    return 0;
}
 *
 * 坑 1：for (int i = 1; i <= 10; i++);  ← 最后那个分号是灾难，
 *       等于循环体是空语句，白白转十圈什么都不做。
 * 坑 2：循环递增用 i++ 还是 ++i？单条语句里没差别，别纠结。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 3：do-while —— 至少要转一圈 --------------------
 * 语法：do { 循环体 } while (条件);
 * 注意句尾那个分号不能漏。
 *
 * 跟 while 的唯一区别：do-while 先干再问，while 先问再干。
 * 典型场景：菜单至少显示一次，选错了再重来。
 *
#include <stdio.h>

int main(void) {
    int choice = 0;
    do {
        printf("==== 作业菜单 ====\n");
        printf("1. 耕地  2. 播种  0. 退出\n");
        printf("请选择：");
        if (scanf("%d", &choice) != 1) { printf("输入错误\n"); return 1; }
    } while (choice != 0);
    printf("已退出\n");
    return 0;
}
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 4：break 和 continue ---------------------------
 *   break    —— 直接跳出整个循环（跑路）
 *   continue —— 跳过本次剩下的部分，进入下一轮（旷一轮）
 *
#include <stdio.h>

int main(void) {
    for (int i = 1; i <= 10; i++) {
        if (i == 6) { continue; }   // 6 号探头坏了，跳过
        if (i == 9) { break; }      // 9 以后不再采
        printf("采集第 %d 号点\n", i);
    }
    return 0;
}
 * 输出：1 2 3 4 5 7 8（没有 6，到 9 停）
 *
 * 坑：continue 在 while 里要特别小心 —— 它跳过的是 continue 之后的部分，
 *     如果「更新循环变量」那句在后面，就会被跳过，直接死循环。
 * ------------------------------------------------------------------------- */

/* ---------------- 模范示例 5：嵌套循环（棚 × 时刻）------------------------
#include <stdio.h>

int main(void) {
    for (int shed = 1; shed <= 3; shed++) {
        for (int hour = 8; hour <= 10; hour++) {
            printf("第%d棚 %d时  ", shed, hour);
        }
        printf("\n");        // 换棚才换行
    }
    return 0;
}
 * 外层转 1 圈，内层转满 3 圈。总次数 = 3 × 3 = 9。
 * ------------------------------------------------------------------------- */

/* ====================== 下面是今天可直接编译运行的版本 ===================== */
#include <stdio.h>

int main(void) {
    int temp = 0;
    int count = 0;
    int sum = 0;

    printf("请输入今天各次采样的温度（整数），输入 -1 表示结束：\n");

    if (scanf("%d", &temp) != 1) { printf("输入格式不对\n"); return 1; }

    while (temp != -1) {
        count++;
        sum += temp;
        printf("  第 %d 次：%d 度\n", count, temp);

        if (scanf("%d", &temp) != 1) { printf("输入格式不对\n"); return 1; }
    }

    if (count > 0) {
        printf("---- 日报 ----\n");
        printf("采样次数：%d\n", count);
        printf("合计：%d 度\n", sum);
        printf("整除平均：%d 度\n", sum / count);
        printf("精确平均：%.1f 度\n", sum / (double)count);
    } else {
        printf("今天没有采样数据\n");
    }

    return 0;
}
