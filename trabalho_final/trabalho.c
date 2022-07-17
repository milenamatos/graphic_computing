/*
Nome: Milena de Matos Siqueira 
RA: 122.044

Este exercício é composto por 2 cenas diferentes, clique o número correspondente no teclado para alterar a visualização:
1- Gangorra: formada com um cilindro, dois retângulos para representar os bancos e um cone para 
representar o suporte, o movimento obedece o de uma gangorra real, para isto limitei o ângulo a +-25 graus.
2- Estrelas: formadas com superquádricas, existem 3 que giram em torno do eixo Z.

Interações:
-Mouse: o click do mouse altera a posição da iluminação do tipo holofote.
-Setas direta/esquerda: mexem o objeto.
-Teclado, letras 'a' e 'd': alteram a visão da cämera 360 em volta da cena 

O exercício implementa, conforme solicitado:
- 3D
- Projeção perspectiva;
- Movimento da câmera;  
- Iluminação posicionando pelo menos duas fontes de luz: ambiente e holofote;
- Textura;
- Interação com mouse e teclado;
- Animação;
- Pelo menos 4 objetos: gangorra = cilindro (sweep) + 2 retângulos (objeto simples) + cone (simples), e 3 estrelas (superquádricas)

Com o prazo definido este foi o máximo que consegui fazer, a iluminção holofote parece que não está funcionando corretamente, 
mas não consegui entender porque. Faltou também cobrir as estrelas com a textura corretamente.
*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

GLfloat light0_pos[4] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat ox = 0.0f;
GLfloat oy = 0.0f;
GLfloat direction[] = {0.0f, 0.0f, -1.0f, 1.0f};

float angulo = 0.0;
float angCamera = 0.0;
float angZ = 0.0;
float val = PI / 360;

int objeto = 1;
//-----------------------------------------------------------------------------

typedef struct BMPImagem
{
    int width;
    int height;
    char *data;
} BMPImage;

#define MAX_NO_TEXTURES 6
GLuint texture_id[MAX_NO_TEXTURES];
GLUquadricObj *obj;
char *filenameArray[MAX_NO_TEXTURES] = {
    "earthTexture.bmp",
    "surface1.bmp",
    "surface2.bmp",
    "surface3.bmp",
    "surface4.bmp",
    "surface5.bmp"};

void getBitmapImageData(char *pFileName, BMPImage *pImage)
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if ((pFile = fopen(pFileName, "rb")) == NULL)
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek(pFile, 18, SEEK_CUR);

    if ((i = fread(&pImage->width, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if ((i = fread(&pImage->height, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if ((fread(&nNumPlanes, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if (nNumPlanes != 1)
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if ((i = fread(&nNumBPP, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if (nNumBPP != 24)
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek(pFile, 24, SEEK_CUR);

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char *)malloc(nTotalImagesize);

    if ((i = fread(pImage->data, nTotalImagesize, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for (i = 0; i < nTotalImagesize; i += 3)
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i + 2];
        pImage->data[i + 2] = charTemp;
    }
}

/*Função para Carregar uma imagem .BMP */
void CarregaTextura()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                                /* texture_id = vetor que guardas os números das texturas */
    for (int i = 0; i < MAX_NO_TEXTURES; i++)
    {
        getBitmapImageData(filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

void lightning()
{
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {ox, oy, 6.0f, 1.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);  //espalhamento angular
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f); //atenuação angular

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST);              //habilita o teste de profundidade

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);                                                                              //define que a matrix È a model view
    glLoadIdentity();                                                                                        //carrega a matrix de identidade
    gluLookAt(sin(angCamera * val) + cos(angCamera * val), 1.0, cos(angCamera * val) - sin(angCamera * val), //posiÁ„o da c‚mera
              0.0, 0.0, 0.0,                                                                                 //para onde a c‚mera aponta
              0.0, 1.0, 0.0);                                                                                //vetor view-up

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 8.0); //define uma projeção perspectiva simétrica
    glViewport(0, 0, 700, 700);
}

void initTexture(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    CarregaTextura();
}

double sgnf(double x)
{
    if (x < 0)
        return -1.0;
    if (x > 0)
        return 1.0;
    return 0;
}

