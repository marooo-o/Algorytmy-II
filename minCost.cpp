#include "minCostFlow.h"
using namespace std;

int graphSize, minCostValue = 0, addCost, minusCost;
vector<bool> found;
vector<int> dist, d;
vector<vector<bool>> visited;
bool visitedNewPath;

// szukanie min dystansu
int minCostFlow::miniDist(vector<int> dist, vector<bool> found)
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

void minCostFlow::DijkstraAlgo(vector<vector<int>> cost, int src, bool print)
{
    d.clear();
    found.assign(found.size(), false);
    dist.assign(dist.size(), INT_MAX);

    addCost = 0;
    minusCost = 0;
    int current;

    dist[src] = 0;

    for(int k = 0; k<graphSize; k++) {
        int m=miniDist(dist,found);
        found[m]=true;
        for(int k = 0; k<graphSize; k++) {
            // updating the distance of neighbouring vertex
            if(!(found[k]) && (cost[m][k]) && (dist[m]!=INT_MAX) && (dist[m]+cost[m][k]<dist[k])) {
                dist[k]=dist[m]+cost[m][k];
                d[k]=m;
                //cout << m << ", " << k << ", " << dist[k] << " : " << dist[m] << "\t\t" << cost[m][k] << endl;
            }
        }
    }

    //dodawanie kosztu tylko tych sciezek, ktorych jeszcze nie odwiedzilismy
    current = cost.size()-1;
    visitedNewPath = false;
    while(current) {
        //cout << d[current] << "-" << current << " : " << cap[d[current]][current] << endl;
        if(!visited[d[current]][current]) {
            visited[d[current]][current] = true;
            visitedNewPath = true;
        }
            addCost += cost[d[current]][current];
            //cout << "d: " << d[current] << ", " << current << endl;
            //usuwanie nadmiarowego kosztu, chyba ze znajde sposob aby algorytm nie ignorowal sciezek o koszcie 0
            /*if(d[current]== 0) {
                addCost--;
                //minusCost++;
                //cout << "source" << endl;
            }
            if(current == cost.size()-1) {
                addCost--;
                //minusCost++;
                //cout << "sink" << endl;
            }*/
        //}
        current = d[current];
    }
    if(visitedNewPath)
        minCostValue += addCost;

    if(debuggMode)
        cout << "cost: " << minCostValue << "; addCost: " << addCost << endl;
}

int minCostFlow::minCost(vector<vector<int>> cap, vector<vector<int>> cost)
{
			//0   1   2   3   4   5   6   7
    cout << "matrix" << endl;
    cap = { {  0,   4,   4,  0,   0,   0,   0,   0 },

            { -4,   0,   0,  5,   6,   0,   0,   0 },

            { -4,   0,   0,  5,   0,   0,   0,   0 },

            {  0,  -5,  -5,  0,   0,   5,   2,   0 },

            {  0,  -6,   0,  0,   0,   0,   5,   0 },

            {  0,   0,   0, -5,   0,   0,   0,   5 },

            {  0,   0,   0, -2,  -5,   0,   0,   2 },

            {  0,   0,   0,  0,   0,  -5,  -2,   0 }};

            // 0    1    2    3    4    5    6    7    8
    cost = {{  0,   2,   3,   0,   0,   0,   0,   0 },

            { -2,   0,   0,   2,   5,   0,   0,   0 },

            { -3,   0,   0,   3,   0,   0,   0,   0 },

            {  0,  -2,  -3,   0,   0,   2,   4,   0 },

            {  0,  -5,   0,   0,   0,   0,   3,   0 },

            {  0,   0,   0,  -2,   0,   0,   0,   4 },

            {  0,   0,   0,  -4,  -3,   0,   0,   1 },

            {  0,   0,   0,   0,   0,  -4,  -1,   0 }};

    graphSize = cost.size();
    d = vector<int> (graphSize);
    found = vector<bool> (graphSize, 0);
    dist = vector<int> (graphSize);
    visited = vector<vector<bool>> (graphSize, vector<bool>(graphSize));

    //cout << "\n\n" << endl;
    while(1) {
        DijkstraAlgo(cost, 0, 0);
        if(visitedNewPath == false) {
            break;
        }

        int minFlowValue = INT_MAX;
        int current = cost.size()-1;
        while(current) {
            if(debuggMode)
                cout << d[current] << "-" << current << " : " << cap[d[current]][current] << endl;

            if(cap[d[current]][current] < minFlowValue) {
                minFlowValue = cap[d[current]][current];
            }
            /*if(current == 0) {
                //cout << endl;
                break;
            }*/
            current = d[current];
        }
        //cout << "\n" << minFlowValue << "\n" << endl;
        current = cost.size()-1;
        while(current) {
            cap[d[current]][current] -= minFlowValue;
            //cout << d[current] << "-" << current << " : " << cap[d[current]][current] << endl;
            if(cap[d[current]][current] == 0) {
                cost[d[current]][current] = 0;
                //cout << d[current] << ", " << current << " : " << cost[d[current]][current] << endl;
            }
            current = d[current];
        }
        /* else {
            cout << "HERE" << endl;
            minCostValue -= minusCost;
        }*/
        cout << "\n------------------------\n" << endl;
    }

    cout << "MIN COST: " << minCostValue << endl;
    return 0;
}
