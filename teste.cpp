#include <iostream>
#include <vector>
#include "DataStructures/matrix.h"

void b(Matrix3d m){

}

int main(){
    /*
    double f[] = {2,1,3,3,1,2,1,2,3};
    Matrix3d m(std::vector<double>(f,f+sizeof(f)/sizeof(double)));
    Matrix3d n = m.transpose();
    Matrix3d c = n.cof();
    Matrix4d q(std::vector<double>({3,2,1,8,4,2,1,4,3,1,2,3,4,1,2,2}));
    Matrix4d q2(std::vector<double>({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}));
    //Matrix3d q(std::vector<double>({4,-2,1,5,0,3,-1,2,6}));
    Matrix4d qi = q.inverse();
    //Matrix4f r = q.cof();
    //std::cout<< r << std::endl;
    //std::cout<< n <<"\n";
    std::cout<< qi * q <<"\n";
    std::cout<< q <<"\n";
    
    //std::cout<< m.det() <<"\n";
    */
   
   Vec3 v(2,2,2);
   v+= Vec3(1,1,1);
   std::cout<<v;
    
}