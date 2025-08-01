#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include <mmsystem.h>  // timeGetTime()용
#pragma comment(lib, "psapi.lib")  // GetProcessMemoryInfo
#pragma comment(lib, "winmm.lib")  // timeGetTime() 라이브러리


#define MAX_SIZE 10
#define MAX_QUEUE_SIZE 1000
#define MAX_STACK_SIZE 1000

// 방향 벡터 (상, 우, 하, 좌)
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// 타이머 종류 열거형
typedef enum {
    TIMER_QUERY_PERFORMANCE,    // QueryPerformanceCounter (고해상도)
    TIMER_GET_TICK_COUNT,      // GetTickCount (ms 단위)
    TIMER_CLOCK,               // clock() (C 표준)
    TIMER_TIME_GET_TIME        // timeGetTime (멀티미디어)
} TimerType;

// 좌표 구조체
typedef struct {
    int x;
    int y;
} Point;

// 큐 구조체
typedef struct {
    Point data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

// 스택 구조체
typedef struct {
    Point data[MAX_STACK_SIZE];
    int top;
} Stack;

// 큐 함수들
void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int isQueueEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, Point p) {
    if (q->size < MAX_QUEUE_SIZE) {
        q->data[q->rear] = p;
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->size++;
    }
}

Point dequeue(Queue* q) {
    Point p = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->size--;
    return p;
}

// 스택 함수들
void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, Point p) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->top++;
        s->data[s->top] = p;
    }
}

Point pop(Stack* s) {
    Point p = s->data[s->top];
    s->top--;
    return p;
}

// 유효성 검사 함수
int isValid(int x, int y, int rows, int cols) {
    return (0 <= x && x < rows && 0 <= y && y < cols);
}

// 맵 복사 함수
void copyMap(char source[MAX_SIZE][MAX_SIZE], char dest[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            dest[i][j] = source[i][j];
        }
    }
}

// BFS Queue
int bfsQueue(char graph[MAX_SIZE][MAX_SIZE], int rows, int cols, int startX, int startY) {
    Queue q;
    Point current, newPoint;
    int visitCount = 0;
    int i, newX, newY;

    initQueue(&q);

    graph[startX][startY] = 'X';
    newPoint.x = startX;
    newPoint.y = startY;
    enqueue(&q, newPoint);
    visitCount++;

    while (!isQueueEmpty(&q)) {
        current = dequeue(&q);

        for (i = 0; i < 4; i++) {
            newX = current.x + dx[i];
            newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols) && graph[newX][newY] == 'O') {
                graph[newX][newY] = 'X';
                newPoint.x = newX;
                newPoint.y = newY;
                enqueue(&q, newPoint);
                visitCount++;
            }
        }
    }
    return visitCount;
}

// DFS Stack
int dfsStack(char graph[MAX_SIZE][MAX_SIZE], int rows, int cols, int startX, int startY) {
    Stack s;
    Point current, newPoint;
    int visitCount = 0;
    int i, newX, newY;

    initStack(&s);

    newPoint.x = startX;
    newPoint.y = startY;
    push(&s, newPoint);

    while (!isStackEmpty(&s)) {
        current = pop(&s);

        if (!isValid(current.x, current.y, rows, cols) || graph[current.x][current.y] != 'O') {
            continue;
        }

        graph[current.x][current.y] = 'X';
        visitCount++;

        for (i = 3; i >= 0; i--) {
            newX = current.x + dx[i];
            newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols) && graph[newX][newY] == 'O') {
                newPoint.x = newX;
                newPoint.y = newY;
                push(&s, newPoint);
            }
        }
    }
    return visitCount;
}

// DFS Recursive
int dfsRecursive(char graph[MAX_SIZE][MAX_SIZE], int rows, int cols, int x, int y) {
    int visitCount = 1;
    int i, newX, newY;

    if (!isValid(x, y, rows, cols) || graph[x][y] != 'O') {
        return 0;
    }

    graph[x][y] = 'X';

    for (i = 0; i < 4; i++) {
        newX = x + dx[i];
        newY = y + dy[i];
        visitCount += dfsRecursive(graph, rows, cols, newX, newY);
    }

    return visitCount;
}

