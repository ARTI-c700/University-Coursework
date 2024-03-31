#include <iostream>
#include <cmath>
#include <omp.h>
#define N 50
using namespace std;

double F (double x) { return exp(x); } // 

int main () 
{
    int a = 0, b = 1, n = 16; // 
    float A = 0; 
    float X[N], h, S1 = 0, S2 = 0; // 
    int i,j,k;

    h = (b - a)/(float)n; // 
    
    X[0] = a; // 
    X[n] = b;
    
    printf("F(x) funksiyasinin [0;8] araliginda inteqralini tapmali: \n");
    printf("Verilir:\n");
    printf("F(x) = e^(x)   |  a = %d, b = %d; n = %d; h=(b-a)/n = %f;\n",a,b,n,h);
    printf("\nx'in tapilacaq qiymetleri:\n");
    printf("x[0] = %f, x[%d] = %f\n",X[0],n,X[n]);
    
    printf("%1.1f ",X[0]);
    for (int i=1; i<n; i++) { printf("----- x[%d]", i); }
    printf(" ----- %1.2f",X[n]);
    
    printf("\n\n");
    omp_set_num_threads(5);
    
    #pragma omp parallel for private (i) // Massivin (yeni, X[]) diger qiymetleri hesablanmasi ucun parallel hisse yaradilir
        for (i = 1; i < n; i++) {
            X[i] = X[0] + i*h;
            printf("x[%d] =  %1.2f (CPU[%d])\n--------------------------\n", i, X[i], omp_get_thread_num());
        }

printf("\n");

    printf("Inteqralin hesablanmasi ucun Simpson dusturu:\n");
    printf("- (inteqral) F(x) = h/3( F(x[0]) + 4*S1 + 2*S2 + F(x[n]) );\n");
    printf("- S1 = ");
    for (int a1=1; a1<=n-1; a1+=2) { printf("+ X[%d] ",a1); }
    printf("\n- S2 = ");
    for (int a2=2; a2<=n-2; a2+=2) { printf("+ X[%d] ",a2); }

printf("\n\n");    
    
    #pragma omp parallel for private(j) reduction (+: S1) // 
                                                         // 
        for (j = 1; j <= n-1; j += 2) {
            S1 += F(X[j]);
            printf("(CPU[%d]) S1[%d] = %f \n----------------------------\n",omp_get_thread_num(),omp_get_thread_num(), S1);
        }

printf("\n");
    
    #pragma omp parallel for private (k) reduction (+:S2) // 𝑥_2,𝑥_4,𝑥_6,…,𝑥_𝑛 qiymetlerinin istifade edilmesi ile 
                                                         // 
        for (k = 2; k <= n-2; k += 2) {
            S2 += F(X[k]);
            printf("(CPU[%d]) S2[%d] = %f \n----------------------------\n",omp_get_thread_num(),omp_get_thread_num(), S2);
        }
    
    printf("\n");
    printf("Yekun-> S1 = %f\n",S1);
    printf("Yekun-> S2 = %f\n\n",S2);

    printf("Area or Integral of F(x):\n\n"); 
    A = (h/3)*(F(X[0]) + F(X[n]) + 4*S1 + 2*S2); // 
    printf(" I = (h/3)*(F(X[0]) + F(X[n]) + 4*S1 + 2*S2)\n"); //
    printf(" I = (%f)*(%f + %f + 4*%f + 2*%f) = %f", (h/3), F(X[0]), F(X[n]), S1, S2, A);
    return 0;
}



