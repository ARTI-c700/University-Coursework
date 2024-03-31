#include <iostream>
#include <omp.h>
#include <cmath>
#define N 50

using namespace std;

double F (double X) { return exp(X); } // Function

int main () 
{
    int a=0, b=1, n=6;        // The range of the integral is [a,b]; a variable is created for the number of particles (n).
    double X[N], h, S = 0;   // An array for the X values of the function, the length of each part, an expression S is created for the formula
    int k, i;
    h = (b-a)/(float)n;  // Calculation of the division

    X[0] = a;  
    X[n] = b;
    
    printf("Sual: \n");
    printf("F(x) funksiyasinin [%d; %d] araliginda inteqralini tapmali: \n",a,b);
    printf("Verilir:\n");
    printf("F(X) = e^(x)   |  a = %d, b = %d; n = %d; h=(b-a)/n = %1.2f;\n",a,b,n,h);
    printf("\nX'in tapilacaq qiymetleri:\n");
    printf("X[0] = %1.0f, X[%d] = %1.0f\n",X[0],n,X[n]);
    
    printf("%1.1f ",X[0]);
    for (int i=1; i<n; i++) { printf("----- X[%d]", i); }
    printf(" ----- %1.1f",X[n]);

    printf("\n\nX'in qiymetleri:");
    #pragma omp parallel for private (i) 
    for (i = 1; i < n; i++) {
        X[i] = X[0] + i*h;
        printf("\nX[%d] = %2.2f (CPU[%d])\n",i,X[i],omp_get_thread_num() );
    }

    printf("------------------------\n\n");
    i = 0;
    int num = n/2;  
   
    #pragma omp parallel private(k) reduction (+:S)    
       {
            #pragma omp for
            for (k = 0; k < num; k++) {
                S = S + (F(X[2*k]) + 4*F(X[2*k+1]) + F(X[2*k+2]));
                printf("CPU[%d] >> x[%d] ----- x[%d] ----- x[%d]\n", omp_get_thread_num(),2*k,2*k+1,2*k+2);
                printf("S = ( F(x[%d]) + 4*F(x[%d]) + F(x[%d]) ) = %f", 2*k, 2*k+1, 2*k+2, S);
                printf("\n---------------------------------------------\n");
            } 
        }
    printf("Yekun S = %f\n",S); 
    double A = (h/3)*S;  
    printf("\nInteqral = (h/3)*S = %f\n",A); 
    return 0;
}
