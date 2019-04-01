/* @(#)topology.h
*/

#ifndef _TOPOLOGY_H
#define _TOPOLOGY_H 

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
using std::cout;
using std::endl;


class Topology {
    public:
        Topology(const TString &treeName="sig");
        ~Topology();

        int run(TString out = "mclist.txt");
        void test();
        void SetCut(const TCut &cut);
        void setOutFile(const TString&);
        void AddFiles(const TString &_file);
        void SetBranchName( const TString &index, const TString &pdgid
                , const TString &motherindex);


    private:
        vector<TString> _files;
        TString _treeName;
        TString m_outFile;
        TString _pdgid, _indexmc, _motheridx;
        TCut _cut;


};

#endif

