#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float px = 0.0, py = 0.0;

void ponto(){
    glPointSize(5.0);
    glBegin(GL_POINTS);
        glVertex2f(px, py);
    glEnd();
}

void desenha(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    ponto();
    glFlush();
}

void mouse(int botao, int estado, int x, int y){
    switch (botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN) {
                printf("x = %i, y = %i\n",x,y);
                px = (x/200.0)-1.0;
                py = -((y/200.0)-1.0);
            }
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
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Atividade 01 - Ponto Azul");
    glutDisplayFunc (desenha);
    glutMouseFunc(mouse);
    glutMainLoop ();
    return 0;
}