#include "minCostFlow.h"
using namespace std;

int graphSize, minCostValue = 0, addCost, minusCost;
vector<int> dist1, path;
vector<vector<bool>> visited;
bool visitedNewPath;
vector<bool> found1;

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

void minCostFlow::getFlowDijkstra(vector<vector<int>> cost, int src)
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
            if(!(found1[k]) && (cost[m][k]) && (dist1[m]!=INT_MAX) && (dist1[m]+cost[m][k]<dist1[k])) {
                dist1[k]=dist1[m]+cost[m][k];
                path[k]=m;
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
    if(debuggMode)
        cout << "Dijkstra" << endl;

    graphSize = cost.size();
    path = vector<int> (graphSize);
    found1 = vector<bool> (graphSize, 0);
    dist1 = vector<int> (graphSize);
    visited = vector<vector<bool>> (graphSize, vector<bool>(graphSize));

    while(1) {
        getFlowDijkstra(cost, 0);
        if(visitedNewPath == false) {
            break;
        }

        int minFlowValue = INT_MAX;
        int current = cost.size()-1;
        while(current) {
            if(debuggMode)
                cout << path[current] << "-" << current << " : " << cap[path[current]][current] << endl;

            if(cap[path[current]][current] < minFlowValue) {
                minFlowValue = cap[path[current]][current];
            }
            current = path[current];
        }
        current = cost.size()-1;
        while(current) {
            cap[path[current]][current] -= minFlowValue;
            if(cap[path[current]][current] == 0) {
                cost[path[current]][current] = 0;
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
