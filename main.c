// #include<windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <string.h>

#define MODEL_QUANT 50

void setup_lighting();

GLfloat angle = 50, fAspect = (GLfloat)800 / (GLfloat)600, rotX = 0, rotY = -2, obsZ = 2;
GLfloat Cx = 0, Cy = -3.1, Cz = 2.9, Fx = 0, Fy = 4, Fz = -4.1, Ux = 0, Uy = 1, Uz = 0;
// Posição inicial da bola
GLfloat Bx = 0, By = 0, Bz = 0.25;
char placar[10] = " 0 x 0";
int ligado = 1, dia = 0;
int frame = 0.2;
double turningSpeed = 1.0;

void load_texture(const char *path, int index)
{
    unsigned int textureID;

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &textureID);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }
    else
    {
        printf("Não foi possível carregar a textura\n");
    }
}

void put_pixel(GLfloat xo, GLfloat yo)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(3.0);
    glBegin(GL_POINTS);
    glVertex3f(xo, yo, 0.25);
    glEnd();
}

void put_pixel_center(GLfloat xo, GLfloat yo)
{
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(xo, yo, 0.25);
    glEnd();
}

void bresenhamCircularEsq(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc + x, yc - y);
        put_pixel(xc + y, yc - x);
        put_pixel(xc + y, yc + x);
        put_pixel(xc + x, yc + y);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircularDir(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc - x, yc + y);
        put_pixel(xc - y, yc + x);
        put_pixel(xc - y, yc - x);
        put_pixel(xc - x, yc - y);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircular(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc + x, yc - y);
        put_pixel(xc + y, yc - x);
        put_pixel(xc + y, yc + x);
        put_pixel(xc + x, yc + y);
        put_pixel(xc - x, yc + y);
        put_pixel(xc - y, yc + x);
        put_pixel(xc - y, yc - x);
        put_pixel(xc - x, yc - y);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircularInfDirEscanteio(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc - x, yc + y);
        put_pixel(xc - y, yc + x);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircularSupDirEscanteio(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {

        put_pixel(xc - y, yc - x);
        put_pixel(xc - x, yc - y);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircularInfEsqEscanteio(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc + y, yc + x);
        put_pixel(xc + x, yc + y);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamCircularSupEsqEscanteio(GLfloat xc, GLfloat yc, GLfloat raio)
{
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc + x, yc - y);
        put_pixel(xc + y, yc - x);

        if (d < 0)
        {
            d += 2 * x + 0.0003;
        }
        else
        {
            d += 2 * (x - y) + 0.0005;
            y -= 0.0001;
        }
        x += 0.0001;
    }
}

void bresenhamY(GLfloat xo, GLfloat yo, GLfloat xf, GLfloat yf)
{
    GLfloat dy = yf - yo;
    GLfloat dx = xf - xo;

    GLfloat E = 2 * dy;
    GLfloat Ne = 2 * (dx - dy);

    GLfloat d = 2 * dx - dy;

    GLfloat x = xo, y = yo;

    while (y < yf)
    {
        put_pixel(x, y);
        if (d <= 0)
        {
            y += 0.001;
            d += E;
        }
        else
        {
            // x += 0.001;
            y += 0.001;
            d += Ne;
        }
    }
}

void bresenhamX(GLfloat xo, GLfloat yo, GLfloat xf, GLfloat yf)
{
    GLfloat dy = yf - yo;
    GLfloat dx = xf - xo;

    GLfloat E = 2 * dy;
    GLfloat Ne = 2 * (dy - dx);

    GLfloat d = 2 * dy - dx;

    GLfloat x = xo, y = yo;

    while (x < xf || y < yf)
    {
        put_pixel(x, y);
        if (d <= 0)
        {
            x += 0.001;
            d += E;
        }
        else
        {
            x += 0.001;
            y += 0.001;
            d += Ne;
        }
    }
}

void myInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}

void square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glBegin(GL_POLYGON);

    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);

    glEnd();
}

void trave(GLfloat t0[], GLfloat t1[], GLfloat t2[], GLfloat t3[], GLfloat t4[], GLfloat t5[], GLfloat t6[], GLfloat t7[])
{
    glColor3f(1, 1, 1);
    square(t0, t1, t2, t3);

    glColor3f(1, 1, 1);
    square(t4, t5, t6, t7);

    glColor3f(1, 1, 1);
    square(t0, t4, t7, t3);

    glColor3f(1, 1, 1);
    square(t1, t5, t6, t2);

    glColor3f(1, 1, 1);
    square(t3, t2, t6, t7);

    glColor3f(1, 1, 1);
    square(t0, t1, t5, t4);
}