// 최적화된 DFS Stack
int optimizedDfsStack(char graph[MAX_SIZE][MAX_SIZE], int rows, int cols, int startX, int startY) {
    Stack s;
    Point current, newPoint;
    int visitCount = 0;
    int i, newX, newY;

    initStack(&s);

    if (isValid(startX, startY, rows, cols) && graph[startX][startY] == 'O') {
        graph[startX][startY] = 'X';
        newPoint.x = startX;
        newPoint.y = startY;
        push(&s, newPoint);
        visitCount++;
    }

    while (!isStackEmpty(&s)) {
        current = pop(&s);

        for (i = 3; i >= 0; i--) {
            newX = current.x + dx[i];
            newY = current.y + dy[i];

            if (isValid(newX, newY, rows, cols) && graph[newX][newY] == 'O') {
                graph[newX][newY] = 'X';
                newPoint.x = newX;
                newPoint.y = newY;
                push(&s, newPoint);
                visitCount++;
            }
        }
    }
    return visitCount;
}

// 다양한 타이머 함수들
double getCurrentTime(TimerType timerType) {
    switch (timerType) {
    case TIMER_QUERY_PERFORMANCE: {
        LARGE_INTEGER frequency, counter;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&counter);
        return (double)counter.QuadPart / frequency.QuadPart * 1000000.0; // 마이크로초
    }

    case TIMER_GET_TICK_COUNT: {
        return (double)GetTickCount() * 1000.0; // ms를 마이크로초로 변환
    }

    case TIMER_CLOCK: {
        return (double)clock() / CLOCKS_PER_SEC * 1000000.0; // 마이크로초
    }

    case TIMER_TIME_GET_TIME: {
        return (double)timeGetTime() * 1000.0; // ms를 마이크로초로 변환
    }

    default:
        return 0.0;
    }
}

const char* getTimerName(TimerType timerType) {
    switch (timerType) {
    case TIMER_QUERY_PERFORMANCE: return "QueryPerformanceCounter";
    case TIMER_GET_TICK_COUNT: return "GetTickCount";
    case TIMER_CLOCK: return "clock()";
    case TIMER_TIME_GET_TIME: return "timeGetTime";
    default: return "Unknown";
    }
}

const char* getTimerDescription(TimerType timerType) {
    switch (timerType) {
    case TIMER_QUERY_PERFORMANCE: return "고해상도, 마이크로초 단위";
    case TIMER_GET_TICK_COUNT: return "시스템 부팅시간, ms 단위, 49일 순환";
    case TIMER_CLOCK: return "프로세스 CPU 시간, C 표준";
    case TIMER_TIME_GET_TIME: return "멀티미디어 타이머, ms 단위";
    default: return "";
    }
}

// 성능 측정 함수 포인터 타입
typedef int (*AlgorithmFunc)(char[MAX_SIZE][MAX_SIZE], int, int, int, int);

