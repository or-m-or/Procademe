#include <iostream>
#include <cstdlib>  // system() 함수용
#include <thread>   // sleep 함수용
#include <chrono>   // 시간 지연용
#include <stack>    // 스택 자료구조용
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

void dfsStack(int startX, int startY)
{
    stack<pair<int, int>> s;  // 좌표를 저장할 스택
    s.push({ startX, startY }); // 시작점을 스택에 추가

    while (!s.empty())
    {
        // 스택에서 좌표를 꺼냄
        pair<int, int> current = s.top();
        s.pop();

        int x = current.first;
        int y = current.second;

        // 유효하지 않거나 이미 방문한 노드인 경우 건너뛰기
        if (!isValid(x, y) || graph[x][y] != 'O')
        {
            continue;
        }

        // 현재 노드 방문 처리
        graph[x][y] = 'X';

        // 화면 지우고 현재 상태 출력
        clearScreen();
        printGraph();
        cout << "방문: (" << x << ", " << y << ")" << endl;
        cout << "스택 크기: " << s.size() << endl;
        cout << "계속 탐색 중..." << endl << endl;

        // 0.2초 대기 (시각화를 위한 지연)
        this_thread::sleep_for(chrono::milliseconds(200));

        // 네 방향을 스택에 추가 (역순으로 추가하여 상->우->하->좌 순서 유지)
        for (int i = 3; i >= 0; i--)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            // 유효한 좌표이고 아직 방문하지 않은 경우에만 스택에 추가
            if (isValid(newX, newY) && graph[newX][newY] == 'O')
            {
                s.push({ newX, newY });
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
    cout << "DFS 스택 탐색을 시작합니다..." << endl;
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

    // DFS 스택 탐색 시작
    dfsStack(startX, startY);

    // 최종 결과 출력
    clearScreen();
    cout << "==================== DFS 스택 탐색 완료 ====================" << endl;
    printGraph();
    cout << "탐색이 완료되었습니다!" << endl;
    cout << "시작 좌표: (" << startX << ", " << startY << ")" << endl;

    return 0;
}