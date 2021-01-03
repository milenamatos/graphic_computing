#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float angZ = 0.0;
float angY = 0.0;
int opcao = 3;
//1 e 2 movimenta o chapéu pra direita e esquerda
//3 e 4 movimenta o rosto do palhaco pra direita e esquerda

void init()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-7.0, 7.0, -7.0, 7.0, -7.0, 7.0);
  glPushMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  glPopMatrix();
  glPushMatrix();

  glRotatef(angY, 0.0, 1.0, 0.0);
  glutWireSphere(3, 30, 30);

  //nariz
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.5, 3.0);
    glutWireSphere(0.5, 20, 20);
  glPopMatrix();

  //olhos
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
    glTranslatef(-1.8, 0.5, 3.0);
    glutWireSphere(0.5, 20, 20);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(1.8, 0.5, 3.0);
    glutWireSphere(0.5, 20, 20);
  glPopMatrix();
  //detalhe acima do olho
  glColor3f(0.0, 0.0, 1.0);
  glPushMatrix();
    glTranslatef(-1.8, 1.0, 3.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.3, 0.8, 20, 20);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(1.8, 1.0, 3.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.3, 0.8, 20, 20);
  glPopMatrix();

  //chapeu
  glRotatef(angZ, 0.0, 0.0, 1.0);
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.5, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(2.0, 3.5, 50, 50);
  glPopMatrix();

  glutSwapBuffers();
}

void anima(int value)
{
  switch (opcao)
  {
    case 1:
      angZ += 5;
      if (angZ + 5 >= 45)
        opcao = 2;
      break;
    case 2:
      angZ -= 5;
      if (angZ - 5 <= -45)
        opcao = 1;
      break;
    case 3:
      angY += 5;
      break;
    case 4:
      angY -= 5;
      break;
    default:
      break;
  }
  glutPostRedisplay();
  glutTimerFunc(100, anima, 1);
}

void rotacoes(int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_UP:
      opcao = 1;
      break;
    case GLUT_KEY_DOWN:
      opcao = 2;
      break;
    case GLUT_KEY_LEFT:
      opcao = 3;
      break;
    case GLUT_KEY_RIGHT:
      opcao = 4;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Objetos 3D - Palhaco");
  glutDisplayFunc(display);
  glutSpecialFunc(rotacoes);
  glutTimerFunc(100, anima, 1);
  init();
  glutMainLoop();
}