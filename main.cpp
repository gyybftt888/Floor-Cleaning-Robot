#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <stack>

using namespace std;

#define MAXSIZE 1005

int m, n, B;
int dust_cnt = 0;
int steps = 0;
char floorplan[MAXSIZE][MAXSIZE] = { '\0' };
char map[MAXSIZE][MAXSIZE] = { '\0' };
double dist_f[MAXSIZE][MAXSIZE] = { 0 };
double dist_g[MAXSIZE][MAXSIZE] = { 0 };
double dist_h[MAXSIZE][MAXSIZE] = { 0 };

ofstream outfile("final.path");

class Point {
public:
    int y, x;
};

Point pt(int y, int x) {
    Point p = { y,x };
    return p;
}
Point start;
Point cur;
queue<Point> path;
stack<Point> farthest;

void visit(Point start, Point end, int power) {
    stack<Point> s;                     //end to start
    stack<Point> e;                     //start to end (not include end)
    Point p = pt(end.y, end.x);
    s.push(p);
    while (!s.empty()) {
        p = s.top();
        e.push(p);
        s.pop();
        if (floorplan[p.y][p.x] != '1') {
            if (floorplan[p.y][p.x] == '0')
                floorplan[p.y][p.x] = '2';
        }
        if (dist_g[p.y - 1][p.x] == dist_g[p.y][p.x] - 1 && floorplan[p.y - 1][p.x] == '0') {
            s.push(pt(p.y - 1, p.x));
        }
        else if (dist_g[p.y][p.x - 1] == dist_g[p.y][p.x] - 1 && floorplan[p.y][p.x - 1] == '0') {
            s.push(pt(p.y, p.x - 1));
        }
        else if (dist_g[p.y + 1][p.x] == dist_g[p.y][p.x] - 1 && floorplan[p.y + 1][p.x] == '0') {
            s.push(pt(p.y + 1, p.x));
        }
        else if (dist_g[p.y][p.x + 1] == dist_g[p.y][p.x] - 1 && floorplan[p.y][p.x + 1] == '0') {
            s.push(pt(p.y, p.x + 1));
        }
        else if (dist_g[p.y - 1][p.x] == dist_g[p.y][p.x] - 1) {
            s.push(pt(p.y - 1, p.x));
        }
        else if (dist_g[p.y][p.x - 1] == dist_g[p.y][p.x] - 1) {
            s.push(pt(p.y, p.x - 1));
        }
        else if (dist_g[p.y + 1][p.x] == dist_g[p.y][p.x] - 1) {
            s.push(pt(p.y + 1, p.x));
        }
        else if (dist_g[p.y][p.x + 1] == dist_g[p.y][p.x] - 1) {
            s.push(pt(p.y, p.x + 1));
        }
            //cout << p.y << ' ' << p.x << ' ' << steps++ << endl;
    }
    while (!e.empty()) {
        p = e.top();
        if ((p.y != end.y || p.x != end.x) && (p.y != start.y || p.x != start.x))
            s.push(p);
        //cout << p.y << ' ' << p.x << ' ' << steps++ << endl;
        path.push(p);
        steps++;
        e.pop();
    }
   while (!s.empty()) {
        p = s.top();
        //cout << p.y << ' ' << p.x << ' ' << steps++ << endl;
        path.push(p);
        steps++;
        s.pop();
    }
}

void BFS(Point p, int power) {
    queue<Point> q;
    stack<Point> forward;
    stack<Point> backward;
    q.push(p);
    //if (floorplan[p.y][p.x] == '0')
      //  floorplan[p.y][p.x] = '2';              // 2 = visited by BFS
    while (!q.empty()) {
        p = q.front();
        q.pop();
        //cout << p.y << ' ' << p.x << endl;
        farthest.push(p);
        if (map[p.y][p.x + 1] == '0') {
            //q.push(pt(p.y, p.x + 1));
            q.push({ p.y,p.x + 1 });
            map[p.y][p.x + 1] = '2';
            dist_g[p.y][p.x + 1] = dist_g[p.y][p.x] + 1;
        }
        if (map[p.y + 1][p.x] == '0') {
            //q.push(pt(p.y + 1, p.x));
            q.push({ p.y + 1,p.x });
            map[p.y + 1][p.x] = '2';
            dist_g[p.y + 1][p.x] = dist_g[p.y][p.x] + 1;
        }
        if (map[p.y][p.x - 1] == '0') {
            //q.push(pt(p.y, p.x - 1));
            q.push({ p.y,p.x - 1 });
            map[p.y][p.x - 1] = '2';
            dist_g[p.y][p.x - 1] = dist_g[p.y][p.x] + 1;
        }
        if (map[p.y - 1][p.x] == '0') {
            //q.push(pt(p.y - 1, p.x));
            q.push({ p.y - 1,p.x });
            map[p.y - 1][p.x] = '2';
            dist_g[p.y - 1][p.x] = dist_g[p.y][p.x] + 1;
        }
    }
    //p = farthest.top();
    //visit(start, p);
    while (!farthest.empty()) {
        p = farthest.top();
        //cout << p.y << ' ' << p.x << endl;
        farthest.pop();
        if (floorplan[p.y][p.x] == '0') {                //visited by BFS but not robot yet
            visit(start, p, power);
            //cout << endl;
        }
    }
    outfile << steps << endl;
    while (!path.empty()) {
        p = path.front();
        outfile << p.y << ' ' << p.x << endl;
        path.pop();
    }
    outfile << start.y << ' ' << start.x << endl;
}

int main(int argc, char* argv[]) {
    ifstream infile("floor3.data");
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
            //if (map[i][j] == '0') {
            //    dust_cnt++;
            //}
            if (map[i][j] == '1') {
                dist_f[i][j] = -2;
                dist_g[i][j] = -2;
                dist_h[i][j] = -2;
            }
            else if (map[i][j] == 'R') {
                cur.y = start.y = i;
                cur.x = start.x = j;
            }
        }
    }
    BFS(cur, B);
    /*for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(4) << floorplan[i][j] << " ";
        }
        cout << endl;
    }*/

    infile.close();
    outfile.close();
	return 0;
}