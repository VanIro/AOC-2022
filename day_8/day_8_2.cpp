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
    inp_file.open("input2.txt");

    long int acc=0;
    string s1,s2,s3;
    string s;

    int i1,i2,j1,j2;
    long int visibility=0;
    int temp_sum_row;
    int temp_diff_row;

        getline(inp_file, s);
        int num_cols = s.size();

        int max_row=-1;
        int min_row=NUM_HEIGHTS;
        vector<bool> from_end_row(NUM_HEIGHTS);

        vector<int> max_cols(num_cols-2);
        for(int i=0;i<num_cols-2;i++) max_cols[i]=s[i+1];
        vector<int> min_cols(num_cols-2);
        for(int i=0;i<num_cols-2;i++) min_cols[i]=s[i+1];
        
        vector<vector<bool>> from_end_cols(num_cols-2); 
        for(int j=0;j<num_cols-2;j++){
            from_end_cols[j] = vector<bool>(NUM_HEIGHTS);
            for(int i=0;i<NUM_HEIGHTS;i++)from_end_cols[j][i]=false;
        }
        //temp_diff_cols and temp_sum_cols have been created for debugging purpose only
        vector<int> temp_diff_cols(num_cols-2);
        vector<int> temp_sum_cols(num_cols-2);
        for(int i=0;i<num_cols-2;i++){
            temp_diff_cols[i]=0;
            temp_sum_cols[i]=0;
        }

    visibility+=s.size();//first row
    cout<<"Num Cols = "<<s.size()<<endl;

    
    vector<vector<int>> tmp_from_end_map_cols(num_cols-2);
    for(int j=0;j<num_cols-2;j++){
        tmp_from_end_map_cols[j] = vector<int>(NUM_HEIGHTS);
        for(int i=0;i<NUM_HEIGHTS;i++){
            tmp_from_end_map_cols[j][i] = -1;
        }
    }

    int row=1;
    while(true){
        getline(inp_file, s);
        row++;
        if(DEBUG)  cout<<"Row : "<<row<<endl;
        visibility+=1;//first in the row
        max_row=min_row=s[0];
        for(int i=0;i<NUM_HEIGHTS;i++)from_end_row[i]=false;
        temp_diff_row=0;
        temp_sum_row=0;

        // from_end_row[s[0]-'0']=false;
        vector<int> tmp_from_end_map(NUM_HEIGHTS);
        vector<int> tmp_from_beg_map(NUM_HEIGHTS);
        for(int i=0;i<NUM_HEIGHTS;i++){
            tmp_from_end_map[i] = tmp_from_beg_map[i] = -1;
        }

        for(int i=1;i<s.size();i++){
            char c = s[i];
            

            for(int j=min_row-'0';j<=(c-'0');j++){
                if(from_end_row[j]){
                    from_end_row[j]=false;
                    tmp_from_end_map[j]=-1;
                    visibility-=1;
                    temp_diff_row++;
                }
            }

            min_row=c;
            if(c>max_row){
                visibility+=1;
                if(DEBUG)  cout<<"<row_B>("<<row<<" , "<<i+1<<")"<<endl;
                max_row=c;
                tmp_from_beg_map[c-'0']=i;
            }
            else{
                visibility+=1;
                temp_sum_row++;
                from_end_row[c-'0']=true;
                tmp_from_end_map[c-'0']=i;
            }

        }
        if(DEBUG)  cout<<"<row>  Temp Sum : "<<temp_sum_row<<" & Temp Diff : "<<temp_diff_row<<endl;
        for(int i=(min_row-'0');i<=max_row;i++){
            if(from_end_row[i]){
                if(DEBUG)  cout<<"<row_E>("<<row<<" , "<<tmp_from_end_map[i]+1<<")"<<endl;
            }
        }


        //column part
        for(int i=1;i<s.size()-1;i++){
            char c=s[i];
            // if(DEBUG)  cout<<tmp_from_beg_map.size()<<" , "<<tmp_from_end_map.size()<<" | "<<(c-'0')<<endl;   
            

            for(int j=min_cols[i-1]-'0';j<=(c-'0');j++){
                if(from_end_cols[i-1][j]){
                    from_end_cols[i-1][j]=false;
                    tmp_from_end_map_cols[i-1][j]=-1;
                    visibility-=1;
                    temp_diff_cols[i-1]+=1;
                }
            }

            min_cols[i-1]=c;
            if(c>max_cols[i-1]){
                max_cols[i-1]=c;
                if(tmp_from_beg_map[c-'0']==i) continue;
                if(tmp_from_end_map[c-'0']==i) continue;
                if(DEBUG)  cout<<"<col_B>("<<row<<" , "<<i+1<<")"<<endl;
                visibility+=1;
            }
            else{
                if(tmp_from_beg_map[c-'0']==i) continue;
                if(tmp_from_end_map[c-'0']==i) continue;
                from_end_cols[i-1][c-'0']=true;
                tmp_from_end_map_cols[i-1][c-'0']=row;
                visibility+=1;
                temp_sum_cols[i-1]+=1;
            }
        }
        
        if(inp_file.eof()){
            //for last row
            if(DEBUG)  cout<<"<cols> Temp Sum  : ";
            for(int i=0;i<num_cols-2;i++){
                if(DEBUG)  cout<<temp_sum_cols[i]<<",";
            }
            if(DEBUG)  cout<<"\n<cols> Temp Diff : ";
            for(int i=0;i<num_cols-2;i++){
                if(DEBUG)  cout<<temp_diff_cols[i]<<",";
            }
            if(DEBUG)  cout<<endl;
            for(int j=0;j<num_cols-2;j++){
                for(int i=min_cols[j]-'0';i<=max_cols[j];i++){
                    if(from_end_cols[j][i]){
                        if(DEBUG)  cout<<"<col_E>("<<tmp_from_end_map_cols[j][i]<<" , "<<j+2<<")"<<endl;
                    }
                }
            }

            break;
        }
    }   
    
    if(DEBUG)  cout<<"\n------------"<<endl;

    cout<<"Ans : "<<visibility<<endl;
    return 0;
}