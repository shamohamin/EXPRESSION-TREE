#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#define _USE_MATH_DEFINES 

void display1();
void draw_circle() ;
void setup() {   glClearColor(1.0f, 1.0f, 1.0f, 1.0f); }

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    // glRectf(-0.75f,0.75f, 0.75f, -0.75f);
    // glBegin(GL_LINES);
    //     glVertex3f(0.0 , 0.0 , 0);
    //     glVertex3f(15 , 0.0 , 0);
    // glEnd();
    glEnableClientState(GL_VERTEX_ARRAY);
    display1() ;
    draw_circle();
    glDisableClientState(GL_VERTEX_ARRAY) ;
    glutSwapBuffers();
}

void display1(){
    GLfloat lineVertices[] = {
        0 - 0.05 , 0  + 0.9, 0 ,
        0.2 - 0.05, -0.2 + 0.9, 0 
    };
    glVertexPointer(3 , GL_FLOAT , 0 , lineVertices) ;
    glDrawArrays(GL_LINES , 0 , 2) ;
}

void draw_circle(){
    float radius = 0.05 ;
    float x1,y1,x2,y2;
    x1 = 0.5,y1=0.6;
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);

            // for (int i = 0; i <1000; i++)
        // {
            // double x = r * cos(i) ;
            // double y = r * sin(i) ;
            // glVertex3f(x ,y ,0);
    
            // x = r * cos(i) ;
            // y = r * sin(i) ;
            // glVertex3f(x,y,0);

        // glVertex3f(cos(2*3.14159*i/1000.0),sin(2*3.14159*i/1000.0),0);
    // }
    for (float angle=1.0f;angle<361.0f;angle+=0.2)
    {
        x2 = x1+sin(angle)*radius;
        y2 = y1+cos(angle)*radius;
        glVertex2f(x2,y2);
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH) ;
}

int main(int argc, char *argv[])
  {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
     glutInitWindowSize(2000,2000);
     glutCreateWindow("Hello World");

     setup();
     glutDisplayFunc(display);
     glutMainLoop();
     return 0;
  }