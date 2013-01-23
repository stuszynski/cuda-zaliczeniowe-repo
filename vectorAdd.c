#include <stdio.h>

int main(int argc, char const *argv[])
{
	int VectorA = {1,2,3,4,5};
	int VectorB = {5,4,3,2,1};
	int VectorC[sizeof(VectorA)];

	for (int i = 0; i < sizeof(VectorA); ++i)
	{
		for (int j = 0; j < sizeof(VectorB); ++j)
		{
			VectorC[i] += VectorA[i] * VectorB[j];
		}
	}

	for (int i = 0; i < sizeof(VectorC); ++i)
	{
		printf("%i\n", VectorC[i]);
	}

	return 0;
}
