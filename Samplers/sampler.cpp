#include <iostream>
#include "sampler.h"


Sampler::Sampler(){
    __numSamples = 0;
    __numChunks = 0;
    __indexChunk1 = 0;
    __indexChunk2 = 0;
    __currentSample = 0;
    __randIndex = 0;
    __mt = std::mt19937(__rd()); 
    __dis = std::uniform_real_distribution<>(0.0,1.0);
}

Sampler::Sampler(int numChunks,int numSamples){
    __numChunks = numChunks;
    __numSamples = numSamples;
    __currentSample = 0;
    __indexChunk1 = 0;
    __indexChunk2 = 1;
    __randIndex = 0;
    __mt = std::mt19937(__rd()); 
    __dis = std::uniform_real_distribution<double>(0.0,1.0);
    __vector_samples = std::vector<std::vector<double>>(__numChunks,std::vector<double>(__numSamples,0));
    __random_vector.reserve(__numChunks*__numSamples);
    __random_vector.resize(__numChunks*__numSamples);
    for(int i = 0; i<__numChunks*__numSamples;i++){
        Point2 p = Point2(getRandomNumber(),getRandomNumber());
        //std::cout<< p;
        __random_vector[i] = p;
    }
}

Sampler::~Sampler(){}

double Sampler::getRandomNumber(){
    return(__dis(__mt));
}

Vec2 Sampler::getRandomSample(){
    //std::cout<<__randIndex<<std::endl;
    return __random_vector[++(__randIndex) % __random_vector.size()];
}

//remember that its not a cossine distributed sample, only work for perfct diffuse surfaces, otherwise exponent 
// sampler must be implemented for glossy reflections
Vec3 Sampler::sampleHemisphere(){
    Vec2 randSample = getRandomSample();
    double cos_phi = cos(2.0 * PI * randSample.y());
    double sin_phi = sin(2.0 * PI * randSample.y());
    double cos_theta = /*randSample.x()*/pow((1.0 - randSample.x()), 1.0 / (2 + 1.0)); //testing cossine
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    double pu = sin_theta * cos_phi;
    double pv = sin_theta * sin_phi;
    double pw = cos_theta;
    return Vec3(pu,pv,pw);
}

Vec3 Sampler::sampleHemisphere(const double cosExp){
    Vec2 randSample = getRandomSample();
    double cos_phi = cos(2.0 * PI * randSample.y());
    double sin_phi = sin(2.0 * PI * randSample.y());
    double cos_theta = pow((1.0 - randSample.x()), 1.0 / (cosExp + 1.0));
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    double pu = sin_theta * cos_phi;
    double pv = sin_theta * sin_phi;
    double pw = cos_theta;
    return Vec3(pu,pv,pw);
}

Vec2 Sampler::sampleSquare(){
    return getRandomSample();
}

Vec3 Sampler::sampleSphere(){
    Vec2 sample = getRandomSample();
    double z = 1.0 - 2.0 * sample.x();
    double r = sqrt(std::max(0.0, 1.0 - z * z));
    double phi = 2.0 * PI * sample.y();
    return Vec3(r * cos(phi), r * sin(phi), z);
}