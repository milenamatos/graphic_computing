#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define LIMIT 200
float angulo = 0.0;
int opcao = 0;
int tempoInicial = LIMIT;
int animacao = 0;

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

  //base
  glPushMatrix();
    glTranslatef(0.0, -6.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(1, 6, 30, 30);
  glPopMatrix();

  glRotatef(angulo, 0.0, 0.0, 1.0);
  
  //centro
  glPushMatrix();
    glutWireSphere(1.0, 20, 20);
  glPopMatrix();

  //red
  glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.8, 3.0, 50, 50);
  glPopMatrix();

  //blue
  glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(-90, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.8, 3.0, 50, 50);
  glPopMatrix();

  //green
  glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
     glRotatef(180, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.8, 3.0, 50, 50);
  glPopMatrix();

  //yellow
  glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-1.0, 0.0, 0.0);
     glRotatef(90, 0.0, 0.0, 1.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutWireCone(0.8, 3.0, 50, 50);
  glPopMatrix();

  glutSwapBuffers();
}

void anima(int value)
{
  if (animacao == 0)
    animacao = 1;

  switch (opcao) {
    case 1: 
      opcao = 0;
      tempoInicial += 5;
      if (tempoInicial >= LIMIT) 
        tempoInicial = LIMIT;
      break;
    case 2: 
      opcao = 0;
      tempoInicial -= 5;
      if (tempoInicial <= 0) 
        tempoInicial = 2;
      break;
    case 3: 
      tempoInicial += 5;
      if (tempoInicial >= LIMIT) {
        tempoInicial = LIMIT;
        opcao = 0;
      }
      break;
    case 4: 
      tempoInicial -= 5;
      if (tempoInicial <= 0) {
        tempoInicial = 2;
        opcao = 0;
      }
      break;
    default: 
      break;
  }

  angulo -= (tempoInicial < 15) ? 1 : 5;
  if (angulo == -360) {
    angulo = 0;
  }
  if (tempoInicial < LIMIT) {
    glutPostRedisplay();   
    glutTimerFunc(tempoInicial, anima, 1);
  } else {
    animacao = 0;
  }
}

void rotacoes(int key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_LEFT:
      opcao = 1;     
      break;
    case GLUT_KEY_RIGHT:
      opcao = 2;
      if (animacao == 0) {
        glutTimerFunc(LIMIT, anima, 1);
      }
      break;
    default:
      break;
  }
}

void mouseClick(int botao, int estado, int x, int y){
    switch (botao) {
        case GLUT_LEFT_BUTTON:
            if(estado==GLUT_DOWN) {              
              opcao = 4;
              if (animacao == 0) 
                glutTimerFunc(LIMIT, anima, 1);
            }
            break;
            
        case GLUT_RIGHT_BUTTON:
            if(estado==GLUT_DOWN) {
              opcao = 3;
            }
            break;
            
        default:
            break;
    }
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Objetos 3D - Catavento");
  glutDisplayFunc(display);
  glutSpecialFunc(rotacoes);
  glutMouseFunc(mouseClick);
  init();
  glutMainLoop();
}