#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>


using namespace std;

const bool DEBUG=false;

void do_cycle(int cycle, int X, long int& ans){
    if(abs(X-(cycle-1)%40)<2){
        cout<<"#";
    }
    else{cout<<".";}
    if((cycle)%40==0) cout<<endl;

    if((cycle-20)%40==0){
        if (DEBUG) cout<<"cycle : "<<cycle<<" X : "<<X<<endl;
        ans+=(cycle*X);
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
    string s;
    string s1;
    int z;
    int X=1;
    int cycle=1;

    while(true){
        getline(inp_file, s);
        stringstream ss;
        ss<<s<<"\n";
        ss>>s1;
        
        do_cycle(cycle,X,ans);
        if (s1[0]=='a'){
            ss>>z;
            cycle+=1;
        }
        else if(s1[0]=='n'){
            cycle+=1;
        }
        if(s1[0]=='a'){
            do_cycle(cycle,X,ans);
            if(DEBUG) cout<<"adding "<<z<<endl;
            X+=z;
            cycle+=1;
        }

        
        // if(cycle>220){ //this was for part 1
        //     break;
        // }       
        if(inp_file.eof()){

            break;
        }
    }   
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<ans<<endl;
    return 0;
}