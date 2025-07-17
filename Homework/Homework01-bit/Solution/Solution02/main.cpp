/*
과제 2. unsigned short (16bit) 변수의 각 비트를 컨트롤 하기

[v] unsigned short 변수 = 0 으로 초기값 가짐.
[v] 키보드로 1 ~ 16의 비트 자리 입력을 받음
[v] 1 / 0  을 사용자로부터 받아서 지정된 자리의 비트를 0 또는 1로 바꿔줌.
[v] 다른 위체이 입력된 기존 데이터는 보존이 되어야 함
*/
#include <iostream>
#include <stdio.h>

int main()
{
	unsigned short num = 0; // 2bytes(16bit)
	int bitPosition;
	int bitValue;

	while (1)
	{
		printf("비트위치 (1~16) : "); 
		int result1 = scanf_s("%d", &bitPosition); // 비트 위치 예외 처리 필요 // scanf_s : 버퍼 크기 검사하여 오버플로우 방지
		
		printf("OFF/ON [0,1] : "); 
		int result2 = scanf_s("%d", &bitValue); // 0 이 아닌 케이스가 입력되면 무조껀 1로 취급

		if (bitPosition < 1 || 16 < bitPosition)
		{
			printf("비트 범위를 초과하였습니다.\n\n");
			continue;
		}

		if (bitValue == 0)
		{
			// ~(1 | 1) -> 0
			// ~(0 | 1) -> 0
			num = ~(num | (1 << (bitPosition-1)));
		}
		else
		{
			// OR 연산
			// 1 | 1 -> 1 
			// 0 | 1 -> 1
			num = num | (1 << (bitPosition-1));
		}


		char temp;
		for (int i = 15; i >= 0; i--)
		{
			// num 0010 0101 0000 1111
			// i   1000 0000 0000 0000
			//     001

			// num 0010 0101 0000 1111
			// i     10 0000 0000 0000
			//       1
			temp = (num >> i) & 1;
			if (temp == 1)
			{
				printf("%d 번 Bit : ON\n", i);
			}
			else
			{
				printf("%d 번 Bit : OFF\n", i);
			}
		}
		printf("\n\n");
	}

	return 0;
}