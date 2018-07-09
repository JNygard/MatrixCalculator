#include "elementarysquarematrix.h"

//ElementarySquareMatrix<IntElement> constructor
template<>
ElementarySquareMatrix<IntElement>::ElementarySquareMatrix( std::vector<std::vector< uniq_intelem_ptr >>& elems, int elemN){
    ptrElements = std::move(elems);
    n = elemN;
}


//String constructors
template<>
ElementarySquareMatrix<IntElement>::ElementarySquareMatrix(const std::string& r){
    std::vector<uniq_intelem_ptr> rowVector;
    n=std::numeric_limits<int>::max();

    bool matrix_start = false;
    bool on_row = false;
    int rows = 0;
    int column = 0;
    int column_temp = 1;

    int number_length = 0;


    int l = r.length();
    int i = 0;

    if(l==0){
        throw(std::invalid_argument("1"));
    }
    while(i<l){


        //Row start
        if(r[i]=='[' && on_row==false){

            if(matrix_start){
                column_temp=1;
                on_row = true;
                //rowVector.clear();
                std::vector<uniq_intelem_ptr> rowVector;

            }else if(r[i+1]=='['){
                matrix_start = true;
            }else{
                throw(std::invalid_argument("2"));
            }



        //Row ends
        }else if(r[i]==']'&& on_row==true && isdigit(r[i-1])){
            if(rows==0){
                column=column_temp;
            }
            if(column_temp!=column){
                //Different length rows
                throw(std::invalid_argument("3"));
            }
            ptrElements.push_back(std::move(rowVector));
            rows++;
            on_row = false;

            //Matriw ends
            if((i+2)>=l){
                if(r[i+1]==']'){
                    break;
                }else{
                    throw(std::invalid_argument("4"));
                }
            }

        //Check that its number
        }else if(on_row==true && r[i]!=',' && r[i] != ']'&& r[i] != '['){
            if(!isdigit(r[i])){

                if (r[i]=='+' || r[i]=='-'){

                    //- and + are allowed only before number
                    if(!(isdigit(r[i+1]) && (r[i-1]==','|| r[i-1]=='['))){
                        throw(std::invalid_argument("5"));
                    }
                }else{
                    throw(std::invalid_argument("6"));
                }
            }

            if(r[i+1]==',' || r[i+1]==']'){

                if(number_length==0){
                    //IntElement ie(r[i]-'0');
                    //rowVector.push_back(std::unique_ptr<IntElement> (&ie));



                    rowVector.push_back(uniq_intelem_ptr(new IntElement(r[i]-'0')));

                }else{
                    std::ostringstream nstr;
                    while(number_length>0){

                        nstr << r[i-number_length];
                        number_length--;
                    }
                    nstr << r[i];
                    IntElement ie(std::stoi(nstr.str()));

                    //rowVector.push_back(ie);
                    rowVector.push_back(uniq_intelem_ptr(new IntElement(std::stoi(nstr.str()))));

                }
                number_length = 0;
            }else{
                number_length++;
            }

        //Comma -> new column
        }else if (r[i]==',' && isdigit(r[i-1])){
            column_temp++;

        //Not square matrix
        }else{
            cout << r[i] << endl;
            throw(std::invalid_argument("7"));
        }

        i++;
    }

    if(rows==column&&column>0){
        n = rows;
    }else{
        //Not square
        throw(std::invalid_argument("8"));
    }
}
template<>
ElementarySquareMatrix<Element>::ElementarySquareMatrix(const std::string& r){
    std::vector<uniq_Elem_ptr> rowVector;
    n=std::numeric_limits<int>::max();

    bool matrix_start = false;
    bool on_row = false;
    int rows = 0;
    int column = 0;
    int column_temp = 1;
    int number_length = 0;
    int l = r.length();
    int i = 0;

    if(l==0){
        throw(std::invalid_argument("1"));
    }
    while(i<l){


        //Row start
        if(r[i]=='[' && on_row==false){

            if(matrix_start){
                column_temp=1;
                on_row = true;
                //rowVector.clear();
                std::vector<uniq_Elem_ptr> rowVector;

            }else if(r[i+1]=='['){
                matrix_start = true;
            }else{
                throw(std::invalid_argument("2"));
            }

        //Row ends
        }else if(r[i]==']'&& on_row==true){
            if(rows==0){
                column=column_temp;
            }
            if(column_temp!=column){
                //Different length rows
                throw(std::invalid_argument("3"));
            }
            ptrElements.push_back(std::move(rowVector));
            rows++;
            on_row = false;

            //Matriw ends
            if((i+2)>=l){
                if(r[i+1]==']'){
                    break;
                }else{
                    throw(std::invalid_argument("4"));
                }
            }

        //Check that its number
        }else if(on_row==true && r[i]!=',' && r[i] != ']'&& r[i] != '['){
            if(!isdigit(r[i])){

                if (r[i]=='+' || r[i]=='-'){
                    //- and + are allowed only before number
                    if(!(isdigit(r[i+1]) && (r[i-1]==','|| r[i-1]=='['))){
                        throw(std::invalid_argument("5"));
                    }
                    number_length++;
                }else if( (r[i-1]==','||r[i-1]=='[') && (r[i+1]==','||r[i+1]==']') ){
                    rowVector.push_back(uniq_Elem_ptr(new VariableElement(r[i])));
                    number_length = 0;
                }else{
                    throw(std::invalid_argument("6"));
                }


            }else if(r[i+1]==',' || r[i+1]==']'){

                if(number_length==0){

                    rowVector.push_back(uniq_intelem_ptr(new IntElement(r[i]-'0')));

                }else{
                    std::ostringstream nstr;
                    while(number_length>0){

                        nstr << r[i-number_length];
                        number_length--;
                    }
                    nstr << r[i];
                    IntElement ie(std::stoi(nstr.str()));

                    rowVector.push_back(uniq_intelem_ptr(new IntElement(std::stoi(nstr.str()))));

                }
                number_length = 0;
            }else{
                number_length++;
            }

        //Comma -> new column
        }else if (r[i]==','){
            column_temp++;

        //Not square matrix
        }else{
            cout << r[i] << endl;
            throw(std::invalid_argument("7: " + r[i]));
        }

        i++;
    }

    if(rows==column&&column>0){
        n = rows;
    }else{
        //Not square
        throw(std::invalid_argument("8"));
    }
}


