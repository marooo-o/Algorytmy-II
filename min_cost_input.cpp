//http://www.algorytm.org/algorytmy-grafowe/algorytm-forda-bellmana.html
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int tmp;
    int fieldNum, breweryNum, innNum, crossNum, roadNum;
    int maks;
    string roadStart, roadEnd, flow, cost;

    ifstream in("inCost.txt");
    in >> fieldNum >> breweryNum >> innNum >> crossNum >> roadNum;
    maks = fieldNum + breweryNum + crossNum + innNum+2;

    int fieldProduction[fieldNum], innCapacity[innNum], flowMatrix[maks][maks], costMatrix[maks][maks];
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            flowMatrix[i][j] = 0;
            costMatrix[i][j] = -1;
        }
    }

    for (int i = 0; i < fieldNum; i++)
    {
        in >> tmp;
        fieldProduction[i] = tmp;
    }
    for (int i = 0; i < innNum; i++)
    {
        in >> tmp;
        innCapacity[i] = tmp;
    }

    for (int i = 0; i < roadNum; i++)
    {
        int addX=0, addY=0;
        in >> roadStart >> roadEnd >> flow >> cost;
        switch (roadStart[0])
        {
            case 's':
            {
                addX = fieldNum;
                break;
            }
            case 'b':
            {
                addX = fieldNum + crossNum;
                break;
            }
        }

        switch (roadEnd[0])
        {
            case 's':
            {
                addY = fieldNum;
                break;
            }
            case 'b':
            {
                addY = fieldNum + crossNum;
                break;
            }
            case 'k':
            {
                addY = fieldNum + crossNum + breweryNum;
                break;
            }
        }
        int x = addX + stoi(roadStart.erase(0, 1));
        int y = addY + stoi(roadEnd.erase(0, 1));

        flowMatrix[x][y] = stoi(flow);
        costMatrix[x][y] = stoi(cost);
    }
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            cout << costMatrix[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            if(costMatrix[i][j] == -1);
        }
    }
    return 0;
}
