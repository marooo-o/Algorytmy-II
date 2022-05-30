#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class minCostFlow {
public:

    bool debuggMode, testMode;
    vector<vector<int>> cap, costDijkstra, costBellmanFord;

    void readInput(string fileName);

    int searchGraphDijkstra(vector<int> dist, vector<bool> found);
    void getFlowDijkstra(vector<vector<int>> cost, int src, vector<vector<int>>);
    int minCostDijkstra(vector<vector<int>>, vector<vector<int>>);

    bool searchGraphBellmanFord(int src, int sink);
    int getFlowBellmanFord(int src, int sink);
    int minCostBellmanFord(vector<vector<int>>, vector<vector<int>>);
};
