#include "minCostFlow.h"

using namespace std;

int N;
int INF	= INT_MAX / 2 - 1;
//vector<vector<int>> cap, cost;
vector<int> dist, dad, pi;
vector<vector<int>> flow;
vector<bool> found;

//sprawdzanie czy sciezka ze zrodla do ujscia istnieje
bool minCostFlow::searchGraphBellmanFord(int src, int sink) {

    found.assign(found.size(), false);
    dist.assign(dist.size(), INF);

    dist[src] = 0;

    while (src != N) {
        int best = N;
        found[src] = true;
        for (int k = 0; k < N; k++) {
            if (found[k])
                continue;

            if (flow[k][src] != 0) {
                int val = dist[src] + pi[src] - pi[k] - cost[k][src];
                if (dist[k] > val) {
                    dist[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < cap[src][k]) {
                int val = dist[src] + pi[src] - pi[k] + cost[src][k];
                if (dist[k] > val) {
                    dist[k] = val;
                    dad[k] = src;
                }
            }
            if (dist[k] < dist[best])
                best = k;
        }

        src = best;
        //if(debuggMode)
        //    cout << src << endl;
    }
    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist[k], INF);

    return found[sink];
}

//szukanie minimalnego kosztu maksymalnego przeplywu ze zrodla (src) do ujscia (sink)
int minCostFlow::getFlowBellmanFord(int src, int sink) {

	int totcost = 0;
    int tmpcost = 0;
    int addcost = 0;

	while (searchGraphBellmanFord(src, sink)) {
        tmpcost = totcost;
		int amt = INF;
        for (int x = sink; x != src; x = dad[x])
            amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);

        for (int x = sink; x != src; x = dad[x]) {
            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                totcost -= /*amt * */ cost[x][dad[x]];
                if(debuggMode)
                    cout <<"1:  " << x << " - " << dad[x] << endl;
            } else {
                flow[dad[x]][x] += amt;
                totcost += /*amt * */ cost[dad[x]][x];
                if(debuggMode)
                    cout <<"1:  "<< dad[x] << " - " << x << endl;
            }
        }
        if(debuggMode)
            cout << "cost: " << totcost << "; added cost: " << totcost-tmpcost << "\n" << endl;
    }

    return totcost;
}

int minCostFlow::minCostBellmanFord(vector<vector<int>> cap, vector<vector<int>> cost) {

    if(debuggMode)
        cout << "\nBellmanFord" << endl;

    N = cap.size();
    int s = 0, t = N-1;
    found = vector<bool> (N, 0);
    flow = vector<vector<int>> (N, vector<int>(N) );
    dist = vector<int> (N+1);
    dad = vector<int> (N);
    pi = vector<int> (N);
    int wynik = getFlowBellmanFord(s, t);

    if(debuggMode) {
        cout << "cost: " << wynik << endl;
        cout << "\n\n" << endl;
    }
    return wynik;
}
