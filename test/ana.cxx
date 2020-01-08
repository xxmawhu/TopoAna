#include <iostream>
#include <string>
#include "TChain.h"
#include "TString.h"
using std::cout;
using std::endl;
void ana(){
    gSystem->Load("../lib/libtopology.so");
    // the tree name is "sig"
    Topology topo("mctruth");
    // a TCut could be set
    topo.SetCut("");
    topo.SetBranchName(
            "indexmc", 
            "pdgid", 
            "motheridx");
    // if more than one files should be analysised, 
    // please use "AddFiles" add them one by one
    topo.AddFiles("input.root");
    //topo.AddFiles("/scratc/sig.DpDm_dst_round04.root");
    topo.run();
}
