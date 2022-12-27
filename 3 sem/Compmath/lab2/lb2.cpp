#include <cmath>
#include <vector>
#include <stdio.h>
#include <bitset>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <random>
#include <ctime> 

using namespace std;

double sum(double &t, double a, double b){
  double s = a + b;//s = RN(a+b) - машинная сумма 
  double bs = s - a;//b'= RN(s-a)
  double as = s - bs;//a'= RN(s-b')
  t = (b - bs) + (a - as);
  return s;
}

double mul(double &e, double a, double b){
  double m = a * b;
  e = fma(a, b, -m);// fms
  return m;
}

int count_ulp(double machine, double standart){
  double e = abs(machine - standart);
  e = e / abs(standart) * 100;
  printf("Относительная погрешность: %1.16f%% \n\n", e);
  return 0;
}

double machine(double &e, vector<double>& X, vector<double>& Y){ //метод Ogita—Rump—Oishi
  double s = 0.0, m, e1, e2;

  for (int i=0; i < X.size(); ++i){
    m = mul(e1, X[i], Y[i]);// m = RN(X[i]*Y[i]), т.е. с включенной ошибкой е

    s = sum(e2, s, m);// s += m

    e += e1 + e2;// суммируем ошибки
  }
  return s;// Общая сумма с общей ошибкой
}

double standart_method(vector<double>& X, vector<double>& Y){
  double s = 0.0, m;
  for (int i = 0; i < X.size(); ++i){

    m = X[i] * Y[i];
    s += m;

  }
  return s;
}

int main(){
  double machine_res, res_t, res_m, value, standart_res;
  double e = 0;
  vector<double> X = {};
  vector<double> Y = {};

  int a, b, size;
  printf("\nВведите диапазон значений: ");
  scanf("%d %d", &a, &b);
  printf("Введите кол-во компонент: ");
  scanf("%d", &size);
  printf("\n");
  srand(time(0)); 

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dist(a, b);

  for(int i = 0; i < size; i++){
    value = dist(gen);
    X.push_back(value);
  }
  for(int i = 0; i < size; i++){
    value = dist(gen);
    Y.push_back(value);
  }  
  // X.push_back(pow(10,22));
  // X.push_back(pow(10,8));
  // X.push_back(1);
  // X.push_back(pow(10,20));

  // Y.push_back(pow(10,-22));
  // Y.push_back(pow(10,8));
  // Y.push_back((-1) * pow(10, 16));
  // Y.push_back(pow(10,-20));

  printf("Vector X: [ ");
  std::copy(X.begin(), X.end(), std::ostream_iterator<double>(std::cout, " "));
  printf("]\n\n");
  std::cout << "Vector Y: [ ";
    std::copy(Y.begin(), Y.end(), std::ostream_iterator<double>(std::cout, "  "));
  printf("]\n\n");

  machine_res = machine(e, X, Y);
  standart_res = standart_method(X, Y);
  res_t = machine_res + e;
  

  printf("Standart (X,Y) = %1.16f\n", standart_res);
  printf("Machine (X,Y) = %1.16f\n", res_t);
 // cout << machine_res << ' ' << e << endl;
  
  count_ulp(res_t, standart_res);
  return 0;
}