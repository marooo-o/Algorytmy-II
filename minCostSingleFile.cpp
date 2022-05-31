#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool debuggMode, testMode;
vector<vector<int>> cap, costDijkstra, costBellmanFord;


void readInput(string fileName)
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
    cap  = flowMatrix;
    costBellmanFord = costMatrix;

    for(int i = 0; i<fieldNum; i++) {
        costMatrix[0][i+1] = 1;
        costMatrix[i+1][0] = -1;
    }
    for(int i = 0; i<innNum; i++) {
        costMatrix[maks-(innNum+1)+i][maks-1] = 1;
        costMatrix[maks-1][maks-(innNum+1)+i] = -1;
    }

    costDijkstra = costMatrix;
}

int graphSize, minCostValue = 0, addCost, minusCost;
vector<int> dist1, path;
vector<vector<bool>> visited;
bool visitedNewPath;
vector<bool> found1;
vector<vector<int>> tmpCost;

// szukanie min dystansu
int searchGraphDijkstra(vector<int> dist, vector<bool> found)
{
    int minimum=INT_MAX,ind;

    for(int k=0;k<graphSize;k++) {
        if(found[k]==false && dist[k]<=minimum) {
            minimum=dist[k];
            ind=k;
        }
    }
    return ind;
}

void getFlowDijkstra(vector<vector<int>> costTmp, int src, vector<vector<int>> cost)
{
    path.clear();
    found1.assign(found1.size(), false);
    dist1.assign(dist1.size(), INT_MAX);

    addCost = 0;
    minusCost = 0;
    int current;

    dist1[src] = 0;

    for(int k = 0; k<graphSize; k++) {
        int m=searchGraphDijkstra(dist1,found1);
        found1[m]=true;
        for(int k = 0; k<graphSize; k++) {
            // uaktualnianie kosztu do sasiednich wierzcholkow
            if(!(found1[k]) && (costTmp[m][k]) && (dist1[m]!=INT_MAX) && (dist1[m]+costTmp[m][k]<dist1[k])) {
                dist1[k]=dist1[m]+costTmp[m][k];
                path[k]=m;
                if(debuggMode)
                    cout << m << " - " << k << ", dist m: " << dist1[m] << " : dist k: " << dist1[k] << "\t\t cost m-k: " << costTmp[m][k] << endl;
            }
        }
    }

    //dodawanie kosztu tylko tych sciezek, ktorych jeszcze nie odwiedzilismy
    current = cost.size()-1;
    visitedNewPath = false;
    while(current) {
        if(!visited[path[current]][current]) {
            visited[path[current]][current] = true;
            visitedNewPath = true;
        }
        if(path[current]!= 0 && current != cost.size()-1) {
            //addCost--;
            addCost += cost[path[current]][current];
        }
        //addCost += cost[d[current]][current];
        //usuwanie nadmiarowego kosztu, chyba ze znajde sposob aby algorytm nie ignorowal sciezek o koszcie 0
        current = path[current];
    }
    if(visitedNewPath)
        minCostValue += addCost;

    if(debuggMode)
        if(visitedNewPath)
            cout << "\ncost: " << minCostValue << "; addCost: " << addCost << "\n" << endl;
}

int minCostDijkstra(vector<vector<int>> cap, vector<vector<int>> cost)
{
    int loopSize;
    if(debuggMode)
        cout << "Dijkstra" << endl;

    graphSize = cost.size();
    path = vector<int> (graphSize);
    found1 = vector<bool> (graphSize, 0);
    dist1 = vector<int> (graphSize);
    visited = vector<vector<bool>> (graphSize, vector<bool>(graphSize));
    tmpCost = cost;

    int minCostVal = INT_MAX;
    loopSize = tmpCost.size();
    for(int i = 0; i<loopSize; i++) {
        for(int j = 0; j<loopSize; j++) {
            if(tmpCost[i][j]<minCostVal) {
                minCostVal = tmpCost[i][j];
            }
        }
    }
    for(int i = 0; i<loopSize; i++) {
        for(int j = 0; j<loopSize; j++) {
            if(tmpCost[i][j] != 0) {
                tmpCost[i][j] += (abs(minCostVal)+1);
            }
        }
    }
    if(debuggMode) {
        cout << "minCostPathValue: " << minCostVal << endl;
        cout << "\n------------------\ncostMatrix:\n" << endl;
        cout << "   ";
        for(int i = 0; i<loopSize; i++) {
            cout << i%10 << "    ";
        }
        cout << "\n" << endl;
        for(int i = 0; i<loopSize; i++) {
            for(int j=0; j<loopSize; j++) {
                if(tmpCost[i][j] < 10) {
                    cout << " ";
                }
                if(tmpCost[i][j] >= 0) {
                    cout << " ";
                }
                if(tmpCost[i][j] > -10) {
                    cout << " ";
                }
                cout << tmpCost[i][j] << " ";
            }
            cout << "\t|" << i << endl;
        }
    }
    cout << "------------------\n" << endl;
    while(1) {
        getFlowDijkstra(tmpCost, 0, cost);
        if(visitedNewPath == false) {
            break;
        }

        int minFlowValue = INT_MAX;
        int current = cost.size()-1;
        while(current) {
            if(debuggMode)
                cout << path[current] << "-" << current << " : " << cost[path[current]][current] << endl;

            if(cap[path[current]][current] < minFlowValue) {
                minFlowValue = cap[path[current]][current];
            }
            current = path[current];
        }
        current = cost.size()-1;
        while(current) {
            cap[path[current]][current] -= minFlowValue;
            if(cap[path[current]][current] == 0) {
                tmpCost[path[current]][current] = 0;
            }
            current = path[current];
        }
        if(debuggMode)
            cout << "\n------------------------\n" << endl;
    }

    if(debuggMode)
        cout << "MIN COST: " << minCostValue << endl;

    return minCostValue;
}