void posicionaObservador(void)
{
    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    glTranslatef(0, 0, -obsZ);
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
}

void especificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
    gluPerspective(angle, fAspect, 0.5, 500);

    posicionaObservador();
}

void gerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        { // Zoom-in
            if (angle >= 10)
                angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
        { // Zoom-out
            if (angle <= 130)
                angle += 5;
        }
    especificaParametrosVisualizacao();
    glutPostRedisplay();
}

void cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    glPushMatrix();
    load_texture("gramado.jpg", 0);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(2.0, 0.0);
    glVertex3f(-1, 1, 0.25001);
    glTexCoord2f(2.0, 1.0);
    glVertex3f(-1, -1, 0.25001);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1, -1, 0.25001);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1, 1, 0.25001);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    if (dia)
        glNormal3f(0, 0, 0.4);
    if (ligado)
        glNormal3f(-1.25, -0.9, 0);
    glColor3f(0, 1, 0); // green
    square(V0, V1, V2, V3);

    if (ligado)
        glNormal3f(1.25, 0.9, 0);
    glColor3f(0, 1, 0); // green
    square(V4, V5, V6, V7);

    if (ligado)
        glNormal3f(-1.25, 0.9, 0);
    glColor3f(0, 1, 0); // green
    square(V0, V4, V7, V3);

    if (ligado)
        glNormal3f(1.25, -0.9, 0);
    glColor3f(0, 1, 0); // green
    square(V1, V5, V6, V2);

    glColor3f(0, 1, 0); // green
    square(V3, V2, V6, V7);

    glColor3f(0, 1, 0); // green
    square(V0, V1, V5, V4);
}

void bresenham()
{
    glPushMatrix();
    bresenhamX(-1, 1, 1, 1);   // linha superior
    bresenhamX(-1, -1, 1, -1); // linha inferior
    bresenhamY(-1, -1, -1, 1); // linha esquerda
    bresenhamY(1, -1, 1, 1);   // linha direita
    bresenhamY(0, -1, 0, 1);   // linha central

    // area direita
    bresenhamY(0.6, -0.6, 0.6, 0.6);
    bresenhamX(0.6, -0.6, 1, -0.6);
    bresenhamX(0.6, 0.6, 1, 0.6);

    // area pequena direita
    bresenhamY(0.8, -0.3, 0.8, 0.3);
    bresenhamX(0.8, -0.3, 1, -0.3);
    bresenhamX(0.8, 0.3, 1, 0.3);

    // area esquerda
    bresenhamY(-0.6, -0.6, -0.6, 0.6);
    bresenhamX(-1, -0.6, -0.6, -0.6);
    bresenhamX(-1, 0.6, -0.6, 0.6);

    // area pequena esquerda
    bresenhamY(-0.8, -0.3, -0.8, 0.3);
    bresenhamX(-1, -0.3, -0.8, -0.3);
    bresenhamX(-1, 0.3, -0.8, 0.3);

    bresenhamCircular(0, 0, 0.25);
    bresenhamCircularEsq(-0.6, 0, 0.15);
    bresenhamCircularDir(0.6, 0, 0.15);

    bresenhamCircularSupEsqEscanteio(-1, 1, 0.07);
    bresenhamCircularInfEsqEscanteio(-1, -1, 0.07);
    bresenhamCircularSupDirEscanteio(1, 1, 0.07);
    bresenhamCircularInfDirEscanteio(1, -1, 0.07);

    put_pixel_center(-0.7, 0);
    put_pixel_center(0.7, 0);
    put_pixel_center(0, 0);
}

void bola()
{

    glPushMatrix();
    glColor3f(0, 0, 1);
    turningSpeed = 1.5;
    glRotatef(turningSpeed * frame, 0, 1, 0);
    glTranslatef(Bx, By, Bz + 0.02);
    glutSolidSphere(0.02, 10, 10);
    glPopMatrix();
}

void displayScore(float x, float y, void *font)
{
    glColor3f(1, 1, 1);

    glRasterPos2f(x, y);
    glutBitmapString(font, placar);
}

void arquibancada(int r, int g, int b, GLfloat p0[], GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[], GLfloat p5[], GLfloat p6[], GLfloat p7[])
{

    glColor3f(r, g, b);
    square(p0, p1, p2, p3);

    glColor3f(r, g, b);
    square(p4, p5, p6, p7);

    glColor3f(r, g, b);
    square(p0, p4, p7, p3);

    glColor3f(r, g, b);
    square(p1, p5, p6, p2);

    glColor3f(r, g, b);
    square(p3, p2, p6, p7);

    glColor3f(r, g, b);
    square(p0, p1, p5, p4);
}

