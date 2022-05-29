#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <cstdlib>


using namespace std;


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


int det(Point p, Point q, Point r){
    
    int d;
    
    d = p.x * q.y + q.x * r.y + r.x * p.y  - p.x * r.y - q.x * p.y - r.x * q.y;
  
    
    if(d>0) return 1; //r leży po lewej stronie wektora p->q
    else if(d==0) return 0; //p q r są współliniowe
    else return -1; // r leży po prawej stronie wektora p->
}


bool smaller(Point x, Point y){
    return x < y;
}


double vectorLength(Point A, Point B)
{
    return sqrt(pow(A.x - B.x, 2)+pow(A.y - B.y, 2));
}

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


void loadDate(vector<vector<Point> > &quartersOfTheKingdom,
              char path1[], vector<Point> &fields,
              char path2[]){
   
    
    int n; //ilość ćwiartek
    int f; //ilość pól
    vector<int> m; //ilość punktów w każdej ćwiartce
    FILE *file1, *file2;
    fields.clear();

    file1 = fopen(path1, "r");
    file2 = fopen(path2, "r");
        
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

void findBordersOfQuatersOfTheKingdom(vector<vector<Point> > &quartersOfTheKingdom,
                                      vector<vector<Point> > &bordersOfQuatersOfTheKingdom){
    
    
    bordersOfQuatersOfTheKingdom.resize(quartersOfTheKingdom.size());
    
    for(int i=0; i<quartersOfTheKingdom.size(); i++){
        bordersOfQuatersOfTheKingdom[i] = convexHull(quartersOfTheKingdom[i]);
    }
    
   
}


//punkty muszą być podane przeciwnie do wskazówek zegara
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

void assignFieldsToQuarter(vector<vector<Point> > bordersOfQuatersOfTheKingdom,
                           vector<Point> fields,
                           vector<vector<Point> > &divisionOfTheKingdom){
        
    for(int i=0; i<bordersOfQuatersOfTheKingdom.size(); i++){
        divisionOfTheKingdom.push_back(belongingToAConvexPolygon(fields, bordersOfQuatersOfTheKingdom[i]));
    }
    
}

void saveInFile(vector<vector<Point> > divisionOfTheKingdom){
    ofstream file;
    file.open("input2.txt");
    for(int i = 0; i< divisionOfTheKingdom.size(); i++){
        file<<"c"<<i+1<<endl;
        for(int j=0; j< divisionOfTheKingdom[i].size(); j++){
            file<<divisionOfTheKingdom[i][j];
        }
    }
    
    file.close();
    
}

void displayTheBordersAndFieldsInsideOnConsole(vector<vector<Point> > bordersOfQuatersOfTheKingdom,
                                               vector<vector<Point> > divisionOfTheKingdom){
    for(int i = 0; i< bordersOfQuatersOfTheKingdom.size(); i++){
        cout<<"granice cwiartki nr: "<<i+1<<endl;
        for(int j=0; j< bordersOfQuatersOfTheKingdom[i].size(); j++){
            cout<<bordersOfQuatersOfTheKingdom[i][j];
        }
        cout<<"pola nalezace do cwiartki"<<endl;
        for(int j=0; j< divisionOfTheKingdom[i].size(); j++){
            cout<<divisionOfTheKingdom[i][j];
        }
    }
}


int main(int argc, char* argv[]){
    
    vector<vector<Point> > quartersOfTheKingdom;
    vector<vector<Point> > bordersOfQuatersOfTheKingdom;
    vector<Point> fields;
    vector<vector<Point> > divisionOfTheKingdom;
        
    char path[] = "input.txt";
    char path2[] = "fields.txt";

    loadDate(quartersOfTheKingdom, path, fields,path2);
    findBordersOfQuatersOfTheKingdom(quartersOfTheKingdom, bordersOfQuatersOfTheKingdom);
    assignFieldsToQuarter(bordersOfQuatersOfTheKingdom, fields, divisionOfTheKingdom);
    
    int p = argv[1][0] - '0';
    switch (p) {
        case 1:
            saveInFile(divisionOfTheKingdom);
            break;
        case 2:
            displayTheBordersAndFieldsInsideOnConsole(bordersOfQuatersOfTheKingdom,
                                                      divisionOfTheKingdom);
            break;
            
        default:
            cout<<"Bad argument!"<<endl;
            break;
    }
    
   
  

    return 0;
}
