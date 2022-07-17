#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLfloat light0_pos[4] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat red[4] = {1.0f, 0.0f, 0.0f, 1.0f};
GLfloat blue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
GLfloat green[4] = {0.0f, 1.0f, 0.0f, 1.0f};
GLfloat yellow[4] = {1.0f, 1.0f, 0.0f, 1.0f};

GLfloat ox = 0.0f;
GLfloat oy = 0.0f;
GLfloat direction[] = {0.0f, 0.0f, -1.0f, 1.0f};
float angulo = 0.0;

void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT, black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, black);
    glLightfv(GL_LIGHT0,GL_SPECULAR, black);

    glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION, 0.15f);
    glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION, 0.1f);

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {ox, oy, 6.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);  
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,15.0f);               //espalhamento angular
    // glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.5f);              //atenuação angular

    glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix È a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(0.0, 0.0, 1.0,   //posiÁ„o da c‚mera
              0.0, 0.0, 0.0,   //para onde a c‚mera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix È a de projeÁ„o
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); //define uma projeÁ„o ortogonal
    glViewport(0, 0, 500, 500);
    lightning();
    glPushMatrix();
}

void esferas(){
    GLfloat ns = 50.0f;

    glPushMatrix();
    glRotatef(angulo,0.0,0.0,1.0);

    //vermelha
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,red);
    glMaterialfv(GL_FRONT,GL_SPECULAR,white);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glPushMatrix();
        glTranslatef(-1.5, 0.0, 0.0);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    //verde
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,green);
    glMaterialfv(GL_FRONT,GL_SPECULAR,white);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glPushMatrix();
        glTranslatef(1.5, 0.0, 0.0);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    //azul
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blue);
    glMaterialfv(GL_FRONT,GL_SPECULAR,white);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glPushMatrix();
        glTranslatef(0.0, -1.5, 0.0);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    //amarela
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,yellow);
    glMaterialfv(GL_FRONT,GL_SPECULAR,white);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glPushMatrix();
        glTranslatef(0.0, 1.5, 0.0);
        glutSolidSphere(0.25, 40, 40);
    glPopMatrix();    

    glPopMatrix();
}

void displayFunc() {
       glPushMatrix();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

        glMatrixMode(GL_MODELVIEW); //define que a matrix È a model view
        glLoadIdentity(); //carrega a matrix de identidade
        // gluLookAt(0.0, 0.0, 1.0,   //posiÁ„o da c‚mera
        //           0.0, 0.0, 0.0,   //para onde a c‚mera aponta
        //           0.0, 1.0, 0.0);  //vetor view-up
        glPopMatrix();

        esferas();
        lightning();    
        glFlush();
}

void mouse(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            ox = (x/ 250.0) -1;
            oy = -((y/ 250.0) -1);
            printf("%f %f \n", ox, oy);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void anima()
{
    angulo += 0.1;
    glutPostRedisplay();
    // glutTimerFunc(10, anima, 1);
}


int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Iluminacao direcionada");
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouse);
    // glutTimerFunc(10, anima, 1);
    glutIdleFunc(anima);
    init();
    glutMainLoop();
    return 0;
}