void textureArq(float x_min, float x_max, float y_min, float y_max, float z)
{
    load_texture("telha-cor.jpg", 1);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(1, 0.0);
    glVertex3f(x_min, y_max, z);
    glTexCoord2f(1, 0.5);
    glVertex3f(x_min, y_min, z);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x_max, y_min, z);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x_max, y_max, z);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void textureArq2(float x, float y_min, float y_max, float z_min, float z_max)
{
    load_texture("creme-cor.jpg", 2);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(1, 0.0);
    glVertex3f(x, y_min, z_max);
    glTexCoord2f(1, 0.5);
    glVertex3f(x, y_min, z_min);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x, y_max, z_min);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x, y_max, z_max);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void textureArq3(float x_min, float x_max, float y, float z_min, float z_max)
{
    load_texture("creme-cor.jpg", 2);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    glTexCoord2f(1, 0.0);
    glVertex3f(x_min, y, z_max);
    glTexCoord2f(1, 0.5);
    glVertex3f(x_min, y, z_min);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x_max, y, z_min);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x_max, y, z_max);

    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void arquibancadas()
{
    GLfloat arquibancadaGolEsq[8][3] = {
        {-2.1, 2, 0.55},
        {-1.75, 2, 0.55},
        {-1.75, -2, 0.55},
        {-2.1, -2, 0.55},
        {-2.1, 2, 0},
        {-1.75, 2, 0},
        {-1.75, -2, 0},
        {-2.1, -2, 0},
    };
    GLfloat arquibancadaGolEsq_B[8][3] = {
        {-2.1, 2, 0.56},
        {-1.75, 2, 0.56},
        {-1.75, -2, 0.56},
        {-2.1, -2, 0.56},
        {-2.1, 2, 0.56},
        {-1.75, 2, 0.56},
        {-1.75, -2, 0.56},
        {-2.1, -2, 0.56},
    };

    GLfloat arquibancadaGolEsq_2[8][3] = {
        {-1.75, 1.75, 0.35},
        {-1.5, 1.75, 0.35},
        {-1.5, -1.75, 0.35},
        {-1.75, -1.75, 0.35},
        {-1.75, 1.75, 0.25},
        {-1.5, 1.75, 0.25},
        {-1.5, -1.75, 0.25},
        {-1.75, -1.75, 0.25},
    };
    GLfloat arquibancadaGolEsq_3[8][3] = {
        {-1.49, 1.75, 0.35},
        {-1.49, 1.75, 0.35},
        {-1.49, -1.75, 0.35},
        {-1.49, -1.75, 0.35},
        {-1.49, 1.75, 0.25},
        {-1.49, 1.75, 0.25},
        {-1.49, -1.75, 0.25},
        {-1.49, -1.75, 0.25},
    };

    GLfloat arquibancadaGolDir[8][3] = {
        {1.75, 2, 0.55},
        {2.1, 2, 0.55},
        {2.1, -2, 0.55},
        {1.75, -2, 0.55},
        {1.75, 2, 0},
        {2.1, 2, 0},
        {2.1, -2, 0},
        {1.75, -2, 0},
    };
    GLfloat arquibancadaGolDir_B[8][3] = {
        {1.75, 2, 0.56},
        {2.1, 2, 0.56},
        {2.1, -2, 0.56},
        {1.75, -2, 0.56},
        {1.75, 2, 0.56},
        {2.1, 2, 0.56},
        {2.1, -2, 0.56},
        {1.75, -2, 0.56},
    };
    GLfloat arquibancadaGolDir_2[8][3] = {
        {1.5, 1.75, 0.35},
        {1.75, 1.75, 0.35},
        {1.75, -1.75, 0.35},
        {1.5, -1.75, 0.35},
        {1.5, 1.75, 0.25},
        {1.75, 1.75, 0.25},
        {1.75, -1.75, 0.25},
        {1.5, -1.75, 0.25},
    };

    GLfloat arquibancadaGolDir_3[8][3] = {
        {1.49, 1.75, 0.35},
        {1.49, 1.75, 0.35},
        {1.49, -1.75, 0.35},
        {1.49, -1.75, 0.35},
        {1.49, 1.75, 0.25},
        {1.49, 1.75, 0.25},
        {1.49, -1.75, 0.25},
        {1.49, -1.75, 0.25},
    };

    GLfloat arquibancadaFront[8][3] = {
        {-2.1, -1.75, 0.55},
        {2.1, -1.75, 0.55},
        {2.1, -2.1, 0.55},
        {-2.1, -2.1, 0.55},
        {-2.1, -2, 0},
        {2.1, -2, 0},
        {2.1, -2.1, 0},
        {-2.1, -2.1, 0},
    };
    GLfloat arquibancadaFront_B[8][3] = {
        {-2.1, -1.75, 0.56},
        {2.1, -1.75, 0.56},
        {2.1, -2.1, 0.56},
        {-2.1, -2.1, 0.56},
        {-2.1, -1.75, 0.56},
        {2.1, -1.75, 0.56},
        {2.1, -2.1, 0.56},
        {-2.1, -2.1, 0.56},
    };
    GLfloat arquibancadaFront_2[8][3] = {
        {-1.75, -1.5, 0.35},
        {1.75, -1.5, 0.35},
        {1.75, -2, 0.35},
        {-1.75, -2, 0.35},
        {-1.75, -1.5, 0.25},
        {1.75, -1.5, 0.25},
        {1.75, -2, 0.25},
        {-1.75, -2, 0.25},
    };
    GLfloat arquibancadaFront_3[8][3] = {
        {-1.75, -1.49, 0.35},
        {1.75, -1.49, 0.35},
        {1.75, -1.49, 0.35},
        {-1.75, -1.49, 0.35},
        {-1.75, -1.49, 0.25},
        {1.75, -1.49, 0.25},
        {1.75, -1.49, 0.25},
        {-1.75, -1.49, 0.25},
    };

    GLfloat arquibancadaBack[8][3] = {
        {-2, 2, 0.55},
        {2, 2, 0.55},
        {2, 1.75, 0.55},
        {-2, 1.75, 0.55},
        {-2, 2, 0.25},
        {2, 2, 0.25},
        {2, 1.75, 0.25},
        {-2, 1.75, 0.25},
    };
    GLfloat arquibancadaBack_B[8][3] = {
        {-2, 2, 0.56},
        {2.1, 2, 0.56},
        {2.1, 1.75, 0.56},
        {-2, 1.75, 0.56},
        {-2, 2, 0.56},
        {2.1, 2, 0.56},
        {2.1, 1.75, 0.56},
        {-2, 1.75, 0.56},
    };
    GLfloat arquibancadaBack_2[8][3] = {
        {-1.75, 1.75, 0.35},
        {1.75, 1.75, 0.35},
        {1.75, 1.5, 0.35},
        {-1.75, 1.5, 0.35},
        {-1.75, 1.75, 0.25},
        {1.75, 1.75, 0.25},
        {1.75, 1.5, 0.25},
        {-1.75, 1.5, 0.25},
    };
    GLfloat arquibancadaBack_3[8][3] = {
        {-1.75, 1.49, 0.35},
        {1.75, 1.49, 0.35},
        {1.75, 1.49, 0.35},
        {-1.75, 1.49, 0.35},
        {-1.75, 1.49, 0.25},
        {1.75, 1.49, 0.25},
        {1.75, 1.49, 0.25},
        {-1.75, 1.49, 0.25},
    };

    arquibancada(1, 1, 1, arquibancadaGolEsq[0], arquibancadaGolEsq[1], arquibancadaGolEsq[2], arquibancadaGolEsq[3], arquibancadaGolEsq[4], arquibancadaGolEsq[5], arquibancadaGolEsq[6], arquibancadaGolEsq[7]);
    arquibancada(1, 1, 1, arquibancadaGolEsq_3[0], arquibancadaGolEsq_3[1], arquibancadaGolEsq_3[2], arquibancadaGolEsq_3[3], arquibancadaGolEsq_3[4], arquibancadaGolEsq_3[5], arquibancadaGolEsq_3[6], arquibancadaGolEsq_3[7]);
    // textura de telha
    arquibancada(0, 1, 1, arquibancadaGolEsq_B[0], arquibancadaGolEsq_B[1], arquibancadaGolEsq_B[2], arquibancadaGolEsq_B[3], arquibancadaGolEsq_B[4], arquibancadaGolEsq_B[5], arquibancadaGolEsq_B[6], arquibancadaGolEsq_B[7]);
    arquibancada(0, 1, 1, arquibancadaGolEsq_2[0], arquibancadaGolEsq_2[1], arquibancadaGolEsq_2[2], arquibancadaGolEsq_2[3], arquibancadaGolEsq_2[4], arquibancadaGolEsq_2[5], arquibancadaGolEsq_2[6], arquibancadaGolEsq_2[7]);

    arquibancada(1, 1, 1, arquibancadaGolDir[0], arquibancadaGolDir[1], arquibancadaGolDir[2], arquibancadaGolDir[3], arquibancadaGolDir[4], arquibancadaGolDir[5], arquibancadaGolDir[6], arquibancadaGolDir[7]);
    arquibancada(1, 1, 1, arquibancadaGolDir_3[0], arquibancadaGolDir_3[1], arquibancadaGolDir_3[2], arquibancadaGolDir_3[3], arquibancadaGolDir_3[4], arquibancadaGolDir_3[5], arquibancadaGolDir_3[6], arquibancadaGolDir_3[7]);
    // textura de telha
    arquibancada(0, 1, 1, arquibancadaGolDir_B[0], arquibancadaGolDir_B[1], arquibancadaGolDir_B[2], arquibancadaGolDir_B[3], arquibancadaGolDir_B[4], arquibancadaGolDir_B[5], arquibancadaGolDir_B[6], arquibancadaGolDir_B[7]);
    arquibancada(0, 1, 1, arquibancadaGolDir_2[0], arquibancadaGolDir_2[1], arquibancadaGolDir_2[2], arquibancadaGolDir_2[3], arquibancadaGolDir_2[4], arquibancadaGolDir_2[5], arquibancadaGolDir_2[6], arquibancadaGolDir_2[7]);

    arquibancada(1, 1, 1, arquibancadaFront[0], arquibancadaFront[1], arquibancadaFront[2], arquibancadaFront[3], arquibancadaFront[4], arquibancadaFront[5], arquibancadaFront[6], arquibancadaFront[7]);
    arquibancada(1, 1, 1, arquibancadaFront_3[0], arquibancadaFront_3[1], arquibancadaFront_3[2], arquibancadaFront_3[3], arquibancadaFront_3[4], arquibancadaFront_3[5], arquibancadaFront_3[6], arquibancadaFront_3[7]);
    // textura de telha
    arquibancada(0, 1, 1, arquibancadaFront_B[0], arquibancadaFront_B[1], arquibancadaFront_B[2], arquibancadaFront_B[3], arquibancadaFront_B[4], arquibancadaFront_B[5], arquibancadaFront_B[6], arquibancadaFront_B[7]);
    arquibancada(0, 1, 1, arquibancadaFront_2[0], arquibancadaFront_2[1], arquibancadaFront_2[2], arquibancadaFront_2[3], arquibancadaFront_2[4], arquibancadaFront_2[5], arquibancadaFront_2[6], arquibancadaFront_2[7]);

    arquibancada(1, 1, 1, arquibancadaBack[0], arquibancadaBack[1], arquibancadaBack[2], arquibancadaBack[3], arquibancadaBack[4], arquibancadaBack[5], arquibancadaBack[6], arquibancadaBack[7]);
    arquibancada(1, 1, 1, arquibancadaBack_3[0], arquibancadaBack_3[1], arquibancadaBack_3[2], arquibancadaBack_3[3], arquibancadaBack_3[4], arquibancadaBack_3[5], arquibancadaBack_3[6], arquibancadaBack_3[7]);
    // textura de telha
    arquibancada(0, 1, 1, arquibancadaBack_B[0], arquibancadaBack_B[1], arquibancadaBack_B[2], arquibancadaBack_B[3], arquibancadaBack_B[4], arquibancadaBack_B[5], arquibancadaBack_B[6], arquibancadaBack_B[7]);
    arquibancada(0, 1, 1, arquibancadaBack_2[0], arquibancadaBack_2[1], arquibancadaBack_2[2], arquibancadaBack_2[3], arquibancadaBack_2[4], arquibancadaBack_2[5], arquibancadaBack_2[6], arquibancadaBack_2[7]);

    textureArq(-2.1, -1.75, -2, 2, 0.56001);
    textureArq(-1.75, -1.5, -1.75, 1.75, 0.35001);
    textureArq(1.75, 2.1, -2, 2, 0.56001);
    textureArq(1.5, 1.75, -1.75, 1.75, 0.35001);
    textureArq(-2.1, 2.1, -2.1, -1.75, 0.56001);
    textureArq(-1.75, 1.75, -2, -1.5, 0.35001);
    textureArq(-2, 2.1, 1.75, 2, 0.56001);
    textureArq(-1.75, 1.75, 1.5, 1.75, 0.35001);

    textureArq2(-1.74999, -2, 2, 0.25, 0.55);
    textureArq2(-1.48999, -1.75, 1.75, 0.25, 0.35);
    textureArq2(1.74999, -2, 2, 0.25, 0.55);
    textureArq2(1.48999, -1.75, 1.75, 0.25, 0.35);

    textureArq3(-2.1, 2.1, 1.74999, 0.25, 0.55001);
    textureArq3(-1.75, 1.75, -1.48999, 0.25, 0.35001);
    textureArq3(-2, 2, 1.48999, 0.25, 0.35001);
    textureArq3(-1.75, 1.75, -1.74999, 0.25, 0.55001);
}

