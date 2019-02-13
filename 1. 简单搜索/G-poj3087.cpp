#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f

// POJ 3087 Shuffle'm Up

// 思想：简单模拟+STL的使用；
// vector 存筹码序列，set 存每一次 shuffle 后结果堆的序列，
// 当又出现了 set 中已保存的序列时，说明无法求解（出现了循环）

const int MAX = 10001;

int main() {
    int N, C;
    cin >> N;
    vector<char> s1;
    vector<char> s2;
    vector<char> target; // 目标筹码（stack）序列
    vector<char> s12;

    set<vector<char>> s;  // 用于判断是否可解

    char tempc;
    int cnt;
    for (int n = 0; n < N; n++) {
        cnt = 0;
        s1.clear();
        s2.clear();
        s12.clear();
        s.clear();
        target.clear();
        cin >> C; // 初始堆高
        for (int i = 0; i < C; i++) {
            cin >> tempc;
            s1.push_back(tempc);
        }
        for (int i = 0; i < C; i++) {
            cin >> tempc;
            s2.push_back(tempc);
        }
        for (int i = 0; i < 2 * C; i++) {
            cin >> tempc;
            target.push_back(tempc);
        }
        while (true) {
            for (int i = 0; i < C; i++) {
                s12.push_back(s2[i]);
                s12.push_back(s1[i]);
            }
            cnt++;
            if (s12 == target) {
                cout << n + 1 << " " << cnt << endl;
                break;
            }
            if (s.count(s12)) {
                cout << n + 1 << " -1" << endl;
                break;
            }
            s.insert(s12);
            s1.clear();
            s2.clear();
            for (int i = 0; i < C; i++) {
                s1.push_back(s12[0]);
                s12.erase(s12.begin());
            }
            for (int i = 0; i < C; i++) {
                s2.push_back(s12[0]);
                s12.erase(s12.begin());
            }
        }
    }

    return 0;
}

// 这里不用重载 vector 的 == 操作符，默认判断每个元素相同时 vector 相同
// bool operator == (vector<char> s1, vector<char> s2) {
//    if (s1.size() != s2.size()) {
//        return false;
//    }
//    for (int i = 0; i < s1.size(); i++) {
//        if (s1[i] != s2[i]) {
//            return false;
//        }
//    }
//    return true;
//}