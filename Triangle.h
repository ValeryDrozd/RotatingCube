//
// Created by neo on 7/21/20.
//
#include <bits/stdc++.h>
#include "Vec.h"
using namespace std;

#ifndef SPHERE_TRIANGLE_H
#define SPHERE_TRIANGLE_H


struct Model{
    vector <Vec> points;
    vector <Vec> faces;
    Model(){}

    void read(){
        points.clear();
        faces.clear();
        points.push_back(Vec(0,0,0));

        char filename[256];
        cout<<"Enter path to the file\n";
     //   cin>>filename;
        ifstream file("/home/neo/CLionProjects/cubeProject/untitled.obj");
        if(!file){cout<<"Wrong file\n";exit(1);}
        stringstream ss;
        string line,word;
        vector <string> nums(4);
        char i = 0;
        while (getline(file,line)){
            if(line[0] == 'v' or line[0] == 'f'){
                ss = stringstream(line);
                nums.clear();
                i = 0;
                while (getline(ss,word,' ')){
                    nums[i] = word;
                    i++;
                }
                Vec smth = Vec(stod(nums[1]),stod(nums[2]),stod(nums[3]));
                if(line[0]=='v'){
                    points.push_back(smth);
                }
                else
                    faces.push_back(smth);
            }
        }
        file.close();
    }

    Vec point(int i){
        return points[i];
    }

    bool rayIntersect(int n,Vec origin,Vec dir,double t){

        Vec edge1 = points[int(faces[n].y)] - points[int(faces[n].x)];
        Vec edge2 = points[int(faces[n].z)] - points[int(faces[n].x)];
        Vec pvec = cross(dir,edge2);
        double det = dot(edge1,pvec);
        if(det<0.00001)return false;
        Vec tvec = origin - points[int(faces[n].x)];
        double u = dot(tvec,pvec);
        if(u<0 || u>det)return false;
        Vec qvec = cross(tvec,edge1);
        double v = dot(dir,qvec);
        if(v<0 || u+v>det)return false;;
        t = dot(edge2,qvec)*(1./det);
        return t>0.00001;
    }
};
#endif //SPHERE_TRIANGLE_H
