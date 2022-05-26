/*
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <random>
#include <cassert>
#include <ctime>
#include <fstream>
#include <chrono>
#include <thread>
*/
#include <bits/stdc++.h>
#include <unistd.h>

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
/**
 *
 */
struct graph {
        int n, s, t; // zrodlo i ujscie
        vector < vector < int >> adj; // sasiedzi kazdego wierzcholka
        vector < vector < int >> cap; // pojemnosc przeplywu
        vector < int > parent; // tablica rodzicow po znalezieniu sciezki powiekszajacej przeplyw
        vector < vector < int >> flow; // wartosc przeplywu
        queue < int > excess_vertices; // nadmiar wierzcholkow
        vector < int > height, excess, seen;
        graph(size_t n, int s, int t): n(n), s(s), t(t), adj(n), cap(n, vector < int > (n)), parent(n),
                height(n), excess(n), flow(n, vector < int > (n)) {}


                int bfs() {
                // resetujemy tablice rodzicow
                fill(parent.begin(), parent.end(), -1);
                parent[s] = -2;

                queue < pair < int, int >> q;
                // rozpoczynamy bfs z zrodla z brakiem ograniczenia na przeplyw
                q.push({
                        s,
                        1000000000
                });

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

                                        q.push({
                                                next,
                                                new_flow
                                        });
                                }
                        }
                }

                return 0;
        }

        // ford-fulkerson
        /**
         * <p>funkcja stosujaca algorytm forda fulkersona do znalezienia maksymalnego przeplywu</p>
         * @return maksymalny przeplyw
         */
        int ford_fulkerson() {
                int flow = 0, new_flow;
                // szukana jest sciezka powiekszajaca
                while (new_flow = bfs()) { // konczymy jezeli nie istnieje dodatnia sciezka powiekszajaca
                        flow += new_flow; // dodajemy do przeplywu ilosc o ktora zostal powiekszony
                        int current = t;
                        while (current != s) { // od ujscia do zrodla przechodzimy po znalezionej sciezce
                                int prev = parent[current];

                                // odejmujemy od pojemnosci znaleziony przeplyw i dodajemy go w odwrotna strone
                                // zgodnie z algorytmem
                                cap[prev][current] -= new_flow;
                                cap[current][prev] += new_flow;
                                current = prev;
                        }
                }

                return flow;
        }

        void push(int u, int v) {
                int d = min(excess[u], cap[u][v] - flow[u][v]);
                flow[u][v] += d;
                flow[v][u] -= d;
                excess[u] -= d;
                excess[v] += d;
                if (d && excess[v] == d)
                        excess_vertices.push(v);
        }

        void relabel(int u) {
                int d = numeric_limits < int > ::max();
                for (int i = 0; i < n; i++) {
                        if (cap[u][i] - flow[u][i] > 0)
                                d = min(d, height[i]);
                }
                if (d < numeric_limits < int > ::max())
                        height[u] = d + 1;
        }

        void discharge(int u) {
                while (excess[u] > 0) {
                        if (seen[u] < n) {
                                int v = seen[u];
                                if (cap[u][v] - flow[u][v] > 0 && height[u] > height[v])
                                        push(u, v);
                                else
                                        seen[u]++;
                        } else {
                                relabel(u);
                                seen[u] = 0;
                        }
                }
        }

        int push_relabel() {
                height[s] = n;
                excess[s] = 1000000000; // bardzo duza wartosc przekraczajaca wszystkie inne

                for (int i = 0; i < n; i++) {
                        if (i != s)
                                push(s, i);
                }
                seen.assign(n, 0);

                while (!excess_vertices.empty()) {
                        int u = excess_vertices.front();
                        excess_vertices.pop();
                        if (u != s && u != t)
                                discharge(u);
                }

                int max_flow = 0;
                for (int i = 0; i < n; i++)
                        max_flow += flow[i][t];
                return max_flow;
        }

        void add_edge(int u, int v, int capacity) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                cap[u][v] = cap[v][u] = capacity;
        }

        void add_directed_edge(int u, int v, int capacity) {
                adj[u].push_back(v);
                adj[v].push_back(u);
                cap[u][v] = capacity;
        }
};

