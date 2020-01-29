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
#include <ctype.h>
#include <vector>
// #define size 80
using namespace std ;

struct Node {
    Node *left ;
    Node *right;
    char value;

    Node(char value) : value(value) , left(nullptr) , right(nullptr){};

};


map <char,int> precedence ;
stack <char> operators ;
stack <string> numbers;
int last_precedence = 0 ;
string postfix = "";
Node *root = nullptr;
int value ;
// string post[10000] ;
vector<string> post ; 

bool find_operator(char) ;
bool checker(char) ;
void pop_operators(char , int &) ;
void pop_inside_practense(int &) ;
int calculate(string first_element , string last_elemnt , char op);
void display_tree(Node *root , float x , float y ,float vgap , float hgap);
int calculate_the_value_of_postfix();
Node * make_tree() ;
void display() ;

void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); }

int main(int argc, char *argv[]) {
    
    // cout << "hello " ;
    string infix = "1-2^2^2222^4442^2" ;
    
    // char * hold = &argv[1][0] ;
    // cout << argv[1] ;
    // for(;*hold != '\0';hold++)
        // infix += *hold ;
    // infix = "2+(3^(4*2))+8+8";
    string str = "";
    int index = 0 ;

    // str += "#" ;
    // for(int i = 0 ; i < infix.length() ; i++){
    //     if(!isdigit(infix.at(i))){
    //         if (infix.at(i) != '(')
    //             str += '#';
    //         str+= infix.at(i) ;
    //         index = i ;
    //     }else{
    //         str += infix.at(i) ;
    //     }
    //     // str.at(index) = '#';
    // }

    //     if(!isdigit(infix.at(i))){
    //         if (infix.at(i) != '(')
    //             str += '#';
    //         str+= infix.at(i) ;
    //         index = i ;
    //     }else{
    //         str += infix.at(i) ;
    //     }
    //     // str.at(index) = '#';
    // }

    //     if(!isdigit(infix.at(i))){
    //         if (infix.at(i) != '(')
    //             str += '#';
    //         str+= infix.at(i) ;
    //         index = i ;
    //     }else{
    //         str += infix.at(i) ;
    //     }
    //     // str.at(index) = '#';
    // }

    //     if(!isdigit(infix.at(i))){
    //         if (infix.at(i) != '(')
    //             str += '#';
    //         str+= infix.at(i) ;
    //         index = i ;
    //     }else{
    //         str += infix.at(i) ;
    //     }
    //     // str.at(index) = '#';
    // }

    // str+="#";

    // cout << str << endl;

    //exit(1);
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    // glutInitWindowSize(2000,2000);
    // glutCreateWindow("Expression Tree");

    precedence['+'] = 1 ;
    precedence.insert(pair<char , int>('-' , 1)) ;
    precedence['/'] = 2 ;
    precedence['*'] = 2 ;
    precedence['^'] = 3 ;

    
    int counter = 0;
    try {
        for (int i = 0; i < infix.length(); i++) {
            char hold = infix.at(i);
            if (!find_operator((char) hold) && hold != '(' && hold != ')'){
                postfix += hold ;
                int j = i;
                string num = "";

                while (j < infix.length()&& (find_operator(infix.at(j)) == false) && infix.at(j) != '(' && infix.at(j) != ')'){
                    num += infix.at(j) ;
                    j++ ;
                }
                post.push_back(num) ;
                counter++;
                i = j - 1;
                // cout << post[counter - 1] <<  " ";
            } else {
                if(hold == '('){
                    operators.push(hold);
                    last_precedence = 0 ;
                }else if(hold == ')'){
                    pop_inside_practense(counter) ;
                }else{
                    if(checker(hold)) operators.push(hold) ;
                    else pop_operators(hold , counter) ;
                }
            }
            // cout << postfix << endl ;
        }
    }catch (const char *err){
        cout << err << endl ;
    }

    while(!operators.empty()){
        string str1 = "" ;
        char h = operators.top() ;
        postfix += h ;
        operators.pop() ;
        str1 += h ;
        post.push_back(str1) ;
    }

    cout << postfix << endl;
    for(int i = 0 ; i < post.size() ; i++)
        cout << post[i] << " ";

    exit(1);
    value = calculate_the_value_of_postfix() ;
    cout << value << endl ;

    sleep(1);

    root = make_tree() ;

    // display_tree(::root ,0.05 ,0.9 , 0.2 , 0.2);   

    // cout << root->value << endl ;

    // setup();
    // glutDisplayFunc(display);
    // glutMainLoop();

    return 0;
}

//this functions is for poping inside the prantense
void pop_inside_practense(int &count){
    char operators_inside_stack = ' ' ;
    
    while(operators_inside_stack != '('){
        operators_inside_stack = operators.top() ;
        operators.pop();
        string str = "";
        if (operators_inside_stack == '(' || operators_inside_stack == ')'){
            continue ;
        }
        str += operators_inside_stack ;
        post.push_back(str);
        count++;
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
void pop_operators(char scanned_operator , int &count){

    map<char , int >::iterator it ;

    while(1){
        string str = "" ;
        char operator_precedence = operators.top() ;
        str += operator_precedence ;
        operators.pop();
        it = precedence.find(operator_precedence) ;
        last_precedence = it->second ;
        if(checker(scanned_operator)) {
            operators.push(operator_precedence);
            operators.push(scanned_operator);
            break;
        }else if (operators.empty()){
            postfix += operator_precedence ;
            post.push_back(str) ;
            count++;
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
        post.push_back(str) ;
        count++;   
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
        return (int)pow(stoi(last_elemnt) , stoi(first_element)) ;
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
    float radius = 0.005 ;
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
    glDisable(GL_POINT_SMOOTH);
}

void display_tree(Node *root , float x , float y ,float vgap , float hgap){
    // sleep(1);
    // fflush(stdout);
    // getc() ;
    if (root->left != nullptr){
        glLineWidth(5);
        glColor3f(0.0f, 1.0f, 0.0f);
        drawLine(x , y , -vgap , -hgap) ;
        display_tree(root->left , x - vgap , y - hgap , vgap/2  , hgap/2) ;
    }
    if(root->right != nullptr){
        glColor3f(0.0f, 0.0f, 1.0f);
        drawLine(x , y , vgap , -hgap) ;
        display_tree(root->right , x + vgap , y - hgap , vgap/2  , hgap/2 ) ;
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

    if(::root != nullptr) display_tree(::root ,0.05 ,0.9 , 0.2 , 0.2);   

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

