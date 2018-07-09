#ifndef ELEMENTARYSQUAREMATRIX_H
#define ELEMENTARYSQUAREMATRIX_H


#include <iostream>
#include <exception>
#include <memory>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

#include "squarematrix.h"
#include "element.h"
#include "telement.h"

using Valuation = std::map<char, int>;

template <typename T>
class ElementarySquareMatrix;

template <class T>
class ElementarySquareMatrix : public SquareMatrix{

    private:
        unsigned int n;
        std::vector<std::vector<std::unique_ptr<T>>> ptrElements;

    public:
        ElementarySquareMatrix(){
        }
        ~ElementarySquareMatrix(){
        }
        ElementarySquareMatrix(const ElementarySquareMatrix<T>& sm){
            *this = sm;
        }
        ElementarySquareMatrix(ElementarySquareMatrix<T>&& sm){
            n = sm.n;
            ptrElements = std::move(sm.ptrElements);
        }

        //Copy and move operators
        ElementarySquareMatrix& operator=(const ElementarySquareMatrix<T>& other){
                if(&other == this)
                    return *this;

                n = other.n;
                ptrElements.clear();

                for(auto &m_row:other.ptrElements){
                    std::vector<std::unique_ptr<T>> row;
                    for(auto &elem:m_row){
                        row.push_back(std::unique_ptr<T>(static_cast<T*>(elem->clone())));
                    }
                    ptrElements.push_back(std::move(row));
                }
                return(*this);
        }
        ElementarySquareMatrix& operator=(ElementarySquareMatrix<T>&& other){
            n = other.n;
            ptrElements = std::move(other.ptrElements);
            return(*this);
        }

        //Transpose
        ElementarySquareMatrix transpose(){
            ElementarySquareMatrix<T> rm;
            int i = 0;

            while(i<n){
                int e = 0;
                std::vector<std::unique_ptr<T>> newRow;
                while(e<n){
                    newRow.push_back(std::unique_ptr<T>(static_cast<T*>(ptrElements.at(e).at(i)->clone())));
                    e++;
                }
                rm.ptrElements.push_back(std::move(newRow));
                i++;
            }
            return rm;
        }


        bool operator==(const ElementarySquareMatrix<T>& other){
            return toString()==other.toString();
        }
        bool operator==(const ElementarySquareMatrix<T>& other) const{
            return toString()==other.toString();
        }

        std::string toString() const{
            std::ostringstream oss;
            oss << "[";
            for(auto& row:ptrElements){
                oss << "[";
                bool first = true;
                for(auto& elem:row){
                    if(!first)
                        oss << ",";
                    oss << (*elem).toString();
                    first = false;
                }
                oss << "]";
            }
            oss << "]";
            std::string s = oss.str();
            return s;
        }


        SquareMatrix* clone()const{
            return new ElementarySquareMatrix(*this);
        }

        void print(std::ostream &os)const{
            os << toString();
        }


        //Different ElementarySquareMatrix<IntElement> and ElementarySquareMatrix<Element>
        ElementarySquareMatrix(const std::string& s);
        ElementarySquareMatrix<IntElement> evaluate(const Valuation& val) const;


        //Only ElementarySquareMatrix<IntElement>
        ElementarySquareMatrix<T>( std::vector<std::vector< uniq_intelem_ptr >>& , int);

        ElementarySquareMatrix<T>& operator+=(const ElementarySquareMatrix<T>& other);
        ElementarySquareMatrix<T>& operator-=(const ElementarySquareMatrix<T>& other);
        ElementarySquareMatrix<T>& operator*=(const ElementarySquareMatrix<T>& other);

};

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2);
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2);
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2);

#endif // ELEMENTARYSQUAREMATRIX_H