// struktura zawierajaca wszystkie informacje o swiecie
struct world {
        // ilosc zboza produkowana przez pola
        int fields_produce;
        vector < field > fields;
        vector < intersection > intersections;
        vector < brewery > breweries;
        vector < road > roads;
        vector < tavern > taverns;

        world(int n_roads, int fields_produce): fields_produce(fields_produce), roads(n_roads) {}
        
        // funkcja do przetransformowania swiata w graf
        graph to_graph() {
                int n = fields.size() + intersections.size() + breweries.size() + taverns.size();
                graph g(2 * n + 2, 0, 2 * n + 1);

                // kazda droga jest umieszczona jako krawedz w grafie w obu warstwach
                for (size_t i = 0; i < roads.size(); ++i) {
                        road r = roads[i];
                        g.add_edge(r.u, r.v, r.barley_capacity);
                        g.add_edge(n + r.u, n + r.v, r.beer_capacity);
                }

                // oznaczamy, ze pole produkuje dana ilosc zboza poprzez
                // dodanie krawedzi z zrodla przeplywu do wierzcholka pola
                for (size_t i = 0; i < fields.size(); ++i) {
                        field f = fields[i];
                        g.add_directed_edge(0, f.id, fields_produce);
                }

                // dla kazdego browaru dodajemy skierowana krawedz do kolejnej warstwy grafu
                // z przepustowoscia rowna limitowi produkcji piwa w browarze
                for (size_t i = 0; i < breweries.size(); ++i) {
                        brewery b = breweries[i];
                        g.add_directed_edge(b.id, n + b.id, b.limit);
                }

                // dla kazdej karczmy dodajemy krawedz z wierzcholka w drugiej warstwie
                // do ujscia z przepustowoscia rowna limitowi sprzedazy
                for (size_t i = 0; i < taverns.size(); ++i) {
                        tavern t = taverns[i];
                        g.add_directed_edge(n + t.id, 2 * n + 1, t.sell_limit);
                }

                return g;
        }

        void print() {
                cout << "fields_produce: " << fields_produce << endl;
                cout << "fields:\n";
                for (auto f: fields) {
                        cout << f.id << " ";
                }
                cout << endl;
                cout << "intersections:\n";
                for (auto i: intersections) {
                        cout << i.id << " ";
                }
                cout << endl;
                cout << "taverns:\n";
                for (auto t: taverns) {
                        cout << t.id << ", " << t.sell_limit << "  ";
                }
                cout << endl;
                cout << "breweries:\n";
                for (auto b: breweries) {
                        cout << b.id << ", " << b.limit << "  ";
                }
                cout << endl;

                for (auto r: roads) {
                        cout << r.u << " " << r.v << " " << r.beer_capacity << " " << r.barley_capacity << endl;
                }
        }
/**
 * <p>szuka maksymalnego przeplywu metoda brute force</p>
 * @param flow_size
 * @return maksymalny przeplyw
 */
        int brute_force(int flow_size) {
                vector < int > road_flows(2 * roads.size(), -flow_size);;

                int n = fields.size() + intersections.size() + breweries.size();
                vector < int > barley_through(n + 1), beer_through(n + 1);

                int best = 0;

                // dekrementujemy 0-wy element o 1,
                // bo na poczatku pierwszej iteracji go zwiekszymy
                --road_flows[0];

                // iterujemy sie po wszystkich mozliwych przeplywach przez kazda droge
                // przeplyw x w road_flow 2*i oznacza ze z u do v i-tej drogi plynie x zboza
                // natomiast w 2*i+1 ze z u do v plynie x piwa
                // co oznaczamy w tablicach barley_through i beer_through
                while (road_flows.back() <= flow_size) {

                        int i = 0;
                        // inkrementuje koejne elementy,
                        // jesli doszlismy do wartosci granicznej (flow_size+1) to resetujemy element
                        // (ustawiamy go na -flow_size) i inkrementujemy kolejny
                        while (i < road_flows.size() && ++road_flows[i] == flow_size + 1) {
                                road_flows[i++] = -flow_size;
                        }
                        if (road_flows.back() == flow_size) break;

                        // ile przeplywa surowcow przez kazdy wierzcholek
                        for (int i = 0; i < roads.size(); ++i) {
                                barley_through[roads[i].u] -= road_flows[2 * i];
                                barley_through[roads[i].v] += road_flows[2 * i];

                                beer_through[roads[i].u] -= road_flows[2 * i + 1];
                                beer_through[roads[i].v] += road_flows[2 * i + 1];
                        }

                        int res = 0;

                        bool correct = 1;
                        // weryfikacja wierzcholkow
                        for (auto & i: intersections)
                                if (!(barley_through[i.id] == 0 && beer_through[i.id] == 0)) {
                                        correct = 0;
                                        break;
                                }
                        if (!correct) continue;

                        for (auto & f: fields)
                                if (!(barley_through[f.id] >= -fields_produce && barley_through[f.id] <= 0 &&
                                                beer_through[f.id] == 0)) {
                                        correct = 0;
                                        break;
                                }
                        if (!correct) continue;

                        for (auto & b: breweries)
                                if (!(barley_through[b.id] >= 0 && beer_through[b.id] == -barley_through[b.id])) {
                                        correct = 0;
                                        break;
                                }
                        if (!correct) continue;

                        for (auto & t: taverns) {
                                if (barley_through[t.id] == 0 && beer_through[t.id] >= 0) {
                                        res += beer_through[t.id];
                                } else {
                                        correct = 0;
                                        break;
                                }
                        }
                        if (!correct) continue;

                        // jezeli nigdzie nie znalezlismy bledu,
                        // to poprawiamy best na res jezeli jest wieksze
                        cout << res << endl;
                        best = max(best, res);
                }

                return best;
        }
};

