
#include "Trail.h"


Trail::Trail() {
   length = 0;
   breadcrumbs = new Breadcrumb*[0];
}

Trail::~Trail() {
   delete[] &breadcrumbs;
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
   //make the trail longer, copy the old one and add the next crumb.
   length++;
   Breadcrumb **newTrail = new Breadcrumb *[length];
   std::copy(breadcrumbs, breadcrumbs + (length - 1), newTrail);
   delete [] breadcrumbs;
   newTrail[length - 1] = t;
   breadcrumbs = newTrail;
}

bool Trail::contains(int x, int y) {
   //check each breadcrumb in array, compare bc's x and y to parameter x and y
   bool crumbExists = false;

   for (int i = 0; i < length; i++) {
      Breadcrumb crumb = *breadcrumbs[i];
      if (crumb.getX() == x && crumb.getY() == y) {
         crumbExists =  true;
      }
   }

   return crumbExists;
}
