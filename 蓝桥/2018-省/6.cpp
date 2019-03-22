#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;
using namespace std;

string i2s(int a) {
    char s[5];
    if (a < 10) {
        s[0] = '0';
        s[1] = a + '0';
        s[2] = '\0';
    } else {
        s[0] = a / 10 + '0';
        s[1] = a % 10 + '0';
        s[2] = '\0';
    }
    return s;
}
class Date {
  public:
    int h, m, s;
    Date(string s, int add) {
        int t = s[0] - '0';
        if (!t) {
            t = s[1] - '0';
        } else {
            t *= 10;
            t += s[1] - '0';
        }
        h = t + add * 24;
        t = s[3] - '0';
        if (!t) {
            t = s[4] - '0';
        } else {
            t *= 10;
            t += s[4] - '0';
        }
        m = t;
        t = s[6] - '0';
        if (!t) {
            t = s[7] - '0';
        } else {
            t *= 10;
            t += s[7] - '0';
        }
        this->s = t;
    }
    Date(int h, int m, int s) {
        this->h = h;
        this->m = m;
        this->s = s;
    }
    Date() {}
    string toString() { return i2s(h) + ":" + i2s(m) + ":" + i2s(s); }
};
Date diff(const Date &d2, const Date &d1) {
    // d2-d1
    int s = d2.s - d1.s;
    int m = d2.m - d1.m;
    int h = d2.h - d1.h;
    if (s < 0) {
        s += 60;
        m--;
    }
    if (m < 0) {
        m += 60;
        h--;
    }
    return Date(h, m, s);
}
Date operator/(const Date &d, const int a) {
    int m = d.h * 60 * 60 + d.m * 60 + d.s;
    m /= a;
    return {m / 3600, m % 3600 / 60, m % 3600 % 60};
}

Date add(const Date &d1, const Date &d2) {
    int s = d2.s + d1.s;
    int m = d2.m + d1.m;
    int h = d2.h + d1.h;
    if (s > 59) {
        m++;
        s -= 60;
    }
    if (m > 59) {
        h++;
        m -= 60;
    }
    return Date(h, m, s);
}

int main() {
    int T;
    char s[50];
    scanf("%d\n", &T);
    stringstream ss;
    while (T--) {
        gets(s);
        ss.clear();
        ss << s;
        string t;
        ss >> t;
        Date start1(t, 0);
        ss >> t;
        string tt;
        ss >> tt;
        int tmpi = 0;
        if (tt.size()) {
            tmpi = tt[2] - '0';
        }
        Date end1(t, tmpi);
        Date diff1 = diff(end1, start1);

        gets(s);
        ss.clear();
        ss << s;
        ss >> t;
        Date start2(t, 0);
        ss >> t;
        ss >> tt;
        tmpi = 0;
        if (tt.size()) {
            tmpi = tt[2] - '0';
        }
        Date end2(t, tmpi);
        Date diff2 = diff(end2, start2);

        Date fly = add(diff1, diff2);
        fly = fly / 2;
        cout << fly.toString() << endl;
    }

    return 0;
}
