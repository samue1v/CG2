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

HaltonSampler::HaltonSampler(int numChunks,int numSamples,bool fixed) : Sampler(numChunks,numSamples,fixed){

    perms.reserve(numChunks);
    perms.resize(numChunks);
    for(int i = 0;i<numChunks;i++){
        perms[i].reserve(primes[i]);
        perms[i].resize(primes[i]);
        for(int j = 0;j<primes[i];j++){
            perms[i][j] = j;
        }
        std::shuffle(perms[i].begin()+1,perms[i].end(),__mt);
    } 


    for(int f = 0;f<numChunks;f++){
        for(int s = 0;s<numSamples;s++){
            __vector_samples[f][s] = genSamples(s,primes[f],f);
        }
    }

    if(fixed){
        
        __indexChunk1 = getRandomNumber() * __numChunks;
        __indexChunk2 = __indexChunk1;
        while(__indexChunk1 == __indexChunk2){
            __indexChunk2 = getRandomNumber() * __numChunks;
        }

    }
}

double HaltonSampler::genSamples(int index,int base,int baseIndex){
    double fraction = 1.0;
    double res = 0.0;
    //index = perms[baseIndex][index];
    while(index>0.0){
        fraction /= base;
        res += fraction * perms[baseIndex][(index % base)];
        index /= base;
    }
    return res;
}

Pair HaltonSampler::getSample(){
    Pair p;
    if(__fixed){
        p = Pair(__vector_samples[__indexChunk1][__currentSample],__vector_samples[__indexChunk2][__currentSample]);
        __currentSample = (__currentSample + 1) % __numSamples;
    }
    else{
        __indexChunk1 == __indexChunk2 ? __indexChunk1 = (__indexChunk1+1) % __numChunks,__indexChunk2 = (__indexChunk1 + 1) % __numChunks: 1;
        p = Pair(__vector_samples[__indexChunk1][__currentSample],__vector_samples[__indexChunk2][__currentSample]);
        __currentSample+1 >= __numSamples ? __indexChunk2 = (__indexChunk2+1) % __numChunks,__currentSample = 0 : __currentSample++;
    }
    
    return p;

}



