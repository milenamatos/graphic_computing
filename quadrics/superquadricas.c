#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat kd = 0.0f;
GLfloat ks = 0.0f;

double phi = 0.0;
double theta = 0.0;
int n = 200;

double rx = 0.5;
double ry = 0.5;
double rz = 0.5;

double s1 = 2.5;
double s2 = 2.5;

float angX = 0;
float angY = 0;
float angZ = 0;

void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {-2.0, 0.0, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0f);               //espalhamento angular
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.5f);              //atenuação angular

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}


void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1.0, 1.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 8.0); //define uma projeção ortogonal
    lightning();
    glPushMatrix();
}

/* Returns the sign of x */
double sgnf ( double x ) {
   if ( x < 0 )
       return -1.0;
   if ( x > 0 )
       return 1.0;
   return 0;
}


void superquadrics(){
    int i,j;
    for(i=0;i<n;i++){
        glBegin(GL_POINTS);
            for(j=0;j<n;j++){
                glVertex3f(rx*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(cos(theta))*pow(fabs(cos(theta)),s2)),ry*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(sin(theta))*pow(fabs(sin(theta)),s2)),rz*sgnf(sin(phi))*pow(fabs(sin(phi)),s1));
                glNormal3f(rx*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(cos(theta))*pow(fabs(cos(theta)),s2)),ry*sgnf(cos(phi))*pow(fabs(cos(phi)),s1)*(sgnf(sin(theta))*pow(fabs(sin(theta)),s2)),rz*sgnf(sin(phi))*pow(fabs(sin(phi)),s1));
                phi = phi + (2*M_PI)/n;
            }
        glEnd();
        phi = 0.0;
        theta = theta+(2*M_PI)/n;
    }
}



void displayFunc() {
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat ns;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a de modelo
    diffuse[0] = 0.0;
    diffuse[1] = kd;
    diffuse[2] = 0.0;
    diffuse[3] = 1.0f;
    specular[0] = ks;
    specular[1] = ks;
    specular[2] = ks;
    specular[3] = 1.0f;
    ns = 50.0f;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.0,-1.0,0.0);
    glRotatef(angX,1,0,0);
    glRotatef(angY,0,1,0);
    glRotatef(angZ,0,0,1);
    superquadrics();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0,1.0,0.0);
    glRotatef(angX,1,0,0);
    glRotatef(angY,0,1,0);
    glRotatef(angZ,0,0,1);
    superquadrics();

    
    glFlush();
}

void keyboardSpecial(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
             if(kd<1.0)
                 kd+=0.1;
             if(ks<1.0)
                 ks+=0.1;
             break ;
        case GLUT_KEY_DOWN :
             if(kd>0.0)
                 kd-=0.1;
             if(ks>0.0)
                 ks-=0.1;
             break ;
        default:
             break;
     }
     glutPostRedisplay() ;
}

void keyboard(unsigned char key, int x, int y){
     switch (key){
        case 'x' :
             angX+=15;
             break ;
        case 'y' :
             angY+=15;
             break ;
         case 'z' :
             angZ+=15;
             break ;
        default:
             break;
     }
     glutPostRedisplay() ;
}


int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Superquádricas");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}