#include "minCostFlow.h"
using namespace std;

int graphSize, minCostValue = 0, addCost, minusCost;
vector<int> dist1, path;
vector<vector<bool>> visited;
bool visitedNewPath;
vector<bool> found1;
vector<vector<int>> tmpCost;
// szukanie min dystansu
int minCostFlow::searchGraphDijkstra(vector<int> dist, vector<bool> found)
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

void minCostFlow::getFlowDijkstra(vector<vector<int>> costTmp, int src, vector<vector<int>> cost)
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
                    cout << m << ", " << k << ", dist: " << dist1[m] << " : " << dist1[k] << "\t\t" << costTmp[m][k] << endl;
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
            cout << "cost: " << minCostValue << "; addCost: " << addCost << endl;
}

int minCostFlow::minCostDijkstra(vector<vector<int>> cap, vector<vector<int>> cost)
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
        cout << "minCostValue: " << minCostVal << endl;
        cout << "\n------------------\n" << endl;
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
