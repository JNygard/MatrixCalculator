#ifndef COMPOSITESQUAREMATRIX_H
#define COMPOSITESQUAREMATRIX_H

#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "element.h"

#include "telement.h"

#include "squarematrix.h"
//#include "concretematrix.h"
#include "elementarysquarematrix.h"

#include <functional>
using namespace std;

using Valuation = std::map<char, int>;
using CSMFunction =  std::function<ConcreteSquareMatrix(const ConcreteSquareMatrix&,const ConcreteSquareMatrix&)>;

class CompositeSquareMatrix : public SquareMatrix{

private:
    uniq_sqm_ptr oprnd1;
    uniq_sqm_ptr oprnd2;
    CSMFunction oprtor;
    char op_sym;

public:
    //Constructors
    CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2,
        const CSMFunction& opr,char ops);
    CompositeSquareMatrix(const CompositeSquareMatrix& m);
    CompositeSquareMatrix(CompositeSquareMatrix&& m);
    ~CompositeSquareMatrix();

    //Copy and move operators
    CompositeSquareMatrix& operator=(const CompositeSquareMatrix& other);
    CompositeSquareMatrix& operator=(CompositeSquareMatrix&& other);


    SquareMatrix* clone() const;
    void print(std::ostream &os) const;
    std::string toString() const;
    ConcreteSquareMatrix evaluate(const Valuation& val) const;

};


#endif // COMPOSITESQUAREMATRIX_H
