#include "minCostFlow.h"

using namespace std;

//wczytywanie danych z pliku tekstowego o nazwie zapisanej w zmiennej string fileName
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

    //zmienianie znawy string wierzcholkow na nazwe liczbowa i zapisywanie w macierzy sasiedztwa
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

        flowMatrix[y][x] = -stoi(flow);
        costMatrix[y][x] = -stoi(cost);
    }

    //tworzenie glownego zrodla i ujscia
    for(int i = 0; i<fieldNum; i++) {
        flowMatrix[0][i+1] = fieldProduction[i];
        flowMatrix[i+1][0] = -fieldProduction[i];
    }

    for(int i = 0; i<innNum; i++) {
        flowMatrix[maks-(innNum+1)+i][maks-1] = innCapacity[i];
        flowMatrix[maks-1][maks-(innNum+1)+i] = -innCapacity[i];
    }

    if(debuggMode) {
        cout << "   ";
        for(int i = 0; i<flowMatrix.size(); i++) {
            cout << i << "    ";
        }
        cout << "\n" << endl;
        for(int i = 0; i<maks; i++) {
            for(int j=0; j<maks; j++) {
                if(costMatrix[i][j] < 10) {
                    cout << " ";
                }
                if(costMatrix[i][j] >= 0) {
                    cout << " ";
                }
                if(costMatrix[i][j] > -10) {
                    cout << " ";
                }
                cout << costMatrix[i][j] << " ";
            }
            cout << "\t|" << i << endl;
        }

        cout << "\n------------------\n" << endl;
        cout << "   ";
        for(int i = 0; i<flowMatrix.size(); i++) {
            cout << i << "    ";
        }
        cout << "\n" << endl;
        for(int i = 0; i<maks; i++) {
            for(int j=0; j<maks; j++) {
                if(flowMatrix[i][j] < 10) {
                    cout << " ";
                }
                if(flowMatrix[i][j] >= 0) {
                    cout << " ";
                }
                if(flowMatrix[i][j] > -10) {
                    cout << " ";
                }
                cout << flowMatrix[i][j] << " ";
            }
            cout << "\t|" << i << endl;
        }

        cout << "\n\nwymiary: " << flowMatrix.size() << " x " << flowMatrix[0].size() << endl;
    }
    this->cap  = flowMatrix;
    this->costBellmanFord = costMatrix;

    for(int i = 0; i<fieldNum; i++) {
        costMatrix[0][i+1] = 1;
        costMatrix[i+1][0] = -1;
    }
    for(int i = 0; i<innNum; i++) {
        costMatrix[maks-(innNum+1)+i][maks-1] = 1;
        costMatrix[maks-1][maks-(innNum+1)+i] = -1;
    }

    this->costDijkstra = costMatrix;

}
