/* C01 Step2 —— 变量与打印
 * 编译：gcc -Wall -g c01_step2_variable.c -o c01_step2_variable.exe
 * 运行：c01_step2_variable.exe
 */
#include <stdio.h>

int main(void) {
    int   temp = 25;        // 整数
    float humi = 68.5f;     // 小数（float 后面的 f 可以写也可以不写）
    char  shed = 'A';       // 单个字符，必须单引号

    printf("温度 %d 度\n", temp);      // %d  整数
    printf("湿度 %.1f %%\n", humi);    // %.1f 保留 1 位小数；%% 才是真的百分号
    printf("棚号 %c\n", shed);         // %c  单个字符

    return 0;
}

/* 要点：
 *   1. C 的变量必须先声明类型，再使用（Python 不用）
 *   2. 每条语句结尾必须有分号 ;
 *   3. 变量要放引号外面、用逗号隔开 —— printf("温度 %d 度\n", temp);
 *   4. 声明时就赋初值，永远别让「垃圾值」有机会露面
 */
