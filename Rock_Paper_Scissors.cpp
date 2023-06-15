#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
using namespace std;
struct history_w{
	double r,p,s;
	history_w(double x,double y,double z){
		r=x;p=y;s=z;
	}
};
int t = 1;
double reward_1 = 0.1,reward_2=0.05;
vector<history_w> history_weight;
double weight[3]={1.00,1.00,1.00};
int check_win(char,char);
int agent();

void transitin_fn(int aa,int r){//aa = action agent
	int index = history_weight.size()-1;
	double temp_r1 = reward_1;
	double temp_r2 = reward_2;
	if(r==-1){
		temp_r1*=-1.00;
		temp_r2*=-1.00;
	}else if(r==0){
		temp_r1=temp_r2=-0.02;
	}
	double temp[3] = {history_weight[index].r,history_weight[index].p,history_weight[index].s};
	
	if(t <= 2) {
		temp[aa]=temp[aa]+temp_r1;
	}else{
		double temp_2[3] = {history_weight[index-1].r,history_weight[index-1].p,history_weight[index-1].s};
		temp[aa]=((temp[aa]+temp_r1)+(temp_2[aa]+temp_r2))/2;
	}
	for(int i=0;i<3;i++){
		weight[i]=temp[i];
//		cout<<weight[i]<<' ';
	}
//	cout<<endl;
	history_w newData(temp[0],temp[1],temp[2]);
	history_weight.push_back(newData);
	t+=1;
}
int main(){
//	rock , paper scissors
	srand(time(NULL));

	// Get a random number
	int random = rand()%3;
	history_w start(1.00,1.00,1.00);
	history_weight.push_back(start);
	char action[4]={"rps"};
	int num[3]={0,0,0};
	cout<<"r (rock)\np (paper)\ns (scissors)\n";
	char Envi,ag;
	int result = 0;
	do{
		cout<<"Environment : ";
		cin>>Envi;
		if(!(Envi=='r' || Envi=='s' ||Envi=='p')) break;
		if(Envi=='r'){
			num[0]++;
		}else if(Envi=='p'){
			num[1]++;
		}else{
			num[2]++;
		}
		ag = action[agent()];
		if(t==1) ag = action[random];
		cout<<"Agent : "<<ag<<"\n";
		result = check_win(ag,Envi);
		if(result == 0){
			cout<<"tie game!!!\n";
		}else if (result == 1){
			cout<<"You losss!!!\n";
		}else{
			cout<<"You are winnerr!!@\n";
		}
		cout<<"===============================\n";
		transitin_fn(agent(),result);
	}while(true);
	cout<<"\nrock\t\t\tpaper\t\t\tscissors"<<endl;
	cout<<num[0]<<"\t\t\t"<<num[1]<<"\t\t\t"<<num[2]<<endl;
	cout<<"-------------------------------------------------------------------------------\n";
	for(int index=0;index<history_weight.size();index++){
		cout<<history_weight[index].r<<"\t\t\t"<<history_weight[index].p<<"\t\t\t"<<history_weight[index].s<<endl;
	}
	return 0;
}
int check_win(char A,char E){
	//-1 loss / 0 equivalent / 1 win for Agent
	if(A==E){
		return 0;
	}else if(A=='r'){
		if(E=='p'){
			return -1;
		}else{
			return 1;
		}
	}else if(A=='p'){
		if(E=='r'){
			return 1;
		}else{
			return -1;
		}
	}else if(A=='s'){
		if(E=='p'){
			return 1;
		}else {
			return -1;
		}
	}
}
int agent(){
	int temp = 0;
	for(int i=1 ;i<3;i++){
		if(weight[i]>weight[temp]){
			temp=i;
		}
	}
	return temp;
}