mt19937 gen(time(NULL)); //generator liczb losowych

// zwraca przypadkowa wartosc pomiedzy a, b
int rand_between(int a, int b) {
        return gen() % (b - a + 1) + a;
}
world random_world() {
        int n_roads = 100, n_objects = 100, flow_size = 100; //deklaracja zmiennych
        world w(n_roads, rand_between(1, flow_size));

        // used up roads
        vector < vector < bool >> used(n_objects + 1, vector < bool > (n_objects + 1));
        for (int i = 0; i < n_roads; ++i) {
                road r;
                do {
                        r.u = rand_between(1, n_objects), r.v = rand_between(1, n_objects);
                } while (r.u == r.v || used[r.u][r.v]);

                r.beer_capacity = rand_between(1, flow_size);
                r.barley_capacity = rand_between(1, flow_size);
                w.roads[i] = r;
                used[r.u][r.v] = used[r.v][r.u] = 1;
        }

        for (int i = 1; i <= n_objects; ++i) {
                int idx = rand_between(1, 4);
                if (idx == 1) {
                        field f;
                        f.id = i;
                        w.fields.push_back(f);
                } else if (idx == 2) {
                        brewery b;
                        b.id = i;
                        b.limit = rand_between(1, flow_size);
                        w.breweries.push_back(b);
                } else if (idx == 3) {
                        tavern t;
                        t.id = i;
                        t.sell_limit = rand_between(1, flow_size);
                        w.taverns.push_back(t);
                } else if (idx == 4) {
                        intersection inter;
                        inter.id = i;
                        w.intersections.push_back(inter);
                }
        }

        return w;
}

void test() {
        int loop=0;
        while (true) {
                loop++;
                world w = random_world(); //wygenerowanie swiata w sposob losowy
                graph g1 = w.to_graph(), g2 = w.to_graph();
                int res_ford = g1.ford_fulkerson(), res_pr = g2.push_relabel();
                if (res_ford != res_pr) {
                        cout << "test #" << loop << ": NIEPRAWIDLOWY, " << res_ford << " " << res_pr << endl;
                        w.print();
                        exit(0);
                } else {
                        cout << "test #" << loop << ": POPRAWNY, " << res_ford << " = " << res_pr << endl;
                        //w.print();
                        //exit(0);
                }
                //zakomentować if'a, jeśli chcemy nieskonczenie wiele testow
                if(loop==100){
                        exit(0);
                }
        }
}

