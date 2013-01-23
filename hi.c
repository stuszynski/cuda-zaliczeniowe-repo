#include <stdio.h>

#define N 100

int main(int argc, char const *argv[])
{
	int v1[N] = {1,2,3,4,5};
	int v2[N] = {5,4,3,2,1};
	int wynik;

for (int i = 0; i < N; ++i)
{
	wynik += v1[i] * v2[i];
}

printf("%i\n", wynik);

	return 0;
}