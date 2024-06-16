#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<random>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::find;
vector<int> playerpositions;
vector<int> cpupositions;
void printboard(vector<vector<char>>& board){
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    for(auto r:board){
    	cout<<"\t\t\t\t\t\t\t\t\t";
        for(char i:r){
            cout<<i;
        }
        cout<<endl;
    }
}
void placepiece(vector<vector<char>>& board,int pos,string turn){

    char symbol='X';
    if(turn =="player"){
        symbol='X';
        playerpositions.push_back(pos);
    }
    else{
        symbol='O';
        cpupositions.push_back(pos);
    }
    switch(pos){
        case 1:
            board[0][0]=symbol;
            break;
        case 2:
            board[0][2]=symbol;
            break;
        case 3:
            board[0][4]=symbol;
            break;
        case 4:
            board[2][0]=symbol;
            break;
        case 5:
            board[2][2]=symbol;
            break;
        case 6:
            board[2][4]=symbol;
            break;
        case 7:
            board[4][0]=symbol;
            break;
        case 8:
            board[4][2]=symbol;
            break;
        case 9:
            board[4][4]=symbol;
            break;
        default:
            break;
    }
}
int randomgen(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,9);
    return dis(gen);
}
bool search(vector<int>& arr1,vector<int>& arr2){
    for(int i:arr2){
        if(find(arr1.begin(),arr1.end(),i)==arr1.end()){
            return false;
        }
    }
    return true;
}
string checkwinner(vector<vector<char>>& board){
    vector<int> toprow={1,2,3};
    vector<int> midrow={4,5,6};
    vector<int> bottomrow={7,8,9};
    vector<int> topcol={1,4,7};
    vector<int> midcol={2,5,8};
    vector<int> bottomcol={3,6,9};
    vector<int> cross1={1,5,9};
    vector<int> cross2={7,5,3};
    vector<vector<int>> result={toprow,midrow,bottomrow,topcol,midcol,bottomcol,cross1,cross2};
    for(auto row:result){
        if(search(playerpositions,row)){
            return "Congratulations.YOU WON!";
        }
        else if(search(cpupositions,row)){
            return "Sorry.CPU WON :(";
        }
    }
    if(playerpositions.size()+cpupositions.size()==9){
            return "TIE.COMEBACK STRONGER!";
    }
    return "";
}

int main(){
    vector<vector<char>> board={{' ','|',' ','|',' '},
                     {'-','+','-','+','-'}, 
                     {' ','|',' ','|',' '},
                     {'-','+','-','+','-'},
                     {' ','|',' ','|',' '}};
    printboard(board);
    while(true){
        int pos,cpupos;
        cout<<"Enter Positions (1-9):"<<endl;
        cin>>pos;
        while((std::find(playerpositions.begin(),playerpositions.end(),pos) !=playerpositions.end() ||  std::find(cpupositions.begin(),cpupositions.end(),pos) != cpupositions.end() )|| pos<=0 || pos>9){
            if(pos<1 || pos>9){
                cout<<"Invalid position."<<endl;
            }else{
                cout<<"position taken."<<endl;
            }
            cin>>pos;
        }
        placepiece(board,pos,"player");
        printboard(board);
        string res=checkwinner(board);
        if(res.size()>1){
            cout<<res<<endl;
            break;
        }
        cpupos=randomgen();
        while(find(playerpositions.begin(),playerpositions.end(),cpupos)!=playerpositions.end() || find(cpupositions.begin(),cpupositions.end(),cpupos)!=cpupositions.end()){
            cpupos=randomgen();
        }
        placepiece(board,cpupos,"cpu");
        std::system("cls");
        printboard(board);
        res=checkwinner(board);
        if(res.size()>1){
            cout<<res<<endl;
            break;
        }
    }
}
