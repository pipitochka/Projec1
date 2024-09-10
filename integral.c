#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double f1(double x);
double f2(double x);
double f3(double x);
double df1(double x);
double df2(double x);
double df3(double x);
double test1 (double x);
double test2 (double x);
double test3 (double x);
double dtest1 (double x);
double dtest2 (double x);
double dtest3 (double x);

static long long unsigned iterations;

static double root(double (*f)(double), double (*df)(double), double (*g)(double), double (*dg)(double), double a, double b, double eps){
	iterations = 0;	
	int is_increasing = 0;
	int is_upper = 0;
	int is_ddfdf_positive = 0;

	if ((f(a) - g(a)) < 0){
      		is_increasing = 1;
   	}
   	if ((f((a + b) / 2) - g((a + b) / 2)) > (f(a) - g(a) + f(b) - g(b)) / 2){
      		is_upper = 1;
   	}
   	if ((is_increasing && !(is_upper)) | (!(is_increasing) && is_upper)){
      		is_ddfdf_positive = 1;
   	}

	double d = a;
	if (is_ddfdf_positive){
      		d = b;
   	}
	
	double c;

	while(1){
		
		c = d - (f(d) - g(d)) / (df(d) - dg(d));
		
		iterations++;	
		if (is_ddfdf_positive){
         		if ((f(c - eps) - g(c - eps)) * (f(c) - g(c)) < 0){
            			break;
         		}
      		}
      		else{
         		if ((f(c + eps) - g(c + eps)) * (f(c) - g(c)) < 0){
            			break;
         		}
      		}
      		d = c;
	}
	return c;
}

static double sum(double (*f)(double), double a, double b, int n){
   double x = 0;
   double h = (b - a) / n;
   for (double i = 0; i < n; i++){
      x += ((f(a + i * h) + f(a + (i + 1) * h)) / 2) * h;
   }
   return x;
}


static double integral(double (*f)(double), double a, double b, double esp){
	int n = 10;
   	double I = sum(f, a, b, n);
   	double I_n = 0;
   	double esp0 = 1000;
   	while(esp0 > esp){
      		n *= 2;
      		I_n = sum(f, a, b, n);
      		esp0 = (1 / 3) * (I - I_n);
   	}
   	return I_n;
}

int main(int argc, char* argv[]) {
	double (*f[6]) (double) = {f1, f2, f3, test1, test2, test3};
	double (*df[6]) (double) = {df1, df2, df3, dtest1, dtest2, dtest3};
	if (argc > 1){
	if((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)){
        	printf("--help\n");
        	printf("-h\n");
        	printf("--root\n");
        	printf("-r\n");
        	printf("--iterations\n");
        	printf("-i\n");
        	printf("--test-root\n");
        	printf("-R\n");
        	printf("--test-integral\n");
        	printf("-I\n");
	}
	else if((strcmp(argv[1], "-r") == 0) || (strcmp(argv[1], "--root") == 0)){
        	printf("%lf\n", root(f1, df1, f2, df2, 0, 2, 0.001));
        	printf("%lf\n", root(f1, df1, f3, df3, -10, 10, 0.001));
         	printf("%lf\n", root(f3, df3, f2, df2, -10, -0.1, 0.001));
	}
	else if((strcmp(argv[1], "-i") == 0) || (strcmp(argv[1], "--iterations") == 0)){
        	long long unsigned counter = 0;
		root(f1, df1, f2, df2, 0, 2, 0.001);
		counter += iterations;
		root(f1, df1, f3, df3, -10, 10, 0.001);
		counter += iterations;
		root(f2, df2, f3, df3, -10, -0.1, 0.001);
		counter += iterations;
		printf("%llu\n", counter);
	}
	else if((strcmp(argv[1], "-R") == 0) || (strcmp(argv[1], "--test-root") == 0)){
		int x, y;
		double a,b, eps, r;
		sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &x, &y, &a, &b, &eps, &r);
        	x--;
		y--;
		double test_root = root(f[x], df[x], f[y], df[y], a, b, eps); 
	        printf("%lf %lf %lf\n", test_root, fabs(test_root - r), fabs((test_root - r) / r));
	}
      	else if((strcmp(argv[1], "-I") == 0) || (strcmp(argv[1], "--test-integral") == 0)){
		int x;
		double a,b, eps, r;
		sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &x, &a, &b, &eps, &r);
        	x--;
		double test_integral = integral(f[x], a, b, eps);
		printf("%lf %lf %lf\n", test_integral, fabs(test_integral - r), fabs((test_integral - r) / r));		
	}
}
	else{
		double r1 = root(f1, df1, f2, df2, 0, 2, 0.001);
		double r2 = root(f1, df1, f3, df3, -10, 10, 0.001);
		double r3 = root(f2, df2, f3, df3, -5, -0.1, 0.001);
		double i1 = integral(f1, r3, r1, 0.001);
      		double i2 = integral(f2, r3, r1, 0.001);
      		double i3 = integral(f3, r3, r2, 0.001);
		printf("%lf\n", i3 + i2 - i1);

	}
		
}



