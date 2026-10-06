#include<stdio.h>

int main(void){
    int mode=0;
    printf("请选择模式（1.耕地  2.播种  3.收获）:");
    if(scanf("%d",&mode)!=1){printf("输入错误\n"); return 1;}

    switch(mode){
        case 1: printf("耕地模式，低转速大扭矩\n");break;
        case 2: printf("播种模式，中转速中扭矩\n");break;
        case 3: printf("耕地模式，高转速小扭矩\n");break;
        default:printf("还没有设置这个模式哦亲\n");
    }
    return 0;
}