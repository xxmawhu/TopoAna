#include <algorithm>
#include "ParticleObject.hh"
#include <cstdlib>
#include "TEventList.h"
#include <stdio.h>  
#include "WriteToFile.hh"
#include<algorithm>
#include<sstream>
#include "Bubble.hh"
using std::vector;
using std::ios;
using std::cout;
using std::endl;
using std::setw;
using std::pair;
using std::map;
bool WriteToFile::Compare(const std::pair<TString, int> & T1, 
        const std::pair<TString, int> &T2)
{
    return T1.second > T2.second;
}
void WriteToFile::TopoWrite(std::map<TString, int> &dir_itopo, 
        std::map<TString, int> &dir_Num, const TString &file)
{
    vector< pair< TString, int> > _Num(dir_Num.begin(), dir_Num.end());
    std::sort(_Num.begin(), _Num.end(), WriteToFile::Compare);

    std::ofstream output;

    output.open(file, ios::out);
    long int totevts= 0;
    for(vector< pair<TString, int> > ::iterator itr = _Num.begin();
            itr != _Num.end();
            itr++){
        totevts += itr->second;
    }
    output<<"the topology category statisticcal information"<<endl;
    output<<"Total events: "<<totevts<<"\t";
    output<<"the total topology number is: "<<dir_Num.size()<<endl;
    // tddi
    for(vector< pair<TString, int> > ::iterator itr = _Num.begin();
            itr != _Num.end();
            itr++){
        TString key = itr->first;
        output.flags(ios::left | ios::fixed);
        output << "\ntopology: " << setw(10) << dir_itopo[key]
            << " Events: "    << setw(10) << itr->second 
            << std::endl << std::endl;

        output.flags(ios::right | ios::fixed);
        output << std::setw(30) <<"Event listing (summary)" << endl;
        output.flags(ios::left | ios::fixed);
        output << std::setw(10) << "I";
        output << std::setw(15) << "particle/jet";
        output.flags(ios::right | ios::fixed);
        output << std::setw(8) << "KF";
        output << std::setw(8) << "orig" << endl;
        //m_outputFile << endl << endl;
        vector<int> pid, mother;
        WriteToFile::Str_to_Vect(key, pid, mother);
        ParticleObject parObj;

        for(int index = 0; index != pid.size(); index++){
            std::string mcname = parObj.GetParName(pid[index]);
            output.flags(ios::left | ios::fixed);
            output << setw(10) << index; 
            output << setw(15) << mcname;
            output.flags(ios::right | ios::fixed);
            output << setw(8) << std::setprecision(0) << pid[index];
            output << setw(8) << std::setprecision(0) << mother[index];
            output.flags(ios::right | ios::showpoint | ios::fixed);
            output << endl;
        }
    }
    output.close();
}
void WriteToFile::Str_to_Vect(TString &s, vector<int> &pid, vector<int> &mother)
{
    std::stringstream ss;
    ss<<s;
    int aPid(0), aMother(0);
    while(true){
        ss>>aPid;
        ss>>aMother;
        if(aPid==0){
            break;
        }
        pid.push_back(aPid);
        aPid = 0;
        mother.push_back(aMother);
        aMother = 0;
    }
}
