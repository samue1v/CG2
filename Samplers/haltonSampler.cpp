#include <iostream>
#include "haltonSampler.h"
#include "../Misc/global.h"

HaltonSampler::HaltonSampler() : Sampler(){}

HaltonSampler::HaltonSampler(int numChunks,int numSamples) : Sampler(numChunks,numSamples){
    for(int j = 0;j<numChunks;++j){
        for(int s = 1;s<=numSamples;s++){
            __vector_samples[j][s-1] = genSamples(s,primes[j]);
        }
    }
}

double HaltonSampler::genSamples(int index,int base){
    double fraction = 1;
    double res = 0;
    while(index>0){
        fraction /= base;
        res += fraction * (index % base);
        index /= base;
    }
    return res;
}

Pair HaltonSampler::getSample(){
    __indexChunk1 == __indexChunk2 ? __indexChunk1 = (__indexChunk1+1) % __numChunks,__indexChunk2 = (__indexChunk1 + 1) % __numChunks: 1;
    Pair p(__vector_samples[__indexChunk1][__currentSample],__vector_samples[__indexChunk2][__currentSample]);
    //std::cout<< "ic1: "<<__indexChunk1 << " ic2 "<<__indexChunk2<<std::endl;
    __currentSample+1 >= __numSamples ? __indexChunk2 = (__indexChunk2+1) % __numChunks,__currentSample = 0 : __currentSample++;
    return p;

}



