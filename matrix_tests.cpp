//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <map>
#include "telement.h"
#include "elementarysquarematrix.h"
#include "compositematrix.h"

using namespace std;

using Valuation = std::map<char, int>;

TEST_CASE( "", "[g]" ) {


    string s1 = "[[1,2][3,4]]";
    string s3 = "[[5,6][7,8]]";
    string s4 = "[[2,4][2,3]]";
    string s1transpose = "[[2,-4][1,3]]";
    string s2 = "[[c,-1][s,23]]";
    string s2transpose = "[[c,s][-1,23]]";

    ConcreteSquareMatrix cm1x(s1);
    ConcreteSquareMatrix cm2x(s3);
    SymbolicSquareMatrix sm1x(s2);


    CSMFunction implPlus = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a+b;};
    CSMFunction impMultiply = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a*b;};
    CSMFunction impMinus = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a-b;};
    Valuation valu;
    valu.insert(pair<char, int>('c', 55));
    valu.insert(pair<char, int>('s', 44));

    //Composite matrix plus
    CompositeSquareMatrix cmX(cm1x,cm2x, implPlus, '+');
    CHECK(cmX.toString()=="([[1,2][3,4]]+[[5,6][7,8]])");
    CompositeSquareMatrix cmZ(CompositeSquareMatrix(cm1x,cm2x, implPlus, '+'));
    CHECK(cmX.toString()==cmZ.toString());
    CompositeSquareMatrix cmY(std::move(CompositeSquareMatrix(cmX)));
    CHECK(cmX.toString()==cmY.toString());
    CompositeSquareMatrix cmT = cmX;
    CHECK(cmX.toString()==cmY.toString());
    CompositeSquareMatrix cmJ(std::move(cmX));

    //Compositematrix multiply
    CompositeSquareMatrix comMu1(cm1x,cm2x, impMultiply, '*');
    CHECK(comMu1.toString()=="([[1,2][3,4]]*[[5,6][7,8]])");
    CompositeSquareMatrix comMu2(cm1x,sm1x, impMultiply, '*');
    CHECK(comMu2.toString()=="([[1,2][3,4]]*[[c,-1][s,23]])");
    CompositeSquareMatrix comMu3 = comMu2;
    CHECK(comMu3.toString()==comMu2.toString());
    comMu3 = cmT;
    CHECK(comMu3.toString()==cmT.toString());


    //Compositematrix minus
    CompositeSquareMatrix comMi1(cm1x,cm2x, impMinus, '-');
    CHECK(comMi1.toString()=="([[1,2][3,4]]-[[5,6][7,8]])");




     //Symbolic squarematrix test
    SymbolicSquareMatrix sm(s1);
    SymbolicSquareMatrix sm2(s2);
    CHECK(sm.toString() == s1);
    CHECK(sm.toString() == s1);
    CHECK(sm2.transpose().toString() == s2transpose);
    sm = sm2;
    CHECK(sm.toString() == s2);
    sm = SymbolicSquareMatrix(s1);
    CHECK(sm.toString()==s1);
    sm = SymbolicSquareMatrix(SymbolicSquareMatrix(s3));
    CHECK(sm.toString()==s3);


    //Concrete squarematrix test
    ConcreteSquareMatrix cm3(s3);
    ConcreteSquareMatrix cm4(s4);
    cm3*=cm4;
    CHECK(cm3.toString() == "[[22,38][30,52]]");
    cm3 = ConcreteSquareMatrix("[[1,2][3,4]]");
    cm4 = ConcreteSquareMatrix(ConcreteSquareMatrix("[[5,6][7,8]]"));
    cm3+=cm4;
    CHECK(cm3==ConcreteSquareMatrix("[[6,8][10,12]]"));
    cm3-=cm4;
    CHECK(cm3.toString()=="[[1,2][3,4]]");
    cm3 = cm4;
    CHECK(cm3==cm4);
    CHECK(cm4.transpose().toString()=="[[5,7][6,8]]");

    //IntElement tests
    IntElement ie(3);
    IntElement ie2(3);
    VariableElement ve('c');
    VariableElement ve2('c');
    CHECK(ie==ie2);
    CHECK(ve==ve2);

    IntElement ie10 = IntElement(5) + IntElement(5);
    CHECK(ie10.getVal()==10);
    IntElement ie11 = IntElement(5) * IntElement(5);
    CHECK(ie11.getVal()==25);
    IntElement ie12 = IntElement(5) - IntElement(5);
    CHECK(ie12.getVal()==0);

    ie*=ie2;
    CHECK(ie.getVal()==9);
    ie-=ie2;
    CHECK(ie.getVal()==6);
    ie+=ie2;
    CHECK(ie.getVal()==9);
    ie.setVal(3);
    CHECK(ie.getVal()==3);
    CHECK(ie==ie2);

    //Variable element tests
    VariableElement vaa('a');
    VariableElement vab('b');
    VariableElement vac('c');
    CHECK(vac==VariableElement('c'));
    CHECK(vac.toString()=="c");
    CHECK(vac.toString()!="d");
    vaa.setVal('g');
    CHECK(vaa.toString()=="g");
    CHECK(vaa.getVal()=='g');
    vaa = VariableElement('a');
    CHECK(vaa==VariableElement('a'));
    vaa.setVal('b');
    CHECK(vaa==vab);


}