//Evaluate
template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::evaluate(const Valuation& val)const{
    return *this;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Element>::evaluate(const Valuation& val)const{
    std::vector<std::vector<uniq_intelem_ptr>> pelements;
    int i = 0;
    while(i<n){
        int e = 0;
        std::vector<uniq_intelem_ptr> newRow;
        while(e<n){
            Element* ve = ptrElements.at(i).at(e)->clone() ;

            if(typeid(*ve) == typeid(VariableElement)){
                newRow.push_back(uniq_intelem_ptr(  new IntElement(ve->evaluate(val))  ));
            }else{
                newRow.push_back(uniq_intelem_ptr(  static_cast <IntElement*>(ve)  ));
            }
            e++;
        }
        pelements.push_back(std::move(newRow));
        i++;
    }
    ElementarySquareMatrix<IntElement> rm(pelements, n);
    return rm;
}



//ElementarySquareMatrix<IntElement> operatros
template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator+=(const ConcreteSquareMatrix& other){
    if(n==other.n){
        vector<vector<uniq_intelem_ptr>>::iterator it = ptrElements.begin();
        vector<vector<uniq_intelem_ptr>>::const_iterator it_o = other.ptrElements.begin();

         for (it, it_o; it != ptrElements.end() && it_o!=other.ptrElements.end() ; ++it, ++it_o){
            vector<uniq_intelem_ptr>::iterator it2 = it -> begin();
            vector<uniq_intelem_ptr>::const_iterator it2_o = it_o -> begin();
            for(it2,it2_o ; it2 != it->end() && it2_o!=it_o->end(); ++it2,++it2_o){
                 *(*it2)+=*(*it2_o);
            }
        }

    }else{
        throw(std::invalid_argument("different size matrixes +"));
    }

    return(*this);
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator-=(const ConcreteSquareMatrix& other){
    if(n==other.n){
        vector<vector<uniq_intelem_ptr>>::iterator it = ptrElements.begin();
        vector<vector<uniq_intelem_ptr>>::const_iterator it_o = other.ptrElements.begin();

         for (it, it_o; it != ptrElements.end() && it_o!=other.ptrElements.end() ; ++it, ++it_o){
            vector<uniq_intelem_ptr>::iterator it2 = it -> begin();
            vector<uniq_intelem_ptr>::const_iterator it2_o = it_o -> begin();
            for(it2,it2_o ; it2 != it->end() && it2_o!=it_o->end(); ++it2,++it2_o){
                 *(*it2)-=*(*it2_o);
            }
        }

    }else{
        throw(std::invalid_argument("different size matrixes -"));
    }
    return(*this);
}
template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator*=(const ConcreteSquareMatrix& other){
    if(n!=other.n){
        throw(std::invalid_argument("different size matrixes *"));
    }
    ConcreteSquareMatrix sm1 =  *this;
    ConcreteSquareMatrix sm2 =  other;
    ptrElements.clear();
    int i = 0;

    while(i<n){
        int e = 0;
        std::vector<uniq_intelem_ptr> rm;
        while(e<n){

            IntElement matrixTemp(0);

            int v = 0;
            while(v<n){

                matrixTemp+= *(sm1.ptrElements.at(i).at(v)) * *(sm2.ptrElements.at(v).at(e)) ;
                v++;
            }
            rm.push_back(uniq_intelem_ptr(new IntElement(matrixTemp)));
            e++;
        }
        ptrElements.push_back(std::move(rm));
        i++;
    }
    return(*this);
}



//ConcreteSquareMatrix +, -, * operators
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2){
    ConcreteSquareMatrix ret = ConcreteSquareMatrix(o1);
    ret+=o2;
    return ret;
 }
 ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2){
    ConcreteSquareMatrix ret = ConcreteSquareMatrix(o1);
    ret-=o2;
    return ret;
 }
 ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& o1, const ConcreteSquareMatrix& o2){
    ConcreteSquareMatrix ret = ConcreteSquareMatrix(o1);
    ret*=o2;
    return ret;
 }

