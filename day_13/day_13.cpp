#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<cctype>


using namespace std;

const bool DEBUG=true;

bool compare(string l, string r){ //l<=r operation
    if(DEBUG) cout<<"comparing "<<l<<" <= "<<r<<endl;
    int l_level=0;
    int l_size=l.size();
    int l_mark=0;
    int r_level=0;
    int r_size=r.size();
    int r_mark=0;

    while(true){
        if(DEBUG) cout<<l_mark<<" "<<r_mark<<endl;
        if(l_mark<l_size)
            if(l[l_mark]=='[')
                while (l[l_mark]=='['){
                    l_level++;
                    l_mark++;
                }
            else
                while (l[l_mark]==']'){
                    l_level--;
                    l_mark++;
                    if (l_mark==l_size) break;
                }
        if(r_mark<r_size)
            if(r[r_mark]=='[')
                while (r[r_mark]=='['){
                    r_level++;
                    r_mark++;
                }
            else
                while(r[r_mark]==']'){
                    r_level--;
                    r_mark++;
                    if (r_mark==r_size) break;
                }
        if( (l_mark==l_size) != (r_mark==r_size) ){
            if(DEBUG) cout<<"List end..."<<endl;
            if(l_mark==l_size){ 
                return true;
            }
            else{return false;}
        }
        else if(l_mark==l_size){
            if(DEBUG) if(DEBUG) cout<<"List end..."<<endl;
            return true;
        }
        if(l[l_mark]==',') l_mark++;
        if(r[r_mark]==',') r_mark++;

        if(l[l_mark]=='[' || r[r_mark]=='[') continue;

        int l_int=0;
        while(isdigit(l[l_mark])){
            l_int=l_int*10+l[l_mark++]-'0';
        }
        int r_int=0;
        while(isdigit(r[r_mark])){
            r_int=r_int*10+r[r_mark++]-'0';
        }
        if(l_int<r_int){
            if(DEBUG) cout<<"int_magnitude : "<<l_int<<" vs "<<r_int<<endl;
            return true;
        }
        else if(r_int<l_int){
            if(DEBUG) cout<<"int_magnitude : "<<l_int<<" vs "<<r_int<<endl;
            return false;
        }

        if(l_level!=r_level){
            if(l_level>r_level && l[l_mark]!=']'){ 
                if(DEBUG) cout<<"list_level"<<endl;
                return false;
            }
            if(r_level>l_level && r[r_mark]!=']'){ 
                if(DEBUG) cout<<"list_level"<<endl;
                return true;
            }
            if( l[l_mark-1]=='[' ){ //left was empty list means right was also empty list, else right would have been greater
                if(DEBUG) cout<<"List end <both emp>..."<<endl;
                return l_level<r_level; // less level would run out first
            }
        }
    }

}


int main(int argc,char* argv[]){

    if(argc>1){
        cout<<"Using Terminal args..."<<endl;
        cout<<argv[1]<<" vs "<<argv[2]<<" --> "<<"..."<<endl;
        return 0;
    }
    cout<<"Using file..."<<endl;

    ifstream inp_file;
    inp_file.open("input.txt");

    long int ans=0;

    string s1,s2;
    string ls1,ls2;

    int pair_ind=0;

    while(true){
        pair_ind++;
        getline(inp_file, s1);
        getline(inp_file, s2);


        if(compare(s1,s2)){
            if(DEBUG) cout<<"True"<<"\n";
            ans+=pair_ind;
        }
        else{
            if(DEBUG) cout<<"False"<<"\n";
        }

        // break;
        getline(inp_file,s1);
        
        if(inp_file.eof()){

            break;
        }
    }   
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<ans<<endl;
    return 0;
}