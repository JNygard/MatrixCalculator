#include "compositematrix.h"


//Constructors

CompositeSquareMatrix::CompositeSquareMatrix(const SquareMatrix& op1, const SquareMatrix& op2, const CSMFunction& opr,char ops){
    oprnd1 = uniq_sqm_ptr(op1.clone());
    oprnd2 = uniq_sqm_ptr(op2.clone());
    oprtor = opr;
    op_sym = ops;
}
CompositeSquareMatrix::CompositeSquareMatrix(const CompositeSquareMatrix& m){
    oprnd1 = uniq_sqm_ptr(m.oprnd1->clone());
    oprnd2 = uniq_sqm_ptr(m.oprnd2->clone());
    oprtor = m.oprtor;
    op_sym = m.op_sym;
}
CompositeSquareMatrix::CompositeSquareMatrix(CompositeSquareMatrix&& m){
    oprnd1 = std::move(m.oprnd1);
    oprnd2 = std::move(m.oprnd2);
    oprtor = std::move(m.oprtor);
    op_sym = m.op_sym;
}
CompositeSquareMatrix::~CompositeSquareMatrix(){}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(const CompositeSquareMatrix& m){

    if(&m == this)
        return *this;

    oprnd1 = uniq_sqm_ptr(m.oprnd1->clone());
    oprnd2 = uniq_sqm_ptr(m.oprnd2->clone());
    oprtor = m.oprtor;
    op_sym = m.op_sym;
    return *(this);//
}

CompositeSquareMatrix& CompositeSquareMatrix::operator=(CompositeSquareMatrix&& m){

    oprnd1 = std::move(m.oprnd1);
    oprnd2 = std::move(m.oprnd2);
    oprtor = std::move(m.oprtor);
    op_sym = m.op_sym;

    return *(this);//
}


//Clone
SquareMatrix* CompositeSquareMatrix::clone()const{
    return new CompositeSquareMatrix(*this);
}

//Print
void CompositeSquareMatrix::print(std::ostream &os)const{
    os << toString();
}

//ToString
std::string CompositeSquareMatrix::toString() const{
    std::ostringstream oss;
    oss << "(" << (*oprnd1).toString() << op_sym << (*oprnd2).toString() << ")";
    std::string s = oss.str();

    return s;
}

//Evaluate
 ConcreteSquareMatrix CompositeSquareMatrix::evaluate(const Valuation& val)const{

    ConcreteSquareMatrix cm1 = (*oprnd1).evaluate(val);
    ConcreteSquareMatrix cm2 = (*oprnd2).evaluate(val);
    return  oprtor(cm1,cm2);
 }
