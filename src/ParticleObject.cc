// Copyright (c) 2019-4-1 maxx
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "ParticleObject.hh"
#include "currentPath.hh"
using std::string;

ParticleObject::ParticleObject() {
    string name = string(TOPOLOGYPATH) + string("/src/particle.table");
    parListFile.open(name.c_str(), std::ios::in);
    string line;
    if (parListFile.is_open()) {
        while (!parListFile.eof()) {
            // getline (parListFile, line);
            // if (line.substr(0,3)=="add") { std::cout << line << std::endl; }
            parListFile >> aMyParticle.col1        >> aMyParticle.col2
                >> aMyParticle.ParType     >> aMyParticle.ParName
                >> aMyParticle.ParId       >> aMyParticle.ParMass
                >> aMyParticle.ParWidth    >> aMyParticle.ParDm
                >> aMyParticle.Par3Charge  >> aMyParticle.Par2Spin
                >> aMyParticle.ParLifeTime >> aMyParticle.ParLundKC;

            Vparticle.push_back(aMyParticle);
            // std::cout << aMyParticle.ParName << std::endl;
        }
    } else {
        std::cout << "Unable to open file: particle.table" << std::endl;
        exit(1);
    }
}

ParticleObject::~ParticleObject() {
    parListFile.close();
}

std::string ParticleObject::GetParName(int pdgid) const {
    std::string aParName = "Unknown";

    int listLength = Vparticle.size();
    for (int i=0; i < listLength; i++) {
        if (Vparticle[i].ParId == pdgid) {
            aParName = Vparticle[i].ParName;
            break;
        }
    }
    return aParName;
}

double ParticleObject::GetParMass(int pdgid) const {
    double aParMass = 0.0;

    int listLength = Vparticle.size();
    for (int i=0; i < listLength; i++) {
        if (Vparticle[i].ParId == pdgid) {
            aParMass = Vparticle[i].ParMass;
            break;
        }
    }
    return aParMass;
}
