/*
과제 3. unsigned int (32bit) 변수를 바이트 단위로 사용하기

[v] unsigned int 변수 = 0 초기값 가짐
[v] 키보드로 1 ~ 4 의 바이트 위치를 입력 받고
[v] 해당 위치에 넣을 데이터 0 ~ 255 를 입력 받음
[v] 사용자가 입력한 바이트 위치에 해당 값을 넣음
[v] 데이터가 입력 되면 바이트 단위로 쪼개서 출력 & 4바이트 16진수 출력
[v] 기존 데이터는 보존이 되어야 하며
[v] 입력된 바이트 위치의 데이터는 기존 값을 지우고 넣음.
[v] 위치는 범위를 벗어나면 예외처리
[v] 값은 범위를 벗어나면 unsigned int 가 표현하는 값 그대로 처리
    -1 -> 255
    256 -> 0
    257 -> 1
*/
#include <iostream>
#include <stdio.h>

int main()
{
    unsigned int num = 0;
    unsigned int bytePosition;  // 기록하려는 위치 (바이트 단위)
    int byteValue;     // 기록하려는 값

    while (1)
    {
        printf("위치 (1~4) : ");
        int result1 = scanf_s("%d", &bytePosition);

        printf("값 [0~255] : ");
        int result2 = scanf_s("%d", &byteValue);

        if (bytePosition < 1 || 4 < bytePosition)
        {
            printf("위치 범위를 초과하였습니다.");
            continue;
        }

        // 위치 1 -> 24번 이동
        // 위치 2 -> 16번 이동
        // 위치 3 -> 8번 이동
        unsigned int mask = ~(0xFF << (8 * (4 - bytePosition)));
        // num  : 0000 1000 0000 1111 0100 0000 1101 1101
        // mask : 0000 0000 1111 1111 1111 1111 1111 1111
        //      : 0000 0000 0000 1111 0100 0000 1101 1101 
        num = num & mask; // 수정하려는 위치(바이트 단위) 0으로 초기화

        byteValue = (unsigned char)byteValue << (8 * (4 - bytePosition)); // 기록하려는 값으로 기록하려는 위치에 초기화
        num = byteValue | num;


        // 출력
        unsigned char curByte; // 1byte(8bit)
        for (int i = 1; i <= 4; i++)
        {
            curByte = num >> (8 * (4 - i));
            printf("%d 번째 바이트 값 : %d\n", i, curByte);
        }

        printf("\n전체 4바이트 값 : 0x%08X\n\n\n", num);
    }

    return 0;
}