#include "minCostFlow.h"

using namespace std;

int N;
int INF	= INT_MAX / 2 - 1;
vector<vector<int>> cap, cost;
vector<int> dist2, dad, pi;
vector<vector<int>> flow;
vector<bool> found2;

bool minCostFlow::searchGraphBellmanFord(int src, int sink) {
    // Initialise found2[] to false
    found2.assign(found2.size(), false);
    // Initialise the dist2[] to INF
    dist2.assign(dist2.size(), INF);
    // Distance from the source node
    dist2[src] = 0;
    // Iterate until src reaches N
    while (src != N) {
        int best = N;
        found2[src] = true;
        for (int k = 0; k < N; k++) {
            // If already found2
            if (found2[k])
                continue;
            // Evaluate while flow
            // is still in supply
            if (flow[k][src] != 0) {
                // Obtain the total value
                int val = dist2[src] + pi[src] - pi[k] - cost[k][src];
                // If dist2[k] is > minimum value
                if (dist2[k] > val) {
                    // Update
                    dist2[k] = val;
                    dad[k] = src;
                }
            }

            if (flow[src][k] < cap[src][k]) {
                int val = dist2[src] + pi[src] - pi[k] + cost[src][k];
                // If dist2[k] is > minimum value
                if (dist2[k] > val) {
                    // Update
                    dist2[k] = val;
                    dad[k] = src;
                }
            }
            if (dist2[k] < dist2[best])
                best = k;
        }
        // Update src to best for
        // next iteration
        src = best;
        if(debuggMode)
            cout << src << endl;
    }
    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist2[k], INF);
    // Return the value obtained at sink
    return found2[sink];
}

	// Function to obtain the maximum Flow
output minCostFlow::getFlowBellmanFord(int src, int sink) {
    output o;

	int totflow = 0, totcost = 0;

    // If a path exist from src to sink
	while (searchGraphBellmanFord(src, sink)) {
        // Set the default amount
		int amt = INF;
        for (int x = sink; x != src; x = dad[x])
        amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);
        for (int x = sink; x != src; x = dad[x]) {
            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                totcost -= /*amt * */ cost[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                totcost += /*amt * */ cost[dad[x]][x];
            }
        }
        totflow += amt;
        if(debuggMode)
            cout << "cost: " << totcost << endl;
    }

    // Return pair total cost and sink
    o.flow = totflow;
    o.cost = totcost;
    return o;
}

int minCostFlow::minCostBellmanFord(vector<vector<int>> cap, vector<vector<int>> cost) {
            // 0    1    2   3    4    5    6    7    8
    /*cap = { {  0,   4,   4,  0,   0,   0,   0,   0 },

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
    */

    N = cap.size();
    int s = 0, t = N-1;
    found2 = vector<bool> (N, 0);
    flow = vector<vector<int>> (N, vector<int>(N) );
    dist2 = vector<int> (N+1);
    dad = vector<int> (N);
    pi = vector<int> (N);
    output wynik = getFlowBellmanFord(s, t);

    if(debuggMode)
        printf("cost: %d, flow:%d\n", wynik.cost, wynik.flow);
    return wynik.cost;
}
