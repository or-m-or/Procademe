#include <iostream>
#include <cstdlib>  // system() 함수용
#include <thread>   // sleep 함수용
#include <chrono>   // 시간 지연용
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

void dfs(int x, int y)
{
    // 유효하지 않거나 방문한 노드인 경우 종료
    if (!isValid(x, y) || graph[x][y] != 'O')
    {
        return;
    }

    // 현재 노드 방문 처리
    graph[x][y] = 'X';

    // 화면 지우고 현재 상태 출력
    clearScreen();
    printGraph();
    cout << "방문: (" << x << ", " << y << ")" << endl;
    cout << "계속 탐색 중..." << endl << endl;

    // 0.5초 대기 (시각화를 위한 지연)
    this_thread::sleep_for(chrono::milliseconds(200));

    // 네 방향으로 재귀 호출
    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];
        dfs(newX, newY);
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
    cout << "DFS 탐색을 시작합니다..." << endl;
    cout << "Enter 키를 눌러 시작하세요." << endl;
    cin.get(); // 사용자 입력 대기

    // DFS 탐색 시작
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

    // DFS 탐색 시작
    dfs(startX, startY);

    // 최종 결과 출력
    clearScreen();
    cout << "==================== DFS 탐색 완료 ====================" << endl;
    printGraph();
    cout << "탐색이 완료되었습니다!" << endl;
    cout << "시작 좌표: (" << startX << ", " << startY << ")" << endl;

    return 0;
}