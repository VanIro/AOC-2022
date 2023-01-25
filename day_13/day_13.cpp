#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<cctype>


using namespace std;

const bool DEBUG=false;
const bool DEBUG2=false;

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
        if(!isdigit(l[l_mark])) l_int=-1;
        while(isdigit(l[l_mark])){
            l_int=l_int*10+l[l_mark++]-'0';
        }
        int r_int=0;
        if(!isdigit(r[r_mark])) r_int=-1;
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
            if( l[l_mark-1]=='[' ){ //left was empty list means right was also empty list, else right would have been greater <note: this is because empty list evaluates to -1 >
                if(DEBUG) cout<<"List end <both emp>..."<<endl;
                return l_level<r_level; // less level would run out first
            }
        }
    }

}

void part_one(ifstream& inp_file, long int& ans){
    string s1,s2;
    string ls1,ls2;

    int pair_ind=0;

    while(true){
        pair_ind++;
        getline(inp_file, s1);
        getline(inp_file, s2);


        if(compare(s1,s2)){
            if(DEBUG) cout<<"True"<<"\n";
            // cout<<pair_ind<<endl;
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
}

void part_two(ifstream& inp_file, long int& ans){
    string s;


    string first_key="[[2]]";
    int first_key_pos=1;
    string second_key="[[6]]";
    int second_key_pos=2;
    while(getline(inp_file, s)){
        if(s.size()==0) continue;
        if(DEBUG2) cout<<s<<endl;
        if(!compare(first_key,s)) first_key_pos++;
        if(!compare(second_key,s)) second_key_pos++;
        if(DEBUG2) cout<<first_key_pos<<" * "<<second_key_pos<<endl;
    }
    ans=first_key_pos*second_key_pos;
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

    // part_one(inp_file,ans);
    part_two(inp_file,ans);
     
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<ans<<endl;
    return 0;
}