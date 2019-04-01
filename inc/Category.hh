/* @(#)Category.h
*/

#ifndef _Category_H
#define _Category_H

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


class Category 
{
    public:
        Category(const TString &treeName, vector<TString> &Files, 
                TCut cut = "");
        ~Category();

        void getSignalTopo(const TString&);
        void setOutFile(const TString&);
        void SetBranchName( const TString &index, const TString &pdgid
                , const TString &motherindex);
        //void openRootFile();
        bool TopoRead();
        std::map<TString, int> & GetDirTopo();
        std::map<TString, int> & GetDirNum();
        void TopoWrite(TString outputFile = "mclist.txt");
        void TopoLog();

    private:
        void Str_to_Vect(TString &s, vector<int> &pid, vector<int> &mother);
        std::map<TString, int > dir_Num, dir_itopo;
        void Classification(vector<int> &, vector<int> &, int &);

        TString m_treeName;
        vector<TString>  m_files;
        TString  m_indexmc, m_pdgid, m_motheridx;
        TString m_outFile;
        TCut  m_cut;

        ParticleObject aParticleObject;
        bool CompareByValue(std::pair<TString, int> &item1, std::pair<TString, int> &item2); 
};

#endif

