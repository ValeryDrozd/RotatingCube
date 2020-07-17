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
        return Vec(this->x - v.x,this->y - v.y,this->z - z);
    }

};

double dot(Vec a,Vec b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

struct Ray{
    Vec o;
    Vec d;
    Ray(Vec o, Vec d) {
        this->o = o;
        this->d = d;
    }
};

struct Sphere{
    Vec c;
    double r;
    Sphere(Vec c,double r){
        this->c = c;
        this->r = r;
    }
    bool intersect(Ray r){
        Vec o = r.o;
        Vec d = r.d;
        Vec oc = o - c;
        double b = 2*dot(oc,d);
        double c = dot(oc,oc) - this->r*this->r;
        double disc = b*b-4*c;
        if(disc<0)return false;
        else
            return true;
    }
};

struct Color{
    int r,g,b;
    Color(int r,int g,int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

ostream& operator<<(ostream& out,Color c){
    out<<c.r<<endl<<c.g<<endl<<c.b<<endl;
    return out;
}


Vec cam = Vec(0,0,0);
Sphere sphere = Sphere(Vec(0,0,0),20);
const int width = 500;
const int height = 500;
Color white(255,255,255),black(0,0,0);


void render(){
    ofstream out("out.ppm");
    out << "P3\n" << width << "\n" << height << "\n"<<"255\n";
    for(int i = height/2;i>-height/2;i-=1){
        for(int j = -width/2;j<width/2;j++){
            Ray ray(Vec(j,i,0),Vec(0,0,1));
            //Ray ray(Vec(0,i,j),cam);
            if(sphere.intersect(ray))out<<white;
            else
                out<<black;
        }
    }
}

int main(){
    render();
}
