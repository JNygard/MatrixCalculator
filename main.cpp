#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "matrix_tests.cpp"
#include <iostream>
#include <string>

#include <stdio.h>
#include <ctype.h>
#include <stack>

using namespace std;

bool isNumber(const std::string& s){
    return !s.empty() && std::find_if(s.begin(),s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

//If user gives invalid input
void invArg(){
    cout << "Try again" << endl;
}

//Printed at beginning
void printProgramInfo(){
    cout << "Matrix calculator" << endl;
    cout << "--------------------" << endl;
    cout << "quit: Exit program" << endl;
    cout << "[[x,x][x,x]]: Add new squarematrix (replace x with number or character)" << endl;
    cout << "+: Sums up the two last matrixes" << endl;
    cout << "-: Subtraction with the two last matrixes" << endl;
    cout << "*: Multiplys the two last matrixes" << endl;
    cout << "=: Valuates the two last matrixes" << endl;
    cout << "x=0: Adds new valuation (replace x with character and 0 with number)" << endl << endl;
}

int main(int argc, char *  argv[]){
    int result = Catch::Session().run(argc, argv);


    Valuation valu;
    stack<SymbolicSquareMatrix> mstack;


    printProgramInfo();

    //UI loop
    string ui = "";
    while(ui!="quit"){
        //Read user input
        cin >>ui;

        if(ui=="quit"){
            break;
        }else if(ui=="+"){
            //+
            if(mstack.size()>1){
                try{
                CSMFunction impl = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a+b;};
                SymbolicSquareMatrix sm1=mstack.top();
                mstack.pop();
                CompositeSquareMatrix csm(sm1,mstack.top(), impl, '+');
                mstack.push(sm1);

                    try{
                        mstack.push(SymbolicSquareMatrix(csm.evaluate(valu).toString()) );
                        cout << csm << " = " << csm.evaluate(valu).toString() << endl;
                    }catch(const std::out_of_range& ia){invArg();}

                }catch(const std::invalid_argument& ia){invArg();}

            }else{
                invArg();
            }
        }else if(ui=="*"){
            //*
            if(mstack.size()>1){
                try{
                CSMFunction impl = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a*b;};
                SymbolicSquareMatrix sm1=mstack.top();
                mstack.pop();
                CompositeSquareMatrix csm(sm1,mstack.top(), impl, '*');
                mstack.push(sm1);

                    try{
                        mstack.push(SymbolicSquareMatrix(csm.evaluate(valu).toString()) );
                        cout << csm << " = " << csm.evaluate(valu).toString() << endl;
                    }catch(const std::out_of_range& ia){invArg();}

                }catch(const std::invalid_argument& ia){invArg();}

            }else{
                invArg();
            }
        }else if(ui=="-"){
            //-
            if(mstack.size()>1){
                try{
                CSMFunction impl = [](ConcreteSquareMatrix a, ConcreteSquareMatrix b){return a-b;};
                SymbolicSquareMatrix sm1=mstack.top();
                mstack.pop();
                CompositeSquareMatrix csm(sm1,mstack.top(), impl, '-');
                mstack.push(sm1);

                    try{
                        mstack.push(SymbolicSquareMatrix(csm.evaluate(valu).toString()) );
                        cout << csm << " = " << csm.evaluate(valu).toString() << endl;
                    }catch(const std::out_of_range& ia){invArg();}

                }catch(const std::invalid_argument& ia){invArg();}

            }else{
                invArg();
            }
        }else if(ui=="="){
            //Evaluate last matrix
            if(mstack.size()>0){
                try{cout << mstack.top().evaluate(valu).toString() << endl;
                }catch(const std::out_of_range& ia){invArg();}
            }
        }else if(isalpha(ui.at(0))&& ui.at(1)=='='){
            //Add valuation
            int i = 2;
            if(ui.at(2)=='-')
                i=3;
            if(isNumber(ui.substr (i,ui.length()))){
                i = stoi(ui.substr (i,ui.length()));
                valu.insert(pair<char, int>(ui.at(0), i));
                cout << "Valuation added  " << ui.at(0) << "=" << valu.at(ui.at(0)) <<endl;
            }else
                invArg();
            cout << endl;
        }else{
            //Add matrix to stack
            try{
                SymbolicSquareMatrix sm(ui);
                mstack.push(sm);
                cout << sm << " added to stack" <<  endl;
            }catch (const std::invalid_argument& ia){
                invArg();
                //cout << ia.what();
            }
        }

        //Print all elements in stack
        stack<SymbolicSquareMatrix> temp = mstack;
        cout << endl << "Current stack: " << endl;
        while(temp.size()>0){
            cout << temp.top().toString() << endl;
            temp.pop();
        }
        cout << endl;

    }


    return 0;
}






