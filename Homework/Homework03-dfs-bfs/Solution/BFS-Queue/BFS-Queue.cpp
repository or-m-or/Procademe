#include <iostream>
#include <cstdlib>  // system() 함수용
#include <thread>   // sleep 함수용
#include <chrono>   // 시간 지연용
#include <queue>    // 큐 자료구조용
using namespace std;

const int MAX_SIZE = 10;
char graph[MAX_SIZE][MAX_SIZE];
int rows, cols;
int dx[4] = { -1, 0, 1, 0 }; // 상, 우, 하, 좌
int dy[4] = { 0, 1, 0, -1 };

bool isValid(int x, int y)
{
    return (0 <= x && x < rows && 0 <= y && y < cols);
}

void clearScreen()
{
    system("cls");
}

void printGraph()
{
    cout << "==================== 현재 맵 상태 ====================" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << "======================================================" << endl;
}

void bfsQueue(int startX, int startY)
{
    queue<pair<int, int>> q;  // 좌표를 저장할 큐

    // 시작점을 먼저 방문 처리하고 큐에 추가
    graph[startX][startY] = 'X';
    q.push({ startX, startY });

    // 시작점 방문 표시
    clearScreen();
    printGraph();
    cout << "방문: (" << startX << ", " << startY << ")" << endl;
    cout << "큐 크기: " << q.size() << endl;
    cout << "계속 탐색 중..." << endl << endl;
    this_thread::sleep_for(chrono::milliseconds(200));

    while (!q.empty())
    {
        // 큐에서 좌표를 꺼냄 (FIFO)
        pair<int, int> current = q.front();
        q.pop();

        int x = current.first;
        int y = current.second;

        // 네 방향으로 탐색
        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // 유효한 좌표이고 아직 방문하지 않은 경우
            if (isValid(newX, newY) && graph[newX][newY] == 'O')
            {
                // 즉시 방문 처리 (중복 방문 방지)
                graph[newX][newY] = 'X';

                // 큐에 추가
                q.push({ newX, newY });

                // 화면 지우고 현재 상태 출력
                clearScreen();
                printGraph();
                cout << "방문: (" << newX << ", " << newY << ")" << endl;
                cout << "큐 크기: " << q.size() << endl;
                cout << "현재 처리 중인 좌표: (" << x << ", " << y << ")" << endl;
                cout << "계속 탐색 중..." << endl << endl;

                // 0.2초 대기 (시각화를 위한 지연)
                this_thread::sleep_for(chrono::milliseconds(200));
            }
        }
    }
}

int main()
{
    char testMap[10][10] = {
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

    rows = 10;
    cols = 10;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            graph[i][j] = testMap[i][j];
        }
    }

    // 초기 맵 상태 출력
    clearScreen();
    cout << "==================== 초기 맵 상태 ====================" << endl;
    printGraph();
    cout << "BFS 큐 탐색을 시작합니다..." << endl;
    cout << "Enter 키를 눌러 시작하세요." << endl;
    cin.get(); // 사용자 입력 대기

    // BFS 탐색 시작
    int startX = 4, startY = 0;

    if (!isValid(startX, startY))
    {
        cout << "시작 좌표가 유효하지 않습니다." << endl;
        return -1;
    }
    if (graph[startX][startY] != 'O')
    {
        cout << "시작 좌표가 방문할 수 없는 지점입니다." << endl;
        return -1;
    }

    // BFS 큐 탐색 시작
    bfsQueue(startX, startY);

    // 최종 결과 출력
    clearScreen();
    cout << "==================== BFS 큐 탐색 완료 ====================" << endl;
    printGraph();
    cout << "탐색이 완료되었습니다!" << endl;
    cout << "시작 좌표: (" << startX << ", " << startY << ")" << endl;

    return 0;
}