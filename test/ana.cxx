#include <iostream>
#include <string>
#include "TChain.h"
#include "TString.h"
using std::cout;
using std::endl;
void ana(){
    gSystem->Load("../lib/libtopology.so");
    // the tree name is "sig"
    Topology topo("sig");
    // a TCut could be set
    topo.SetCut("");
    topo.SetBranchName(
            "sig_indexmc", 
            "sig_pdgid", 
            "sig_motheridx");
    // if more than one files should be analysised, 
    // please use "AddFiles" add them one by one
    topo.AddFiles(
            "/scratchfs/bes/maxx/4180/DsSTag/AllMCSample/mode/open*root"
            );
    //topo.AddFiles("/scratchfs/bes/maxx/3770/D_KsKsK/stag/inclusiveMC/mode/sig.DpDm_dst_round04.root");
    topo.run();
}
