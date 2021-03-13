#ifndef SOTRUDNIK_H
#define SOTRUDNIK_H
#include <vector>
using namespace std;
class Sotrudnik
{
public:
    vector<int> abilities;
    Sotrudnik();
    int norm;
    int busy;
    bool entry;
};

#endif // SOTRUDNIK_H
