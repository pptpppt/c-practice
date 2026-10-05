/* C01 Step1 —— 最小的 C 程序
 * 编译：gcc -Wall -g c01_step1_hello.c -o c01_step1_hello.exe
 * 运行：c01_step1_hello.exe
 */
#include <stdio.h>

int main(void) {
    printf("hello C\n");
    return 0;
}

/* 要点：
 *   #include <stdio.h>  ==  Python 的 import
 *   main 是唯一入口，程序从它第一行往下执行
 *   return 0 表示正常结束
 *   stdio = standard input output（标准输入输出库）
 */
