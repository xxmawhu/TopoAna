#ifndef ParticleObject_h
#define ParticleObject_h

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iostream>
#include "TString.h"

#include "MyParticle.hh"

class ParticleObject{
    public:
        ParticleObject();
        ~ParticleObject();

        std::string GetParName(int ) const;
        double GetParMass(int ) const;

    private:

        std::ifstream parListFile;
    std:: map<int, TString> dir_name; 

        MyParticle aMyParticle;

        std::vector<MyParticle> Vparticle;
};

#endif

