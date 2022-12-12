#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>


using namespace std;

#define NUM_HEIGHTS 10
const bool DEBUG=false;


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

    while(true){
        getline(inp_file, s);
               
        if(inp_file.eof()){

            break;
        }
    }   
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<ans<<endl;
    return 0;
}