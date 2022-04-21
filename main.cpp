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


int main(){
    
    Point point = Point(1,2);
    
    vector<Point> ar;
    ar.push_back(Point(0,0));
    ar.push_back(Point(0,4));
    ar.push_back(Point(-4,0));
    ar.push_back(Point(5,0));
    ar.push_back(Point(0,-6));
    ar.push_back(Point(1,0));
    
    
    
    
    vector<Point> hull = convexHull(ar);
    
    for(int i = 0; i < hull.size(); i++){
        cout<<hull[i];
    }
    
    
    
    

   
    
    
  

    
    
    return 0;
}
