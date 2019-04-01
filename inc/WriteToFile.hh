/* @(#)WriteToFile.h
*/

#ifndef _WriteToFile_H
#define _WriteToFile_H

#include "ParticleObject.hh"

#include <iostream>
#include <iomanip> //for setw
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include <TROOT.h>
#include <TTree.h>
#include <TCut.h>
#include <TChain.h>
#include <TFile.h>
#include "TTree.h"
#include "TFile.h"
#include "TCut.h"
#include "TString.h"
#include "TEventList.h"

using std::vector;
using std::string;


namespace WriteToFile {
    void TopoWrite(std::map<TString, int> & dir_topo, 
            std::map<TString, int> &dir_Num, const TString &filename);
    bool Compare(const std::pair<TString, int> &T1, 
            const std::pair<TString, int> &T2 );

    void Str_to_Vect(TString &s, vector<int> &pid, vector<int> &mother);
}

#endif

