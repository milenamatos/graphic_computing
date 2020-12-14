#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.141592654

float theta = 0.0;

void circulo()
{
  int i;
  float angulo = 0.0;
  glBegin(GL_POLYGON);
  for (i = 0; i <= 50; i++)
  {
    angulo = 2 * PI * i / 50.0;
    glVertex2f(0.125 * cos(angulo), 0.125 * sin(angulo));
  }
  glEnd();
}

void desenha()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);

  //miolo
  glPushMatrix();
  glColor3f(0.52, 0.35, 0.17); //marrom
  glScalef(2.0, 2.0, 1);
  circulo();
  glPopMatrix();

  //petalas
  glPushMatrix();
  glRotatef(theta, 0.0, 0.0, 1.0);
  float ang = 0.0;
  for (int i = 0; i <= 10; i++)
  {
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0); //amarelo
    ang = 2 * PI * i / 10.0;
    glTranslatef(0.5 * cos(ang), 0.5 * sin(ang), 0.0);
    circulo();
    glPopMatrix();
  }
  glPopMatrix();

  glFlush();
}

void tecladoEspecial(int tecla, int x, int y)
{
  switch (tecla)
  {
  case GLUT_KEY_RIGHT:
    theta += 5;
    break;
  case GLUT_KEY_LEFT:
    theta -= 5;
    break;

  default:
    break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(400, 400);
  glutCreateWindow("Girassol");
  glutDisplayFunc(desenha);
  glutSpecialFunc(tecladoEspecial);
  glutMainLoop();
  return 0;
}