/* C01 Step3 —— 从键盘读入（带输入校验，这是你今天改出来的最终版）
 * 编译：gcc -Wall -g c01_step3_scanf.c -o c01_step3_scanf.exe
 * 运行：c01_step3_scanf.exe
 * 测试：输入 25  → 你输入的是 25 度
 *       输入 jk  → 你输入的不是数字（程序结束，返回 1）
 *       输入 -5  → 你输入的是 -5 度
 */
#include <stdio.h>

int main(void) {
    int temp = 0;                              // ① 声明时就赋初值

    printf("请输入温度: ");
    int r = scanf("%d", &temp);                // ② scanf 必须加 &；返回值存进 r

    if (r != 1) {                              // ③ 返回值≠1 说明没读到整数
        printf("你输入的不是数字\n");
        return 1;
    }

    printf("你输入的是 %d 度\n", temp);
    return 0;
}

/* 要点回顾（今天踩过的坑，全在这儿）：
 *   ① int temp = 0;   —— 不赋初值，变量里是上一块内存的残留垃圾（你看到的 32759）
 *   ② &temp 读作「temp 的地址」。scanf 要把输入写进变量，必须知道它住哪 —— 这就是指针的第一次露面
 *   ③ scanf 的返回值 = 成功读到的数据个数。失败时它不报错，只是悄悄返回 0，必须自己判断
 *   ④ if (条件) 的圆括号不能省；条件后面千万不能加分号（加了 if 就变空语句）
 *   ⑤ r 也要先声明类型：int r = scanf(...);  一行同时完成「读值 + 接返回值」
 *   ⑥ 重新编译前必须关掉还在运行的 exe，否则报 Permission denied / ld returned 1 exit status
 */
