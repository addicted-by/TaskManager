#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <list>
#include <vector>
#include "Sotrudnik.h"

using namespace std;

vector<vector<double>> centrs;
//Euclidean norm
double norm(vector<double> FirstGuy, vector<double> SecondGuy) {
    double sum = 0;
    for (int i = 0; i < static_cast<int>(FirstGuy.size()); i++) {
        sum += (FirstGuy[i] - SecondGuy[i]) * (FirstGuy[i] - SecondGuy[i]);
    }
    return sqrt(sum);
}

//finding center of mass
vector<vector<double>> Finding_Centr(double R, vector<Sotrudnik> employees, vector<double> centr) {
    vector<vector<double>> answer;
    vector<double> tmp;
    vector<double> sum = {};
    for (int i = 0; i < employees[0].abilities.size(); i++)
        sum.push_back(0);
    //vector<double> sum;
    //fill(sum.begin(), sum.begin() + employees[0].abilities.size(), 0);
    for (int i = 0; i < static_cast<int>(employees.size()); i++) {
        //pushing guys in sphere
        if (norm(centr, employees[i].abilities) <= R) {
            tmp.push_back(i);
            for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++) {
                //sum of abilities
                sum[j] += employees[i].abilities[j]; //сумма по всем координатам для всех сотрудников на расстоянии до R
            }
        }
    }
    //finding centr
    for (int i = 0; i < static_cast<int>(sum.size()); i++) {
        sum[i] /= tmp.size();
        centr[i] = sum[i];
    }
    answer.push_back(centr);
    answer.push_back(tmp);
    return answer;
}

//finding minimal radius of sphere that contain all employees
double find_r(vector<Sotrudnik> employees) {
    vector<double> center_postition = employees[0].abilities;
    double max = 0;
    for (int i = 1; i < static_cast<int>(employees.size()); i++)
        for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++)
            if (norm(center_postition, employees[i].abilities) > max)
                max = norm(center_postition, employees[i].abilities);
    return max;
}

//normalize dots
vector<double> normalize(vector<double> abilities, double xMin, double xMax) {
    for (int i = 0; i < static_cast<int>(abilities.size()); i++)
        abilities[i] = (abilities[i] - xMin) / (xMax - xMin);
    return abilities;
}

vector<double> UnNormalize(vector<double> abilities, double xMin, double xMax) {
    for (int i = 0; i < static_cast<int>(abilities.size()); i++)
        abilities[i] = abilities[i] * (xMax - xMin) + xMin;
    return abilities;
}

//Forel
vector<vector<Sotrudnik>> forel(vector<Sotrudnik> employees, double xMin, double xMax) {
    for (int i = 0; i < static_cast<int>(employees.size()); i++)
        employees[i].abilities = normalize(employees[i].abilities, xMin, xMax);
    vector<vector<Sotrudnik>> clusters = {};
    vector<double> centr = employees[0].abilities;
    vector<double> first_centr = centr;
    double Rconst = find_r(employees);
    double R;
    while (employees.size() != 0) {
        vector<double> centr = employees[0].abilities;
        R = Rconst;
        vector<vector<double>> tmp = Finding_Centr(R, employees, centr);
        R /= 5;
        vector<double> previous_centr = tmp[0];
        //probably shit
        bool flag = true;
        while (flag) {
            previous_centr = centr;
            tmp = Finding_Centr(R, employees, centr);
            centr = tmp[0];
            flag = false;
            for (unsigned int i = 0; i < centr.size(); i++) {
                if (centr[i] != previous_centr[i]) {
                    flag = true;
                    break;
                }  
            } 
        }
        int i = tmp[1].size()-1;
        vector<Sotrudnik> cluster;
        centrs.push_back(tmp[0]);
        while (i >= 0) {
             cluster.push_back(employees[tmp[1][i]]);
             employees.erase(employees.begin() + tmp[1][i]);
             i--;
         }
        tmp.clear();
        //удалить этот код
        for (unsigned int i = 0; i < cluster.size(); i++)
            cluster[i].abilities = UnNormalize(cluster[i].abilities, xMin, xMax);
        //тута конец удаления
        clusters.push_back(cluster);
        cluster.clear();
    }
    return clusters;
}



int main() {
    vector<Sotrudnik> space;
    space.push_back(Sotrudnik(vector<double> {1, 1}, 1,1,true));
    space.push_back(Sotrudnik(vector<double> {3, 2}, 1,1,true));
    space.push_back(Sotrudnik(vector<double> {2, 3}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {2, 2}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {1, 2}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {11, 11}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {13, 12}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {12, 13}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {12, 12}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {11, 21}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {7, 5}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {9, 6}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {8, 7}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {8, 6}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {7, 6}, 1, 1, true));
    /*space.push_back(Sotrudnik(vector<double> {1, 1,2,3,4}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {3, 2,2,1,3}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {2, 3,3,2,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {2, 2,14,12,3}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {1, 2, 0, 1,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {11, 11,1,1,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {13, 12,33,12,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {12, 13,22,22,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {12, 12,1,1,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {11, 21,0,0,0}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {7, 5,20,20,20}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {9, 6,15,15,15}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {8, 7,1,1,1}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {8, 6,1,2,3}, 1, 1, true));
    space.push_back(Sotrudnik(vector<double> {7, 6,6,6,6}, 1, 1, true));*/
    vector<vector<Sotrudnik>> clusters = forel(space, 1, 21);
    
    for (unsigned int i = 0; i < clusters.size(); i++) {
        cout << i + 1 << " cluster\nCenter: ";
        if (!clusters[i].empty()) {
            for (unsigned int j = 0; j < centrs[i].size(); j++) {
                cout << centrs[i][j] << " ";
            }
            cout << endl;
        }
        for (unsigned int j = 0; j < clusters[i].size(); j++) {
            cout << j + 1 << " employee\n";
            for (unsigned int k = 0; k < clusters[i][j].abilities.size(); k++)
                cout << clusters[i][j].abilities[k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}