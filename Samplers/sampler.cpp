#include <iostream>
#include "sampler.h"


Sampler::Sampler(){
    __numSamples = 0;
    __numChunks = 0;
    __indexChunk1 = 0;
    __indexChunk2 = 0;
    __currentSample = 0;
    __mt = std::mt19937(__rd()); 
    __dis = std::uniform_real_distribution<>(0.0,1.0);
}

Sampler::Sampler(int numChunks,int numSamples){
    __numChunks = numChunks;
    __numSamples = numSamples;
    __currentSample = 0;
    __indexChunk1 = 0;
    __indexChunk2 = 1;
    __mt = std::mt19937(__rd()); 
    __dis = std::uniform_real_distribution<>(0.0,1.0);
    __vector_samples = std::vector<std::vector<double>>(__numChunks,std::vector<double>(__numSamples,0));
}

Sampler::~Sampler(){}

double Sampler::getRandomNumber(){
    return(__dis(__mt));
}