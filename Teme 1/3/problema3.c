#include <stdio.h>
#include <stdlib.h>

#define ITER_LIMIT 1000000

double power(double x, int exp)
{
	double res = x;
	for(;--exp;)
		res *= x;
	return res;
}

double absolute(double x)
{
	if(x > 0) return x;
	return -1 * x;
}	

double radicaln(double num, double ord, double eps)
{
	double left = 0, right = num;
	double approximation, val;
	int iter = 0;

	do
	{
		val = (left + right) / 2;
		approximation = power(val, ord);
		
		if(absolute(approximation - num) < eps)
        {
            //printf("%d\n", iter);
			return val;
        }
		
		if(approximation < num)
			left = val;
		else
			right = val;
		iter += 1;
	}
	while(iter < ITER_LIMIT);

	return val;
}

int calcDigits(float eps)
{
	int cnt = 0;
	while(eps < 1)
	{
		cnt += 1, eps *= 10;
	}
	return cnt;
}

int main()
{
	FILE* fin, *fout;
	unsigned int n, m;
	float eps;
	
	fin = fopen("radicaln.in", "r");
	if(fin == NULL)
	{
		perror("fopen radicaln.in");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fin, "%u", &n);
	fscanf(fin, "%f", &eps);
	fscanf(fin, "%u", &m);
	
	fclose(fin);

	fout = fopen("radicaln.out", "w");
	if(fout == NULL)
	{
		perror("fopen radicaln.out");
		exit(EXIT_FAILURE);
	}
	
	double res = radicaln(m, n, eps);

	fprintf(fout, "%.*f\n", calcDigits(eps), res);
	//printf("%.*f\n", calcDigits(eps), res);

	fclose(fout);
    return 0;
}