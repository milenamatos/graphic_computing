#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define BLUE '0'
#define RED '1'
#define GREEN '2'
#define YELLOW '3'
#define PURPLE '4'
#define ORANGE '5'
#define WHITE '6'
#define PINK '7'
#define GREY '8'
#define CYAN '9'

float px = 0.0, py = 0.0;
float colors[3] = {0.0, 0.0, 1.0};

void ponto()
{
  glPointSize(5.0);
  glBegin(GL_POINTS);
    glVertex2f(px, py);
  glEnd();
}

void desenha()
{
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(colors[0], colors[1], colors[2]);
  ponto();
  glFlush();
}

void teclado(unsigned char tecla, int x, int y)
{
  switch (tecla)
  {
    case BLUE:
      colors[0] = 0.0;
      colors[1] = 0.0;
      colors[2] = 1.0;
      break;
    case RED:
      colors[0] = 1.0;
      colors[1] = 0.0;
      colors[2] = 0.0;
      break;
    case GREEN:
      colors[0] = 0.0;
      colors[1] = 1.0;
      colors[2] = 0.0;
      break;
    case YELLOW:      
      colors[0] = 1.0;
      colors[1] = 1.0;
      colors[2] = 0.0;
      break;
    case PURPLE:      
      colors[0] = 0.5;
      colors[1] = 0.0;
      colors[2] = 0.5;
      break;
    case ORANGE:      
      colors[0] = 1.0;
      colors[1] = 0.64;
      colors[2] = 0.0;
      break;
    case WHITE:      
      colors[0] = 1.0;
      colors[1] = 1.0;
      colors[2] = 1.0;
      break;
    case PINK:      
      colors[0] = 1.0;
      colors[1] = 0.2;
      colors[2] = 0.6;
      break;
    case GREY:      
      colors[0] = 0.5;
      colors[1] = 0.5;
      colors[2] = 0.5;
      break;
    case CYAN:      
      colors[0] = 0.0;
      colors[1] = 1.0;
      colors[2] = 1.0;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void mouse(int botao, int estado, int x, int y)
{
  switch (botao)
  {
    case GLUT_LEFT_BUTTON:
      if (estado == GLUT_DOWN)
      {
        printf("x = %i, y = %i\n", x, y);
        px = (x / 200.0) - 1.0;
        py = -((y / 200.0) - 1.0);
      }
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
  glutCreateWindow("Atividade 02 - Ponto colorido");
  glutDisplayFunc(desenha);
  glutKeyboardFunc(teclado);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}