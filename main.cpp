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

    Vec operator*(float t){
        return Vec(x*t,y*t,z*t);
    }

    Vec operator/(double t){
        return Vec(x/t,y/t,z/t);
    }

    bool operator==(Vec a){
        return abs(this->x - a.x)<0.0001 && abs(this->y - a.y)<0.0001  && abs(this->z - a.z)<0.0001;
    }

    Vec reverse(){
        return Vec(-this->x,-this->y,-this->z);
    }

    double getLen(){
        return sqrt(x*x+y*y+z*z);
    }

    Vec normalise(){
        double len = this->getLen();
        if(len==0)return Vec(0,0,0);
        return Vec(x/len,y/len,z/len);
    }
};

double dot(Vec a,Vec b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vec reflect(Vec I,Vec N) {
    return I - N*2.0*dot(I,N);
}


ostream& operator<<(ostream& out,Vec c){
    out<<c.x<<' '<<c.y<<' '<<c.z<<' ';
    return out;
}

struct Color{
    int r,g,b;
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


struct material{
    Color c;
    double aldebo[2];
    double exCoef = 10;
    material(){}
    material (Color c, double aldebo1, double aldebo2){ this->c = c;this->aldebo[0] = aldebo1;this->aldebo[1] = aldebo2;}
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

struct Sphere{
    Vec c;
    double r;
    material m = material(Color(102,102,77),0.9,0.1);
    Sphere(Vec c,double r){
        this->c = c;
        this->r = r;
    }
    bool intersect( Vec orig,  Vec dir, double &t0)  {
        Vec L = this->c - orig;
        float tca = dot(L,dir);
        float d2 = dot(L,L) - tca*tca;
        if (d2 > r*r) return false;
        float thc = sqrt(r*r - d2);
        t0       = tca - thc;
        float t1 = tca + thc;
        if (t0 < 0) t0 = t1;
        if (t0 < 0) return false;
        return true;
    }
    Vec getNormal(Vec p){
        return (p - c)/(p-c).getLen();
    }
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


double calculateLight(Light li,Vec intersectPoint,Sphere s){
    float coef = 0;
    Vec lightDir = (li.origin() - intersectPoint).normalise();
    Vec norm = s.getNormal(intersectPoint);
    double cos = dot(lightDir,norm);
    double diffLight = li.intensity*max(0.,cos);
    double specLight = pow(max(0.,dot(reflect(lightDir,norm),intersectPoint)),s.m.exCoef)*li.intensity;
    return s.m.aldebo[0]*diffLight+s.m.aldebo[1]*specLight;
}

ostream& operator<<(ostream& out,Color c){
    out<<c.r<<endl<<c.g<<endl<<c.b<<endl;
    return out;
}

Vec cam = Vec(-80,0,0);
Sphere sphere = Sphere(Vec(0,0,0),50);
const int width = 201;
const int height = 201;
Color white(255,255,255),black(0,0,0),red(220,30,20),gray(100,100,100);//Justeasytohack1
Light l = Light(Vec(-55,30,9),white,2);

void render(){
    ofstream out("out.ppm");
    Color image[501][501];
    out << "P3\n" << width << "\n" << height << "\n"<<"255\n";
    int row = 0,col = 0;
    double t = 20000,t1 = 20000;
    for(int i = height/2;i>-height/2;i-=1){

        row += 1;
        col = 0;
        for(int j = -width/2;j<width/2;j++){
            col+=1;
            Ray ray = Ray(cam,Vec(0,j,i));
            ray.d = ray.d.normalise();
            if(sphere.intersect(ray.origin(),ray.direction(),t)){
                Vec pointIntersect = ray.getPoint(t);
                Ray lightRay = Ray(l.origin(),pointIntersect);
                lightRay.d = lightRay.d.normalise();
                if(sphere.intersect(lightRay.origin(),lightRay.direction(),t1) && lightRay.getPoint(t1) == pointIntersect){
                    image[row][col] = sphere.m.c*calculateLight(l,pointIntersect,sphere);
                } else
                    image[row][col] = black;
            }
            else
                image[row][col] = gray;
        }
    }
    for(int i = 0;i<height;i++){
        for(int j = 0;j<width;j++){
            out<<image[i][j];
        }
    }
}

int main(){
    double t;
    render();
}