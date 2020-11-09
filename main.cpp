#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

#define MAXSIZE 1005

int m, n, B;
char floorplan[MAXSIZE][MAXSIZE] = { '\0' };

int main(int argc, char* argv[]) {
    ifstream infile("floor2.data");
    //ifstream infile(argv[1]);               //開啟檔案
    if (!infile) {                          //判斷是否正確開啟檔案
        cout << "Can not open file!\n";
        return 1;
    }
    infile >> m >> n >> B;
    //cin >> m >> n >> B;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            infile >> floorplan[i][j];
            if (floorplan[i][j] == 'R') {

            }
            //cout << i << ' ' << j;
        }
    }

    /*for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << floorplan[i][j] << " ";
        cout << endl;
    }*/
    //ofstream outfile("final.path");
    infile.close();
    //outfile.close();
	return 0;
}