void superquadrics()
{
    double phi = 0.0;
    double theta = 0.0;
    int n = 200;
    double rx = 0.5;
    double ry = 0.5;
    double rz = 0.5;
    double s1 = 2.5;
    double s2 = 2.5;

    int i, j;
    for (i = 0; i < n; i++)
    {
        glBegin(GL_POINTS);
        for (j = 0; j < n; j++)
        {
            glVertex3f(rx * sgnf(cos(phi)) * pow(fabs(cos(phi)), s1) * (sgnf(cos(theta)) * pow(fabs(cos(theta)), s2)), ry * sgnf(cos(phi)) * pow(fabs(cos(phi)), s1) * (sgnf(sin(theta)) * pow(fabs(sin(theta)), s2)), rz * sgnf(sin(phi)) * pow(fabs(sin(phi)), s1));
            glNormal3f(rx * sgnf(cos(phi)) * pow(fabs(cos(phi)), s1) * (sgnf(cos(theta)) * pow(fabs(cos(theta)), s2)), ry * sgnf(cos(phi)) * pow(fabs(cos(phi)), s1) * (sgnf(sin(theta)) * pow(fabs(sin(theta)), s2)), rz * sgnf(sin(phi)) * pow(fabs(sin(phi)), s1));
            phi = phi + (2 * M_PI) / n;
        }
        glEnd();
        phi = 0.0;
        theta = theta + (2 * M_PI) / n;
    }
}

void cylinder()
{
    double theta = 0.0;
    double step;
    int n = 20;

    glBindTexture(GL_TEXTURE_2D, texture_id[2]);

    step = (2 * M_PI) / n;
    for (int i = 0; i < n; i++)
    {
        glBegin(GL_QUADS);
        glNormal3f(0.05 * cos(theta), 0.0, 0.05 * sin(theta));
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.05 * cos(theta), 0.0, 0.05 * sin(theta));
        glNormal3f(0.05 * cos(theta + step), 0.0, 0.05 * sin(theta + step));
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.05 * cos(theta + step), 0.0, 0.05 * sin(theta + step));
        glNormal3f(0.05 * cos(theta + step), -0.75, 0.05 * sin(theta + step));
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.05 * cos(theta + step), -0.75, 0.05 * sin(theta + step));
        glNormal3f(0.05 * cos(theta), -0.75, 0.05 * sin(theta));
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.05 * cos(theta), -0.75, 0.05 * sin(theta));
        glEnd();
        theta += step;
    }
}

void seesaw()
{
    glPushMatrix();
    glRotatef(angulo, 1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.65);
    glScalef(1.5, 1.5, 1.75);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    cylinder();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.2, 0.2, 1.5);
    glTranslatef(0.0, 0.6, 0.4);
    glRotatef(-90, 0.0, 0.0, 1.0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glScalef(1.2, 0.2, 1.5);
    glTranslatef(0.0, 0.6, -0.4);
    glRotatef(-90, 0.0, 0.0, 1.0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(0.0, -0.75, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.2, 0.6, 20, 20);
    glPopMatrix();
}

void stars()
{
    glRotatef(angZ, 0, 0, 1);
    for (int i = 3; i < 6; i++)
    {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glScalef(0.6, 0.6, 0.6);
        glTranslatef(i - 4, 0.0, 0.0);
        superquadrics();
        glPopMatrix();
    }
}

void draw()
{
    GLfloat ns = 50.0f;

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

    switch (objeto)
    {
    case 1:
        seesaw(angulo);
        break;
    case 2:
        stars();
        break;
    default:
        break;
    }

    glPopMatrix();
}

void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(sin(angCamera * val) + cos(angCamera * val), 1.0, cos(angCamera * val) - sin(angCamera * val),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    draw();
    lightning();
    glutSwapBuffers();
}

void mouse(int botao, int estado, int x, int y)
{
    switch (botao)
    {
    case GLUT_LEFT_BUTTON:
        if (estado == GLUT_DOWN)
        {
            ox = (x / 350.0) - 1;
            oy = -((y / 350.0) - 1);
            printf("%f %f \n", ox, oy);
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_LEFT:
        if (angulo <= 25)
            angulo += 5;
        angZ -= 5;
        break;
    case GLUT_KEY_RIGHT:
        if (angulo >= -25)
            angulo -= 5;
        angZ += 5;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
    case 'd':
        angCamera += 5.0;
        break;
    case 'a':
        angCamera -= 5.0;
        break;
    case '1':
        objeto = 1;
        break;
    case '2':
        objeto = 2;
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
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Trabalho final");
    glutDisplayFunc(displayFunc);
    glutMouseFunc(mouse);
    glutSpecialFunc(tecladoEspecial);
    glutKeyboardFunc(teclado);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}
