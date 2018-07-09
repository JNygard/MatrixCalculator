#include "squarematrix.h"


SquareMatrix::~SquareMatrix(){}

ostream& operator<<(ostream& os, SquareMatrix& obj) {
    return os << obj.toString();
}
