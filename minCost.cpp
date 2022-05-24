#include<iostream>
#include<climits>
#include<vector>
using namespace std;

int graphSize, minCost = 0, addCost, minusCost;
vector<bool> found;
vector<int> dist, d;
vector<vector<int>> cap, cost;
vector<vector<bool>> visited;

int miniDist(vector<int> dist, vector<bool> found) // finding minimum distance
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

void DijkstraAlgo(vector<vector<int>> cost, int src, bool print) // adjacency matrix
{
    //int dist[graphSize]; // // array to calculate the minimum distance for each node
    //bool found[graphSize];// boolean array to mark visited and unvisited for each node
    d.clear();
    found.assign(found.size(), false);
    dist.assign(dist.size(), INT_MAX);

    addCost = 0;
    minusCost = 0;
    int current = cost.size()-1;
    /*for(int k = 0; k<graphSize; k++) {
        dist[k] = INT_MAX;
        found[k] = false;
    }*/

    dist[src] = 0;   // Source vertex distance is set 0

    for(int k = 0; k<graphSize; k++) {
        int m=miniDist(dist,found);
        //cout << "m: " << m << endl;
        found[m]=true;
        for(int k = 0; k<graphSize; k++) {
            // updating the distance of neighbouring vertex
            if(!(found[k]) && (cost[m][k]) && (dist[m]!=INT_MAX) && (dist[m]+cost[m][k]<dist[k])) {
                dist[k]=dist[m]+cost[m][k];
                d[k]=m;
                if(print)
                    cout << m << ", " << k << ", " << dist[k] << " : " << dist[m] << "\t\t" << cost[m][k] << endl;
            }
        }
    }
    /*cout<<"Vertex\tDistance from source vertex"<<endl;
    for(int k = 0; k<graphSize; k++) {
        //char str=65+k;
        cout<<k<<"\t"<<dist[k]<<endl;
    }*/

///dodawanie kosztu tylko tych sciezek, ktorych jeszcze nie odwiedzielismy
    while(current) {
        //cout << d[current] << "-" << current << " : " << cap[d[current]][current] << endl;
        if(!visited[d[current]][current]) {
            visited[d[current]][current] = true;
            addCost += cost[d[current]][current];
//usuwanie nadmiarowego kosztu, chyba ze znajde sposob aby algorytm nie ignorowal sciezek o koszcie 0
            if(!d[current]) {
                addCost--;
                //minusCost++;
                //cout << "source" << endl;
            }
            if(current == cost.size()-1) {
                addCost--;
                //minusCost++;
                //cout << "sink" << endl;
            }

//---------------------------------------------------------------------------------------------------
        }
        current = d[current];
    }

    minCost += addCost;
    cout << "cost: " << minCost << "; addCost: " << addCost << endl;
}

int main()
{
			//0   1   2   3   4   5   6   7
    cap = { { 0,  4,  4,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  5,  6,  0,  0,  0 },
            { 0,  0,  0,  5,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  5,  2,  0 },
            { 0,  0,  0,  0,  0,  0,  5,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  5 },
            { 0,  0,  0,  0,  0,  0,  0,  2 },
            { 0,  0,  0,  0,  0,  0,  0,  0 }};

			//0   1   2   3   4   5   6   7
    cost = {{ 0,  2,  3,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  2,  5,  0,  0,  0 },
            { 0,  0,  0,  3,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  2,  4,  0 },
            { 0,  0,  0,  0,  0,  0,  3,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  4 },
            { 0,  0,  0,  0,  0,  0,  0,  1 },
            { 0,  0,  0,  0,  0,  0,  0,  0 }};

    graphSize = cost.size();
    d = vector<int> (graphSize);
    found = vector<bool> (graphSize, 0);
    dist = vector<int> (graphSize);
    visited = vector<vector<bool>> (graphSize, vector<bool>(graphSize));

    //cout << "\n\n" << endl;
    while(1) {
        DijkstraAlgo(cost, 0, 0);


        int minFlowValue = INT_MAX;
        int current = cost.size()-1;
        while(current) {
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
        if(addCost == 0) {
            break;
        }/* else {
            cout << "HERE" << endl;
            minCost -= minusCost;
        }*/
    }

    cout << "MIN COST: " << minCost << endl;
    return 0;
}
