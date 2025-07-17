/*
과제 1. unsigned char 변수의 값을 비트단위로 찍어주기

[v] 지역변수에 특정 값을 하나 넣음 
[v] 비트 단위로 분해해서 0 이면 0 출력, 1 이면 1 출력
*/
#include <iostream>
#include <stdio.h>

int main()
{
    unsigned char num = 40; // 1byte(8bit)
    
    for (int i = 7; i >= 0; i--)
    {
        if (num & (1 << i))
        {
            printf("%d", 1);
        }
        else
        {
            printf("%d", 0);
        }
    }
    
    return 0;
}