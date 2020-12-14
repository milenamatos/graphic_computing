#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.141592654

float theta=0.0, alpha=0.0;

void circulo(){
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
        for (i=0;i<=50;i++) {
            angulo= 2 * PI * i / 50.0;
            glVertex2f(0.125*cos(angulo), 0.125*sin(angulo));
        }
    glEnd ();
}

void linha(float ax, float ay, float bx, float by)
{
  glBegin(GL_LINES);
    glVertex2f(ax, ay);
    glVertex2f(bx, by);
  glEnd();
}

void desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    
    //cabeca
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glScalef(1.5, 1.0, 1.0);
    glTranslatef(0.0,0.8,0.0);
    circulo();
    glPopMatrix();
    
    //corpo
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.0,0.25,0.0);
    glScalef(2.5, 3.5, 1.0);
    circulo();
    glPopMatrix();

    //olhos
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-0.1,0.8,0.0);
    glScalef(0.2, 0.2, 1.0);
    circulo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1,0.8,0.0);
    glScalef(0.2, 0.2, 1.0);
    circulo();
    glPopMatrix();

    glPushMatrix();
    linha(-0.1, 0.8, 0.1, 0.8);
    glPopMatrix();

    //bracos
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-0.4,0.4,0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glScalef(1.5, 0.5, 1.0);
    circulo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4,0.4,0.0);
    glRotatef(-theta, 0.0, 0.0, 1.0);
    glScalef(1.5, 0.5, 1.0);
    circulo();
    glPopMatrix();

    //pernas
    glPushMatrix();
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glTranslatef(-0.1,-0.25,0.0);
    glScalef(0.5, 1.0, 1.0);
    circulo();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-alpha, 0.0, 0.0, 1.0);
    glTranslatef(0.1,-0.25,0.0);
    glScalef(0.5, 1.0, 1.0);
    circulo();
    glPopMatrix();
    
    glFlush();
}

void tecladoEspecial(int tecla, int x, int y){
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            if (theta+5<=25)
                theta+=5;
            break;
        case GLUT_KEY_LEFT:
            if (theta-5>=-25)
                theta-=5;
            break;
        case GLUT_KEY_UP:
            if (alpha-5<=10)
                alpha+=5;
            break;
        case GLUT_KEY_DOWN:
            if (alpha-5>=-25)
                alpha-=5;
            break;            
        default:
            break;
    }
    glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (500,600);
    glutCreateWindow ("Robo Baymax");
    glutDisplayFunc (desenha);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop ();
    return 0;
}