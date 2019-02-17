#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

// 即最朴素的回溯方法，超时...

int width, height;
bool filled[31][31];
int pieNum;
int curFill, allFill;
int curPies, minPies;

typedef struct {
    int x1, y1, x2, y2;
} Pie;
Pie pies[500];

void back(int t) {
    if (curFill == allFill) {
        if (curPies < minPies) {
            minPies = curPies;
        }
        return;
    }
    if (t >= pieNum) {
        return;
    }
    if (curPies >= minPies - 1) {
        return;
    }
    bool putable = true;
    int curi, curj;
    for (int i = pies[t].x1; i < pies[t].x2 && putable; i++) {
        for (int j = pies[t].y1; j < pies[t].y2; j++) {
            if (filled[i][j]) {
                putable = false;
                curi = i;
                curj = j;
                break;
            } else {
                filled[i][j] = true;
            }
        }
    }
    if (!putable) {
        for (int i = pies[t].x1; i < curi; i++) {
            for (int j = pies[t].y1; j < pies[t].y2; j++) {
                filled[i][j] = false;
            }
        }
        for (int j = pies[t].y1; j < curj; j++) {
            filled[curi][j] = false;
        }
    } else {
        curFill += (pies[t].x2 - pies[t].x1) * (pies[t].y2 - pies[t].y1);
        curPies++;
        back(t + 1);
        curPies--;
        for (int i = pies[t].x1; i < pies[t].x2; i++) {
            for (int j = pies[t].y1; j < pies[t].y2; j++) {
                filled[i][j] = false;
            }
        }
        curFill -= (pies[t].x2 - pies[t].x1) * (pies[t].y2 - pies[t].y1);
    }
    back(t + 1); // 把这种情况放到“放该片”情况的上面就错了...
}

int main() {
    int N;
    cin >> N;
    for (; N > 0; N--) {
        cin >> width >> height;
        allFill = width * height;
        cin >> pieNum;
        for (int i = 0; i < pieNum; i++) {
            cin >> pies[i].x1;
            cin >> pies[i].y1;
            cin >> pies[i].x2;
            cin >> pies[i].y2;
        }
        memset(filled, 0, sizeof(filled));
        curFill = 0;
        curPies = 0;
        minPies = INF;
        back(0);
        if (minPies < INF) {
            cout << minPies << endl;
        } else {
            cout << "-1" << endl;
        }
    }

    return 0;
}