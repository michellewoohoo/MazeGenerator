#include "MyMazeSolver.hpp"
#include "MazeSolution.hpp"
#include "Maze.hpp"
#include <iostream>
#include <random>

#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, MyMazeSolver, "A Maze Solver (Required)");

MyMazeSolver::MyMazeSolver(){

}
Direction chooseDirect(int randnum){
        if(randnum==1){
            return Direction::up;
        }
        else if(randnum==2){
            return Direction::down;
        }
        else if(randnum==3){
            return Direction::left;

        }
        else if(randnum==4){
            return Direction::right;

        }
    }
    std::random_device device;
     std::default_random_engine engine{device()};

void solve(int x, int y,const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<int>> touched){
	 int width=maze.getWidth();
	 int height=maze.getHeight();
	 if(mazeSolution.isComplete()!=true){
	 	std::vector<int> valid;
	
	if(maze.wallExists(x,y,Direction::right)==false && x+1<width && touched[x+1][y]==0){
		valid.push_back(4);
	}
	if(maze.wallExists(x,y,Direction::left)==false && x-1>=0 && touched[x-1][y]==0){
		valid.push_back(3);
	}
	if(maze.wallExists(x,y,Direction::down)==false && y+1<height && touched[x][y+1]==0){
		valid.push_back(2);
	}
	if(maze.wallExists(x,y,Direction::up)==false && y-1>=0 && touched[x][y-1]==0){
		valid.push_back(1);
	}
	
      int size=valid.size();
      size=size-1;
     if(valid.size()==0){
     	touched[x][y]=1;
     	mazeSolution.backUp();
     	std::pair<int,int> current=mazeSolution.getCurrentCell();
     	solve(std::get<0>(current),std::get<1>(current),maze,mazeSolution,touched);

     }
     else{

     std::uniform_int_distribution<int> distribution{0,size};
     int chosen=valid[(distribution(engine))];

     mazeSolution.extend(chooseDirect(chosen));
     touched[x][y]=1;
     std::pair<int,int> current=mazeSolution.getCurrentCell();

	solve(std::get<0>(current),std::get<1>(current),maze,mazeSolution,touched);
	}

	 }
	

}



void MyMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
	int width= mazeSolution.getWidth();
	int height= mazeSolution.getHeight();
	std::pair<int,int> current=mazeSolution.getCurrentCell();

	std::vector<std::vector<int>> touched(width,std::vector<int>(height));
        for(int x=0; x<width; ++x){
            for(int y=0; y<height; ++y){
                touched[x][y]=0;     
                }
            }
      
	solve(std::get<0>(current),std::get<1>(current),maze,mazeSolution,touched);


}