#include<iostream>
#include <vector>
#include <sotrudnik.cpp>
#include <string>
#include <fstream>
#include <math.h>
#include <list>
using namespace std;

//Euclidean norm
double norm(vector<double> FirstGuy, vector<double> SecondGuy){
    double sum = 0;
    for (int i = 0; i < static_cast<int>(FirstGuy.size()); i++){
        sum += (FirstGuy[i] - SecondGuy[i])*(FirstGuy[i] - SecondGuy[i]);
    }
    return sqrt(sum);
}

//finding center of mass
vector<vector<double>> Finding_Centr(double R, vector<Sotrudnik> employees, vector<double> centr, vector<double> sum){
    vector<vector<double>> answer;
    vector<double> tmp;
    for (int i = 1; i < static_cast<int>(employees.size()); i++){
        //pushing guys in sphere
        if (norm(centr, employees[i].abilities) <= R)
        {
            tmp.push_back(i);
            for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++)
            {
                //sum of abilities
                sum[j] += employees[i].abilities[j]; //сумма по всем координатам для всех сотрудников на расстоянии до R
            }
        }
    }
//finding centr
    for (int i = 0; i < static_cast<int>(sum.size()); i++){
        sum[i] /= tmp.size();
        centr[i] = sum[i];
    }
    answer.push_back(centr);
    answer.push_back(tmp);
    return answer;
}

//finding minimal radius of sphere that contain all employees
double find_r(vector<Sotrudnik> employees)
{
    vector<double> center_postition = employees[0].abilities;
    double max = 0;
    for (int i = 1; i < static_cast<int>(employees.size()); i++)
        for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++)
            if (abs(center_postition[j] - employees[i].abilities[j]) > max)
                max = abs(center_postition[j] - employees[i].abilities[j]);
    return max;
}

//normalize dots
vector<double> normalize(vector<double> abilities, double xMin, double xMax){
    for (int i = 0; i < static_cast<int>(abilities.size()); i++)
        abilities[i] = (abilities[i] - xMin) / (xMax - xMin);
    return abilities;
}

//Forel
vector<vector<Sotrudnik>> forel(vector<Sotrudnik> employees, double xMin, double xMax){
    for (int i = 0; i < static_cast<int>(employees.size()); i++)
        employees[i].abilities = normalize(employees[i].abilities, xMin, xMax);
    vector<vector<Sotrudnik>> clusters = {};
    vector<double> centr = employees[0].abilities;
    vector<double> first_centr = centr;
    //vector<double> tmp;
    //double R = 30;
    double R = find_r(employees);
    vector<double> sum;
    //double sum_1 = 0;
    //tmp.push_back(employees[0].abilities);
    sum = employees[0].abilities;
    //sum of abilities of the first guy in space
    for (int i = 1; i < static_cast<int>(employees[0].abilities.size()); i++){
        sum.push_back(employees[0].abilities[i]);
    }
    while (employees.size()!=0){
        vector<vector<double>> tmp = Finding_Centr(R, employees, centr, sum);
        vector<double> previous_centr = tmp[0];
        R /= 8;
//probably shit
        while (centr != previous_centr) {
            previous_centr = centr;
            tmp = Finding_Centr(R, employees, centr, sum);
            centr = tmp[0];
        }
        int i = 0;
        vector<Sotrudnik> cluster;
        while (!tmp[1].empty()){
            cluster.push_back(employees[tmp[1][i]]);
            tmp[1].erase(tmp[1].begin() + i);
            i++;
        }
        clusters.push_back(cluster);
        cluster.clear();

    }
    //centr = sum;
    vector<Sotrudnik> space;
    return clusters;
}






