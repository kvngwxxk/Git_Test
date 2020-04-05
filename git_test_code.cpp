#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#define arr_size 750010


int N;
long long SUM = 0;
string input;
int set[1001];
bool part[1001];
long long prev_memo[arr_size];
long long cur_memo[arr_size];
int main() {
	while (1) {
		cin >> input;
		if (input == "EOI" || input == "eoi") {
			exit(1);
		}
		else {
			N = atoi(input.c_str());
			SUM = 0;

			memset(set, 0, 1001);
			memset(part, false, 1001);

			for (int i = 0; i < N; ++i) {
				cin >> set[i];
				SUM += set[i];
			}
			sort(set, set + N);

			for (int i = 0; i <= SUM / 2; ++i)
				prev_memo[i] = 0;
			prev_memo[0] = 1;
			cur_memo[0] = 1;

			for (int i = 1; i <= N; ++i) {
				for (int j = 1; j <= SUM / 2; ++j) {
					if (set[i - 1] > j) {
						cur_memo[j] = prev_memo[j];
					}
					else if (set[i - 1] <= j) {
						cur_memo[j] = prev_memo[j] + prev_memo[j - set[i - 1]];
					}
				}

				for (int j = 0; j <= SUM / 2; ++j)
					prev_memo[j] = cur_memo[j];
				cur_memo[0];

			}

			unsigned int answer = cur_memo[SUM / 2] / 2;
			if (answer < 0)
				cout << "NUMEROUS\n" << endl;
			else
				printf("%lu\n", answer);
			if (answer == 0) continue;

			int sum = SUM / 2, index = N - 1;
			int part1Index = N - 1, part2Index = 0;
			while (sum >= 0 && index >= 0) {
				if (sum - set[index] >= 0) {
					sum -= set[index];
					part[index] = true;
					if (index > part1Index)
						part1Index = index;
				}
				else {
					if (index > part2Index)
						part2Index = index;
				}
				index--;
			}

			printf("{");
			for (int i = 0; i < N; ++i) {
				if (part[i]) {
					printf("%d", set[i]);
					if (part1Index != i)
						printf(",");
				}
			}
			printf("},{");
			for (int i = 0; i < N; ++i) {
				if (!part[i]) {
					printf("%d", set[i]);
					if (part2Index != i)
						printf(",");
				}
			}

			printf("}\n");
		}
		
	}
	return 0;
}