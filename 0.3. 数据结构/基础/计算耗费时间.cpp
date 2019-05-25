#include <iostream>
#include <ctime>
using namespace std;
#define INF 0x3f3f3f3f
#define ll long long

clock_t durStart, durEnd;

int main() {
	durStart = clock();

	for (ll i = 0; i < INF*2; i++) {
		continue;
	}

	durEnd = clock();
    
	// 获取中间一段代码耗费的 time_tick，再除以 CLK_TCK，获取秒数：
	cout << (durEnd - durStart) / CLK_TCK << endl;

	return 0;
}
