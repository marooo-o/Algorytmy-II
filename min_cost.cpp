#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int tmp, add;
    int fieldNum, breweryNum, innNum, crossNum, roadNum;
    int flow, cost, maks;
    string x, y;
    ifstream in("inCost.txt");
    in >> fieldNum >> breweryNum >> innNum >> crossNum >> roadNum;
    maks = fieldNum + breweryNum + crossNum + innNum;
    int fieldProduction[fieldNum], innCapacity[innNum], flowMatrix[maks][maks], costMatrix[maks][maks];
    for (int i = 0; i < fieldNum; i++)
    {
        in >> tmp;
        fieldProduction[i] = tmp;
        cout << tmp << endl;
    }
    for (int i = 0; i < innNum; i++)
    {
        in >> tmp;
        innCapacity[i] = tmp;
        cout << tmp << endl;
    }
    for (int i = 0; i < roadNum; i++)
    {
        in >> x >> y >> flow >> cost;
        switch (x[0])
        {
        case 'p':
        {
            break;
        }
        case 's':
        {
            break;
        }
        case 'b':
        {
            break;
        }

        default:
            break;
        }

        switch (y[0])
        {
        case 's':
        {
            break;
        }
        case 'b':
        {
            break;
        }
        case 'k':
        {
            break;
        }

        default:
            break;
        }
    }

    return 0;
}