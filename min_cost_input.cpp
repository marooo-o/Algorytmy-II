//http://www.algorytm.org/algorytmy-grafowe/algorytm-forda-bellmana.html
#include "minCostFlow.h"

using namespace std;

void minCostFlow::readInput(string fileName)
{
    int tmp;
    int fieldNum, breweryNum, innNum, crossNum, roadNum;
    int maks;
    string roadStart, roadEnd, flow, cost;

    ifstream in(fileName);
    in >> fieldNum >> breweryNum >> innNum >> crossNum >> roadNum;
    maks = fieldNum + breweryNum + crossNum + innNum+2;

    int fieldProduction[fieldNum], innCapacity[innNum];
    vector<vector<int>> flowMatrix(maks, vector<int>(maks));
    vector<vector<int>> costMatrix(maks, vector<int>(maks));
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            flowMatrix[i][j] = 0;
            costMatrix[i][j] = 0;
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

    for(int i = 0; i<fieldNum; i++) {
        flowMatrix[0][i+1] = fieldProduction[i];
        costMatrix[0][i+1] = 1;
    }

    for(int i = 0; i<innNum; i++) {
        flowMatrix[maks-(innNum+1)+i][maks-1] = innCapacity[i];
        costMatrix[maks-(innNum+1)+i][maks-1] = 1;
    }

    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            if(costMatrix[i][j] < 10) {
                cout << " ";
            }
            cout << costMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n------------------\n" << endl;
    cout << " 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5\n" << endl;
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            if(flowMatrix[i][j] < 10) {
                cout << " ";
            }
            cout << flowMatrix[i][j] << " ";
        }
        cout << "\t|" << i << endl;
    }

    cout << "\n\nwymiary: " << flowMatrix.size() << " x " << flowMatrix[0].size() << endl;
    /*for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            if(costMatrix[i][j] == -1);
        }
    }*/
//    return 0;
    this->cap  = flowMatrix;
    this->cost = costMatrix;
}
