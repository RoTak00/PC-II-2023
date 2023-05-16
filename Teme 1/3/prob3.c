#include <stdio.h>
#include <stdlib.h>

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

double relativeError(double val, double oldval)
{
	return absolute((val - oldval) / oldval);
}

double radicalnrec(double num, double left, double right, double ord, double eps)
{
	double val = (left + right) / 2;
	double approximation = power(val, ord);
	if(absolute(approximation - num) < eps)
		return val;
	
	if(approximation < num)
		return radicalnrec(num, val, right, ord, eps);
	return radicalnrec(num, left, val, ord, eps);
}

double radicaln(double num, double ord, double eps)
{
    return(radicalnrec(num, 0, num, ord, eps));
}

double radicaln2(double num, double ord, double eps)
{
	double left = 0, right = num;
	double approximation, val, oldval = -1;
	int iter = 0;

	do
	{
		val = (left + right) / 2;
		approximation = power(val, ord);
		
		if(absolute(approximation - num) < eps)
			return val;
		
		if(approximation < num)
			left = val;
		else
			right = val;
		
		oldval = val;
		iter += 1;
	}
	while(1);
	
	return val;
}


int main()
{
	FILE* fin, fout;
	unsigned int n, m;
	float eps;
	
	fin = fopen("radicaln.in", "r");
	if(fin == NULL)
	{
		perror("fopen radicaln.in");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fin, "%ud", &n);
	fscanf(fin, "%f", &eps);
	fscanf(fin, "%ud", &m);
	
	fclose(fin);
	
	printf("%.16f\n", radicaln2(m, n, eps));
}