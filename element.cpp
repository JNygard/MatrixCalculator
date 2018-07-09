#include "element.h"

Element::~Element(){};


ostream& operator<<(ostream& os, Element& obj) {
    return os << obj.toString();
}
