
#include "MazeSolver.h"

MazeSolver::MazeSolver() {
   
}

MazeSolver::~MazeSolver() {
   delete &solution;
}

void MazeSolver::solve(Maze maze, int width, int height)
{

   MazeSolver::solution = new Trail();

   //b
   int currentX = 0;
   int currentY = 0;
   //l
   int checkX = 0;
   int checkY = 0;

   //scan map for 'S' (start)
   //use foundStart to break out of for loop,
   //and also to detect errors in map file
   //look for a terminator for the end of a line, and two in
   //a row indicate the end of the maze
   bool foundStart = false;

   for (int i = 0; i < height - 1; i++) {
      for (int j = 0; j < width; j++) {
         if (maze[i][j] == 'S') {
            currentX = j;
            currentY = i;
            Breadcrumb* newCrumb = new Breadcrumb(j, i, false);
            solution->addCopy(newCrumb);
            foundStart = true;
            i = height;
            j = width;
         }
      }
   }



   if (foundStart == false)
   {

   }
   else
   {
      std::cout << "Found start, Searching..." << std::endl;
      // used for backtracking through our path
      int backtrackCounter = 1;
      bool checkIfMoved = false;
      bool backAtStart = false;

      //maze time
      do
      {
         checkIfMoved = false;

         //if no breadcrumb in current location, make one, and make it fresh
         if (!solution->contains(currentX, currentY))
         {
            Breadcrumb *newCrumb = new Breadcrumb(currentX, currentY, false);
            solution->addCopy(newCrumb);
         }

         //look for a place to go, N, E, S, W
         for (int i = 0; i < 4; i++)
         {
            if (i == 0)
            {
               checkX = currentX;
               checkY = currentY - 1;
            }
            else if (i == 1)
            {
               checkY = currentY;
               checkX = currentX + 1;
            }
            else if (i == 2)
            {
               checkX = currentX;
               checkY = currentY + 1;
            }
            else
            {
               checkY = currentY;
               checkX = currentX - 1;
            }
            //if the checked position has no crumb and is a valid path, move
            if (checkY >= 0 && checkX >= 0)
            {
               if (checkY <= height && checkX <= width)
               {
                  if ((maze[checkY][checkX] == OPEN || 
                  maze[checkY][checkX] == 'E') && 
                  !solution->contains(checkX, checkY))
                  {
                     currentX = checkX;
                     currentY = checkY;
                     i = 4;

                     checkIfMoved = true;
                     backtrackCounter = 1;
                  }
               }
            }
         }
         //if we didnt move, no valid forward move exists, so backtrack

         //get pointer for current and previous crumb,
         //set current to stale
         //move hansel back to previous crumb
         if (checkIfMoved == false)
         {
            int currentPosInTrail = solution->size() - backtrackCounter;

            if (currentPosInTrail == 0)
            {
               backAtStart = true;
            }
            else
            {
               Breadcrumb *currentCrumb = solution->getPtr(currentPosInTrail);
               Breadcrumb *nextCrumbBack = 
                           solution->getPtr(currentPosInTrail - 1);

               currentCrumb->setStale(true);
               currentX = nextCrumbBack->getX();
               currentY = nextCrumbBack->getY();

               backtrackCounter++;
            }
         }
      } while (maze[currentY][currentX] != 'E' && !backAtStart);

      if (maze[currentY][currentX] == 'E') {
         Breadcrumb *newCrumb = new Breadcrumb(currentX, currentY, false);
         solution->addCopy(newCrumb);
      }
   }
}

Trail *MazeSolver::getSolution()
{
   //setting up a new variable to get a deep trail
   Trail *deepSolution = new Trail();
   //new crumbs for all crumbs
   for (int i = 0; i < solution->size(); i++)
   {
      Breadcrumb *refCrumb = solution->getPtr(i);
      Breadcrumb *crumb = new Breadcrumb(refCrumb->getX(),
                    refCrumb->getY(), refCrumb->isStale());
      deepSolution->addCopy(crumb);
   }
   //return new trail with new crumbs
   return deepSolution;
}
