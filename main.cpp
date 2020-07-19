#include <bits/stdc++.h>
using namespace std;

struct Vec{
    double x,y,z;
    Vec(){}

    Vec(double x,double y,double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double distanceToPoint(Vec a){
        return sqrt(pow(this->x - a.x,2)+pow(this->y - a.y,2) + pow(this->z - a.z,2));
    }
    Vec operator+(Vec a){
        return Vec(x+a.x,y+a.y,z+a.z);
    }

    Vec operator-(Vec v) {
        return Vec(this->x - v.x,this->y - v.y,this->z - v.z);
    }

    Vec operator*(double t){
        return Vec(x*t,y*t,z*t);
    }

    Vec operator/(double t){
        return Vec(x/t,y/t,z/t);
    }

    bool operator==(Vec a){
        return this->x==a.x && this->y == a.y && this->z == a.z;
    }

    double getLen(){
        return sqrt(x*x+y*y+z*z);
    }

    Vec normalise(){
        double len = this->getLen();
        return Vec(x/len,y/len,z/len);
    }
};

double dot(Vec a,Vec b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

struct Ray{
    Vec o;
    Vec d;
    Ray(){}

    Ray(Vec o, Vec d) {
        this->o = o;
        this->d = (d - o);
    }

    Vec origin() {return o; }
    Vec direction() {return d; }
    Vec getPoint(double t) {return o+d*t; }

};

struct Sphere{
    Vec c;
    double r;
    Sphere(Vec c,double r){
        this->c = c;
        this->r = r;
    }
    bool intersect(Ray r, double &t){
        Vec oc = r.origin() - c;
        double a = dot(r.d,r.d);
        float b = 2.0*dot(oc,r.d);
        float c = dot(oc,oc) - this->r*this->r;
        float d = b*b - 4*a*c;
        if(d<0)return false;
        else
        {
    //        double dist = INT_MAX;
            float num1 = -b+sqrt(d),num2 = -b-sqrt(d);
            //if(num1>0)dist = min(r.origin().getLen(r.getPoint(num1)))
            return (num1>0 || num2>0);
        }
    }

};

struct Color{
    int r,g,b;
    Color(){}

    Color(int r,int g,int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

struct Light{
    Vec point;
    Color c;
    double intensivity;
    Light(){}
    Light(Vec Point,Color c,double intensivity){
        this->point = point;
        this->c = c;
        this->intensivity = intensivity;
    }
    Vec origin(){return point;}
};

ostream& operator<<(ostream& out,Color c){
    out<<c.r<<endl<<c.g<<endl<<c.b<<endl;
    return out;
}


Vec cam = Vec(10,0,0);
Sphere sphere = Sphere(Vec(13,0,0),10);
const int width = 501;
const int height = 501;
Color white(255,255,255),black(0,0,0),red(254,10,10),gray(240,100,100);//Justeasytohack1
Light l = Light(Vec(25,0,0),white,100);

void render(){
    ofstream out("out.ppm");
    Color image[501][501];
    out << "P3\n" << width << "\n" << height << "\n"<<"255\n";
    int row = 0,col = 0;
    for(int i = height/2;i>-height/2;i-=1){

        row += 1;
        col = 0;

        for(int j = -width/2;j<width/2;j++){

            col+=1;
            double t = 20000;
            Ray ray = Ray(cam,Vec(0,j,i));
            if(sphere.intersect(ray,t)){
                double t1 = 20000;
                Vec pointIntersect = ray.getPoint(t);
                Ray lightRay = Ray(l.origin(),pointIntersect);
                if(sphere.intersect(lightRay,t1) && lightRay.getPoint(t1) == ray.getPoint(t)){
                    image[row][col] = white;
                } else
                    image[row][col] = gray;
            }
            else
                image[row][col] = black;

        }
    }
    for(int i = 0;i<height;i++){
        image[250][i] = red;
        image[i][250] = red;
    }

    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
            out<<image[i][j];
        }
    }
}

int main(){
    double t;
   // cout<<sphere.intersect(Ray(cam,Vec(1,0,0)),t);
    render();
}
