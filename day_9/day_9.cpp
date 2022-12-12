#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<array>
#include<set>
#include<map>

#include<cmath>


using namespace std;

#define SIZE_BODY 9
const bool DEBUG=false;
const bool DEBUG2=false;


int main(int argc,char* argv[]){

    if(argc>1){
        cout<<"Using Terminal args..."<<endl;
        cout<<argv[1]<<" vs "<<argv[2]<<" --> "<<"..."<<endl;
        return 0;
    }
    cout<<"Using file..."<<endl;

    ifstream inp_file;
    inp_file.open("input2.txt");

    long int acc=0;
    
    string s;
    string s1;

    int z;
    char c;

    vector<array<int,2>> rel_head_pos(SIZE_BODY,{0,0});
    vector<array<int,2>> prev_pos_parts(SIZE_BODY, {0,0});
    set<array<int,2>> tail_chain={{0,0}};

    map<string,array<int,2>> move_rule = {
        {"R",{1,0}},
        {"L",{-1,0}},
        {"U",{0,1}},
        {"D",{0,-1}},
        {"A",{0,0}},
        {"RU",{1,1}},
        {"RD",{1,-1}},
        {"LU",{-1,1}},
        {"LD",{-1,-1}},
    };
    map<array<int,2>,string> inv_move_rule;

    for(auto el: move_rule){
        inv_move_rule.insert({el.second,el.first});
    }

    // char d = '>';
    // try{
    // d = inv_move_rule.at({-3,0});
    // }catch(exception e){
    //     cout<<"exception : "<<e.what()<<endl;

    // }
    // cout<<d<<"*******"<<endl;

    while(true){
        getline(inp_file, s);
        stringstream ss;
        ss<<s<<"\n";
        string s1;
        ss>>s1>>z;
        if(DEBUG) cout<<c<<" "<<z<<endl;

        for(int i=0;i<z;i++){
            array<int,2> tail_move;
            string s2 = s1;
            for(int j=0;j<SIZE_BODY;j++){

                if(s2=="A") break;

                //move non-tail parts(including head)
                if(DEBUG) cout<<"rel_head_pos["<<j<<"] : <"<<rel_head_pos[j][0]<<","<<rel_head_pos[j][1]<<">";
                rel_head_pos[j][0]+=move_rule[s2][0];
                rel_head_pos[j][1]+=move_rule[s2][1];
                if(DEBUG) cout<<" --> <"<<rel_head_pos[j][0]<<","<<rel_head_pos[j][1]<<">";
                //handle tail
                int a0 = rel_head_pos[j][0];
                int a1 = rel_head_pos[j][1];
                int move = ((abs(a0)/2 + abs(a1)/2)>0)?1:0 ;
                tail_move = { move*(signbit(-a0)-signbit(a0)), move*(signbit(-a1)-signbit(a1)) };
                try{
                    s2 = inv_move_rule.at(tail_move); //for next body part
                }catch(exception e){
                    cout<<"Exception while accessing ["<<tail_move[0]<<","<<tail_move[1]<<"] key of inv_move_rule "<<endl;
                }

                prev_pos_parts[j][0]+=tail_move[0];
                prev_pos_parts[j][1]+=tail_move[1];
                rel_head_pos[j][0]-=tail_move[0];
                rel_head_pos[j][1]-=tail_move[1];

                if(DEBUG) {
                    cout<<" --> <"<<rel_head_pos[j][0]<<","<<rel_head_pos[j][1]<<">"<<endl;
                    cout<<"moved <"<<tail_move[0]<<" , "<<tail_move[1]<<">  to ["<<prev_pos_parts[j][0]<<" | "<<prev_pos_parts[j][1]<<"]"<<endl;
                }
            }
            if(DEBUG2) {
                    cout<<" --> <"<<rel_head_pos[SIZE_BODY-1][0]<<","<<rel_head_pos[SIZE_BODY-1][1]<<">"<<endl;
                    cout<<"moved <"<<tail_move[0]<<" , "<<tail_move[1]<<">  to ["<<prev_pos_parts[SIZE_BODY-1][0]<<" | "<<prev_pos_parts[SIZE_BODY-1][1]<<"]"<<endl;
            }
            //add tail_pos to the chain
            tail_chain.insert(prev_pos_parts[SIZE_BODY-1]);
        }

               
        if(inp_file.eof()){
            
            break;
        }
    }   
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<tail_chain.size()<<endl;
    return 0;
}