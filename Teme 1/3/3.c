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
	printf("%f\n",absolute((val - oldval) / oldval));
	return absolute((val - oldval) / oldval);
}

double radicaln(double num, double left, double right, double ord, double eps)
{
	double val = (left + right) / 2;
	double approximation = power(val, ord);
	if(absolute(approximation - num) < eps)
		return val;
	
	if(approximation < num)
		return radicaln(num, val, right, ord, eps);
	return radicaln(num, left, val, ord, eps);
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
		
		if(iter >= 1)
		{
			if(relativeError(val, oldval) < eps)
				return val;
		}
		
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

double radicaln3(double num, double ord, double eps)
{
	double left = 0, right;
	
	if(num >= 2)
		right = num / ord;
	else 
		num = right;
	double approximation, val, oldval = -1;
	int iter = 0;
	do
	{
		val = (left + right) / 2;
		approximation = power(val, ord);
		
		printf("%d: %f\n", iter + 1, val);
		
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
	
	printf("%f\n", radicaln(m, 0, m, n, eps));
	printf("ok");
}