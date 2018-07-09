#ifndef ELEMENT_H
#define ELEMENT_H
#include <ostream>
#include <ostream>
#include <memory>
#include <iostream>
#include <map>


using Valuation = std::map<char, int>;

using namespace std;

class Element{
    public:
        virtual ~Element();
        virtual Element* clone() = 0;
        virtual std::string toString() = 0;
        virtual int evaluate(const Valuation& val) = 0;

};

 ostream& operator<<(ostream& os, Element& obj);

typedef std::unique_ptr<Element> uniq_Elem_ptr;

#endif // ELEMENT_H
