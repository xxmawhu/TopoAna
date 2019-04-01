/* @(#)Category.h
*/

#ifndef _Bubble_H
#define _Bubble_H

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
#include "TString.h"

using std::vector;
using std::string;


namespace Bubble {
    int CompareIdentify(const vector<int> &pid, 
            const vector<int> &midx, 
            const int &ii, const int &jj);
    void Sort(vector<int> &, vector<int> &);
    TString TopoString(vector<int> &, vector<int> &);
}

#endif

