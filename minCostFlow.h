#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

class minCostFlow {
public:

    bool debuggMode, testMode;
    vector<vector<int>> cap, cost;

    void readInput(string fileName);

    bool searchGraphBellmanFord(int src, int sink);
    int getFlowBellmanFord(int src, int sink);
    int minCostBellmanFord(vector<vector<int>>, vector<vector<int>>);
};
