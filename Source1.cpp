#include <iostream>
using namespace std;

int main()
{
	int N;
	cin >> N;
	int ndigits = 0;

	while (N > 9)
	{
		ndigits += 1;
		N = N / 10;
	}
	cout << ndigits++ << endl;
}