int N;
int INF	= INT_MAX / 2 - 1;
vector<vector<int>> cost;
vector<int> dist2, dad, pi;
vector<vector<int>> flow;
vector<bool> found2;

bool searchGraphBellmanFord(int src, int sink) {

    found2.assign(found2.size(), false);
    dist2.assign(dist2.size(), INF);

    dist2[src] = 0;

    while (src != N) {
        int best = N;
        found2[src] = true;
        for (int k = 0; k < N; k++) {
            if (found2[k])
                continue;

            if (flow[k][src] != 0) {
                int val = dist2[src] + pi[src] - pi[k] - cost[k][src];
                if (dist2[k] > val) {
                    dist2[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < cap[src][k]) {
                int val = dist2[src] + pi[src] - pi[k] + cost[src][k];
                if (dist2[k] > val) {
                    dist2[k] = val;
                    dad[k] = src;
                }
            }
            if (dist2[k] < dist2[best])
                best = k;
        }
        src = best;
        //if(debuggMode)
        //    cout << src << endl;
    }
    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist2[k], INF);

    return found2[sink];
}

int getFlowBellmanFord(int src, int sink) {

	int totcost = 0;
    int tmpcost;
	while (searchGraphBellmanFord(src, sink)) {
        tmpcost = totcost;
		int amt = INF;
        for (int x = sink; x != src; x = dad[x])
        amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);
        for (int x = sink; x != src; x = dad[x]) {
            //if(x == N-1 || dad[x] == 0)
            //   continue;
            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                totcost -= /*amt * */ cost[x][dad[x]];
                //if(debuggMode)
                    cout << x << " - " << dad[x] << endl;
            } else {
                flow[dad[x]][x] += amt;
                totcost += /*amt * */ cost[dad[x]][x];
                if(debuggMode) {
                    cout << dad[x] << " - " << x << endl;
                }
            }
        }
        if(debuggMode)
            cout << "cost: " << totcost << ", added cost: " << totcost-tmpcost << "\n" << endl;
    }

    return totcost;
}

int minCostBellmanFord(vector<vector<int>> capIn, vector<vector<int>> costIn) {
    cap = capIn;
    cost = costIn;
    N = cap.size();
    int s = 0, t = N-1;
    found2 = vector<bool> (N, 0);
    flow = vector<vector<int>> (N, vector<int>(N) );
    dist2 = vector<int> (N+1);
    dad = vector<int> (N);
    pi = vector<int> (N);


    if(debuggMode) {
        int loopSize = cost.size();
        cout << "BellmanFord" << endl;
        cout << "\n------------------\ncostMatrix:\n" << endl;
        cout << "   ";
        for(int i = 0; i<loopSize; i++) {
            cout << i%10 << "    ";
        }
        cout << "\n" << endl;
        for(int i = 0; i<loopSize; i++) {
            for(int j=0; j<loopSize; j++) {
                if(cost[i][j] < 10) {
                    cout << " ";
                }
                if(cost[i][j] >= 0) {
                    cout << " ";
                }
                if(cost[i][j] > -10) {
                    cout << " ";
                }
                cout << cost[i][j] << " ";
            }
            cout << "\t|" << i << endl;
        }
    }
    cout << "------------------" << endl;

    int wynik = getFlowBellmanFord(s, t);

    if(debuggMode) {
        cout << "final cost: " << wynik << endl;
        cout << "\n\n" << endl;
    }
    return wynik;
}

int main() {
    string fileName = "inCost1.txt";
    int finalCost1, finalCost2;


    debuggMode = 1;
    testMode = 1;
    readInput(fileName);
    finalCost1 = minCostBellmanFord(cap, costBellmanFord);
    if(testMode) {
        finalCost2 = minCostDijkstra(cap, costDijkstra);

        if(finalCost1 == finalCost2) {
            cout << "COMPLETE. Min cost: " << finalCost1 << " == " << finalCost2 << endl;
        } else {
            cout << "ERROR:  BellmanFord: " << finalCost1 << " != Dijkstra: " << finalCost2 << endl;
        }
    } else {
        cout << "minimalny koszt naprawy wynoszi: " << finalCost1 << endl;
    }

    return 0;
}
