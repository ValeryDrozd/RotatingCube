#include <bits/stdc++.h>
#include "Vec.h"
#include "Triangle.h"
using namespace std;

struct Color{
    short int r,g,b;
    Color(){}

    Color(int r,int g,int b){
        this->r = r;
        this->g = g;
        this->b = b;
    }

    Color operator* (double t){
        return Color(int(min(this->r*t,255.0)),int(min(this->g*t,255.0)),int(min(this->b*t,255.0)));
    }
};


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


struct Light{
    Vec point;
    Color c;
    double intensity;
    Light(){}
    Light(Vec point,Color c,double intensity){
        this->point = point;
        this->c = c;
        this->intensity = intensity;
    }
    Vec origin(){return point;}

};

ostream& operator<<(ostream& out,Color c){
    out<<c.r<<endl<<c.g<<endl<<c.b<<endl;
    return out;
}

Vec cam = Vec(-10,0,0);
Color image[501][501];
const int width = 11;
const int height = 11;
Color white(255,255,255),black(0,0,0),red(220,30,20),gray(100,100,100);//Justeasytohack1
Light l = Light(Vec(-55,30,9),white,2);
Model m;

void render(){
    m.read();
    ofstream out("out.ppm");
    out << "P3\n" << width << "\n" << height << "\n"<<"255\n";
    int row = 0,col = 0;
    double t = 20000,t1 = 20000;
    bool intersect = false;
    for(int i = height/2;i>-height/2;i-=1){
        row += 1;
        col = 0;
        for(int j = -width/2;j<width/2;j++){
            col+=1;
            Ray ray = Ray(cam,Vec(0,j,i));
            ray.d = ray.d.normalise();
            intersect = false;
            for(int c = 0;c<m.faces.size();c++){
                if(m.rayIntersect(c,ray.origin(),ray.direction(),t)){
                    intersect = true;
                    image[i][j] = white;
                    break;
                }
            }
            if(intersect==false)image[i][j] = black;
        }
    }
    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
            out<<image[i][j];
        }
    }
    out.close();
}

int main(){
    double t;
    render();
}