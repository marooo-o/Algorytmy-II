#include <iostream>
#include <vector>
#include <math.h>

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


void loadDate(vector<vector<Point>> &quartersOfTheKingdom){
   
    int n; //ilość ćwiartek
    vector<int> m; //ilość punktów w każdej ćwiartce
    
    cin>>n;
    m.resize(n);
    //wczytujemy ilość puntków w każdej ćwiartce
    for(int i=0; i<n; i++){
        cin>>m[i];
    }
    
    quartersOfTheKingdom.resize(n);
 
    
    //wczytujemy punkty
    Point loadPoint;
    for(int i=0; i<n; i++){
        for(int j=0; j<m[i]; j++){
            cin>>loadPoint;
            quartersOfTheKingdom[i].push_back(loadPoint);
        }
    }
}

vector<vector<Point>> findBordersOfQuatersOfTheKingdom(vector<vector<Point>> &quartersOfTheKingdom){
    vector<vector<Point>> bordersOfQuatersOfTheKingdom;
    
    bordersOfQuatersOfTheKingdom.resize(quartersOfTheKingdom.size());
    
    for(int i=0; i<quartersOfTheKingdom.size(); i++){
        bordersOfQuatersOfTheKingdom[i] = convexHull(quartersOfTheKingdom[i]);
    }
    
    return bordersOfQuatersOfTheKingdom;
}


//sprawdzanie czy punkt q leży na odciku p r
bool onStraightaway(Point p, Point q, Point r){
    if(q.x >= min(p.x, r.x) && q.x <= max(p.x, r.x) && q.y >= min(p.y, r.y) && q.y<=max(p.y, r.y))
       return true;
       return false;
}

bool checkThatTheSegmentsIntersect(Point p, Point q, Point r, Point s){
    
    int d1 = det(p, q, r);
    int d2 = det(p, q, s);
    int d3 = det(r, s, p);
    int d4 = det(r, s, q);
    
  
  
    
    //punkty p, q, r są współliniowe i r leży na odciku pq
    if(d1 == 0 && onStraightaway(p,r,q)) return true;
    
    //punkty r, s, q są współliniowe i q leży na odniku rs
    if(d4 == 0 && onStraightaway(r, q, s)) return true;
    
    
    
    //przypadek podstawowy, czyli p i q leżą po przeciwnych stronach odcinka rs, a punkty r i s leżą po przeciwnych stronach pq
    if(d1 != d2 && d3 != d4) return true;
    
    
    return false;
}

//punkty muszą być podane przeciwnie do wskazówek zegara
vector<Point>belongingToAConvexPolygon(vector<Point> points, vector<Point> convexPolygon){
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



int main(){
    

    
    vector<Point> points;
    vector<Point> polygon;
    
    polygon.push_back(Point(0,0));
    polygon.push_back(Point(5,0));
    polygon.push_back(Point(5,5));
    polygon.push_back(Point(0,7));
    
    
   
    points.push_back(Point(0,5));
    points.push_back(Point(-3,7));
    points.push_back(Point(2,5));
    points.push_back(Point(2,0));
    points.push_back(Point(2,1));
    points.push_back(Point(0,0));
    points.push_back(Point(0,1));
    points.push_back(Point(1,1));


    vector<Point> pointsInConvexPolygon = belongingToAConvexPolygon(points, polygon);

    for(int i=0; i<pointsInConvexPolygon.size(); i++){
        cout<<pointsInConvexPolygon[i];
    }

   
   
    
    
    

    
    
    return 0;
}
