
#include "base.h"

using namespace std;
int NPuzzle::turn=0;
int NPuzzle::move=0;
int NPuzzle::getMoves(){
	turn++;
	return turn;
}

void NPuzzle::print(const NPuzzle &game){
    int i=0, k=0;

    for(i=0;i<game.height;i++){
        for(k=0;k<game.lenght;k++){
            if(game.puzzle[i][k]==game.lenght*game.height){
				cout<<"    ";
			} 
			else if(game.puzzle[i][k]>9)
                cout<<" "<<game.puzzle[i][k]<<" ";
            else
                cout<<"  "<<game.puzzle[i][k]<<" ";    
        }
        cout<<endl;
    }
	cout<<endl;
}

void NPuzzle::setsize(NPuzzle & game){
    int i=0;
    cout<<"Please enter height"<<endl;
    cin>>game.height;
    cout<<"Please enter lenght"<<endl;
    cin>>game.lenght;

    game.puzzle=new int *[game.height];
    for(int i = 0; i < game.height; ++i)
      game.puzzle[i] = new int[game.lenght];
    
}


void NPuzzle::Build_Table(NPuzzle & game){
	int i=0,k=0;
	srand(time(NULL));
	
	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
				game.puzzle[i][k]=game.compare(game);	
	    }
    }
}
int NPuzzle::compare(NPuzzle & game){
	int i=0,k=0,num=0;
	srand(time(0));
	num=rand()%(game.height*game.lenght+1);
	
	for(i=0;i<game.height;){
		for(k=0;k<game.lenght;){
			if(game.puzzle[i][k]==num){
				num=rand()%(game.lenght*game.height+1); // big number
				i=0;
				k=0;
			}
            else{
				k++;
			}

		}
		i++;
	}	
	return num;
}



void NPuzzle::move_blank(NPuzzle &game){
	char r='r',l='l',u='u',d='d',i='i',v='v',s='s',e='e', a='a',t='t',o='o',key='v';
	int flag=0,way=0;
	
	cin>>key;
	
	if(r==key){
		flag=right_move(game);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			NPuzzle::getMoves();

	}
	else if(l==key){
		flag=left_move(game);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			NPuzzle::getMoves();
	}
	else if(u==key){
		flag=up_move(game);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			NPuzzle::getMoves();
	}

	else if(d==key){
		flag=down_move(game);
		if(flag==1){
			cout<<"dont move enter diffrent way"<<endl;
		}
		else
			NPuzzle::getMoves();
	}
	else if(s==key){
		moveRandom(game);
	}
	
	else if(t==key){
		PrintReport(game);
	}
	else if(o==key){
		writeToFile(game);
	}
	else if(e==key){
		readFromFile(game);
	}
	else if(i==key){
		moveIntelligent(game);
	}
	else if(v==key){
		while(isSolved(game)!=1){
			moveIntelligent(game);
			print(game);
		}
	}
	else if(a==key){
		setsize(game);
		Build_Table(game);
	}	

}
void NPuzzle::moveIntelligent(NPuzzle &game){
	int way[4],i=0,temp=0;

	for(i=0;i<4;i++){
		way[i]=counterFun(game,i);
	}

	for(i=0;i<4;i++){
		if(way[temp] > way[i]){
			temp=i;
		}
			
	}

	if(0==temp)
		right_move(game);
	else if(1==temp)
		left_move(game);
	else if(2==temp)
		up_move(game);
	else if(3==temp)
		down_move(game);
	else
		cout<<"your coding has bug"<<endl;	
	
	game.stage[game.move]=temp;
	game.move++;

	if(game.move==3){
		game.move=0;
		
		if(game.stage[0]==game.stage[2] || game.stage[1]==game.stage[3])
			another_move(game);
	}			

}
void NPuzzle::another_move(NPuzzle & game){
	int temp=0;
		temp=rand()%4;
		if(temp==0){
			right_move(game);
		}
		else if(temp==1){
			left_move(game);
		}
		else if(temp==2){
			up_move(game);
		}
		else if(temp==3){
			down_move(game);
		}
	
}

