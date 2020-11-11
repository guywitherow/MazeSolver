
#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale) {
   this->x = x;
   this->y = y;
   this->stale = stale;
}

Breadcrumb::~Breadcrumb() {
   //bool and two ints get delete as part of stack 
   //when object is marked as "deleted"
}

int Breadcrumb::getX() {
   return x;
}

int Breadcrumb::getY() {
   return y;
}

bool Breadcrumb::isStale() {
   return stale;
}

void Breadcrumb::setStale(bool stale) {
   this->stale = stale;
}
