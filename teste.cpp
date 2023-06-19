#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
/*
#include "Samplers/haltonSampler.h"

int main(){
    HaltonSampler hs(10,5);
    for(int i = 0;i<100;i++){
        std::cout<<hs.getSample();
    }
    std::cout<<"dasdasdasdas\n";
    

}
*/

int main(){
    std::random_device __rd;
    std::mt19937 __mt(__rd());
    //std::uniform_real_distribution<> __dis;//distr(0.0,1.0);
    double x = 0x1.ffffffffffffp-1;
    double n = 0.99999999999999;
    double d = 0x01.0p-1;
    char c = 0x166;
    //std::cout<<d<<std::endl;
    std::vector<double> a = {0,1,2,3,4,5,6,7,8};
    std::shuffle(a.begin()+1,a.end(),__mt);
    //printf("%a",x);
    for(double d : a){
        std::cout<< d << " ";
    }
    std::cout<<std::endl;
}