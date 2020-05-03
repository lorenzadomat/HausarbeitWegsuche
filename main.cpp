#include "config.h"
#include "Maze.cpp"
#include "SearchAlgorithms.h"
#include "Utils/Console.h"
#include <vector>
#include <tuple>

Maze maze;
vector<tuple<Tile, Tile>> path, path1, path2;
int pathWidth = 0;
int algorithmNo = -1;
int mazeNo = -1;
int columns = -1;
int rows = -1;
int startX = -1;
int startY = -1;
int endX = -1;
int endY = -1;
bool drawInSteps = false;

void benchmark(){
    path1 = breadth_first_search(maze);
    path2 = breadth_first_search_optimized(maze);
    if(path1.size() <= path2.size()){
        path = path1;
    }else{
        path = path2;
    }
}

void userInput(){
    string input;
    //TODO Input validation
    while(mazeNo == -1) {
        printMazeOptions();
        cin >> input;
        if (input == "Example1" || input == "0") {
            mazeNo = 0;
            columns = 5;
            rows = 5;
            startX = 3;
            startY = 0;
            endX = 1;
            endY = 4;
            break;
        } else if (input == "Example2" || input == "1") {
            mazeNo = 1;
            break;
        } else if (input == "Random" || input == "2") {
            mazeNo = 2;
            break;
        } else {
            cout << "\033[1;31mInvalid Input\033[0m" << endl;
        }
    }
    cout << endl;
    if(mazeNo == 2){
        while(columns < 0 || rows < 0){
            cout << "Enter the number of rows";
            cout << endl;
            cout << "Rows = ";
            cin >> rows;
            cout << "Enter the number of columns";
            cout << endl;
            cout << "Columns = ";
            cin >> columns;
        }
        while(startX < 0 || startY < 0 || endX < 0 || endY < 0 || startX > columns || startY > rows || endX > columns || endY > rows) {
            cout << "Enter a Start-Point";
            cout << endl;
            cout << "x = ";
            cin >> startX;
            cout << "y = ";
            cin >> startY;
            cout << "Enter an End-Point";
            cout << endl;
            cout << "x = ";
            cin >> endX;
            cout << "y = ";
            cin >> endY;
        }
    }
    cout << endl;
    while(algorithmNo == -1) {
        printAlgorithmOptions();
        cin >> input;
        if (input == "Breitensuche" || input == "0") {
            algorithmNo = 0;
            break;
        } else if (input == "Breitensuche2" || input == "1") {
            algorithmNo = 1;
            break;
        } else if (input == "Dijkstra" || input == "2") {
            algorithmNo = 2;
            break;
        } else if (input == "Benchmark" || input == "3") {
            algorithmNo = 3;
            break;
        } else if (input == "Exit" || input == "exit") {
            mazeNo = -1;
            algorithmNo = -1;
            userInput();
            return;
        } else {
            cout << "\033[1;31mInvalid Input\033[0m" << endl;
        }
    }

    cout << endl;
    #ifdef makeGUI
        cout << "Draw in Steps? (Y / N): ";
        cin >> input;
        if(input == "Y" || input == "y"){
            drawInSteps = true;
        }
    #endif
    




    // Select one mazes
    // If it´s a random Maze, ask for column and row length
    // Print all available Algorithms
}

void setup() {
    userInput();
    maze = Maze(mazeNo, startX, startY, endX, endY, columns, rows);
    xd::size(1200, 900);
    printTableHeader();
    if(algorithmNo == 0){
        path = breadth_first_search(maze);
    }else if (algorithmNo == 1){
        path = breadth_first_search_optimized(maze);
    }else if (algorithmNo == 2){

    }else if (algorithmNo == 3){
        benchmark();
    }
    if(!drawInSteps){
        pathWidth = path.size();
    }
}

void draw() {
    // Draw Labyrinth
    xd::fill(glm::vec4(1, 1, 1, 1));
    xd::rect(0, 0, tileSize * (maze.getRows() + 2), tileSize * (maze.getColumns() + 2));
    for(int x = 0; x < maze.getRows() ; x++){
        for(int y = 0; y < maze.getColumns(); y++){
            if(maze.getTile(y, x)) {
                Tile* tile = maze.getTile(y, x);
                int xStart = tile->getX() + tileSize;
                int yStart = tile->getY() + tileSize;
                xd::fill(tile->getColor());
                xd::strokeWeight(0);
                xd::rect(xStart,  yStart, tileSize, tileSize);
                xd::strokeWeight(2);
                xd::stroke(glm::vec4(0, 0, 0, 1));
                if (!tile->getTop()) {
                    xd::line(xStart, yStart, xStart + tileSize, yStart);
                }
                if (!tile->getRight()) {
                    xd::line(xStart + tileSize, yStart, xStart + tileSize, yStart + tileSize);
                }
                if (!tile->getBottom()) {
                    xd::line(xStart, yStart + tileSize, xStart + tileSize, yStart + tileSize);
                }
                if (!tile->getLeft()) {
                    xd::line(xStart, yStart, xStart, yStart + tileSize);
                }
            }
        }
    }
    // Draw path
    xd::strokeWeight(1);
    xd::stroke(glm::vec4(1.0f, 0.8f, 0.1f, 1.0f));

    if(path.size() > 0){
        if(pathWidth <= path.size()){
            pathWidth++;
        }else{
            xd::noLoop();
        }
        for(int i = 0; i < pathWidth; i++){
            Tile start = get<0>(path[i]);
            Tile end = get<1>(path[i]);;
            xd::line(start.getX() + tileSize / 2 + tileSize, start.getY() + tileSize / 2 + tileSize, end.getX() + tileSize / 2 + tileSize, end.getY() + tileSize / 2 + tileSize);
        }
    }

}

void destroy() {
}

#ifndef makeGUI
int main(){
    setup();
    //draw();
    //destroy();
    return 0;
}
#endif