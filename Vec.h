//
// Created by neo on 7/21/20.
//
#pragma once
#include <bits/stdc++.h>
using  namespace std;
#ifndef SPHERE_VEC_H
#define SPHERE_VEC_H

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

Vec cross(Vec a,Vec b){
    return Vec(a.y*b.z - a.z*b.y,a.z * b.x - a.x*b.z,a.x*b.y - a.y*b.x);
}
#endif //SPHERE_VEC_H
