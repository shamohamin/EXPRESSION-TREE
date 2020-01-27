#include <iostream>
#include "map"
#include "iterator"
#include <string>
#include <stack>
#include <math.h>
#include <thread> 
#include <chrono>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
Node *root ;
int value ;

bool find_operator(char) ;
bool checker(char) ;
void pop_operators(char) ;
void pop_inside_practense() ;
int calculate(string first_element , string last_elemnt , char op);
int calculate_the_value_of_postfix();
Node * make_tree() ;
void display() ;

void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); }

int main(int argc, char *argv[]) {
    
    cout << "hello " ;
    string infix = "" ;
    char * hold = &argv[1][0] ;
    // cout << argv[1] ;
    for(;*hold != '\0';hold++)
        infix += *hold ;
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(2000,2000);
    glutCreateWindow("Expression Tree");

    precedence['+'] = 1 ;
    precedence.insert(pair<char , int>('-' , 1)) ;
    precedence['/'] = 2 ;
    precedence['*'] = 2 ;
    precedence['^'] = 3 ;

    

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

    // cout << postfix << endl;

    value = calculate_the_value_of_postfix() ;
    cout << value << endl ;

    root = make_tree() ;

    // cout << root->value << endl ;

    setup();
    glutDisplayFunc(display);
    glutMainLoop();

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
            // cout << "cal is : " << cal << endl ;
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

void drawLine(float x , float y , float vgap , float hgap){
    GLfloat lineVertices[] = {
        x  , y , 0 ,
        x + vgap , y + hgap , 0 
    };
    glVertexPointer(3 , GL_FLOAT , 0 , lineVertices) ;
    glDrawArrays(GL_LINES , 0 , 2) ;
}

void draw_circle(float x , float y){
    float radius = 0.1 ;
    float x2,y2;
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
        for (float angle=1.0f;angle<361.0f;angle+=0.2)
        {
            x2 = x + sin(angle)*radius;
            y2 = y + cos(angle)*radius;
            glVertex2f(x2,y2);
        }
    glEnd();
    glDisable(GL_POINT_SMOOTH) ;
}

void display_tree(Node *root , float x , float y ,float vgap , float hgap){
    // sleep(1000);
    // getc() ;
    if (root->left != nullptr){
        glLineWidth(5);
        glColor3f(0.0f, 1.0f, 0.0f);
        drawLine(x , y , -vgap , -hgap) ;
        display_tree(root->left , x - vgap , y - hgap , vgap  , hgap) ;
    }
    if(root->right != nullptr){
        glColor3f(0.0f, 0.0f, 1.0f);
        drawLine(x , y , vgap , -hgap) ;
        display_tree(root->right , x + vgap , y - hgap , vgap  , hgap ) ;
    }
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_circle(x , y) ;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(x, y,0.0);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, root->value);

} 

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);

    
    display_tree(::root ,0.05 ,0.9 , 0.2 , 0.2);    

    glRasterPos3f(-1, 0.8,0.0);
    char value_count[] = "the fucking value is : " ;
    for (char *value = value_count ;*value != '\0' ; value++)  
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *value);

    char *s = (char *)calloc(20,sizeof(char));
    string str = "" ;
    str += to_string(value) ;
    s = &str.at(0) ;
    // cout << s << endl ; 
    for(; *s != '\0' ; s++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);

    glDisableClientState(GL_VERTEX_ARRAY);
    glutSwapBuffers();
}

