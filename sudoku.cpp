#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

void show(int arr[9][9]){
	cout<<"\nTHE SOLUTION OF THIS PUZZLE IS : \n\n";
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<arr[i][j]<<" ";
		}cout<<"\n";
	}
}

bool check_empty_spaces(int arr[9][9],int l[]){
	for(int i=0;i<9;i++)
		for(int j = 0;j<9;j++)
			if (arr[i][j]==0){
				l[0]=i;
				l[1]=j;
				return true;
			}
	return false;				
}

bool row_check(int arr[9][9],int num,int xpos){
	for(int i=0;i<9;i++){
		if(arr[xpos][i]==num){
			return false;
		}
	}
	return true;
}

bool column_check(int arr[9][9],int num,int ypos){
	for(int i=0;i<9;i++){
		if(arr[i][ypos]==num){
			return false;
		}
	}
	return true;
}

bool box_check(int arr[9][9],int num,int xpos, int ypos){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(arr[i+xpos][j+ypos]==num){
				return false;
			}
		}
	}
	return true;
}

bool overall_check(int arr[9][9],int num,int xpos,int ypos){
	return (row_check(arr,num,xpos)&&column_check(arr,num,ypos)&&box_check(arr,num,xpos-xpos%3,ypos-ypos%3));
}


bool solve(int arr[9][9]){
	int xpos,ypos;
	int l[2] = {0,0};
	if(!check_empty_spaces(arr,l)){
		show(arr);
		return true;
	}
	xpos = l[0];
	ypos = l[1];	
	for(int num=1;num<10;num++){
		if (overall_check(arr,num,xpos,ypos)){
			arr[xpos][ypos]=num;
			if(solve(arr)){
				return true;
			}
			arr[xpos][ypos]=0;
		}
	}
	return false;
}

bool input_puzzle(char filename[50],int arr[9][9]){
	ifstream f(filename);
	if(f==NULL){
		return false;
	}
	string str;
	for(int i=0;i<9;i++){
		getline(f,str);
		for(int j=0;j<9;j++){
			arr[i][j]=(str[j]-48);
		}
	}
	f.close();
	return true;
}

void puzzle_show(int arr[9][9]){
	cout<<"THE GIVEN PUZZLE IS :\n\n";
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++)
			cout<<arr[i][j]<<" ";
		cout<<"\n";
	}
}

int main(){
	char filename[50];
	cout<<"\n\t\t\tSUDOKU PUZZLE SOLVER\n made by :\n\nKUNAL(CO19337)\nKULDEEP(CO19336)\nHARDIK(CO19324)\n\n\nENTER NAME OF TEXT FILE WHERE PUZZLE IS PRESENT : ";
	cin>>filename;
	cout<<"\n\n";
	int arr[9][9];
	int recovery[9][9] = {{5,3,0,0,7,0,0,0,0},{6,0,0,1,9,5,0,0,0},{0,9,8,0,0,0,0,6,0},{8,0,0,0,6,0,0,0,3},{4,0,0,8,0,3,0,0,1},{7,0,0,0,2,0,0,0,6},{0,6,0,0,0,0,2,8,0},{0,0,0,4,1,9,0,0,5},{0,0,0,0,8,0,0,7,9}};
	if(!input_puzzle(filename,arr)){
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				arr[i][j] = recovery[i][j];
	}
	puzzle_show(arr);
	if(!(solve(arr))){
		cout<<"no solution possible";
	}
	getch();
}
