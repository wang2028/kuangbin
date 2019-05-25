#include <algorithm>
#include <iostream>

using namespace std;

int maxSubSum(int a[], int len) {
    int curSum = 0, maxSum = 0;
    for (int i = 0; i < len; i++) {
        curSum += a[i];
        maxSum = max(curSum, maxSum);
        curSum = max(0, curSum);
    }
    return maxSum;
}

int main() {
    int a[5], len = 5;
    while (true) {
        for (int i = 0; i < len; i++) {
            cin >> a[i];
        }
        cout << maxSubSum(a, len) << endl;
    }
}