void refletor(GLfloat p0[], GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[], GLfloat p5[], GLfloat p6[], GLfloat p7[])
{
    glColor3f(0.5, 0.5, 0.5);
    square(p0, p1, p2, p3);

    glColor3f(0.5, 0.5, 0.5);
    square(p4, p5, p6, p7);

    glColor3f(0.5, 0.5, 0.5);
    square(p0, p4, p7, p3);

    glColor3f(0.5, 0.5, 0.5);
    square(p1, p5, p6, p2);

    glColor3f(0.5, 0.5, 0.5);
    square(p3, p2, p6, p7);

    glColor3f(0.5, 0.5, 0.5);
    square(p0, p1, p5, p4);
}

void refletores()
{
    GLfloat refletorEsqSup[8][3] = {
        {-1.24, 0.91, 0.85},
        {-1.26, 0.91, 0.85},
        {-1.26, 0.89, 0.85},
        {-1.24, 0.89, 0.85},
        {-1.24, 0.91, 0.25},
        {-1.26, 0.91, 0.25},
        {-1.26, 0.89, 0.25},
        {-1.24, 0.89, 0.25},
    };

    GLfloat refletorEsqInf[8][3] = {
        {-1.24, -0.91, 0.85},
        {-1.26, -0.91, 0.85},
        {-1.26, -0.89, 0.85},
        {-1.24, -0.89, 0.85},
        {-1.24, -0.91, 0.25},
        {-1.26, -0.91, 0.25},
        {-1.26, -0.89, 0.25},
        {-1.24, -0.89, 0.25},
    };

    GLfloat refletorDirSup[8][3] = {
        {1.24, 0.91, 0.85},
        {1.26, 0.91, 0.85},
        {1.26, 0.89, 0.85},
        {1.24, 0.89, 0.85},
        {1.24, 0.91, 0.25},
        {1.26, 0.91, 0.25},
        {1.26, 0.89, 0.25},
        {1.24, 0.89, 0.25},
    };

    GLfloat refletorDirInf[8][3] = {
        {1.24, -0.91, 0.85},
        {1.26, -0.91, 0.85},
        {1.26, -0.89, 0.85},
        {1.24, -0.89, 0.85},
        {1.24, -0.91, 0.25},
        {1.26, -0.91, 0.25},
        {1.26, -0.89, 0.25},
        {1.24, -0.89, 0.25},
    };

    refletor(refletorEsqSup[0], refletorEsqSup[1], refletorEsqSup[2], refletorEsqSup[3], refletorEsqSup[4], refletorEsqSup[5], refletorEsqSup[6], refletorEsqSup[7]);
    refletor(refletorEsqInf[0], refletorEsqInf[1], refletorEsqInf[2], refletorEsqInf[3], refletorEsqInf[4], refletorEsqInf[5], refletorEsqInf[6], refletorEsqInf[7]);
    refletor(refletorDirSup[0], refletorDirSup[1], refletorDirSup[2], refletorDirSup[3], refletorDirSup[4], refletorDirSup[5], refletorDirSup[6], refletorDirSup[7]);
    refletor(refletorDirInf[0], refletorDirInf[1], refletorDirInf[2], refletorDirInf[3], refletorDirInf[4], refletorDirInf[5], refletorDirInf[6], refletorDirInf[7]);
}