// 방법 1: 반복 횟수를 늘려서 측정 (수업 내용 - 100~10만번 반복)
double measurePerformanceByRepetition(AlgorithmFunc algorithm, int iterations, TimerType timerType) {
    char originalMap[MAX_SIZE][MAX_SIZE] = {
        {'O', 'O', ' ', 'O', 'O', ' ', 'O', 'O', 'O', ' '},
        {'O', ' ', ' ', 'O', 'O', ' ', 'O', ' ', 'O', ' '},
        {'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O', 'O', ' '},
        {' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' '},
        {'O', ' ', ' ', ' ', ' ', 'O', 'O', ' ', ' ', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O'},
        {' ', ' ', ' ', 'O', ' ', ' ', ' ', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', ' ', 'O', 'O', 'O'},
        {'O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O'}
    };

    char testMap[MAX_SIZE][MAX_SIZE];
    double startTime, endTime;
    int i;

    startTime = getCurrentTime(timerType);

    for (i = 0; i < iterations; i++) {
        copyMap(originalMap, testMap, 10, 10);
        algorithm(testMap, 10, 10, 4, 0);
    }

    endTime = getCurrentTime(timerType);

    return (endTime - startTime) / iterations; // 평균 실행시간 (마이크로초)
}

// 방법 2: 고정 시간 동안 몇 번 실행되는지 카운트 (수업 내용)
int measurePerformanceByCount(AlgorithmFunc algorithm, double timeLimit, TimerType timerType) {
    char originalMap[MAX_SIZE][MAX_SIZE] = {
        {'O', 'O', ' ', 'O', 'O', ' ', 'O', 'O', 'O', ' '},
        {'O', ' ', ' ', 'O', 'O', ' ', 'O', ' ', 'O', ' '},
        {'O', 'O', 'O', ' ', ' ', ' ', 'O', 'O', 'O', ' '},
        {' ', ' ', ' ', ' ', 'O', 'O', 'O', ' ', ' ', ' '},
        {'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O', 'O', ' '},
        {'O', ' ', ' ', ' ', ' ', 'O', 'O', ' ', ' ', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', ' ', ' ', 'O', 'O'},
        {' ', ' ', ' ', 'O', ' ', ' ', ' ', 'O', 'O', 'O'},
        {'O', 'O', 'O', 'O', 'O', 'O', ' ', 'O', 'O', 'O'},
        {'O', ' ', ' ', ' ', ' ', ' ', ' ', 'O', 'O', 'O'}
    };

    char testMap[MAX_SIZE][MAX_SIZE];
    double startTime = getCurrentTime(timerType);
    double currentTime;
    int count = 0;

    do {
        copyMap(originalMap, testMap, 10, 10);
        algorithm(testMap, 10, 10, 4, 0);
        count++;
        currentTime = getCurrentTime(timerType);
    } while ((currentTime - startTime) < timeLimit);

    return count;
}

// 타이머 해상도 테스트
void testTimerResolution(void) {
    printf("\n=================== 타이머 해상도 테스트 ===================\n");

    TimerType timers[] = { TIMER_QUERY_PERFORMANCE, TIMER_GET_TICK_COUNT, TIMER_CLOCK, TIMER_TIME_GET_TIME };
    int timerCount = sizeof(timers) / sizeof(timers[0]);
    int i, j;

    for (i = 0; i < timerCount; i++) {
        printf("\n[%s]\n", getTimerName(timers[i]));
        printf("설명: %s\n", getTimerDescription(timers[i]));

        // 연속 측정으로 해상도 확인
        double prevTime = getCurrentTime(timers[i]);
        double minDiff = 1000000.0; // 매우 큰 값으로 초기화
        int measurements = 1000;

        for (j = 0; j < measurements; j++) {
            double currentTime = getCurrentTime(timers[i]);
            double diff = currentTime - prevTime;

            if (diff > 0 && diff < minDiff) {
                minDiff = diff;
            }
            prevTime = currentTime;
        }

        printf("최소 측정 단위: %.3f μs\n", minDiff);

        // QueryPerformanceCounter의 주파수 정보
        if (timers[i] == TIMER_QUERY_PERFORMANCE) {
            LARGE_INTEGER frequency;
            QueryPerformanceFrequency(&frequency);
            printf("주파수: %lld Hz\n", frequency.QuadPart);
            printf("이론적 해상도: %.3f μs\n", 1000000.0 / frequency.QuadPart);
        }

        // GetTickCount의 갱신 주기 확인
        if (timers[i] == TIMER_GET_TICK_COUNT) {
            DWORD start = GetTickCount();
            DWORD current = start;
            while (current == start) {
                current = GetTickCount();
            }
            printf("실제 갱신 주기: %lu ms\n", current - start);
        }
    }
    printf("=========================================================\n");
}

// 메모리 사용량 출력 함수
void printMemoryUsage(void) {
    PROCESS_MEMORY_COUNTERS pmc;
    HANDLE hProcess = GetCurrentProcess();

    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        printf("메모리 사용량 정보:\n");
        printf("작업 집합 크기: %zu KB\n", pmc.WorkingSetSize / 1024);
        printf("페이지 파일 사용량: %zu KB\n", pmc.PagefileUsage / 1024);
        printf("최대 작업 집합 크기: %zu KB\n", pmc.PeakWorkingSetSize / 1024);
        printf("최대 페이지 파일 사용량: %zu KB\n", pmc.PeakPagefileUsage / 1024);
        printf("==========================================\n");
    }
    else {
        printf("메모리 정보를 가져올 수 없습니다.\n");
    }

    CloseHandle(hProcess);
}

int main(void) {
    printf("============= 다양한 타이머로 알고리즘 성능 측정 =============\n");

    // 타이머 해상도 테스트
    testTimerResolution();

    printf("\n[초기 메모리 상태]\n");
    printMemoryUsage();

    // 각 타이머별로 성능 측정
    TimerType timers[] = { TIMER_QUERY_PERFORMANCE, TIMER_GET_TICK_COUNT, TIMER_CLOCK, TIMER_TIME_GET_TIME };
    int timerCount = sizeof(timers) / sizeof(timers[0]);
    int i;

    // 방법 1: 대량 반복으로 평균 시간 측정 (수업 내용)
    printf("\n=========== 방법 1: 대량 반복으로 평균 시간 측정 ===========\n");
    printf("반복 횟수: 1,000,000회 (100만번)\n");

    for (i = 0; i < timerCount; i++) {
        printf("\n========== %s 타이머 사용 ==========\n", getTimerName(timers[i]));
        printf("설명: %s\n", getTimerDescription(timers[i]));
        printf("----------------------------------------------------\n");

        const int BIG_ITERATIONS = 1000000; // 100만번

        double bfsTime = measurePerformanceByRepetition(bfsQueue, BIG_ITERATIONS, timers[i]);
        printf("BFS (Queue)        : %.6f μs\n", bfsTime);

        double dfsStackTime = measurePerformanceByRepetition(dfsStack, BIG_ITERATIONS, timers[i]);
        printf("DFS (Stack)        : %.6f μs\n", dfsStackTime);

        double dfsRecTime = measurePerformanceByRepetition(dfsRecursive, BIG_ITERATIONS, timers[i]);
        printf("DFS (Recursive)    : %.6f μs\n", dfsRecTime);

        double optimizedTime = measurePerformanceByRepetition(optimizedDfsStack, BIG_ITERATIONS, timers[i]);
        printf("최적화 DFS (Stack) : %.6f μs\n", optimizedTime);

        // 상대적 성능 비교 (0이 아닌 값들만으로)
        double minTime = 999999.0;
        if (bfsTime > 0 && bfsTime < minTime) minTime = bfsTime;
        if (dfsStackTime > 0 && dfsStackTime < minTime) minTime = dfsStackTime;
        if (dfsRecTime > 0 && dfsRecTime < minTime) minTime = dfsRecTime;
        if (optimizedTime > 0 && optimizedTime < minTime) minTime = optimizedTime;

        if (minTime < 999999.0) {
            printf("\n상대적 성능 (가장 빠른 것 기준):\n");
            if (bfsTime > 0) printf("BFS (Queue)        : %.2fx\n", bfsTime / minTime);
            if (dfsStackTime > 0) printf("DFS (Stack)        : %.2fx\n", dfsStackTime / minTime);
            if (dfsRecTime > 0) printf("DFS (Recursive)    : %.2fx\n", dfsRecTime / minTime);
            if (optimizedTime > 0) printf("최적화 DFS (Stack) : %.2fx\n", optimizedTime / minTime);

            if (dfsStackTime > 0 && optimizedTime > 0) {
                printf("\n최적화 효과: %.1f%%\n", ((dfsStackTime - optimizedTime) / dfsStackTime * 100));
            }
        }
        else {
            printf("측정된 시간이 너무 작아서 비교할 수 없습니다.\n");
        }
    }

    // 방법 2: 고정 시간 동안 실행 횟수 측정 (수업 내용)
    printf("\n\n========= 방법 2: 고정 시간 동안 실행 횟수 측정 =========\n");
    printf("측정 시간: 1초 (1,000,000 μs)\n");

    for (i = 0; i < timerCount; i++) {
        printf("\n========== %s 타이머 사용 ==========\n", getTimerName(timers[i]));
        printf("----------------------------------------------------\n");

        const double TIME_LIMIT = 1000000.0; // 1초 = 1,000,000 마이크로초

        int bfsCount = measurePerformanceByCount(bfsQueue, TIME_LIMIT, timers[i]);
        printf("BFS (Queue)        : %d회 실행\n", bfsCount);

        int dfsStackCount = measurePerformanceByCount(dfsStack, TIME_LIMIT, timers[i]);
        printf("DFS (Stack)        : %d회 실행\n", dfsStackCount);

        int dfsRecCount = measurePerformanceByCount(dfsRecursive, TIME_LIMIT, timers[i]);
        printf("DFS (Recursive)    : %d회 실행\n", dfsRecCount);

        int optimizedCount = measurePerformanceByCount(optimizedDfsStack, TIME_LIMIT, timers[i]);
        printf("최적화 DFS (Stack) : %d회 실행\n", optimizedCount);

        // 실행 횟수 기반 성능 비교 (많이 실행될수록 빠름)
        int maxCount = bfsCount;
        if (dfsStackCount > maxCount) maxCount = dfsStackCount;
        if (dfsRecCount > maxCount) maxCount = dfsRecCount;
        if (optimizedCount > maxCount) maxCount = optimizedCount;

        if (maxCount > 0) {
            printf("\n상대적 성능 (가장 빠른 것 기준):\n");
            printf("BFS (Queue)        : %.2fx\n", (double)bfsCount / maxCount);
            printf("DFS (Stack)        : %.2fx\n", (double)dfsStackCount / maxCount);
            printf("DFS (Recursive)    : %.2fx\n", (double)dfsRecCount / maxCount);
            printf("최적화 DFS (Stack) : %.2fx\n", (double)optimizedCount / maxCount);

            if (dfsStackCount > 0 && optimizedCount > 0) {
                printf("\n최적화 효과: %.1f%% 개선\n",
                    ((double)(optimizedCount - dfsStackCount) / dfsStackCount * 100));
            }
        }
    }

    printf("\n[측정 후 메모리 상태]\n");
    printMemoryUsage();

    printf("\n=================== 수업 내용 검증 ===================\n");
    printf("1. 마이크로초 단위 측정의 한계:\n");
    printf("   - QueryPerformanceCounter만 마이크로초 단위 측정 가능\n");
    printf("   - 다른 타이머들은 ms 단위로 한계 있음\n");
    printf("\n2. 측정 방법:\n");
    printf("   - 대량 반복: 100만번 반복 후 평균 계산\n");
    printf("   - 시간 기준: 1초 동안 실행 횟수 카운트\n");
    printf("\n3. 컨텍스트 스위칭 영향:\n");
    printf("   - 측정값의 편차가 클 수 있음\n");
    printf("   - 여러 번 측정 후 평균값 사용 권장\n");
    printf("=====================================================\n");

    // 디버깅 정보
    printf("\n디버깅 정보:\n");
    printf("구조체 크기:\n");
    printf("Point 구조체: %zu bytes\n", sizeof(Point));
    printf("Queue 구조체: %zu bytes\n", sizeof(Queue));
    printf("Stack 구조체: %zu bytes\n", sizeof(Stack));
    printf("함수 포인터: %zu bytes\n", sizeof(AlgorithmFunc));

    return 0;
}