#include<iostream>
#include <vector>
//#include <sotrudnik.cpp>
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
/*
vector<vector<double>> Finding_Centr(double R, vector<Sotrudnik> employees, vector<double> centr, vector<double> sum){

    vector<vector<double>> answer;
    vector<double> tmp;
    for (int i = 0; i < static_cast<int>(employees.size()); i++){
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
*/

vector<vector<double>> Finding_Centr(double R, vector<vector<double>> employees, vector<double> centr, vector<double> sum){

    vector<vector<double>> answer;
    vector<double> tmp;
    for (int i = 0; i < static_cast<int>(employees.size()); i++){
        //pushing guys in sphere
        if (norm(centr, employees[i]) <= R)
        {
            tmp.push_back(i);
            for (int j = 0; j < static_cast<int>(employees[i].size()); j++)
            {
                //sum of abilities
                sum[j] += employees[i][j]; //сумма по всем координатам для всех сотрудников на расстоянии до R
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
/*double find_r(vector<Sotrudnik> employees)
{
    vector<double> center_postition = employees[0].abilities;
    double max = 0;
    for (int i = 1; i < static_cast<int>(employees.size()); i++)
        for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++)
            if (norm(center_postition, employees[i].abilities) > max)
                max = norm(center_postition, employees[i].abilities);
    return max;
}*/

double find_r(vector<vector<double>> employees)
{
    vector<double> center_postition = employees[0];
    double max = 0;
    for (int i = 1; i < static_cast<int>(employees.size()); i++)
        for (int j = 0; j < static_cast<int>(employees[i].size()); j++)
            if (norm(center_postition, employees[i]) > max)
                max = norm(center_postition, employees[i]);
    return max;
}

//normalize dots
vector<double> normalize(vector<double> abilities, double xMin, double xMax){
    for (int i = 0; i < static_cast<int>(abilities.size()); i++)
        abilities[i] = (abilities[i] - xMin) / (xMax - xMin);
    return abilities;
}

//Forel
/*
vector<vector<Sotrudnik>> forel(vector<Sotrudnik> employees, double xMin, double xMax){
    for (int i = 0; i < static_cast<int>(employees.size()); i++)
        employees[i].abilities = normalize(employees[i].abilities, xMin, xMax);
    vector<vector<Sotrudnik>> clusters = {};
    vector<double> centr = employees[0].abilities;
    vector<double> first_centr = centr;
    //vector<double> tmp;
    double R = 30;
    //double R = find_r(employees);
    vector<double> sum;
    //double sum_1 = 0;
    //tmp.push_back(employees[0].abilities);
    sum = employees[0].abilities;
    //sum of abilities of the first guy in space
    for (int i = 1; i < static_cast<int>(employees[0].abilities.size()); i++){
        sum.push_back(employees[0].abilities[i]);
    }

    while (employees.size()!= 0){
        vector<double> centr = employees[0].abilities;
        R = 30;
        vector<vector<double>> tmp = Finding_Centr(R, employees, centr, sum);
        R /= 2;
        vector<double> previous_centr = tmp[0];
//probably shit
        bool flag = true;

        while (flag) {
            previous_centr = centr;
            tmp = Finding_Centr(R, employees, centr, sum);
            centr = tmp[0];
            for (int i = 0; i < centr.size(); i++)
                if (centr[i] == previous_centr[i])
                    flag = false; //когда будет всего один элемент равен, но не весь вектор, даст неправильный результат
        }
        int i = tmp[1].size() - 1;
        vector<Sotrudnik> cluster;
        vector<Sotrudnik> clear = employees;
        while (i >= 0) {
            cluster.push_back(employees[tmp[1][i]]);
            employees.erase(employees.begin() + tmp[1][i]);
            //tmp[1].erase(tmp[1].begin() + i);
            i--;
        }
        tmp.clear();
        employees.clear();
        clusters.push_back(cluster);
        cluster.clear();
        //vector<vector<double>> tmp = Finding_Centr(R, employees, centr, sum);
    }
    //centr = sum;
   // vector<Sotrudnik> space;
    return clusters;
}*/

vector<vector<vector<double>>> forel(vector<vector<double>> employees, double xMin, double xMax){
    for (int i = 0; i < static_cast<int>(employees.size()); i++)
        employees[i] = normalize(employees[i], xMin, xMax);
    vector<vector<vector<double>>> clusters = {};
    vector<double> centr = employees[0];
    vector<double> first_centr = centr;
    //vector<double> tmp;
    double R = 30;
    //double R = find_r(employees);
    vector<double> sum;
    //double sum_1 = 0;
    //tmp.push_back(employees[0].abilities);
    sum = employees[0];
    //sum of abilities of the first guy in space
    for (int i = 1; i < static_cast<int>(employees[0].size()); i++){
        sum.push_back(employees[0][i]);
    }

    while (employees.size()!= 0){
        vector<double> centr = employees[0];
        R = 30;
        vector<vector<double>> tmp = Finding_Centr(R, employees, centr, sum);
        R /= 2;
        vector<double> previous_centr = tmp[0];
//probably shit
        bool flag = true;

        while (flag) {
            previous_centr = centr;
            tmp = Finding_Centr(R, employees, centr, sum);
            centr = tmp[0];
            for (int i = 0; i < centr.size(); i++)
                if (centr[i] == previous_centr[i])
                    flag = false; //когда будет всего один элемент равен, но не весь вектор, даст неправильный результат
        }
        int i = tmp[1].size() - 1;
        vector<vector<double>> cluster;
        vector<vector<double>> clear = employees;
        /*while (i >= 0) {
            cluster.push_back(employees[tmp[1][i]]);
            employees.erase(employees.begin() + tmp[1][i]);
            //tmp[1].erase(tmp[1].begin() + i);
            i--;
        }*/
        tmp.clear();
        employees.clear();
        clusters.push_back(cluster);
        cluster.clear();
        //vector<vector<double>> tmp = Finding_Centr(R, employees, centr, sum);
    }
    //centr = sum;
   // vector<Sotrudnik> space;
    return clusters;
}






