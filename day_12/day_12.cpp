#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<array>

#include<set>
#include<queue>
#include<functional>


using namespace std;

const bool DEBUG=true;
const bool PART_1=false;

//djikstra's algorithm has been implemented to solve the problems

struct FrontierClass{
    array<int,2> loc;
    int length;
    FrontierClass* prev=nullptr;
};

struct compareFrontiers{
    bool operator()(const FrontierClass* a, const FrontierClass* b){
        return a->length > b->length;
    }
};

// bool compareFrontiers(FrontierClass a, FrontierClass b){ //this gives error
//     return a.length<b.length;
// } 


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

    vector<string> h_map;

    array<int,2> start;
    array<int,2> end;

    bool find_start = true;
    bool find_end = true;

    int r_i=0;
    while(true){
        getline(inp_file, s);
        // stringstream ss;
        // ss<<s<<"\n";
        if(find_start){
            int c_j = s.find('S');
            if(c_j != string::npos ) {
                start = {c_j,r_i};
                s[c_j] = 'a';
                find_start = false;
            }
        }
        if(find_end){
            int c_j = s.find('E');
            if(c_j != string::npos ) {
                end = {c_j,r_i};
                s[c_j] = 'z';
                find_end = false;
            }
        }

        h_map.push_back(s);

        r_i++;
               
        if(inp_file.eof()){
            break;
        }
    }   

    int width = h_map[0].size();
    int height = h_map.size();
    cout<<"width : "<<width<<" | height : "<<height<<endl;
    cout<<"start : "<<start[0]<<" , "<<start[1]<<endl;
    cout<<"end : "<<end[0]<<" , "<<end[1]<<endl;


    set<array<int,2>> done_paths_set;
    set<array<int,2>> frontiers_set;
    vector<FrontierClass*> frontiersContainer;//is this used by the priority queue below?
    priority_queue<FrontierClass*,vector<FrontierClass*>,compareFrontiers> frontiers_q(compareFrontiers(),frontiersContainer);

    auto start_node = 
        (PART_1)?(new FrontierClass{start,0}): //only for part-1
        (new FrontierClass{end,0}); //only for part-2

    frontiers_q.push(start_node);
    frontiers_set.insert(start_node->loc);


    array<array<int,2>,4> move_dirs = {array<int,2>{1,0}, array<int,2>{-1,0}, array<int,2>{0,1}, array<int,2>{0,-1}};//{ {1,0} ,{-1,0},{0,1},{0,-1} };

    FrontierClass* frontier;
    while(true){
        frontier = frontiers_q.top();
        frontiers_q.pop();
        if(done_paths_set.find(frontier->loc)!=done_paths_set.end()){//this is required because in frontiers there may be duplicates, so while one is added to done_paths_set, others remain there and they must be ignored
            continue; 
        }
        done_paths_set.insert(frontier->loc);


        if(PART_1){
            if(frontier->loc[0]==end[0] && frontier->loc[1]==end[1]){ //only for part-1
                break;
            }
        }
        else{
            if(h_map[frontier->loc[1]][frontier->loc[0]]=='a'){ //only for part-2
                break;
            }
        }

        for(auto el:move_dirs){ 
            int x = el[0] + frontier->loc[0];
            int y = el[1] + frontier->loc[1];

            if(x >= 0 && x<width ){
                if(y >= 0 && y<height ){
                    
                    if(done_paths_set.find({x,y})==done_paths_set.end()){
                        if(PART_1){
                            if(h_map[y][x]>(h_map[frontier->loc[1]][frontier->loc[0]]+1)){ //only for part-1
                                continue;
                            }
                        }
                        else{
                            if(h_map[frontier->loc[1]][frontier->loc[0]]>(h_map[y][x]+1)){//only for part-2
                                continue;
                            }
                        }
                        
                        FrontierClass* fcptr = new FrontierClass{ {x,y},frontier->length+1,frontier };
                        frontiers_q.push(fcptr);
                        frontiers_set.insert(fcptr->loc);
                    }
                }
            }
        }
    }


    
    if(DEBUG)  cout<<"\n------------"<<endl;

    // cout<<endl;
    // FrontierClass* node = frontier;
    // while(node!=nullptr){
    //     cout<<"<--{"<<node->loc[0]<<","<<node->loc[1]<<"}("<<h_map[node->loc[1]][node->loc[0]]<<")";
    //     node = node->prev;
    // }

    cout<<endl;
    cout<<"Ans : "<<frontier->length<<endl;
    return 0;
}