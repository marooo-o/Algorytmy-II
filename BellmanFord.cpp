#include "minCostFlow.h"

using namespace std;

int N;
int INF	= INT_MAX / 2 - 1;
vector<vector<int>> cap, cost;
vector<int> dist2, dad, pi;
vector<vector<int>> flow;
vector<bool> found2;

bool minCostFlow::searchGraphBellmanFord(int src, int sink) {

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
        if(debuggMode)
            cout << src << endl;
    }
    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist2[k], INF);

    return found2[sink];
}

int minCostFlow::getFlowBellmanFord(int src, int sink) {

	int totcost = 0;

	while (searchGraphBellmanFord(src, sink)) {
		int amt = INF;
        for (int x = sink; x != src; x = dad[x])
        amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);
        for (int x = sink; x != src; x = dad[x]) {
            if(x == N-1 || dad[x] == 0)
                continue;
            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                totcost -= /*amt * */ cost[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                totcost += /*amt * */ cost[dad[x]][x];
            }
        }
        if(debuggMode)
            cout << "cost: " << totcost << endl;
    }

    return totcost;
}

int minCostFlow::minCostBellmanFord(vector<vector<int>> cap, vector<vector<int>> cost) {

    if(debuggMode)
        cout << "BellmanFord" << endl;

    N = cap.size();
    int s = 0, t = N-1;
    found2 = vector<bool> (N, 0);
    flow = vector<vector<int>> (N, vector<int>(N) );
    dist2 = vector<int> (N+1);
    dad = vector<int> (N);
    pi = vector<int> (N);
    int wynik = getFlowBellmanFord(s, t);

    if(debuggMode) {
        cout << "cost: " << wynik << endl;
        cout << "\n\n" << endl;
    }
    return wynik;
}
