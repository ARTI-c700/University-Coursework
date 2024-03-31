#include <iostream> 
#include <cmath>
#include <iomanip>

#define PI 3.14159265358979323846 // Pi-nin qiyməti
#define MAX 50

using namespace std;

class Dirichlet
{

public:

    double h1;
    double U[10][10];   // 
                        // 

    double u[5][5][MAX];    // 

    int n = 5; //

    double h = 0.2; // X və Y üçün addımın qiyməti

    double x[10]; // X-in təyini
    double y[10]; // Y-in təyini


   // Şərtlər:
   //--------------------------------------------------------------------------------------- *
    double U_AD(double x) { return 25 * x * sin((PI * x) / 2); } // AD      *
    double U_AB(double y) { return 45 * (1 - y) * y; }          // AB       *
    double U_BC(double x) { return 25 * x; }                   // BC        *
    double U_CD()         { return 25; }                      // CD         *
   //--------------------------------------------------------------------------------------- *    

    Dirichlet()
    {
        double eps = 0.02; // 
        cout << "-> h = " << h << " (addimin uzunlugu)" << endl;
        cout << "-> n = " << n << "   (addimlarin sayi)" << endl;

        double a = 0, b = 0, c = 0, d = 0; //

        for (int i = 0; i < 10; i++) { x[i] = i * h; } //
        for (int i = 0; i < 10; i++) { y[i] = i * h; } // 
        
        cout << "\nX ve Y-in qiymetleri:" << endl;
        for (int i = 0; i <= n; i++)
        {
            cout << "X[" << i << "] = " << x[i] << "\tY[" << i << "] = " << y[i] << endl;
        }

        cout << "\nY = 0 ve Y = 1 noqtelerinde serhed qiymetleri (AD ve BC) :\n\n";
        cout << "AD Terefi :\t\t" << "BC Terefi :" << endl;
        
        for (int i = 0; i <= n; i++) //
        {
            U[i][0] = U_AD(x[i]);
            U[i][n] = U_BC(x[i]);

            cout << setprecision(2) << "U("  << x[i] << ", " << y[0] << ") = " << U[i][0] << "\t\t";
            cout << "U(" << x[i] << ", " << y[n] << ") = " << U[i][n] << endl;
        }


        cout << "\n\nX = 0 ve X = 1 noqtelerinde serhed qiymetleri (AB ve CD) :\n\n";
        cout << "AB Terefi :\t\t" << "CD Terefi :" << endl;

        for (int j = 0; j <= n; j++) // 
        {
            U[0][j] = U_AB(y[j]);
            U[n][j] = U_CD();
            cout << setprecision(2) << "U(" << x[0] << ", " << y[j] << ") = " << U[0][j]<<"\t\t";
            cout << "U(" << x[n] << ", " << y[j] << ") = " << U[n][j] << endl;
        }


        for (int j = 1; j < n; j++)  // 
                                     // 
                                     // 
        {
            h1 = (U[n][j] - U[0][j]) / n;

            for (int i = 1; i < n; i++)
            {
                U[i][j] = U[i - 1][j] + h1;
            }
        }

        for (int j = 1; j < n; j++)
        {
            for (int i = 1; i < n; i++)
            {
                u[i][j][0] = U[i][j]; // 
            }
        }


        int count_iteration = 0; // 
        bool check = true;       // 
        while (check == true) 
        {
            check = false;
            count_iteration++;
            
            for (int j = 1; j < n; j++)
            {
                for (int i = 1; i < n; i++)
                    // 
                {
                         if (i + 1 == n)  a = U[i + 1][j]; 
                    else if (i + 1 != n)  a = u[i + 1][j][count_iteration - 1]; // 

                         if (i - 1 == 0)  b = U[i - 1][j];
                    else if (i - 1 != 0)  b = u[i - 1][j][count_iteration];     // 

                         if (j + 1 == n)  c = U[i][j + 1];
                    else if (j + 1 != n)  c = u[i][j + 1][count_iteration - 1]; // 

                         if (j - 1 == 0)  d = U[i][j - 1];
                    else if (j - 1 != 0)  d = u[i][j - 1][count_iteration];     // 

                    u[i][j][count_iteration] = (a + b + c + d) * 1 / 4;         // 

                    if (abs(u[i][j][count_iteration] - u[i][j][count_iteration - 1]) > eps) // 
                                                                                            // 
                    {
                        check = true;
                    }
                }
            }
        }

        int count = 1;
        cout << "\n\nNetice:  U[n][m] " << endl;
        cout << "\t n - sira nomresi;" << endl;
        cout << "\t m - iterasiyalarin sayi;\n\n";
        cout << "-> Qeyd: Epsilon = " << eps << " (Yigilma serti)\n";
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << "n" << " \t m = 0\t\t" << "m = 1\t\t"<< "m = 2" << "\t\t... ... ...\tm = " << count_iteration << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        for (int j = 1; j < n; j++)
        {
            for (int i = 1; i < n; i++)
            {
                cout << count <<"\t " << setprecision(10) << u[i][j][0] << "\t\t";
                cout << setprecision(10) << u[i][j][1] << "\t";
                cout << setprecision(10) << u[i][j][2] << "\t... ... ...\t";
                cout << setprecision(10) << u[i][j][count_iteration] << endl;
                
                count++;             
            }
        }
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }
};                                                                                          

int main()
{
    Dirichlet Test;
    return 0;
}
