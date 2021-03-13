#include<iostream>
#include <vector>
#include <sotrudnik.cpp>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;
double norm(vector<double> FirstGuy, vector<double> SecondGuy){
    double sum = 0;
    for (int i = 0; i < FirstGuy.size(); i++){
        sum += (FirstGuy[i] - SecondGuy[i])*(FirstGuy[i] - SecondGuy[i]);
    }
    return sqrt(sum);
}

void fOREL(vector<Sotrudnik> employees){
    vector<Sotrudnik> cluster;
    vector<double> centr = employees[0].abilities;
    vector<vector<double>> tmp;
    double R = 30;
    vector<double> sum;
    //double sum_1 = 0;
    tmp.push_back(employees[0].abilities);
    for (int i = 1; i < employees[0].abilities.size(); i++){
        sum.push_back(employees[0].abilities[i]);
    }
    for (int i = 1; i < employees.size(); i++){
        if (norm(centr, employees[i].abilities) <= R)
        {
            tmp.push_back(employees[i].abilities);
            for (int j = 0; j < employees[i].abilities.size(); j++){
                sum[j] += employees[i].abilities[j]; //сумма по всем координатам для всех сотрудников на расстоянии до R
                }
        }

    for (int i = 0; i < sum.size(); i++){
        sum[i] /= tmp.size();
        centr[i] = sum[i];

    }
    //centr = sum;
    vector<Sotrudnik> space;
}
}