void luminarias()
{

    glPushMatrix();
    ligado ? glColor3f(1, 1, 1) : glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-1.25, 0.9, 0.85 + 0.02);
    glutSolidSphere(0.06, 10, 10);
    glPopMatrix();

    glPushMatrix();
    ligado ? glColor3f(1, 1, 1) : glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-1.25, -0.9, 0.85 + 0.02);
    glutSolidSphere(0.06, 10, 10);
    glPopMatrix();

    glPushMatrix();
    ligado ? glColor3f(1, 1, 1) : glColor3f(0.5, 0.5, 0.5);
    glTranslatef(1.25, 0.9, 0.85 + 0.02);
    glutSolidSphere(0.06, 10, 10);
    glPopMatrix();

    glPushMatrix();
    ligado ? glColor3f(1, 1, 1) : glColor3f(0.5, 0.5, 0.5);
    glTranslatef(1.25, -0.9, 0.85 + 0.02);
    glutSolidSphere(0.06, 10, 10);
    glPopMatrix();
}

void Draw()
{
    GLfloat VCampo[8][3] = {
        {-2, 2, 0.25},
        {2, 2, 0.25},
        {2, -2, 0.25},
        {-2, -2, 0.25},
        {-2, 2, 0},
        {2, 2, 0},
        {2, -2, 0},
        {-2, -2, 0},
    };

    GLfloat t1i[8][3] = {
        {-1, 0.2, 0.55},
        {-0.98, 0.2, 0.55},
        {-0.98, 0.18, 0.55},
        {-1, 0.18, 0.55},
        {-1, 0.2, 0.20},
        {-0.98, 0.2, 0.20},
        {-0.98, 0.18, 0.20},
        {-1, 0.18, 0.20},
    };

    GLfloat t2i[8][3] = {
        {-1, -0.2, 0.55},
        {-0.98, -0.2, 0.55},
        {-0.98, -0.18, 0.55},
        {-1, -0.18, 0.55},
        {-1, -0.2, 0.20},
        {-0.98, -0.2, 0.20},
        {-0.98, -0.18, 0.20},
        {-1, -0.18, 0.20},
    };

    GLfloat t3i[8][3] = {
        {-1, -0.2, 0.55},
        {-0.98, -0.2, 0.55},
        {-0.98, 0.2, 0.55},
        {-1, 0.2, 0.55},
        {-1, -0.2, 0.54},
        {-0.98, -0.2, 0.54},
        {-0.98, 0.2, 0.54},
        {-1, 0.2, 0.54},
    };

    GLfloat t4i[8][3] = {
        {1, 0.2, 0.55},
        {0.98, 0.2, 0.55},
        {0.98, 0.18, 0.55},
        {1, 0.18, 0.55},
        {1, 0.2, 0.20},
        {0.98, 0.2, 0.20},
        {0.98, 0.18, 0.20},
        {1, 0.18, 0.20},
    };

    GLfloat t5i[8][3] = {
        {1, -0.2, 0.55},
        {0.98, -0.2, 0.55},
        {0.98, -0.18, 0.55},
        {1, -0.18, 0.55},
        {1, -0.2, 0.20},
        {0.98, -0.2, 0.20},
        {0.98, -0.18, 0.20},
        {1, -0.18, 0.20},
    };

    GLfloat t6i[8][3] = {
        {1, -0.2, 0.55},
        {0.98, -0.2, 0.55},
        {0.98, 0.2, 0.55},
        {1, 0.2, 0.55},
        {1, -0.2, 0.54},
        {0.98, -0.2, 0.54},
        {0.98, 0.2, 0.54},
        {1, 0.2, 0.54},
    };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(Cx, Cy, Cz, Fx + Cx, Fy + Cy, Fz + Cz, Ux, Uy, Uz);
    glPushMatrix();
    cube(VCampo[0], VCampo[1], VCampo[2], VCampo[3], VCampo[4], VCampo[5], VCampo[6], VCampo[7]);
    trave(t1i[0], t1i[1], t1i[2], t1i[3], t1i[4], t1i[5], t1i[6], t1i[7]);
    trave(t2i[0], t2i[1], t2i[2], t2i[3], t2i[4], t2i[5], t2i[6], t2i[7]);
    trave(t3i[0], t3i[1], t3i[2], t3i[3], t3i[4], t3i[5], t3i[6], t3i[7]);
    trave(t4i[0], t4i[1], t4i[2], t4i[3], t4i[4], t4i[5], t4i[6], t4i[7]);
    trave(t5i[0], t5i[1], t5i[2], t5i[3], t5i[4], t5i[5], t5i[6], t5i[7]);
    trave(t6i[0], t6i[1], t6i[2], t6i[3], t6i[4], t6i[5], t6i[6], t6i[7]);
    arquibancadas();
    refletores();
    luminarias();
    bresenham();
    glPopMatrix();
    bola();

    displayScore(-0.5f, 8.0f, GLUT_BITMAP_TIMES_ROMAN_24);

    glutSwapBuffers();
}

