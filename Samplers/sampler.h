#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>
#include <random>
#include <utility>
#include "../DataStructures/vec2.h"
#include "../DataStructures/vec3.h"

class Sampler{
    public:
    Sampler();
    Sampler(int numChunks,int numSamples);

    double getRandomNumber();

    Vec2 getRandomSample();

    Vec3 sampleHemisphere();

    Vec3 sampleHemisphere(const double cosExp);

    virtual ~Sampler();
    
    virtual Pair getSample() = 0;
    

    protected:
    int __numSamples;
    int __numChunks;
    int __indexChunk1,__indexChunk2;
    int __currentSample;
    int __randIndex;
    std::vector<Vec2> __random_vector;
    std::vector<std::vector<double>> __vector_samples;
    std::random_device __rd;
    std::mt19937 __mt;//gen(rd());
    std::uniform_real_distribution<> __dis;//distr(0.0,1.0);

};


#endif