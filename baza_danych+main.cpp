#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

struct pos {
    int x, y;
};

struct field {
    int id;
    pos p;
};

struct intersection {
    int id;
    pos p;
};

struct brewery {
    int id;
    pos p;
    int limit;
};

struct tavern {
    int id;
    pos p;
    int sell_limit;
};

struct road {
    int u, v;
    int barley_capacity, beer_capacity;
};

struct graph {
    int s, t; // zrodlo i ujscie
    vector<vector<int>> adj; // sasiedzi kazdego wierzcholka
    vector<vector<int>> cap; // pojemnosc przeplywu
    vector<int> parent; // tablica rodzicow po znalezieniu sciezki powiekszajacej przeplyw
    
    graph(size_t n, int s, int t) : s(s), t(t), adj(n), cap(n, vector<int>(n)), parent(n) { }
    
    int bfs() {
        // resetujemy tablice rodzicow
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        
        queue<pair<int, int>> q;
        // rozpoczynamy bfs z zrodla z brakiem ograniczenia na przeplyw
        q.push({s, numeric_limits<int>::max()});
            
        while (!q.empty()) {
            int current = q.front().first;
            int flow = q.front().second;
            q.pop();

            // przechodzimy po kazdym sasiedzie
            for (size_t i = 0; i < adj[current].size(); ++i) {
                int next = adj[current][i];
                // interesuja nas tylko sasiedzi ktorzy jeszcze nie sa na zadnej sciezce i do ktorych mozemy poprowadzic dodatni przeplyw
                if (parent[next] == -1 && cap[current][next]) {
                    // oznaczamy ze rodzicem next w sciezce bedzie current
                    parent[next] = current;
                    // nowy przeplyw jest ograniczony przez pojemnosc przeplywu z current do next
                    int new_flow = min(flow, cap[current][next]);
                    if (next == t) {
                        // doszlismy do ujscia
                        return new_flow;
                    }
                    
                    q.push({next, new_flow});
                }
            }
        }
        
        return 0;
    }

// struktura zawierajaca wszystkie informacje o swiecie
struct world {
    // ilosc zboza produkowana przez pola
    int fields_produce;
    vector<field> fields;
    vector<intersection> intersections;
    vector<brewery> breweries;
    vector<road> roads;
    vector<tavern> taverns;
    
    world(int n_roads, int fields_produce) : fields_produce(fields_produce), roads(n_roads) { }
    
    // funkcja do przetransformowania swiata w graf
    graph to_graph() {
        int n = fields.size() + intersections.size() + breweries.size();
        graph g(2*n+2, 0, 2*n+1);
        
        // kazda droga jest umieszczona jako krawedz w grafie w obu warstwach
        for (size_t i = 0; i < roads.size(); ++i) {
            road r = roads[i];
            /*g.add_edge();*/
            /*g.add_edge();*/
        }
        
        // oznaczamy, ze pole produkuje dana ilosc zboza poprzez 
        // dodanie krawedzi z zrodla przeplywu do wierzcholka pola
        for (size_t i = 0; i < fields.size(); ++i) {
            field f = fields[i];
            /*g.add_edge(0, f.id, fields_produce);*/
        }
        
        // dla kazdego browaru dodajemy skierowana krawedz do kolejnej warstwy grafu
        // z przepustowoscia rowna limitowi produkcji piwa w browarze
        for (size_t i = 0; i < breweries.size(); ++i) {
            brewery b = breweries[i];
            /*g.add_directed_edge(b.id, n + b.id, b.limit);*/
        }
        
        // dla kazdej karczmy dodajemy krawedz z wierzcholka w drugiej warstwie 
        // do ujscia z przepustowoscia rowna limitowi sprzedazy
        for (size_t i = 0; i < taverns.size(); ++i) {
            tavern t = taverns[i];
            /*g.add_edge(n + t.id, 2*n+1, t.sell_limit);*/
        }
        
        return g;
    }
};

int main() {
    int n_objects, n_roads, fields_produce;
    cin >> n_objects >> n_roads >> fields_produce;
    world w(n_roads, fields_produce);
    
    // input
    for (int i = 1; i <= n_objects; ++i) {
        char c;
        cin >> c;
        if (c == 'f') {
            // nowy browar
            // f [x pola] [y pola]
            field f;
            f.id = i;
            cin >> f.p.x >> f.p.y;
            w.fields.push_back(f);
        } else if (c == 'b') {
            // nowy browar
            // b [x browaru] [y browaru] [limit produkcji]
            brewery b;
            b.id = i;
            cin >> b.p.x >> b.p.y >> b.limit;
            w.breweries.push_back(b);
        } else if (c == 'i') {
            // nowe skrzyzowanie
            // i [x skrzyzowania] [y skrzyzowania]
            intersection inter;
            inter.id = i;
            cin >> inter.p.x >> inter.p.y;
            w.intersections.push_back(inter);
        } else if (c == 't') {
            // nowa karczma
            // t [x karczmy] [y karczmy] [limit sprzedazy]
            tavern t;
            t.id = i;
            cin >> t.p.x >> t.p.y >> t.sell_limit;
            w.taverns.push_back(t);
        }
    }
    
    // wczytanie drog
    for (int i = 0; i < n_roads; ++i) {
        road r;
        // [id obiektu 1] [id obiektu 2] [limit przewozu jeczmiena] [limit przewozu piwa]
        cin >> r.u >> r.v >> r.barley_capacity >> r.beer_capacity;
        w.roads.push_back(r);
    }
    
    graph g = w.to_graph();
    /*cout << g.maxflow() << endl;*/ /*jak dodasz funkcje, to tutaj powinno zostac wywolanie*/
    return 0;
}