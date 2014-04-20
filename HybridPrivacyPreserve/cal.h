#ifndef CAL_H_
#define CAL_H_

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
 
double binomial(int k,int n,double p);
double prior(int x,int di,double p1,double p2,int n);
int test_binomial(int n,double p);
void temp();
double binomial_con(int k,int n1,int n2,double p1,double p2);
double binomial_con_s(int k,int n1,int n2,double p1,double p2,int di);
 

double test();
double graphtest();

double graphtest2();
#endif