#include <iostream>
#include <sotrudnik.h>
#include <Forel.cpp>
#include <fstream>
using namespace std;



int main()
{
    vector<double> f = {1,2,4,5};
    vector<double> n = {3,2,4,3};
    Sotrudnik x = Sotrudnik(f,2,2,false);
    Sotrudnik k = Sotrudnik(n, 0, 0,false);
    vector<Sotrudnik> employees;
    employees.push_back(x);
    employees.push_back(k);
    vector<Sotrudnik> cluster;
    for (int i = 0; i < static_cast<int>(forel(employees,1,5).size()); i++){
        cluster.push_back(forel(employees,1,5)[i][i]);
    }
    for (int i = 0; i < static_cast<int>(cluster.size()); i++){
        cout << "cluster " << i;
        for (int j = 0; j < static_cast<int>(cluster[i].abilities.size()); j++)
            cout << cluster[i].abilities[j] << "\n";
    }
    /*ifstream inf;
    inf.open("EmployeeSpace.csv");
    while(inf){
        string input;
        inf >> input;
        cout << input;
    }*/
    return 0;
}
