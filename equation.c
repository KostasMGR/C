#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	double a, b, c; // Variables
	double D; // discriminant
	double x1, x2; // roots

	printf("Type the factors\n");
	scanf("%lf%lf%lf", &a, &b, &c); // Read values for the factors

	if(a==0) // cannot be quadratic
	{
		printf("a cannot have zero as value.....\n");
		return 1;
	}	
		

	D = ((b*b)*4*a*c);

	if (D>0)
	{
		x1 = (-b+sqrt(D))/(2*a);
		x2 = (-b-sqrt(D))/(2*a);

		printf("The roots of equation are: %lf , %lf \n", x1, x2);	
	}
	else if(D==0)
	{
		x1 = -b/(2*a);
		x2=x1;

		printf("The two same roots of equation are: %lf , %lf \n", x1, x2);
	}
	else if(D<0)
	{
		printf("The equation are not able to solve");
		return 2;	
	}
	
	return 0;
}

