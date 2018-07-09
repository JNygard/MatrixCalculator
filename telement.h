#ifndef TELEMENT_H
#define TELEMENT_H
#include <memory>
#include <iostream>
#include <map>
#include "element.h"


template <class T>
class TElement : public Element{
    private:
        T val;
    public:
        TElement(){
        }
        TElement(T v){
            val = v;
        }
        ~TElement(){
        }

        T getVal(){
            return val;
        }
        void setVal(T v){
            val = v;
        }

        Element* clone(){
            Element *pElem = new TElement(val);
            return pElem;
        }
        std::string toString();

        bool operator==(const TElement<T>& other){
            return val==other.val;
        }
        bool operator==(const TElement<T>& other) const{
            return val==other.val;
        }



        int evaluate(const Valuation& v);

        //ONLY IntElement
        TElement<T>& operator+=(const TElement<T>& other);

        TElement<T> operator+(const TElement<T>& other);

        TElement<T>& operator-=(const TElement<T>& other);

        TElement<T> operator-(const TElement<T>& other);

        TElement<T>& operator*=(const TElement<T>& other);

        TElement<T> operator*(const TElement<T>& other);

};

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

typedef std::unique_ptr<IntElement> uniq_intelem_ptr;

#endif // TELEMENT_H
