#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<array>
#include<cmath>
#include<algorithm>


using namespace std;

const bool DEBUG=false;
const bool DEBUG2=false;

const int NUM_ROUNDS=10000;

long long int do_op(char op,long long int old, int arg, long long int mod_num){
    switch (op){
        case '+':
            return (old+arg)%mod_num;
        case '-':
            return (old-arg)%mod_num;
        case '*':
            return (old*arg)%mod_num;
        case '/':
            return (old/arg)%mod_num;
        case '^':
            old = (old<mod_num-old)?old:(mod_num-old);
            // return pow(new_old,arg);
            return (old*old)%mod_num;
        default:
            cout<<"unexpected case! -> do_op"<<endl;
    };
    
    return -1;
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

    double ans=0;
    string s;

    string s1;
    int z;
    char c;

    vector<vector<long long int>> monkeys;
    vector<pair<char,int>> mon_ops;
    vector<array<int,3>> mon_tests;//vec<<div_test,true_mon,false_mon>>

    vector<int> monkey_business;

    while(true){
        getline(inp_file, s);
        stringstream ss;
        ss<<s<<"\n";
        ss>>s1;
        if(s1=="Starting"){
            if(DEBUG) cout<<s1<<" ";
            ss>>s1;
            if(DEBUG) cout<<s1<<" ";
            c='1';
            vector<long long int> monkey;
            while(c!='\n'){
                ss>>noskipws>>c>>z>>c;
                if(DEBUG) cout<<z<<c;
                monkey.push_back(z);
            }
            monkeys.push_back(monkey);
        }
        else if(s1=="Operation:"){
            ss>>s1>>s1>>s1>>c>>s1;
            if(isdigit(s1[0])){
                z=stoi(s1);
            }
            else{
                c='^';
                z=2;
            }
            if(DEBUG) cout<<"Operation : "<<c<<" "<<z<<endl;
            mon_ops.push_back({c,z});
        }
        else if(s1=="Test:"){
            ss>>s1>>s1>>z;
            array<int,3> mon_test;
            mon_test[0]=z;
            for(int i=0;i<2;i++){
                getline(inp_file,s);
                stringstream ss2;
                ss2<<s<<"\n";
                ss2>>s1>>s1>>s1>>s1>>s1>>z;
                mon_test[i+1]=z;
            }
            if(DEBUG) cout<<"divisible by "<<mon_test[0]<<" ? "<<mon_test[1]<<" "<<mon_test[2]<<endl;
            mon_tests.push_back(mon_test);
        }

               
        if(inp_file.eof()){

            break;
        }
    }  

    long long int mod_num = 1;
    for(auto el:mon_tests) mod_num*=el[0];
    
    cout<<"Take mod of "<<mod_num<<" to constrain the values"<<endl;

    monkey_business = vector<int>(monkeys.size(),0);

    for(int i=0;i<NUM_ROUNDS;i++){
        for(int j=0;j<monkeys.size();j++){
            vector<long long int>& monkey = monkeys[j];
            auto monkey_it=monkey.begin();
            if(DEBUG2) cout<<"\tmonkey "<<j<<"("<<monkey.size()<<")"<<endl;
            int mon_num = monkey.size();
            for(int k=0;k<mon_num;k++){
                monkey_business[j]++;
                auto item = *monkey_it;
                monkey_it = monkey.erase(monkey_it);
                // monkey_it++;
                if(DEBUG2) cout<<"\t\t"<<item<<"("<<mon_ops[j].first<<mon_ops[j].second<<") ->";
                item = do_op(mon_ops[j].first,item,mon_ops[j].second, mod_num); //mod_num need to constrain the result
                if(item < 0){
                    cout<<"-------------------\t\t"<<item<<"("<<mon_ops[j].first<<mon_ops[j].second<<")"<<endl;
                }
                if(DEBUG2) cout<<item<<"->";
                // item = item/3; //removed for part 2
                if(DEBUG2) cout<<item<<" | to ";
                int rec_mon;
                if( (item % mon_tests[j][0]) == 0){
                    rec_mon = mon_tests[j][1];
                }
                else{
                    rec_mon = mon_tests[j][2];
                }
                if(DEBUG2) cout<<rec_mon<<endl;

                monkeys[rec_mon].push_back(item);
            }
        }
        if(DEBUG||((i+1)%1000==0)){
            cout<<"After Round "<<i+1<<" : "<<endl;
            for(int p=0;p<monkeys.size();p++){
                cout<<"monkey "<<p<<" : ";
                for (int q:monkeys[p]) cout<<q<<" , ";
                cout<<"<"<<monkey_business[p]<<">"<<endl;
                // cout<<"\b\b"<<endl;
            }
        }
    } 
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    vector<int> monkey_business_sorted;
    for(int i=0;i<monkey_business.size();i++) monkey_business_sorted.push_back(i);
    sort(monkey_business_sorted.begin(), monkey_business_sorted.end(), [monkey_business](int a, int b)->bool{
        return (monkey_business[a]>monkey_business[b]);
    });

    int highest1 = monkey_business[monkey_business_sorted[0]];
    int highest2 = monkey_business[monkey_business_sorted[1]];

    if(DEBUG){
        cout<<"ordered monkey businesses : "<<endl;
        for(int i=0;i<monkey_business.size();i++){
            cout<<"\t"<<monkey_business_sorted[i]<<" : "<<monkey_business[monkey_business_sorted[i]]<<endl;
        }
    }

    cout<<"Ans : "<<highest1<<" , "<<highest2<<"->"<<highest1*highest2<<endl;
    return 0;
}