#include "telement.h"


//Operators

template<>
TElement<int>& TElement<int>::operator+=(const TElement<int>& other){
    val+=other.val;
    return(*this);
}
template<>
TElement<int> TElement<int>::operator+(const TElement<int>& other){
    int i = val+other.val;
    TElement<int> ies(i);
    return ies;
}


template<>
TElement<int>& TElement<int>::operator-=(const TElement<int>& other){
    val-=other.val;
    return(*this);
}
template<>
TElement<int> TElement<int>::operator-(const TElement<int>& other){
    int i = val-other.val;
    TElement<int> ies(i);
    return ies;
}


template<>
TElement<int>& TElement<int>::operator*=(const TElement<int>& other){
    val*=other.val;
    return(*this);
}
template<>
TElement<int> TElement<int>::operator*(const TElement<int>& other){
    int i = val*other.val;
    TElement<int> ies(i);
    return ies;
}


//ToString
template<>
std::string TElement<int>::toString(){
    return std::to_string(val);
}
template<>
std::string TElement<char>::toString(){
    std::string s(1, val);
    return s;
}

//Evaluate
template<>
int TElement<int>::evaluate(const Valuation& v){
    return val;
}
template<>
int TElement<char>::evaluate(const Valuation& v){
    return v.at(val);
}



/*
std::ostream& operator<<(ostream& os,  IntElement& el){
    os << el.getVal();
    return os;
}
*/
