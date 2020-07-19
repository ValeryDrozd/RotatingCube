#include <bits/stdc++.h>
using namespace std;

struct Vec{
    double x,y,z;
    Vec(){

    }
    Vec(double x,double y,double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec operator-(Vec v) {
        return Vec(this->x - v.x,this->y - v.y,this->z - v.z);
    }

    Vec operator*(double t){
        return Vec(x*t,y*t,z*t);
    }

    Vec operator+(Vec a){
        return Vec(x+a.x,y+a.y,z+a.z);
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
    Vec getPoint(int t) {return o+d*t;}

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
            float num1 = -b+sqrt(d),num2 = -b-sqrt(d);
            return (num1>0 || num2>0);
        }
    }
};

struct Color{
    int r,g,b;
    Color(){

    }
    Color(int r,int g,int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

struct Light{
    Vec point;
    double intensivity;
};

ostream& operator<<(ostream& out,Color c){
    out<<c.r<<endl<<c.g<<endl<<c.b<<endl;
    return out;
}


Vec cam = Vec(-10,0,0);
Sphere sphere = Sphere(Vec(0,0,0),10);
const int width = 501;
const int height = 501;
Color white(255,255,255),black(0,0,0),red(254,10,10);//Justeasytohack1


void render(){
    ofstream out("out.ppm");
    Ray ray = Ray(cam,Vec(0,0,250));
    if(sphere.intersect(ray))cout<<white;
    else
      cout<<black;
    Color image[501][501];
    out << "P3\n" << width << "\n" << height << "\n"<<"255\n";
    int row = 0,col = 0;
    for(int i = height/2;i>-height/2;i-=1){

        row +=1;
        col = 0;

        for(int j = -width/2;j<width/2;j++){

            col+=1;
            double t = 20000;
            Ray ray = Ray(cam,Vec(0,j,i));
            if(sphere.intersect(ray,t)){
                Vec pi = ray.o + ray.d*t;
                image[row][col] = white;
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
    render();
}
