#include <algorithm>
#include <cstdlib>
#include "TEventList.h"
#include <stdio.h>  
#include "Category.hh"
#include<algorithm>
#include "Bubble.hh"
#include "WriteToFile.hh"
using std::vector;
using std::ios;
using std::cout;
using std::endl;
using std::setw;


Category::Category(const TString &treeName, vector<TString> &Files, 
        TCut cut)
{
    m_treeName = treeName;
    m_files = Files;
    m_indexmc = "indexmc";
    m_pdgid = "pdgid";
    m_motheridx = "motheridx";
    m_cut= cut;
    m_outFile = "topo.root";
}
void Category::setOutFile(const TString& out)
{
    m_outFile = out;
}

Category::~Category()
{
}

void Category::getSignalTopo(const TString& avstr)
{
    //VsignalTopoStr = avstr;
}

bool Category::TopoRead()
{
    TChain *ch =  new TChain (m_treeName);
    if(m_files.empty()){
        std::cout<<"Error: "<<"No File Input"<<std::endl;
        return false;
    }
    for(int i = 0 ; i < m_files.size(); i++){
        ch->Add(m_files[i]);
    }
    // apply cuts
    
    if(TString(m_cut) !=TString("")){
        TFile *ftmp(0);
        int nn = 1;
        TString tmName ="tmp.root";
        ftmp = TFile::Open(tmName,"recreate");
        TTree *tmp_tree = ch->CopyTree(m_cut);
        tmp_tree->Write();
        ftmp->Close();
        delete ch;
        delete ftmp;
        //delete tmp_tree;
        

        TChain *tmp = new TChain(m_treeName);
        tmp->Add(tmName);
        Int_t indexmc, pdgid[100], motheridx[100];
        tmp->SetBranchAddress(m_indexmc, &indexmc);
        tmp->SetBranchAddress(m_pdgid, pdgid);
        tmp->SetBranchAddress(m_motheridx, motheridx);

        TFile *newfile = new TFile(m_outFile,"recreate");
        cout<<"The out file is: "<<m_outFile<<endl;
        TTree *newtree = tmp->CloneTree(0);

        int n_itopo;
        TBranch *tmpBr(0);
        if( (tmpBr = newtree->FindBranch("n_itopo")) ==0){
            newtree->Branch("n_itopo",  &n_itopo,   "n_itopo/I");
        }
        else if( (tmpBr = newtree->FindBranch("n_itopo2")) ==0){
            newtree->Branch("n_itopo2",  &n_itopo,   "n_itopo2/I");
        }
        else if( (tmpBr = newtree->FindBranch("n_itopo3")) ==0){
            newtree->Branch("n_itopo3",  &n_itopo,   "n_itopo3/I");
        }

        cout<<"Info::"<<"The total events after cuts is :"
            << tmp->GetEntries()<<endl;

            vector<int> parid, midx;
        for(Int_t i=0; i< tmp->GetEntries(); ++i){
            tmp->GetEntry(i);
            //cout<<"events: "<<i << " n_itopo " << n_itopo<<endl;
            parid = vector<int> (pdgid, pdgid+indexmc);
            midx = vector<int> (motheridx, motheridx+indexmc);
            Classification(parid, midx, n_itopo);
            newtree->Fill();
        }
        //newfile->cd();
        newtree->Write();
        newfile->Close();
    }
    else{
        Int_t indexmc, pdgid[100], motheridx[100];
        ch -> SetBranchAddress(m_indexmc, &indexmc);
        ch -> SetBranchAddress(m_pdgid, pdgid);
        ch -> SetBranchAddress(m_motheridx, motheridx);

        TFile *newfile = new TFile(m_outFile,"recreate");
        cout<<"The out file is: "<<m_outFile<<endl;
        //newfile->Cd();
        TTree *newtree = ch -> CloneTree(0);

        int n_itopo;
        newtree->Branch("n_itopo",  &n_itopo,   "n_itopo/I");

        cout<<"Info::"<<"The total events is :"
            << ch->GetEntries()<<endl;

        vector<int> parid;
        vector<int> midx;
        for(Int_t i=0; i< ch->GetEntries(); ++i){
            ch -> GetEntry(i);
            //   if(i%1000000==0){
            //       cout<<"events:"<<i<<endl;
            //   }
            parid = vector<int> (pdgid, pdgid+indexmc);
            midx = vector<int> (motheridx, motheridx+indexmc);
            //cout<<"length 1:" <<midx.size()<<", "<<parid.size()<<endl;
            Classification(parid, midx, n_itopo);
            //cout<<"length 2:" <<midx.size()<<", "<<parid.size()<<endl;
            newtree->Fill();

        }
        newtree->Write();
        newfile->Close();
    }
}

void Category::TopoLog()
{
    /*
       std::ofstream m_outputFile;
       m_outputFile.open("log.txt", ios_base::out);
       cout<<"log*******************************"<<endl;
       vector<int> Vtopoback = Vtopo;
       int totalTopo = Vtopo.size();
       for (int i = 0; i < totalTopo; i++)
       {
       topoIdx.push_back(i);
       }
       Bubble::Sort(topoIdx, Vtopo);
       Bubble::Sort(VtopoNpar, Vtopoback);

       std::cout << "the total topology number is: " << totalTopo << std::endl;
       m_outputFile << "the topology category statisticcal information" 
       << std::endl;
       m_outputFile << "the total topology number is: " << totalTopo << std::endl;
       m_outputFile << "type      " << "Event Number" << std::endl;
       for (int i=0; i<totalTopo; i++)
       {
       m_outputFile.flags(ios::left | ios::fixed);
       m_outputFile << setw(10) << topoIdx[i] 
       << setw(10) << Vtopo[i] << std::endl;
       }
       m_outputFile.close();
       */
}

void Category::TopoWrite(TString outputFile){
    WriteToFile::TopoWrite(dir_itopo, dir_Num, outputFile);
}
bool Category::CompareByValue( std::pair<TString, int> &item1, 
        std::pair<TString, int> &item2){
    return item1.second < item2.second;
} 
void Category::Classification(vector<int> &pdgid, 
        vector<int> &motheridx, int &itopo){
    Bubble::Sort(pdgid, motheridx);
    TString strTopo = Bubble::TopoString(pdgid, motheridx);
    //cout<<strTopo<<endl;
    if(dir_Num.find(strTopo) == dir_Num.end()){
        dir_itopo.insert(std::pair<TString, int>( strTopo, dir_Num.size()));
        dir_Num.insert(std::pair<TString, int> ( strTopo, 1));
    }
    else{
        dir_Num[strTopo] += 1;
    }
    itopo = dir_itopo[strTopo];
}
void Category::SetBranchName( const TString &index, const TString &pdgid
        , const TString &motherindex){
    m_motheridx = motherindex;
    m_indexmc = index;
    m_pdgid = pdgid;
}
