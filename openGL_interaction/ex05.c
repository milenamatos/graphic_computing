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

#define LINHA 'r' //reta
#define TRIANGULO 't'

float px[100], py[100];
float colors[3] = {0.0, 0.0, 1.0};
int pontos = 0;                                                                                                                                                                          
char figuraAtual = LINHA;

void triangulo()                    
{                                                                                                                                   
  glColor3f(colors[0], colors[1], colors[2]);
  if (pontos > 0) {
    glBegin(GL_TRIANGLES);
      for(int i = 0; i < pontos; i++)
        glVertex2f(px[i], py[i]);
    glEnd();
  }
}

void linha()                    
{                                                                                                                                   
  glColor3f(colors[0], colors[1], colors[2]);
  if (pontos > 0) {
    glBegin(GL_LINES);
      for(int i = 0; i < pontos; i++)
        glVertex2f(px[i], py[i]);
    glEnd();
  }
}

void desenha()
{
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);  
  if(figuraAtual==LINHA){
    linha();
  }
  else if(figuraAtual==TRIANGULO){
    triangulo();
  }
  glFlush();
}

void limpa () {
  pontos = 0;
  px[0] = 0.0;
  py[0] = 0.0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void teclado(unsigned char tecla, int x, int y)
{
  switch (tecla)
  {
    case LINHA:
        figuraAtual = LINHA;
        limpa();
        glClearDepth(1.0);
        break;
    case TRIANGULO:
        figuraAtual = TRIANGULO;
        limpa();      
        glLoadIdentity();
        break;
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
        if(pontos > 0){
          px[pontos] = (x / 200.0) - 1.0;
          py[pontos] = -((y / 200.0) - 1.0);
        }
        pontos++;
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
  glutCreateWindow("Atividade 05 - Linhas e triângulos coloridos");
  glutDisplayFunc(desenha);
  glutKeyboardFunc(teclado);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}