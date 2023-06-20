#include <iostream>
#include <algorithm>
#include "haltonSampler.h"
#include "../Misc/global.h"

HaltonSampler::HaltonSampler() : Sampler(){
    perms.reserve(NUM_CHUNKS);
    perms.resize(NUM_CHUNKS);
    for(int i = 0;i<NUM_CHUNKS;i++){
        perms[i].reserve(primes[i]);
        perms[i].resize(primes[i]);
        for(int j = 0;j<primes[i];j++){
            perms[i][j] = j;
        }
        std::shuffle(perms[i].begin()+1,perms[i].end(),__mt);
    }

}

HaltonSampler::HaltonSampler(int numChunks,int numSamples) : Sampler(numChunks,numSamples){

    perms.reserve(NUM_CHUNKS);
    perms.resize(NUM_CHUNKS);
    for(int i = 0;i<NUM_CHUNKS;i++){
        perms[i].reserve(primes[i]);
        perms[i].resize(primes[i]);
        for(int j = 0;j<primes[i];j++){
            perms[i][j] = j;
        }
        std::shuffle(perms[i].begin()+1,perms[i].end(),__mt);
    }

    for(int j = 0;j<numChunks;++j){
        for(int s = 1;s<=numSamples;s++){
            __vector_samples[j][s-1] = genSamples(s,primes[j],j);
        }
    }
}

double HaltonSampler::genSamples(int index,int base,int baseIndex){
    double fraction = 1;
    double res = 0;
    while(index>0){
        fraction /= base;
        res += fraction * perms[baseIndex][(index % base)];
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



