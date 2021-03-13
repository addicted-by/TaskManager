#ifndef SOTRUDNIK_H
#define SOTRUDNIK_H
#include <vector>
using namespace std;
class Sotrudnik
{
public:
    vector<double> abilities;
    Sotrudnik(vector<double> abilities, int norm, int busy, bool entry);
    int norm;
    int busy;
    bool entry;
};

#endif // SOTRUDNIK_H
