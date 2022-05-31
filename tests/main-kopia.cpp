#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstdlib>


using namespace std;


/// Klasa reprezentująca punkt w kartezjańskim układzie współrzędnych,
/// umożliwia porównanie dwóch punktów poprzez operator > jeden punkt jest większy od drugiego jeżeli jego współrzędna x jest większa, jeśli są równe decyduje
/// o tym współrzędna y, jeżeli jest większa to punkt jest większy.
/// dwa punkty są równe przy użyciu operatora == jeśli zarówno mają identyczne współrzędne x jak i y
/// dwa punkty są różne != kiedy albo ich współrzędne x są różne, albo współrzędne y są róże, albo obie naraz
/// możliwe jest wczytanie punktów przy pomocy >> najpierw wczytywana jest współrzędna x potem y
/// możliwe jest wyświetlanie punktów przy pomocy << najpierw wyświetlana jest współrzędna x potem y a na samym końcu jest znak nowej linii
class Point{

public:
    int x;
    int y;
    
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    
    Point(){
        
    }
   
    Point operator =(const Point &right){
        if(&right != this){
            this->x = right.x;
            this->y = right.y;
        }
        return *this;
    }
    
    bool operator >(const Point & right){
        if((this->x > right.x )||(this->x == right.x && this->y > right.y)){
            return true;
        }
        
        return false;
    }
    
    bool operator <(const Point & right){
        if((this->x < right.x) || (this->x == right.x && this->y < right.y)){
            return true;
        }
        
        return false;
    }
    
    bool operator ==(const Point & right){
        if(this->x == right.x && this->y == right.y){
            return true;
        }
        return false;
    }
    
  
    bool operator != (const Point & right){
        if(this->x != right.x || this->y != right.y){
            return true;
        }
        return false;
    }
    
    
};

istream & operator >> (istream &stream, Point &p){
    stream >> p.x;
    stream >> p.y;
    return stream;
}

ostream & operator << (ostream &out, Point &p){
    out<<p.x;
    out<<" ";
    out<<p.y;
    out<<endl;

    return out;
}


/// Funkcja obliczająca wyznacznik macierzy złożonej z punktów p,q,r uzupełnionej w ostatniej kolumnie 1
/// |xp yp 1|
/// |xq yq 1|
/// |xr yr 1 |
/// znak wyznacznika det(p,q,r) jest równy znakowi sinusa kąta nachylenia wektora p->r do wektora p->q
/// det(p,q,r) > 0 - punkt r lęzy po lewej stronie wektora p->q
/// det(p,q,r) = 0 - punkty p, q, r są współliniowe
/// det(p,q,r) < 0 - punkt r leży po prawej stronie wektora p->q
/// @param p Punkt p - początek wektora
/// @param q  Punkt q - koniec wektora
/// @param r  Punkt r - punkt, którego położenie chcemy znać względem wektora p->q
int det(Point p, Point q, Point r){
    
    int d;
    
    d = p.x * q.y + q.x * r.y + r.x * p.y  - p.x * r.y - q.x * p.y - r.x * q.y;
  
    
    if(d>0) return 1; //r leży po lewej stronie wektora p->q
    else if(d==0) return 0; //p q r są współliniowe
    else return -1; // r leży po prawej stronie wektora p->
}


/// Funkcja określająca, czy punkt x jest mniejszy niż punkt y czyli czy punkt y leży dalej na prawo niż x
/// @param x - punkt x
/// @param y - punkt y
bool smaller(Point x, Point y){
    return x < y;
}


/// Funkcja obliczająca długość wektora A->B
/// @param A - początek wektora
/// @param B  - koniec wektora
double vectorLength(Point A, Point B)
{
    return sqrt(pow(A.x - B.x, 2)+pow(A.y - B.y, 2));
}

/// Funkcja szukająca otoczki wypukłej ze zbioru punktów, zwraca wektor z punktami otoczki przeciwnie do wskazówek zegara
/// @param ar zbiór punktów spośród których szukamy otoczki wypukłej
vector<Point> convexHull(vector<Point> ar){
    sort(ar.begin(), ar.end(), smaller);
    int p, q, d;
    p = 0;
    
    //otoczka wypukła
    vector<Point> convexHull;
    
    do{
        convexHull.push_back(ar[p]);
        
        q = (p + 1)/ar.size();
        
        for(int r=0; r<ar.size(); r++){
            d = det(ar[p], ar[q], ar[r]);
            if(d < 0){
                q = r;
            }else if(d == 0 && vectorLength(ar[p], ar[q]) < vectorLength(ar[p], ar[r])){
                q = r;
            }
        }
        
        p=q;
        
    }while(p!=0);
    
    return convexHull;
}



