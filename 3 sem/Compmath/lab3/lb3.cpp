#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double x(double x){
    return -1 * pow(x, 5) - 1;
}

double f(double x){
    return pow(x, 5) + x + 1;
}

double df(double x){
    return 5 * pow(x, 4) + 1;
}

double g(double x){
    return x - f(x) / df(x);
}

double half_divide_method(){
    double L;
    double R;
    double e;
    cout<<"Enter L: "; cin >> L;
    cout<<"Enter R: "; cin >> R;
    cout<<"Enter error of calculation : "; cin >> e;
    int i = 0;
    bool ok = true;
    while (ok){
        i += 1;
        double x = (L + R) / 2; // # максимальное количество итераций = 51 для данного уравнения (из-за погрешности одно из чисел
        std::cout << "Iteration: " << i << x << '\n';
        if (f(x) * f(L) > 0)
            L = x;

        if (f(x) * f(R) > 0)
            R = x;
            
        if ( (f(x) == 0) || (f(x) == R) || (f(x) == L)  || ((R - L) / 2 < e) || (fabs(f(x)) < e) )
            break;
    }
    return (R + L) / 2;
}
 
int Niuton()
{
    double x;
    double eps;
    cout<<"Enter initial root value : "; cin >> x;
    cout<<"Enter error of calculation : "; cin >> eps;
    cout << "\nThe first method - Niuton: \n\n";
    for(double iter = 1; eps < fabs(f(x)); iter = iter + 1)
    {
        /* if ( abs( dx(x) ) > 1 ){
            std::cout << "Error mzf!\n";
            break;
        } */
        cout<<"Iteration : " << setprecision(16) << iter << endl;
        if(df(x) == 0)
            break;
        cout<<"x = " << x << endl;
        cout<<"g(x) = " << g(x) << endl;
        cout<<"df(x) = " << df(x) << endl;
        cout<<"f(x) = " << f(x) << '\n' <<endl;

        x = g(x);
    }
    return 0;
}

int main(){
    Niuton();
    //half_divide_method();
    return 0;
}
