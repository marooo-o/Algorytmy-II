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
    maks = fieldNum + breweryNum + crossNum + innNum;

    int fieldProduction[fieldNum], innCapacity[innNum], flowMatrix[maks][maks], costMatrix[maks][maks];
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
        //flowMatrix[0]
        //cout << tmp << endl;
    }
    for (int i = 0; i < innNum; i++)
    {
        in >> tmp;
        innCapacity[i] = tmp;
        //cout << tmp << endl;
    }
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            cout << flowMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--------------------" << endl;
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
        //costMatrix[x][y] = stoi(cost);
        if(x==0 || y==0)
            cout << "ZERO" <<endl;
        //cout << x << " " << y << " " << stoi(flow) << " " << stoi(cost) << endl;
        //cout << flowMatrix[x][y] << endl;
    }
    for(int i = 0; i<maks; i++) {
        for(int j=0; j<maks; j++) {
            cout << flowMatrix[i][j] << " ";
        }
        cout << endl;
    }
    for(int i = 0; i<maks; i++) {
        int tmp1 = flowMatrix[0][i];
        int tmp2 = flowMatrix[i][0];
        if(tmp1 != 0)
            cout << tmp1 << " ";
        if(tmp2 != 0)
            cout << tmp2 << " ";

    }
    cout << endl;
    //cout << flowMatrix[11][0] << endl;
    return 0;
}
