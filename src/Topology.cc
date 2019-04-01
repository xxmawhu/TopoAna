#include "Category.hh"
#include "Topology.hh"
#include <iostream>
#include "TString.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>


int Topology::run(TString outxt)
{
    Category aTopoCat(_treeName, _files, _cut);
    aTopoCat.SetBranchName(_indexmc, _pdgid, _motheridx);
    aTopoCat.setOutFile(m_outFile);
    aTopoCat.TopoRead();
    aTopoCat.TopoWrite(outxt);
    return 0;
}
void Topology::setOutFile(const TString& out)
{
    m_outFile  = out;
}
Topology::Topology(const TString &tree)
{
    _treeName  = tree;
    _indexmc = "indexmc";
    _pdgid = "pdgid";
    _motheridx = "motheridx";
    m_outFile = "topo.root";
}
Topology::~Topology(){
}
void Topology::test(){
    Category aTopoCat(_treeName, _files, _cut);
    aTopoCat.SetBranchName(_indexmc, _pdgid, _motheridx);
    aTopoCat.TopoRead();
    aTopoCat.TopoWrite();
}
void Topology::SetCut(const TCut &cut){
    _cut = cut;
}
void Topology::SetBranchName( const TString &index, const TString &pdgid
        , const TString &motherindex){
    _indexmc = index;
    _pdgid = pdgid;
    _motheridx = motherindex;
}
void Topology::AddFiles(const TString &_aFile){
    _files.push_back(_aFile);
}

