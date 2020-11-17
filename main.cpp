#include <iostream>
#include <stdio.h>
#include <fstream>
#include <queue>
#include <stack>
#include <ctime>

using namespace std;

#define MAXSIZE 1005

int m, n, B;
int dust_cnt = 0;
int steps = 0;
char floorplan[MAXSIZE][MAXSIZE] = { '\0' };
char map[MAXSIZE][MAXSIZE] = { '\0' };

class Point {
public:
    int y, x;
    //Point();
    /*Point(int a, int b) {
        this->y = a;
        this->x = b;
    }*/
};

Point pt(int y, int x) {
    Point p = { y,x };
    return p;
}
Point start;
Point cur;

int visit(Point start, Point end, int power) {

}

void DFS(Point p, int power) {
    cout << p.y << ' ' << p.x << endl;
    if (map[p.y][p.x] == '0')
        map[p.y][p.x] = '2';
    if (map[p.y][p.x + 1] == '0') {
        DFS(pt(p.y, p.x + 1), power - 1);
    }
    if (map[p.y + 1][p.x] == '0') {
        DFS(pt(p.y + 1, p.x), power - 1);
    }
    if (map[p.y][p.x - 1] == '0') {
        DFS(pt(p.y, p.x - 1), power - 1);
    }
    if (map[p.y - 1][p.x] == '0') {
        DFS(pt(p.y - 1, p.x), power - 1);
    }
}

void IDFS(Point p, int power) {
    stack<Point> s;
    s.push(p);
    while (!s.empty()) {
        p = s.top();
        s.pop();
        if (map[p.y][p.x] == '0' || map[p.y][p.x] == 'R') {
            cout << p.y << ' ' << p.x << endl;
            if (map[p.y][p.x] == '0')
                map[p.y][p.x] = '2';
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    cout << map[i][j] << " ";
                }
                cout << endl;
            }
            if (map[p.y - 1][p.x] == '0') {
                s.push(pt(p.y - 1, p.x));
            }
            if (map[p.y][p.x - 1] == '0') {
                s.push(pt(p.y, p.x - 1));
            }
            if (map[p.y + 1][p.x] == '0') {
                s.push(pt(p.y + 1, p.x));
            }
            if (map[p.y][p.x + 1] == '0') {
                s.push(pt(p.y, p.x + 1));
            }
        }
    }
}

void BFS(Point p,int power) {
    //bool *visited = new bool[dust_cnt];
    queue<Point> q;
    int cnt = 0;
    q.push(p);
   // if (floorplan[p.y][p.x] == '0')
     //   floorplan[p.y][p.x] = '2';              // 2 = visited
    while (!q.empty()) {
        p = q.front();
        q.pop();
        cout << p.y << ' ' << p.x << endl;
        if (map[p.y][p.x + 1] == '0') {
            q.push(pt(p.y, p.x + 1));
            map[p.y][p.x + 1] = '2';
        }
        if (map[p.y + 1][p.x] == '0') {
            q.push(pt(p.y + 1, p.x));
            map[p.y + 1][p.x] = '2';
        }
        if (map[p.y][p.x - 1] == '0') {
            q.push(pt(p.y, p.x - 1));
            map[p.y][p.x - 1] = '2';
        }
        if (map[p.y - 1][p.x] == '0') {
            q.push(pt(p.y - 1, p.x));
            map[p.y - 1][p.x] = '2';
        }
    }
}

void BDS(Point p, int power) {
    queue<Point> q;
    stack<Point> s;
    int steps = 0;
    q.push(p);
    //if (floorplan[p.y][p.x] == '0')
      //  floorplan[p.y][p.x] = '2';              // 2 = visited by BFS
    while (!q.empty()) {
        p = q.front();
        q.pop();
        //cout << p.y << ' ' << p.x << endl;
        s.push(p);
        if (map[p.y][p.x + 1] == '0') {
            q.push(pt(p.y, p.x + 1));
            map[p.y][p.x + 1] = '2';
        }
        if (map[p.y + 1][p.x] == '0') {
            q.push(pt(p.y + 1, p.x));
            map[p.y + 1][p.x] = '2';
        }
        if (map[p.y][p.x - 1] == '0') {
            q.push(pt(p.y, p.x - 1));
            map[p.y][p.x - 1] = '2';
        }
        if (map[p.y - 1][p.x] == '0') {
            q.push(pt(p.y - 1, p.x));
            map[p.y - 1][p.x] = '2';
        }
    }
    while (!s.empty()) {
        p = s.top();
        s.pop();
        if (floorplan[p.y][p.x] == '0') {                //visited by BFS but not robot yet
            visit(start, p, power);
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream infile("floor2.data");
    //ifstream infile(argv[1]);               //開啟檔案
    if (!infile) {                            //判斷是否正確開啟檔案
        cout << "Can not open file!\n";
        return 1;
    }
    infile >> m >> n >> B;
    //cin >> m >> n >> B;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            infile >> map[i][j];
            floorplan[i][j] = map[i][j];
            if (map[i][j] == '0') {
                dust_cnt++;
            }
            else if (map[i][j] == 'R') {
                cur.y = start.y = i;
                cur.x = start.x = j;
                //cout << cur.x << ' ' << cur.y;
                //cout << start.x << ' ' << start.y<<endl;
            }
        }
    }
    //IDFS(cur, B);
    //DFS(cur, B);
    //BFS(cur, B);
    //BDS(cur, B);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    //ofstream outfile("final.path");
    infile.close();
    //outfile.close();
	return 0;
}