/// Funkcja która wczytuje dane
/// @param quartersOfTheKingdom wektor w którym będą przetrzymywane zebrane punkty graniczne
/// @param path1 ścieżka do pliku z punktami granicznymi
/// @param fields wektor w którym będą przetrzymywane pola
/// @param path2 ścieżka do pliku z polami
void loadDate(vector<vector<Point> > &quartersOfTheKingdom,
              string path1, vector<Point> &fields,
              string path2){
   
    
    int n; //ilość ćwiartek
    int f; //ilość pól
    vector<int> m; //ilość punktów w każdej ćwiartce
    FILE *file1, *file2;
    fields.clear();

    file1 = fopen(path1.c_str(), "r");
    file2 = fopen(path2.c_str(), "r");
        
    fscanf(file1, "%d", &n); //wczytujemy ilość ćwiartek
    fscanf(file2, "%d", &f); //wczytujemy ilość pól
    
//    fields.resize(f);
    for(int i=0; i<f; i++){
        Point p;
        fscanf(file2, "%d %d", &p.x, &p.y);
        fields.push_back(p);
    }
    

    m.resize(n);
    //wczytujemy ilość puntków w każdej ćwiartce
    for(int i=0; i<n; i++){
        fscanf(file1,"%d", &m[i]);
    }
    
    quartersOfTheKingdom.resize(n);
 
    
    //wczytujemy punkty
    Point loadPoint;
    for(int i=0; i<n; i++){
        for(int j=0; j<m[i]; j++){
          
            Point p;
            fscanf(file1, "%d %d", &p.x, &p.y);
            
            quartersOfTheKingdom[i].push_back(p);
        }
    }
    
    fclose(file1);
    fclose(file2);
}

/// Funkcja znajdująca granice ćwiartek
/// @param quartersOfTheKingdom wektor w którym przetrzymywane są zebrane punkty graniczne ćwiartek
/// @param bordersOfQuatersOfTheKingdom wektor w którym są przetrzymy punkty graniczne ćwiartek wyznaczone przez otoczkę wypukłą
void findBordersOfQuatersOfTheKingdom(vector<vector<Point> > &quartersOfTheKingdom,
                                      vector<vector<Point> > &bordersOfQuatersOfTheKingdom){
    
    
    bordersOfQuatersOfTheKingdom.resize(quartersOfTheKingdom.size());
    
    for(int i=0; i<quartersOfTheKingdom.size(); i++){
        bordersOfQuatersOfTheKingdom[i] = convexHull(quartersOfTheKingdom[i]);
    }
    
   
}


/// Sprawdza które punkty przynależą do wielokąta wypuklego, w tym przypadku wyznaczonego przez otoczkę wypukla, ktorej punkty muszą być podane przeciwnie do
/// wskazówek zegara, zwracane są punkty wewnątrz wielokąta, punkty, ktore leza na bokach wielokata uznawane sa ze nie naleza do niego
/// @param points - punkty które sprawdzamy, czy przynaleza do wielokata wypuklego
/// @param convexPolygon - punkty graniczne wielokata wypuklego
vector<Point>belongingToAConvexPolygon(vector<Point> points,
                                       vector<Point> convexPolygon){
    vector<Point> pointsInConvexPolygon;

    
    int maxX = convexPolygon[0].x;
    //szukam najbardziej na prawo x z otoczki
    for(int i=0; i<convexPolygon.size(); i++){
        if(maxX < convexPolygon[i].x){
            maxX = convexPolygon[i].x;
        }
    }

    maxX += 100;

    int intersection;

    for(int i = 0; i < points.size(); i++){

        Point s = Point(maxX, points[i].y);
        intersection = 0;

        int next = 0;
        int h = 0;
        
        do{
            next = (h+1)%convexPolygon.size();
            
                if(max(convexPolygon[h].y, convexPolygon[next].y) >= points[i].y
                   && min(convexPolygon[h].y, convexPolygon[next].y) < points[i].y
                   && det(convexPolygon[h], convexPolygon[next], points[i]) != det(convexPolygon[h], convexPolygon[next], s)
                   && det(points[i], s, convexPolygon[h]) != det(points[i], s, convexPolygon[next])){
                intersection++;
            }
            
            
            h = next;
            
        }while(h != 0);

        if(intersection&1){
            pointsInConvexPolygon.push_back(points[i]);
        }
        
    }
    
    return pointsInConvexPolygon;
}

