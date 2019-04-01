#include "Bubble.hh"
#include <algorithm>
#include <cstdlib>
#include <stdio.h>  
using std::vector;
using std::ios;
using std::cout;
using std::endl;
using std::setw;


// * * * * * * * * * * * * * * * * * * * * * * * * * * *
void Bubble::Sort(vector<int> &pid, vector<int> &midx){
    if ((int) pid.size() != (int) midx.size()){
        //cout << "the two vector have different length!" << std::endl;
        //cout << "the size of pid is " << (int) pid.size() << std::endl;
        //cout << "the size of midx is " << (int) midx.size() << std::endl;
        //cout << "Please check your code!" << std::endl; 
        exit(1);
    }

    int vsize = midx.size();

    int pidtemp;
    int idxtemp;
    for ( int i=0; i<vsize-1; i++ ){
        for ( int j=i+1; j<vsize; j++ ){
            // 1: mother: from small to large 
            // i.e if midx[i] < midx[j], then change "i" and "j"
            // 2: pid : if the children from one mother
            // i.e midx[i] == midx[j] 
            // from large to small
            // i.e if pid[i] < pid[j], change "i" and "j"
            // 3: children: if two difference particels from two
            // mother, i.e midx[i] != midx[j]
            // but the mother identifical
            // i.e pid[ midx[i] ] == pid[ midx[j] ]
            // then change the two group particles
            if ( midx[i] > midx[j]|| 
                    (midx[i] == midx[j] && pid[i] < pid[j] ) ){
                pidtemp = pid[i]; 
                pid[i] = pid[j];  
                pid[j] = pidtemp; 
                // change motherid
                idxtemp = midx[i];
                midx[i] = midx[j];
                midx[j] = idxtemp;
                // change the information of
                // the decay of this particle
                //cout<<"exchange "<<i<<" <==> "<<j<<endl;
                for(int kk = 1; kk<vsize; kk++){
                    if(midx[kk]==i){
                        midx[kk]=j;
                    }
                    else if(midx[kk]==j){
                        midx[kk] = i;
                    }
                }
                continue;
            }
            // the most difficult case: compare two identical
            // particles
            // change the two particles
     //      for(int jj=0;jj<midx.size(); ++jj){
     //          //cout<<setw(4)<<jj<<" ";
     //      }
     //      //cout<<endl;
     //      for(int jj=0;jj<midx.size(); ++jj){
     //          //cout<<setw(4)<<pid[jj]<<" ";
     //      }
     //      //cout<<endl;
     //      for(int jj=0;jj<midx.size(); ++jj){
     //          //cout<<setw(4)<<midx[jj]<<" ";
     //      }
     //       //cout<<endl;
            if (midx[i] == midx[j] && pid[i] == pid[j]){
                //cout<<"Ientifical: particle:"<<pid[i]
                 //   <<" and "<<pid[j]<<endl;
                //cout<<"j = "<<j << " i="<<i<<endl;
                if(Bubble::CompareIdentify(pid, midx, j, i) == 1){
                    //cout<<" CompareIdentify(j, i) = 1"<<endl;
                    pidtemp = pid[i]; 
                    pid[i] = pid[j];  
                    pid[j] = pidtemp; 
                    // change motherid
                    idxtemp = midx[i];
                    midx[i] = midx[j];
                    midx[j] = idxtemp;
                    //cout<<"exchange "<<i<<" <==> "<<j<<endl;
                    for(int kk = i; kk<vsize; kk++){
                        if(midx[kk]==i){
                            midx[kk]=j;
                        }
                        else if(midx[kk]==j){
                            midx[kk] = i;
                        }
                    }
                    continue;
                }

            }
        }
    }
}
int Bubble:: CompareIdentify(const vector<int> &pid, 
        const vector<int> &midx, 
        const int &_new, const int &_old){
    // return 0: not sure which is larger, they identify
    // 1:  _new > _old
    // -1: _old > _new
    // principle: small length, if the length is same, compare pid 
    // one by one, select large  pid
    // example: [11, 22] > [211, 11, 11] > [111, 22, 22]
    ////cout<<"Compare _new: "<<_new<<" _old: "<<_old<<endl;
    ////cout<<"pid:"<<midx[_new]<<" " << midx[_old]<<endl;
    int size_new = std::count(midx.begin()+1, midx.end(), _new);
    int size_old = std::count(midx.begin()+1, midx.end(), _old);
    //cout<<"old :"<<_old<<"new :"<<_new<<endl; 
    //cout<<"size new: "<<size_new
    //    <<" size old: "<<size_old<<endl;
    if(size_new > size_old){
        ////cout<<"size_new > size_old "<<endl;
        return -1;
    }
    else if (size_old > size_new){
        return 1;
    }
    else if( size_new == 0){
        return 0;
    }

    vector<int> chilren__new, chilren__old;
    //vector<int>::iterator itr_pid, itr_midx;
    for(int i = 1; i < pid.size(); ++i){
        if(midx[i] == _new){
            chilren__new.push_back(i);
            //cout<<" children of _new "<<i<<" pid "<<pid[i]<<endl;
        }
        if(midx[i] == _old){
            chilren__old.push_back(i);
            //cout<<" children of _old "<<i<<" pid "<<pid[i]<<endl;
        }
    }

    // sort chilren__new and chilren__old
    //cout<<"sort the new list"<<endl;
    int tmp;
    for( int p1 =0 ; p1 < chilren__new.size(); p1++){
        //cout<<"p1 = "<<p1<<endl;
        //cout<<"index:"<<chilren__new[p1]<<endl;
        //cout<<"pid 1="<<pid[ chilren__new[p1]]<<endl;
        for(int p2 = p1+1; p2 < chilren__new.size(); p2++){
            //cout<<"\tp2 = "<<p2<<endl;
            //cout<<"\tindex: "<<chilren__new[p2]<<endl;
            //cout<<"\tpid 2="<<pid[ chilren__new[p2]]<<endl;
            if( pid[ chilren__new[p2] ] > pid[ chilren__new[p1] ]){
                tmp = chilren__new[p1];
                chilren__new[p1] = chilren__new[p2];
                chilren__new[p2] = tmp;
            }
            else if(pid[p2] == pid[p1] && 
                    Bubble::CompareIdentify(pid, midx, 
                        chilren__new[p2], chilren__new[p1])==1){
                tmp = chilren__new[p1];
                chilren__new[p1] = chilren__new[p2];
                chilren__new[p2] = tmp;
            }
            else{
       //         //cout<<"\t\tsame"<<endl;
            }
        }
    }

    ////cout<<"sort the old list"<<endl;
    // sort chilren__old 
    for( int p1 =0 ; p1 < chilren__old.size(); p1++){
        for(int p2 = p1+1; p2 < chilren__old.size(); p2++){
            if( pid[ chilren__old[p2] ] > pid[ chilren__old[p1] ]){
                tmp = chilren__old[p1];
                chilren__old[p1] = chilren__old[p2];
                chilren__old[p2] = tmp;
            }
            else if(pid[p2] == pid[p1] && 
                    Bubble::CompareIdentify(pid, midx, 
                        chilren__old[p2], chilren__old[p1])==1){
                tmp = chilren__old[p1];
                chilren__old[p1] = chilren__old[p2];
                chilren__old[p2] = tmp;
            }
        }
    }
    // compare one by one
    //cout<<"compare one by one"<<endl;
    //cout<<"children size"<<chilren__new.size()<<endl;
    for(int p=0; p < chilren__new.size(); p++){
        //cout<<"p: "<<p<<endl;
        //cout<<"index: new:"<<chilren__new[p]<<endl;
        //cout<<"index: old:"<<chilren__old[p]<<endl;
        //cout<<"pid: new: "<<pid[chilren__new[p]]<<endl;
        //cout<<"pid: old: "<<pid[chilren__old[p]]<<endl;
        if(pid[ chilren__new[p] ] > pid[ chilren__old[p] ]){
            return 1;
        }
        else if( pid[chilren__new[p] ] < pid[ chilren__old[p] ]){
            return -1;
        }
        else{
            int com = Bubble::CompareIdentify(pid, midx, chilren__new[p], chilren__old[p]);
            if(com !=0){
                return com;
            }
            //cout<<"same"<<endl;
        }
    }
    //cout<<"same"<<endl;
    return 0;
}


TString Bubble::TopoString(vector<int> &pid, vector<int> &midx){
    TString tempLine = "";
    //convert int to string
    for (int i=0; i<pid.size(); i++){
        std::stringstream s;
        s << pid[i];
        s << " ";
        s << midx[i];
        s << " ";
        tempLine += s.str();
    }
    return tempLine;
}

