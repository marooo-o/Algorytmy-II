#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct output {
    int cost;
    int flow;
};

int N;
int INF	= INT_MAX / 2 - 1;
vector<vector<int>> cap, cost;
vector<bool> found;
vector<int> dist, dad, pi;
vector<vector<int>> flow;

bool searchGraph(int src, int sink) {
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
    }
    for (int k = 0; k < N; k++)
        pi[k] = min(pi[k] + dist[k], INF);
    return found[sink];
}

int getMaxFlow(int src, int sink) {
    output o;

	int totflow = 0, totcost = 0;

	while (searchGraph(src, sink)) {
		int amt = INF;
        for (int x = sink; x != src; x = dad[x])
        amt = min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] : cap[dad[x]][x] - flow[dad[x]][x]);
        for (int x = sink; x != src; x = dad[x]) {
            if (flow[x][dad[x]] != 0) {
                flow[x][dad[x]] -= amt;
                totcost -= amt * cost[x][dad[x]];
            } else {
                flow[dad[x]][x] += amt;
                totcost += amt * cost[dad[x]][x];
            }
        }
        totflow += amt;
    }

    return totcost;
}

int main() {
    int s = 0, t = 4;
            //0   1   2   3   4   5   6   7   8
    cap = { { 0,  10, 17, 0,  0,  0,  0,  0,  0 }, //0
            { 0,  0,  0,  3,  1,  0,  0,  0,  0 }, //1
            { 0,  0,  0,  6,  0,  4,  0,  0,  0 }, //2
            { 0,  0,  0,  0,  4,  3,  0,  0,  0 }, //3
            { 0,  0,  0,  0,  0,  3,  4,  9,  0 }, //4
            { 0,  0,  0,  0,  0,  0,  8,  7,  0 }, //5
            { 0,  0,  0,  0,  0,  0,  0,  0,  7 }, //6
            { 0,  0,  0,  0,  0,  0,  0,  0,  15}, //7
            { 0,  0,  0,  0,  0,  0,  0,  0,  0 }};//8

            //0   1   2   3   4   5   6   7   8
    cost = {{ 0,  0,  0,  0,  0,  0,  0,  0,  0 }, //0
            { 0,  0,  0,  2,  1,  0,  0,  0,  0 }, //1
            { 0,  0,  0,  1,  0,  2,  0,  0,  0 }, //2
            { 0,  0,  0,  0,  5,  1,  0,  0,  0 }, //3
            { 0,  0,  0,  0,  0,  3,  9,  4,  0 }, //4
            { 0,  0,  0,  0,  0,  0,  5,  4,  0 }, //5
            { 0,  0,  0,  0,  0,  0,  0,  0,  0 }, //6
            { 0,  0,  0,  0,  0,  0,  0,  0,  0 }, //7
            { 0,  0,  0,  0,  0,  0,  0,  0,  0 }};//8

    N = cap.size();
    found = vector<bool> (N, 0);
    flow = vector<vector<int>> (N, vector<int>(N) );
    dist = vector<int> (N+1);
    dad = vector<int> (N);
    pi = vector<int> (N);
    int wynik = getMaxFlow(s, t);

    printf("cost: %d\n", wynik);
}
