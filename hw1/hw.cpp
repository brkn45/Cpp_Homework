#include <iostream>
#include <ctime>

using namespace  std;
void array_take(int *puzzle,int num);
int compare(int *puzzle,int index);
void print_array(int * puzzle,int num);
void move_blank(int * puzzle,int size_num);
int right_move(int *puzzle,int size_num);
int left_move(int *puzzle,int size_num);
int up_move(int * puzzle,int size_num);
int down_move(int * puzzle,int size_num);
int finish(int *puzzle,int size_num);
int inteligent(int * puzzle,int size_num);
int distance(int num,int index);
int turn_way(int * puzzle,int size_num);
int mamhattan(int *puzzle,int size_num);

int main(){
	int size_num=0,i=0;
	int puzzle[81],flag=0;
	do{
		cout<<"how many size n puzzle please enter 9 than smaller and 2 than bigger\n";
		cin>>size_num;
	}while(size_num < 3 || size_num > 9);
	for(i=0;i<81;i++){
		puzzle[i]=999;
	}
	array_take(puzzle,size_num);
	while(flag!=1){
		print_array(puzzle,size_num);
		move_blank(puzzle,size_num);
		flag=finish(puzzle,size_num);
	}	
	return 0;	
	
}
int finish(int *puzzle,int size_num){
	int i=0,pow=0;
	pow=size_num*size_num -1;
	for(i=0;i<pow;i++){
		if(puzzle[i]!=i+1)
			return 0;
	}

	return 1;
}
void move_blank(int *puzzle,int size_num){
	char r='r',l='l',u='u',d='d',i='i',s='s', key='i';
	int flag=0,way=0;
	static int last[4], step=0;
	//cin>>key;
	if(r==key){
		flag=right_move(puzzle,size_num);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
	}
	else if(l==key){
		flag=left_move(puzzle,size_num);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
	}
	else if(u==key){
		flag=up_move(puzzle,size_num);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
	}

	else if(d==key){
		flag=down_move(puzzle,size_num);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
	}
	else if(i==key){
		way=turn_way(puzzle,size_num);
		cout<<"way1:"<<way<<endl;
		if(step==3){
			step=0;
			if(last[0]==last[2] && last[1]==last[3]){
				way=1+rand()%4;
				if(1==way){
					right_move(puzzle,size_num);
				}
				else if(2==way){
					left_move(puzzle,size_num);
				}
				else if(3==way){
					up_move(puzzle,size_num);
				}
				else if(4==way){
					down_move(puzzle,size_num);
				}
			}
			return;	
		}
		else{
			last[step]=way;
			step++;
		}	
		cout<<"way2:"<<way<<endl;
		if(1==way)
			right_move(puzzle,size_num);
		else if(2==way){
			left_move(puzzle,size_num);
		}
		else if(3==way){
			up_move(puzzle,size_num);
		}
		else if(4==way){
			down_move(puzzle,size_num);
		}
	}
	else if(s==key){
		while(flag!=1){
			way=1+rand()%4;
			if(1==way)
				right_move(puzzle,size_num);
			else if(2==way){
				left_move(puzzle,size_num);
			}
			else if(3==way){
				up_move(puzzle,size_num);
			}
			else if(4==way){
				down_move(puzzle,size_num);
			}
			flag=finish(puzzle,size_num);
			print_array(puzzle,size_num);
			cout<<"flag:"<<flag<<endl;

		}
	}
	else
		cout<<"please enter valid character";



}
int turn_way(int * puzzle,int size_num){
	int flag=0, score[5],i=0,index=0,lost=0,square[4]={0};
	score[0]=inteligent(puzzle,size_num);
	flag=right_move(puzzle,size_num);
	if(flag==1)
		score[1]=900000;
	
	else{
		score[1]=inteligent(puzzle,size_num);
		square[0]=mamhattan(puzzle,size_num);
		score[1]=score[1]-square[0];
		flag=left_move(puzzle,size_num);
	}
	flag=left_move(puzzle,size_num);
	if(flag==1)
		score[2]=900000;
	
	else{
		score[2]=inteligent(puzzle,size_num);
		square[1]=mamhattan(puzzle,size_num);
		score[2]=score[2]-square[1];
		flag=right_move(puzzle,size_num);
	}
	flag=up_move(puzzle,size_num);
	if(flag==1)
		score[3]=900000;
	
	else{
		score[3]=inteligent(puzzle,size_num);
		square[2]=mamhattan(puzzle,size_num);
		score[3]=score[3]-square[2];
		flag=down_move(puzzle,size_num);
	}
	flag=down_move(puzzle,size_num);
	if(flag==1)
		score[4]=900000;
	
	else{
		score[4]=inteligent(puzzle,size_num);
		square[3]=mamhattan(puzzle,size_num);
		score[4]=score[4]-square[3];
		flag=up_move(puzzle,size_num);
	}
	lost=score[1];
	index=1;
	for(i=1;i<5;i++){
		cout<<"square:"<<i<<"  "<<square[i]<<endl;

		if(score[i]<lost){
			index=i;
			lost=score[i];
		}
	}
	cout<<endl<<"lost:"<<lost<<endl;
	return index;
}
int mamhattan(int *puzzle,int size_num){
	int i=0,counter=0;

	for(i=0;i<size_num*size_num;i++){
		if(puzzle[i]==(i+1))
			counter++;
	}

	return counter;
}
int inteligent(int * puzzle,int size_num){
	int sum=0,i=8,num=0;
	
	


	for(i=0;i<size_num*size_num;i++){
		num=puzzle[i];
		if(num==0)
			sum=sum +distance(size_num*size_num,i);
		else
			sum=sum +distance(num,i);
		
	}
	return sum;

}
int distance(int num,int index){
	
	int sum=0,zone=num-1;
	
		if(zone-index > 0){
			while(index!=zone){
				if((zone-index)>=3){
					index=index+3;
					sum=sum+1;
				}
				else{
					sum=sum+1;
					index=index+1;
				}
			}	
		}
		else if(zone -index < 0){
			while(index!=zone){	
				if(index - zone >=3){
					index=index -3;
					sum++;
				}
				else{
					sum++;
					index=index-1;
				}
			}
		}
		
	
	return sum;
}
int down_move(int * puzzle,int size_num){
	int i=0,pow=0;

	pow=size_num*size_num;

	for(i=pow -size_num;i<pow;i++){
		if(puzzle[i]==0){
			return 1;
		}
	}

	for(i=0;i<size_num*size_num;i++){
		if(puzzle[i]==0)
			break;
	}

	puzzle[i]=puzzle[i+size_num];
	puzzle[i+size_num]=0;
	return 0;
}
int up_move(int * puzzle,int size_num){
	int i=0;

	for(i=0;i<size_num;i++){
		if(puzzle[i]==0){
			return 1;
		}
	}
	for(i=0;i<size_num*size_num;i++){
		if(puzzle[i]==0)
			break;
	}

	puzzle[i]=puzzle[i-size_num];
	puzzle[i-size_num]=0;

	return 0;

}
int left_move(int *puzzle,int size_num){
	int i=0;
	for(i=0;i<size_num*size_num;i=size_num+i){
		if(puzzle[i]==0){
			return 1;
		}
	}

	for(i=0;i<size_num*size_num;i++){
		if(puzzle[i]==0)
			break;
	}
	puzzle[i]=puzzle[i-1];
	puzzle[i-1]=0;
	return 0;
}
int right_move(int *puzzle,int size_num){
	int i=0;
	
	for(i=size_num-1;i<size_num*size_num;i=size_num+i){
		if(puzzle[i]==0)
			return 1;
	}
	
	for(i=0;i<size_num*size_num;i++){
		if (puzzle[i]==0)
			break;
		
	}

	puzzle[i]=puzzle[i+1];
	puzzle[i+1]=0;
	return 0;
}
void array_take(int *puzzle,int num){
	int pow=0,i=0;

	pow=num*num;
	
	for(i=0;i<pow;i++){
		puzzle[i]=compare(puzzle,pow);
		
	}
}	
int compare(int *puzzle,int index){
	int i=0,num=0;
	srand(time(0));
	num=rand()%index;
	
	while(i<index){
		if(puzzle[i]==num){
			num=rand()%index;
			i=0;
			

		}
		else{
			i++;
		}
	}
	return num;
}
void print_array(int * puzzle,int num){
	int pow=num*num;
	int i=0;
	
	for(i=0;i<pow;i++){
		if(i%num==0){
			//cout<<endl<<"   |";
			if(puzzle[i]==0){
				cout<<endl<<"   "<<" |";
			}
			else{
				if(puzzle[i]>9){
				cout<<endl<<" "<<puzzle[i]<<" |";
			}
			else{
				cout<<endl<<"  "<<puzzle[i]<<" |";
			}
			}			
		}

		else{
			if(puzzle[i]==0){
				cout<<"   "<<" |";
			}
			else{
				if(puzzle[i]>9){
				cout<<" "<<puzzle[i]<<" |";
			}
			else{
				cout<<"  "<<puzzle[i]<<" |";
			}	
			}
		}
	}
	cout<<endl<<endl;
}