/*
*   Milestone 4 (S3783428) Guy Witherow
  
   Approach
    My main approach was to get as much information into the 
    program as I could, and to mostly use throw away variables, rather
    than get any of the big ones (main::maze, MazeSolver::solution) involved,
    as this appears to be more trouble than it is worth.
   
   Issues
    For most items here, the main issue I had was simply understanding
    what I was working with. C++ was a big learning curve for me, as
    I had never really had much reason to understand memory managment.
    Milestone 4 gave me the most grief by far, as restructuring the program led
    to a lot of voodoo going on with my variables.
   
   Justification of Design
    Most of the code was made very early on, as I like to get projects done 
    early, or at least started early. This lead to some poorly 
    thought out code for C++ (despite being... okay in other languages)
    The main justification I want to make is using 2 distinct functions 
    to read in the maze: I had big issues trying to dynamicly make the 
    maze bigger as I went, and eventually I decided that figuring out
    the size, THEN allocating the maze to a static size array was the
    best approach.
   
   Analysis
    The largest maze I have managed to make this program handle is 75x70. 
    I tried a 100x100 maze but this caused some odd overflows, which 
    I suspect have something to do with expected sizes of the variables.
    It might be a bad part of my program, but it can do the 75*70 
    maze in about 2 seconds, so I think it is fairly efficient.
    I would have liked to have a slightly more robust program, able to 
    taken even larger mazes, but this will just be a downside of
    my solution for the time being.
*/


#include <iostream>
#include <string>
#include <fstream>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void inputMaze();
void readMazeStdin(Maze maze);
int width = 0;
int height = 0;
std::string input = "";

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

Maze make_maze(const int rows, const int cols);
void delete_maze(Maze maze, int rows, int cols);

int main(int argc, char **argv)
{

    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT" << 
    // "TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testBreadcrumb();
    // testTrail();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    inputMaze();

    //Load Maze from stdin
    Maze maze = make_maze(height + 1,width);
    readMazeStdin(maze);

    // Solve using MazeSolver
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    MazeSolver* solver = new MazeSolver();
    Trail* solution = new Trail();
    solver->solve(maze, height, width);
    solution = solver->getSolution();

    // Print Maze to stdout
    printMazeStdout(maze, solution);

    delete solver;


    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {

    char character = ' ';
    //read the maze in using the already
    //found width and height
    

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            character = input[((i * width) + j)];
            maze[i][j] = character;
        }
    }

}

void printMazeStdout(Maze maze, Trail* solution) {
    //make a new trail of fresh crumbs, as we can only
    //see if a crumb EXISTS at a certain x/y, but cannot
    //check if it is fresh.
    Trail* fresh = new Trail();
    for (int i = 0; i < solution->size(); i++) {
        if (!solution->getPtr(i)->isStale()) {
            fresh->addCopy(solution->getPtr(i));
        }
    }
    //if there are no fresh crumbs, no valid solution exists.

    int printX = -1;
    int printY = 0;
    while (printY < height)
    {
        while (printX < width)
        {
            //if fresh crumb exists, print star
            if (maze[printY][printX] == 'S' || maze[printY][printX] == 'E') {
                std::cout << maze[printY][printX];
            }
            else if (fresh->contains(printX, printY))
            {
                std::cout << "*";
            }
            //otherwise just print original maze tile
            else if (maze[printY][printX] != '\0') {
                std::cout << maze[printY][printX];
            }

            printX++;
        }
        printX = -1;
        printY++;
    }

    std::cout << std::endl;
    

    

    //PART 3
    //walk through fresh crumbs, checking difference to next crumb
    //to see what to print
    //starting the first, going to second last
    Breadcrumb* current = nullptr;
    Breadcrumb* next = nullptr;

    int diffX = 0;
    int diffY = 0;

    //cases:
    //-1 in x - move right/east
    //+1 in x - move left/west
    //-1 in y - move down/south
    //+1 in y - move up/north

    for (int i = 0; i < fresh->size() - 1;  i++) {
        current = fresh->getPtr(i);
        next = fresh->getPtr(i + 1);

        diffX = current->getX() - next->getX();
        diffY = current->getY() - next->getY();

        if (diffX == -1) {
            std::cout << "east" << std::endl;
        }
        else if (diffX == 1) {
            std::cout << "west" << std::endl;
        }
        else if (diffY == -1) {
            std::cout << "south" << std::endl;
        }
        else if (diffY == 1) {
            std::cout << "north" << std::endl;
        }
        else {
            //two breadcrumbs in the same position or 
            //more than 1 away from each other - broken
        }
    }

    //if we have no start point, also tell the user
    if (solution->size() == 0) {
        std::cout << "Maze has no start point" << std::endl;
    }
    else if (fresh->size() == 0) {
        std::cout << "Maze has no end point / maze has no solution" << std::endl;
    }
}

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;
    
    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
    //edited to make it less than 80 char per line
    std::cout << "PRINTING OUT A TRAIL IS" << 
    "AN EXERCISE FOR YOU TO DO" << std::endl;
}



//dynamic array allocation taken from code repository
Maze make_maze(const int rows, const int cols)
{
    Maze maze = nullptr;

    if (rows >= 0 && cols >= 0)
    {
        maze = new char *[rows];
        for (int i = 0; i != rows; ++i)
        {
            maze[i] = new char[cols];
        }
    }

    return maze;
}

void delete_maze(Maze maze, int rows, int cols)
{
    if (rows >= 0 && cols >= 0)
    {
        for (int i = 0; i != rows; ++i)
        {
            delete maze[i];
        }
        delete maze;
    }

    return;
}

//read the maze and find it's width and height
void inputMaze() {
    char character = ' ';
    bool foundWidth = false;
    //reading the input into a string
    while (!std::cin.eof())
    {
        std::cin.get(character);
        //if we have not set width, make it bigger
        if (!foundWidth)
        {
            width++;
        }
        //if we hit a return, decide if we have hit the end of the
        //maze, and also set the width if we have not already.
        if (character == '\n')
        {
            foundWidth = true;
            height++;
        }

        input.push_back(character);
        character = ' ';
    }

    height++;
}