/// Określa które pola, naleza do ktorej cwiartki
/// @param bordersOfQuatersOfTheKingdom wektor przetrzymujacy granice cwiartek
/// @param fields pola
/// @param divisionOfTheKingdom cwiartki z polami przydzielonymi do nich
void assignFieldsToQuarter(vector<vector<Point> > bordersOfQuatersOfTheKingdom,
                           vector<Point> fields,
                           vector<vector<Point> > &divisionOfTheKingdom){
        
    for(int i=0; i<bordersOfQuatersOfTheKingdom.size(); i++){
        divisionOfTheKingdom.push_back(belongingToAConvexPolygon(fields, bordersOfQuatersOfTheKingdom[i]));
    }
    
}

/// Zapisuje dane wyjsciowe w pliku
/// @param divisionOfTheKingdom cwiartki z polami przydzielonymi do nich
void saveInFile(vector<vector<Point> > divisionOfTheKingdom){
    ofstream file;
    file.open("input-test.txt");
    for(int i = 0; i< divisionOfTheKingdom.size(); i++){
        file<<"c"<<i+1<<endl;
        for(int j=0; j< divisionOfTheKingdom[i].size(); j++){
            file<<divisionOfTheKingdom[i][j];
        }
    }
    
    file.close();
    
}

/// Wyswietla granice cwiartek oraz pola do nich przynalezace
/// @param bordersOfQuatersOfTheKingdom granice cwiartek
/// @param divisionOfTheKingdom pola przynalezace do cwiartek
void displayTheBordersAndFieldsInsideOnConsole(vector<vector<Point> > bordersOfQuatersOfTheKingdom,
                                               vector<vector<Point> > divisionOfTheKingdom){
    for(int i = 0; i< bordersOfQuatersOfTheKingdom.size(); i++){
        cout<<"granice cwiartki nr: "<<i+1<<endl;
        for(int j=0; j< bordersOfQuatersOfTheKingdom[i].size(); j++){
            cout<<bordersOfQuatersOfTheKingdom[i][j];
        }
        cout<<"pola wewnatrz cwiartki nr: "<<i+1<<endl;
        for(int j=0; j< divisionOfTheKingdom[i].size(); j++){
            cout<<divisionOfTheKingdom[i][j];
        }
        cout<<endl;
    }
}


int main(int argc, char* argv[]){
    
    vector<vector<Point> > quartersOfTheKingdom;
    vector<vector<Point> > bordersOfQuatersOfTheKingdom;
    vector<Point> fields;
    vector<vector<Point> > divisionOfTheKingdom;
    string path;
    string path2;
    
    int p = argv[1][0] - '0';
    switch (p) {
        case 1:
            path = "./inputs/input.txt";
            path2 = "./fields/fields.txt";
            break;
        case 3:
            path = "./inputs/input3.txt";
            path2 = "./fields/fields3.txt";
            break;
        case 4:
            path = "./inputs/input4.txt";
            path2 = "./fields/fields4.txt";
            break;
            
        default:
            cout<<"Bad argument!"<<endl;
            return 0;
            break;
    }
    


    loadDate(quartersOfTheKingdom, path, fields,path2);
    findBordersOfQuatersOfTheKingdom(quartersOfTheKingdom, bordersOfQuatersOfTheKingdom);
    assignFieldsToQuarter(bordersOfQuatersOfTheKingdom, fields, divisionOfTheKingdom);
    
    displayTheBordersAndFieldsInsideOnConsole(bordersOfQuatersOfTheKingdom, divisionOfTheKingdom);
    saveInFile(divisionOfTheKingdom);
    
    
   
  

    return 0;
}