void keyboard(unsigned char ch, int x, int y)
{
    switch (ch)
    {
    case 'w':
        // Altera a velocidade da bola em y
        By += 0.03;
        By = (By > 1.04) ? 0 : By;
        break;
    case 's':
        // Altera a velocidade da bola em y
        By -= 0.03;
        By = (By < -1.04) ? 0 : By;
        break;
    case 'a':
        // Altera a velocidade da bola em x
        Bx -= 0.03;
        if (Bx < -1.04)
        {
            if ((By < 0.28 && By > -0.18))
            {
                int tam = strlen(placar) - 1;
                if (placar[tam] - '0' + 1 > 9)
                {
                    placar[tam + 1] = (placar[tam] - '0' + 1) % 10 + '0';
                    placar[tam] = (placar[tam] - '0' + 1) / 10 + '0';
                }
                else
                {
                    placar[tam] += 1;
                }
                Bx = 0, By = 0, Bz = 0.25;
            }
            else
            {
                Bx = 0;
            }
        }
        break;
    case 'd':
        // Altera a velocidade da bola em x
        Bx += 0.03;
        if (Bx > 1.04)
        {
            if ((By < 0.28 && By > -0.18))
            {
                int tam = 1;
                if (placar[tam] - '0' + 1 > 9)
                {

                    placar[tam - 1] = (placar[tam] - '0' + 1) / 10 + '0';
                    placar[tam] = (placar[tam] - '0' + 1) % 10 + '0';
                }
                else
                {
                    placar[tam] += 1;
                }
                Bx = 0, By = 0, Bz = 0.25;
            }
            else
            {
                Bx = 0;
            }
        }
        break;
    case 'W':
        // Altera a velocidade da bola em z
        Bz += 0.03;
        Bz = (Bz > 0.7) ? 0.25 : Bz;
        break;
    case 'S':
        // Altera a velocidade da bola em z
        Bz -= 0.03;
        Bz = (Bz < 0.25) ? 0.25 : Bz;
        break;
    case 'j':
        // Altera a posição da câmera em x
        Cx = Cx - 0.3;
        break;
    case 'l':
        // Altera a posição da câmera em x
        Cx = Cx + 0.3;
        break;

    case 'k':
        // Altera a posição da câmera em y
        Cy = Cy - 0.3;
        break;
    case 'i':
        // Altera a posição da câmera em y
        Cy = Cy + 0.3;
        break;

    case 'z':
        // Altera a posição da câmera em Z
        Cz = Cz - 0.1;
        break;
    case 'Z':
        // Altera a posição da câmera em Z
        Cz = Cz + 0.1;
        break;
    case 'I':
        Fz += 0.3;
        break;
    case 'K':
        Fz -= 0.3;
        break;
    case 'J':
        Fx -= 0.3;
        break;
    case 'L':
        Fx += 0.3;
        break;
    case 'r':
        Cx = 0, Cy = -3.1, Cz = 2.9, Fx = 0, Fy = 4, Fz = -4.1, Ux = 0, Uy = 1, Uz = 0;
        break;
    case 'q':
        ligado = ligado ? 0 : 1;
        break;
    case 'Q':
        ligado = ligado ? 0 : 1;
        break;
    case 'n':
        dia = dia ? 0 : 1;
        if (dia)
        {
            ligado = 0;
            glClearColor(0.529f, 0.808f, 0.922f, 1);
        }
        else
        {
            ligado = 0;
            glClearColor(0, 0, 0, 1);
        }
        break;
    case 'N':
        dia = dia ? 0 : 1;
        if (dia)
        {
            ligado = 0;
            glClearColor(0.529f, 0.808f, 0.922f, 1);
        }
        else
        {
            ligado = 0;
            glClearColor(0, 0, 0, 1);
        }
        break;
    }

    glutPostRedisplay();
}

int main(int argC, char *argV[])
{

    glutInit(&argC, argV);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Soccer field");
    glutMouseFunc(gerenciaMouse);
    myInit();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(keyboard);
    setup_lighting();
    glutMainLoop();
    return 0;
}

void setup_lighting()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float globalAmb[] = {
        0.45f,
        0.45f,
        0.45f,
        0.1f,
    };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    float light0[4][4] = {
        {0.2f, 0.2f, 0.2f, 1.f},
        {0.8f, 0.8f, 0.8f, 1.f},
        {1.f, 1.f, 1.f, 1.f},
        {0.f, 0.f, 1.f, 1.f}};

    glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);
    glEnable(GL_COLOR_MATERIAL);
}