int NPuzzle::counterFun(NPuzzle & game,int key){
	int i=0,k=0,diff=0, flag=0;

	
	if(0==key){
		flag=right_move(game);
		if(flag==1){
			return 9999999;
		}
		else{
			diff=distance(game);
			left_move(game);
			return diff;
		}
	}
	else if(1==key){
		flag=left_move(game);
		if(flag==1){
			return 9999999;
				
		}
		else{
			diff=distance(game);
			right_move(game);
			return diff;
		}
	}
	else if(2==key){
		flag=up_move(game);
		if(flag==1){
			return 9999999;
			
		}
		else{
			diff=distance(game);
			down_move(game);
			return diff;
		}
	}

	else if(3==key){
		flag=down_move(game);
		if(flag==1){
			return 9999999;
			
		}
		else{
			diff=distance(game);
			up_move(game);
			return diff;
		}
	}
	
}
int NPuzzle::distance(NPuzzle & game){
	int i=0, k=0,temp_i=0,temp_k=0,mult=0,sum=0,counter=0;

	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			mult=(i+1)*(k+1);
			while(mult!=game.puzzle[i][k]){
				if(mult >game.puzzle[i][k]){
					if(mult-game.puzzle[i][k]>game.lenght){
						mult=mult-game.lenght;
					
					}
					else{
						mult=mult-1;
					}
				}
				else if(game.puzzle[i][k] >mult){
					if(game.puzzle[i][k] -mult >game.lenght){
						mult=mult+game.lenght;
					}
					else{
						mult++;
					}
				}

			counter++;
			}
		}
	}
	return counter;
}


void NPuzzle::PrintReport(NPuzzle & game){
	cout<<"turn:"<<turn<<endl;
}
int NPuzzle::down_move(NPuzzle &game){
	int i=0,pow=0,k=0,y=0,x=0;

	for(i=0;i<game.lenght;i++){
		if(puzzle[game.height-1][i]==game.height*game.lenght){
			return 1;
		}
	}

	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[i][k]==game.height*game.lenght){
				y=i;
				x=k;
			}
		}	
	}
	i=y;
	k=x;
	
	//cout<<"number"<<puzzle[i][k]<<"i:"<<i<<" k:"<<k <<endl;

	game.puzzle[i][k]=game.puzzle[i+1][k];
	game.puzzle[i+1][k]=game.height*game.lenght;
	return 0;
}
int NPuzzle::up_move(NPuzzle & game){
	int i=0,k=0,y=0,x=0;

	
		
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[0][k]==game.height*game.lenght)
				return 1;
		}
		
		
	
	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[i][k]==game.height*game.lenght){
				y=i;
				x=k;
			}
		}
	}
	i=y;
	k=x;
	//cout<<"number"<<puzzle[i][k]<<"i:"<<i<<" k:"<<k <<endl;

	game.puzzle[i][k]=game.puzzle[i-1][k];
	game.puzzle[i-1][k]=game.height*game.lenght;

	return 0;

}
int NPuzzle::left_move(NPuzzle & game){
	int i=0,k=0,y=0,x=0;

	
		for(i=0;i<game.height;i++){
			if(game.puzzle[i][0]==game.lenght*game.height)
				return 1;
		}
	
	
	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[i][k]==game.height*game.lenght){
				y=i;
				x=k;
			}
		}
		
	}
	i=y;
	k=x;

	game.puzzle[i][k]=game.puzzle[i][k-1];
	game.puzzle[i][k-1]=game.height*game.lenght;
	return 0;
}
int NPuzzle::right_move(NPuzzle & game){
	int i=0,k=0,y=0,x=0;
	for(i=0;i<game.height;i++){
		if(game.puzzle[i][game.lenght-1]==game.lenght*game.height)
			return 1;
	}

	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[i][k]==game.lenght*game.height){
				//cout<<"break"<<endl;
				y=i;
				x=k;
			}
		}
	}
	i=y;
	k=x;
	//cout<<"number:"<<puzzle[i][k]<<"i:"<<i<<" "<<"k:"<<k <<endl;

	game.puzzle[i][k]=game.puzzle[i][k+1];
	game.puzzle[i][k+1]=game.height*game.lenght;
	return 0;
}


void NPuzzle::moveRandom(NPuzzle & game){
	int i,temp=0;
	bool flag;
	while(flag!=1){
		temp=rand()%4;
		if(temp==0){
			right_move(game);
		}
		else if(temp==1){
			left_move(game);
		}
		else if(temp==2){
			up_move(game);
		}
		else if(temp==3){
			down_move(game);
		}
		print(game);
		flag=isSolved(game);
	}
}

void  NPuzzle::writeToFile(NPuzzle &game){
	ofstream file;
	string name;
	int i=0,k=0;
	cout<<"please enter file name"<<endl;
	cin>>name;
	file.open(name);


	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){

			file<<" "<<game.puzzle[i][k]<<" ";
		}
		file<<endl;
	}
}
void NPuzzle::readFromFile(NPuzzle & game){
	ifstream file;
	string name;
	int i=0,k=0;
	cout<< "Please enter file name"<<endl;
	cin>>name;
	file.open(name);

	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			file>>game.puzzle[i][k];
		}
	}


}
bool NPuzzle::isSolved(NPuzzle & game){
	int i=0,k=0,counter=1;

	for(i=0;i<game.height;i++){
		for(k=0;k<game.lenght;k++){
			if(game.puzzle[i][k] != counter)
				return 0;	
		}
	}
	return 1;
}