int main() {
        system("cls");
        system("color a"); //zmiana koloru cmd
        #ifdef TEST
        test(); //przeprowadzanie testow (powinno byc CORRECT)
        #endif
        int n_objects=-1, n_roads=-1, fields_produce=-1;
        //cin >> n_objects >> n_roads >> fields_produce;
        cout << "Program liczacy maksymalny przeplyw piwa" << endl;
        cout << "ktory mozna dostarczyc za pomoca drog z browarow do karczm" << endl;
        cout << "biorac pod uwage wystepujace skrzyzowania" << endl;
        usleep(800000);usleep(800000);usleep(800000);usleep(800000);usleep(800000);
        system("cls");
        ifstream IN("in.txt");
        IN >> n_objects >> n_roads >> fields_produce;
        if((n_objects==-1) || (n_roads==-1) || (fields_produce==-1)){
                cout<<"NIE UDALO SIE WCZYTAC PLIKU"<<endl;
                cout<<"BADZ ZNAJDUJA SIE W NIM NIEPRAWIDLOWE DANE"<<endl;
        }else{
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [                    ]  0%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|                   ]  5%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||                  ]  10%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||                 ]  15%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||                ]  20%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||               ]  25%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||              ]  30%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||             ]  35%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||            ]  40%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||||           ]  45%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||          ]  50%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||||||         ]  55%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||        ]  60%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||||||||       ]  65%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||||      ]  70%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||||||||||     ]  75%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||||||    ]  80%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [|||||||||||||||||   ]  85%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||||||||  ]  90%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||||||||| ]  95%" << endl; usleep(20000); system("cls");
        cout << "Wczytuje dane z pliku..." << endl; cout << "  [||||||||||||||||||||]  100%" << endl; usleep(40000); system("cls");
        cout << "Udalo sie wczytac wszystkie wartosci" << endl; //wyswietlanie "ladowania" :)
        cout << "oczekiwany wynik to: 11";
        //cout << n_objects << " " << n_roads << " " << fields_produce << endl;
        world w(n_roads, fields_produce); 
        // input
        for (int i = 1; i <= n_objects; ++i) {
                char c;
                field f;
                brewery b;
                intersection inter;
                tavern t;
                //cin >> c;
                IN >> c;
                //cout << c << " " << endl;
                if (c == 'f') {
                        // nowy browar
                        // f [x pola] [y pola]
                        f.id = i;
                        //cin >> f.p.x >> f.p.y;
                        IN >> f.p.x >> f.p.y;
                        //cout << f.p.x << " " << f.p.y << endl;
                        w.fields.push_back(f);
                } else if (c == 'b') {
                        // nowy browar
                        // b [x browaru] [y browaru] [limit produkcji]
                        b.id = i;
                        //cin >> b.p.x >> b.p.y >> b.limit;
                        IN >> b.p.x >> b.p.y >> b.limit;
                        //cout << b.p.x << " " << b.p.y << " " << b.limit << endl;
                        w.breweries.push_back(b);
                } else if (c == 'i') {
                        // nowe skrzyzowanie
                        // i [x skrzyzowania] [y skrzyzowania]
                        inter.id = i;
                        //cin >> inter.p.x >> inter.p.y;
                        IN >> inter.p.x >> inter.p.y;
                        //cout << inter.p.x << " " << inter.p.y << endl;
                        w.intersections.push_back(inter);
                } else if (c == 't') {
                        // nowa karczma
                        // t [x karczmy] [y karczmy] [limit sprzedazy]
                        t.id = i;
                        //cin >> t.p.x >> t.p.y >> t.sell_limit;
                        IN >> t.p.x >> t.p.y >> t.sell_limit;
                        //cout << t.p.x << " " << t.p.y << " " << t.sell_limit << endl;
                        w.taverns.push_back(t);
                }
        }

        // wczytanie drog
        road r;
        for (int i = 0; i < n_roads; ++i) {
                // [id obiektu 1] [id obiektu 2] [limit przewozu jeczmiena] [limit przewozu piwa]
                //cin >> r.u >> r.v >> r.barley_capacity >> r.beer_capacity;
                IN >> r.u >> r.v >> r.barley_capacity >> r.beer_capacity;
                //cout << r.u << " " << r.v << " " << r.barley_capacity << " " << r.beer_capacity << endl;
                w.roads.push_back(r);
        }

        graph g = w.to_graph();
        int flow = g.push_relabel();
        int flow2 = g.ford_fulkerson();
        if(flow==flow2){
        cout << endl << endl << "maksymalnych przeplyw z" << "danych znajdujacych sie w wejscu to: " << flow << endl;
        }
        }
        IN.close();
        return 0;
}