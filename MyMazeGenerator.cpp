
#include "MyMazeGenerator.hpp"
#include "Maze.hpp"
#include <random>
#include <iostream>
#include <vector>

//Michelle Woo 31203664

#include <ics46/factory/DynamicFactory.hpp>

    ICS46_DYNAMIC_FACTORY_REGISTER(
        MazeGenerator, MyMazeGenerator,
        "A Maze Generator (Required)");
    
    void createMaze(Maze& maze, int x, int y,std::vector<int> history,std::vector<std::vector<int>>touched);

    Direction chooseDirection(int randnum){
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
    std::random_device device1;
    std::default_random_engine engine1{device1()};

    MyMazeGenerator::MyMazeGenerator(){
    }


    bool all_Filled(Maze& maze, std::vector<std::vector<int>> touched){

        
  int width=maze.getWidth();
        int height=maze.getHeight();
        for(int i=0; i<width;++i){
            for(int j=0; j<height; ++j){
                if(touched[i][j]==0){
                    return false;
                }
            }
        }
        return true;
    }

    int check_adjacent(Maze& maze, int x, int y,std::vector<std::vector<int>>touched){ 
        std::vector<int> possible;
        int width=maze.getWidth();
        int height=maze.getHeight();
        if(x+1<width){ 
            if(touched[x+1][y]==0){
                possible.push_back(4);
            }
        }
        if(x-1>=0){
            if(touched[x-1][y]==0){
                possible.push_back(3);
            }
        }
        if(y+1<height){
            if(touched[x][y+1]==0){
                possible.push_back(2);
            }
        }
        if(y-1>=0){
            if(touched[x][y-1]==0){
                possible.push_back(1);
            }
        }

        int size=possible.size();
        size=size-1;
        if(possible.size()==0){
            return 0;
        }
        else{
            std::uniform_int_distribution<int> distribution1{0,size};
            int chosen=possible[(distribution1(engine1))];
            return chosen;
        }
     }

    void backtrack(Maze& maze, int x, int y, std::vector<int>history, std::vector<std::vector<int>>touched){
        if(all_Filled(maze,touched)==true){
            return;
        }
        else{
            int numdirection=check_adjacent(maze,x,y, touched);
        if(numdirection!=0){
            createMaze(maze,x,y,history,touched); ///fix
        }
        else{

           
            int direct=history.at(history.size()-1);
            
            if(direct==1){ //up
                history.pop_back();
                backtrack(maze,x,y+1,history,touched);

            }
            else if(direct==2){//down
                 history.pop_back();
                backtrack(maze,x,y-1,history,touched);
            }
            else if(direct==3){//left
                 history.pop_back();
                backtrack(maze,x+1,y,history,touched);
            }
            else if(direct==4){
                 history.pop_back();
                backtrack(maze,x-1,y,history,touched);
            }

        }
}
        }


        


    
    void createMaze(Maze& maze, int x, int y,std::vector<int> history,std::vector<std::vector<int>>touched){

        int numdirection=check_adjacent(maze, x,y, touched);
        if(all_Filled(maze,touched)==true){
            return;
        }

        else{

        if(numdirection!=0){
            if(numdirection==1){ 
                maze.removeWall(x, y, Direction::up);
                touched[x][y-1]=1;
                history.push_back(1); 
                createMaze(maze,x,y-1,history,touched);

            }
            else if(numdirection==2){
                maze.removeWall(x,y,Direction::down);
                touched[x][y+1]=1;
                history.push_back(2);
                createMaze(maze,x,y+1,history,touched);
            }
            else if(numdirection==3){
                maze.removeWall(x,y,Direction::left);
                touched[x-1][y]=1;
                history.push_back(3);
                createMaze(maze,x-1,y,history,touched);
            }
            else if(numdirection==4){
                maze.removeWall(x,y,Direction::right);
                touched[x+1][y]=1;
                history.push_back(4);
                createMaze(maze,x+1,y,history,touched);
            }

        }
        else{
            backtrack(maze,x,y,history,touched);

        }
       
    }
       
}
   
    void MyMazeGenerator::generateMaze(Maze& maze){
        maze.addAllWalls();
        int x=0;
        int y=0;
        int width=maze.getWidth();
        int height=maze.getHeight();
        std::vector<std::vector<int>> touched(width,std::vector<int>(height));
        for(int x=0; x<width; ++x){
            for(int y=0; y<height; ++y){
                touched[x][y]=0;     
                }
            }
        touched[x][y]=1;
        std::vector<int> history;

        createMaze(maze,x,y,history,touched);


  }





















