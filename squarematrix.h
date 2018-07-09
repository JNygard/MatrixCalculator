#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include <ostream>
#include <string>
#include "element.h"
#include "telement.h"

using namespace std;


template <typename T>
class ElementarySquareMatrix;


class SquareMatrix{

    public:
        virtual ~SquareMatrix();
        virtual SquareMatrix* clone() const = 0;
        virtual void print(std::ostream &os) const = 0;
        virtual std::string toString() const = 0;
        virtual ElementarySquareMatrix<IntElement> evaluate(const Valuation& val) const = 0;
};
 ostream& operator<<(ostream& os, SquareMatrix& obj);

typedef std::unique_ptr<SquareMatrix> uniq_sqm_ptr;

#endif // SQUAREMATRIX_H
