#include <iostream>
#include <algorithm>

using namespace std;

int N, K, A[33], first[1000009], second[1000009];

int main()
{
	cin >> N >> K;
	for (int i = 0; i < N; i++) cin >> A[i];
	//前半の組み合わせ全列挙
	for (int i = 0; i < (1 << (N / 2)); i++)
	{
		int sum = 0;
		for (int j = 0; j <= N / 2; j++)
		{
			if ((i >> j) & 1) sum += A[j];
		}
		first[i] = sum;
	}
	//後半の組み合わせ全列挙
	for (int i = 0; i < (1 << N - (N / 2)); i++)
	{
		int sum = 0;
		for (int j = 0; j <= N - (N / 2); j++)
		{
			if ((i >> j) & 1) sum += A[j + N / 2];
		}
		second[i] = sum;
	}
	// for (int i = 1; i <= (N/2)*(N/2); i++) cout << first[i] << " ";
	// cout << endl;
	// for (int i = 1; i <= (N/2)*(N/2); i++) cout << second[i] << " ";
	// cout << endl;
	sort(first, first + (1 << N / 2));
	for (int i = 1; i <= (1 << N - (N / 2)); i++)
	{
		int L = 0;
		int R =(1 << N / 2) - 1;
		while (L <= R)
		{
			int mid = (L + R) / 2;
			if (second[i] + first[mid] < K) L = mid + 1;
			else if (second[i] + first[mid] == K)
			{
				cout << "Yes" << endl;
				return 0;
			}
			else R = mid - 1;
		}
	}
	cout << "No" << endl;
	return 0;
}

	// cum_first[1] = A[1];
	// for (int i = 2; i <= N / 2; i++)
	// {
	// 	if (A[i] == K)
	// 	{
	// 		cout << "Yes" << endl;
	// 		return 0;
	// 	}
	// 	cum_first[i] = cum_first[i - 1] + A[i];
	// }
	// cum_second[1] = A[N / 2 + 1];
	// for (int i = 2; i <= N - N / 2; i++)
	// {
	// 	if (A[i + N / 2] == K)
	// 	{
	// 		cout << "Yes" << endl;
	// 		return 0;
	// 	}
	// 	cum_second[i] = cum_second[i - 1] + A[i + N / 2];	
	// }
	// for (int i = 1; i <= N / 2; i++)
	// {
	// 	for (int j = i; j <= N / 2; j++)
	// 	{
	// 		if (cum_first[j] - cum_first[i - 1] == K)
	// 		{
	// 			cout << "Yes" << endl;
	// 			return 0;
	// 		}
	// 		first[(i - 1) * (N / 2) + j] = cum_first[j] - cum_first[i - 1];
	// 	}
	// }
	// for (int i = 1; i <= N - N / 2; i++)
	// {
	// 	for (int j = i; j <= N - N / 2; j++)
	// 	{
	// 		if (cum_second[j] - cum_second[i - 1] == K)
	// 		{
	// 			cout << "Yes" << endl;
	// 			return 0;
	// 		}
	// 		second[(i - 1) * (N / 2) + j] = cum_second[j] - cum_second[i - 1];
	// 	}
	// }
	// for (int i = 1; i <= (N/2)*(N/2); i++) cout << cum_first[i] << " ";
	// cout << endl;
	// for (int i = 1; i <= (N/2)*(N/2); i++) cout << cum_second[i] << " ";
	// cout << endl;