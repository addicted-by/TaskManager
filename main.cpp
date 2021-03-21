#include <iostream>
#include <sotrudnik.h>
#include "Forel.cpp"
#include <fstream>
#include <string>
using namespace std;



int main()
{
    vector<double> f = {1,2,4,5};
    vector<double> n = {3,2,4,3};
    vector<vector<double>> space;
    space.push_back(f);
    space.push_back(n);
    /*Sotrudnik x = Sotrudnik(f,2,2,false);
    Sotrudnik k = Sotrudnik(n, 0, 0,false);
    vector<Sotrudnik> employees;
    employees.push_back(x);
    employees.push_back(k);
    vector<Sotrudnik> cluster;
    for (int i = 0; i < static_cast<int>(employees.size()); i++) {
        cout << i+1 <<" employer \n";
        for (int j = 0; j < static_cast<int>(employees[i].abilities.size()); j++)
            cout << employees[i].abilities[j] << "\n";

    }*/

    forel(space, 1, 5);
    cout << "Hello\n";
    /*ifstream inf;
    inf.open("EmployeeSpace.csv");
    while(inf){
        string input;
        inf >> input;
        cout << input;
    }*/
    return 0;
}
