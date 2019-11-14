
#include <unistd.h>     //包含sleep函数的头文件
#include <stdio.h>
#include <string.h>
int main(){

    char buf[1024]={0};
    const char *s="/-\\|";    //一个用于输出旋转样式的字符串
    int i=0;
    for(i=0;i<=100;i++){
        
        printf("[%d%%][%c][%s]\r",i,s[i%4],buf); //%%  转义成一个%
        fflush(stdout);  //刷新缓冲区
        buf[i]='#';
        usleep(300*1000);
    }

}
