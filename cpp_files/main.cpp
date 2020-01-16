#include <iostream>
#include "map"
#include "iterator"
#include <string>
#include <stack>
#include <math.h>
#define size 80
using namespace std ;

struct Node {
    Node *left ;
    Node *right;
    char value;

    Node(char value) : value(value) , left(nullptr) , right(nullptr){};

};


map <char,int> precedence ;
stack <char> operators ;
int last_precedence = 0 ;
string postfix = "";

bool find_operator(char) ;
bool checker(char) ;
void pop_operators(char) ;
void pop_inside_practense() ;
int calculate(string first_element , string last_elemnt , char op);
int calculate_the_value_of_postfix();
Node * make_tree() ;

int main() {

    precedence['+'] = 1 ;
    precedence.insert(pair<char , int>('-' , 1)) ;
    precedence['/'] = 2 ;
    precedence['*'] = 2 ;
    precedence['^'] = 3 ;

    string infix= "1-2^3^3" ;

    try {
        for (int i = 0; i < infix.length(); i++) {
            char hold = infix.at(i);
            if (!find_operator((char) hold) && hold != '(' && hold != ')') postfix += hold;
            else {
                if(hold == '('){
                    operators.push(hold);
                    last_precedence = 0 ;
                }else if(hold == ')'){
                    pop_inside_practense() ;
                }else{
                    if(checker(hold)) operators.push(hold) ;
                    else pop_operators(hold) ;
                }
            }
        }
    }catch (const char *err){
        cout << err << endl ;
    }

    while(!operators.empty()){
        postfix += operators.top() ;
        operators.pop() ;
    }

    cout << postfix << endl;

    cout << calculate_the_value_of_postfix() << endl ;

    Node *root = make_tree() ;

    cout << root->value ;

    return 0;
}

//this functions is for poping inside the prantense
void pop_inside_practense(){
    char operators_inside_stack = ' ' ;

    while(operators_inside_stack != '('){
        operators_inside_stack = operators.top() ;
        operators.pop();
        if (operators_inside_stack == '(' || operators_inside_stack == ')'){
            continue ;
        }
        postfix += operators_inside_stack ;
    }
    operators_inside_stack = operators.top() ;
    operators.pop() ;
    map<char , int>::iterator it ;
    it = precedence.find(operators_inside_stack) ;
    last_precedence = it->second ;
    operators.push(operators_inside_stack) ;
}

//this function is for pop and insert operators to post fix expression
void pop_operators(char scanned_operator){

    map<char , int >::iterator it ;

    while(1){
        char operator_precedence = operators.top() ;
        operators.pop();
        it = precedence.find(operator_precedence) ;
        last_precedence = it->second ;
        if(checker(scanned_operator)) {
            operators.push(operator_precedence);
            operators.push(scanned_operator);
            break;
        }else if (operators.empty()){
            postfix += operator_precedence ;
            last_precedence = 0 ;
            operators.push(operator_precedence) ;
            break ;
        }else if(operator_precedence == '('){
            last_precedence = 0 ;
            operators.push(operator_precedence) ;
            operators.push(scanned_operator) ;
            break ;
        }
        postfix += operator_precedence ;
    }
}

//this function is for precedence check
bool checker(char precedence_char){

    map<char , int>::iterator it ;
    it = precedence.find(precedence_char) ;

    if(it->second > last_precedence){
        last_precedence = it->second ;
        return true ;
    }
    return false ;
}

//this function is for recognition of operators
bool find_operator(char single){
    switch(single){
        case '*' :
        case '+' :
        case '-' :
        case '/' :
        case '^' :
            return true ;
        default:
            return false ;
    }
}

int calculate_the_value_of_postfix(){
    stack <string> converter;

    for(int i = 0 ; i < postfix.length() ; i++){
        string str = "" ;
        if(find_operator(postfix.at(i)) == false) converter.push(str += postfix.at(i));
        else {  
            string first_element = converter.top();
            converter.pop() ;
            string second_element = converter.top() ;
            converter.pop() ;
            int cal = calculate(first_element , second_element , (char)postfix.at(i)) ;
            converter.push(to_string(cal)) ;
        }
    }

    return stoi(converter.top()) ;
}

int calculate(string first_element , string last_elemnt , char op){
    switch(op)
    {
    case '+':
        return (stoi(last_elemnt) + stoi(first_element)) ;
    case '-':
        return (stoi(last_elemnt) - stoi(first_element)) ;
    case '*':
        return (stoi(last_elemnt) * stoi(first_element)) ;
    case '/':
        return (stoi(last_elemnt) / stoi(first_element)) ;
    case '^':
        return pow(stoi(last_elemnt) , stoi(first_element)) ;
    default:
        break;
    }
    return 0 ;
}


Node *make_tree(){
    stack<Node *> node_holder ;

    for(int i = 0 ; i < postfix.length() ; i++){
        Node *t = (struct Node *)malloc(sizeof(struct Node)) ;
        if(!find_operator(postfix.at(i))){
            t = new Node(postfix.at(i)) ;
            node_holder.push(t) ;
        }else {
            t = new Node(postfix.at(i)) ;
            Node *left = (struct Node *)malloc(sizeof(struct Node)) ;
            Node *right = (struct Node *)malloc(sizeof(struct Node)) ; 
            right = node_holder.top() ;
            node_holder.pop() ;
            left = node_holder.top() ;
            node_holder.pop() ;
            t->right = right ;
            t->left = left ;
            node_holder.push(t) ;
        }
    }

    return node_holder.top() ;
}