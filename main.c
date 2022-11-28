// #include<windows.h>
#include<GL/glut.h>
#include<GL/glut.h>
#include <stdio.h>
#include <string.h>
 
GLfloat Cx = 0, Cy = -4, Cz = 2, Fx = 0, Fy = 4, Fz = -2, Ux = 0, Uy = 1, Uz = 0;
// Posição inicial da bola
GLfloat Bx = 0, By = 0, Bz = 0.25;
char placar[10] = " 0 x 0";

int frame = 0.2;
double turningSpeed = 1.0;

void put_pixel(GLfloat xo, GLfloat yo){ 
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex3f(xo, yo, 0.25);
    glEnd();
}

void put_pixel_center(GLfloat xo, GLfloat yo){ 
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(xo, yo, 0.25);
    glEnd();
}

void bresenhamCirxularEsq(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc+x, yc-y);
        put_pixel(xc+y, yc-x);
        put_pixel(xc+y, yc+x);
        put_pixel(xc+x, yc+y);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}

void bresenhamCirxularDir(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc-x, yc+y);
        put_pixel(xc-y, yc+x);
        put_pixel(xc-y, yc-x);
        put_pixel(xc-x, yc-y);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}

void bresenhamCirxular(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc+x, yc-y);
        put_pixel(xc+y, yc-x);
        put_pixel(xc+y, yc+x);
        put_pixel(xc+x, yc+y);
        put_pixel(xc-x, yc+y);
        put_pixel(xc-y, yc+x);
        put_pixel(xc-y, yc-x);
        put_pixel(xc-x, yc-y);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}

void bresenhamCirxularInfDirEscanteio(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc-x, yc+y);
        put_pixel(xc-y, yc+x);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}


void bresenhamCirxularSupDirEscanteio(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {

        put_pixel(xc-y, yc-x);
        put_pixel(xc-x, yc-y);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}

void bresenhamCirxularInfEsqEscanteio(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc+y, yc+x);
        put_pixel(xc+x, yc+y);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}

void bresenhamCirxularSupEsqEscanteio(GLfloat xc, GLfloat yc, GLfloat raio){
    GLfloat x = 0, y = raio;
    GLfloat d = raio;

    while (y > x)
    {
        put_pixel(xc+x, yc-y);
        put_pixel(xc+y, yc-x);

        if(d < 0){
            d+=2*x+0.0003;
        }
        else{
            d+=2*(x-y) + 0.0005;
            y-=0.0001;
        }
        x+=0.0001;
    }
}



void bresenhamy(GLfloat xo, GLfloat yo, GLfloat xf, GLfloat yf){
    GLfloat dy = yf - yo;
    GLfloat dx = xf - xo;
    
    GLfloat E = 2 * dy;
    GLfloat Ne = 2 * (dx - dy);
    
    GLfloat d = 2 * dx - dy;

    GLfloat x = xo, y = yo;


    while (y < yf){
    // printf("foi %d\n", (int)x);
        put_pixel(x, y);
        if (d <= 0){
            y += 0.001;
            d += E;
        }
        else{
            // x += 0.001;
            y += 0.001;
            d += Ne;
        }
    }
}

void bresenhamx(GLfloat xo, GLfloat yo, GLfloat xf, GLfloat yf){
    GLfloat dy = yf - yo;
    GLfloat dx = xf - xo;
    
    GLfloat E = 2 * dy;
    GLfloat Ne = 2 * (dy - dx);
    
    GLfloat d = 2 * dy - dx;

    GLfloat x = xo, y = yo;


    while (x < xf || y < yf){
    // printf("foi %d\n", (int)x);
        put_pixel(x, y);
        if (d <= 0){
            x += 0.001;
            d += E;
        }
        else{
            x += 0.001;
            y += 0.001;
            d += Ne;
        }
    }
}

void MyInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
}
 
void Square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
    glBegin(GL_POLYGON);
 
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
 
    glEnd();
}
 
 
 
void trave(GLfloat t0[], GLfloat t1[], GLfloat t2[], GLfloat t3[], GLfloat t4[], GLfloat t5[], GLfloat t6[], GLfloat t7[]){
    glColor3f(1,1,1);
    Square(t0, t1, t2, t3);
 
    glColor3f(1,1,1);
    Square(t4, t5, t6, t7);
 
    glColor3f(1,1,1);
    Square(t0, t4, t7, t3);
 
    glColor3f(1,1,1);
    Square(t1, t5, t6, t2);
 
    glColor3f(1,1,1);
    Square(t3, t2, t6, t7);
 
    glColor3f(1,1,1);
    Square(t0, t1, t5, t4);
 
}
 
void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    // glColor3f(1, 0, 0); // 
    glColor3f(0, 1, 0); // green
    Square(V0, V1, V2, V3);
 
    glColor3f(0, 1, 0); // green
    Square(V4, V5, V6, V7);
 
    // glColor3f(0, 0, 1); // blue
    glColor3f(0, 1, 0); // green
    Square(V0, V4, V7, V3);
 
    // glColor3f(1, 1, 0);
    glColor3f(0, 1, 0); // green
    Square(V1, V5, V6, V2);
 
    // glColor3f(1, 0, 1); 
    glColor3f(0, 1, 0); // green
    Square(V3, V2, V6, V7);
 
    // glColor3f(0, 1, 1);
    glColor3f(0, 1, 0); // green
    Square(V0, V1, V5, V4);
}

void bresenham(){
    // glPopMatrix();

    glPushMatrix();
    bresenhamx(-1, 1, 1, 1); // linha superior
    bresenhamx(-1, -1, 1, -1); // linha inferior
    bresenhamy(-1, -1, -1, 1); // linha esquerda
    bresenhamy(1, -1, 1, 1);  // linha direita
    bresenhamy(0, -1, 0, 1);  // linha central

    //area direita
    bresenhamy(0.6, -0.6, 0.6, 0.6);
    bresenhamx(0.6, -0.6, 1, -0.6);
    bresenhamx(0.6, 0.6, 1, 0.6);

    //area pequena direita
    bresenhamy(0.8, -0.3, 0.8, 0.3);
    bresenhamx(0.8, -0.3, 1, -0.3);
    bresenhamx(0.8, 0.3, 1, 0.3);

    //area esquerda
    bresenhamy(-0.6, -0.6, -0.6, 0.6);
    bresenhamx(-1, -0.6, -0.6, -0.6);
    bresenhamx(-1, 0.6, -0.6, 0.6);

    //area pequena esquerda
    bresenhamy(-0.8, -0.3, -0.8, 0.3);
    bresenhamx(-1, -0.3, -0.8, -0.3);
    bresenhamx(-1, 0.3, -0.8, 0.3);

    bresenhamCirxular(0, 0, 0.25);
    bresenhamCirxularEsq(-0.6, 0, 0.15);
    bresenhamCirxularDir(0.6, 0, 0.15);

    bresenhamCirxularSupEsqEscanteio(-1, 1, 0.07);
    bresenhamCirxularInfEsqEscanteio(-1,-1,0.07);
    bresenhamCirxularSupDirEscanteio(1, 1, 0.07);
    bresenhamCirxularInfDirEscanteio(1,-1,0.07);

    put_pixel_center(-0.7, 0);
    put_pixel_center(0.7, 0);
    put_pixel_center(0, 0);
    // glPopMatrix();
}

void bola(){

    glPushMatrix();
    glColor3f(0, 0, 1);
    turningSpeed = 1.5;
    glRotatef(turningSpeed * frame, 0, 1, 0);
    glTranslatef(Bx, By, Bz+0.02);
    glutSolidSphere(0.02, 10, 10);
    glPopMatrix();
    // bresenham();
 
}
 
void displayScore(float x, float y, void *font){
    glColor3f(1,1,1);
    
    glRasterPos2f(x,y);
    glutBitmapString(font, placar);
}

void arquibancada(GLfloat p0[], GLfloat p1[], GLfloat p2[], GLfloat p3[], GLfloat p4[], GLfloat p5[], GLfloat p6[], GLfloat p7[]){
    glColor3f(1,0,0);
    Square(p0, p1, p2, p3);
 
    glColor3f(1,0,0);
    Square(p4, p5, p6, p7);
 
    glColor3f(1,0,0);
    Square(p0, p4, p7, p3);
 
    glColor3f(1,0,0);
    Square(p1, p5, p6, p2);
 
    glColor3f(1,0,0);
    Square(p3, p2, p6, p7);
 
    glColor3f(1,0,0);
    Square(p0, p1, p5, p4);
}

void  arquibancadas(){
    GLfloat arquibancadaGolEsq[8][3] =   {
                            {-2, 2, 0.35}, 
                            {-1.5, 2, 0.35},
                            {-1.5, -2, 0.35},
                            {-2, -2, 0.35},
                            {-2, 2, 0.25}, 
                            {-1.5, 2, 0.25},
                            {-1.5, -2, 0.25},
                            {-2, -2, 0.25},
                        };

    GLfloat arquibancadaGolDir[8][3] =   {
                            {1.5, 2, 0.35}, 
                            {2, 2, 0.35},
                            {2, -2, 0.35},
                            {1.5, -2, 0.35},
                            {1.5, 2, 0.25}, 
                            {2, 2, 0.25},
                            {2, -2, 0.25},
                            {1.5, -2, 0.25},
                        };

    GLfloat arquibancadaFront[8][3] =   {
                            {-2, -1.5, 0.35}, 
                            {2, -1.5, 0.35},
                            {2, -2, 0.35},
                            {-2, -2, 0.35},
                            {-2, -1.5, 0.25}, 
                            {2, -1.5, 0.25},
                            {2, -2, 0.25},
                            {-2, -2, 0.25},
                        };

    GLfloat arquibancadaBack[8][3] =   {
                            {-2, 2, 0.35}, 
                            {2, 2, 0.35},
                            {2, 1.5, 0.35},
                            {-2, 1.5, 0.35},
                            {-2, 2, 0.25}, 
                            {2, 2, 0.25},
                            {2, 1.5, 0.25},
                            {-2, 1.5, 0.25},
                        };
    
    arquibancada(arquibancadaGolEsq[0], arquibancadaGolEsq[1], arquibancadaGolEsq[2], arquibancadaGolEsq[3], arquibancadaGolEsq[4], arquibancadaGolEsq[5], arquibancadaGolEsq[6], arquibancadaGolEsq[7]);
     arquibancada(arquibancadaGolDir[0], arquibancadaGolDir[1], arquibancadaGolDir[2], arquibancadaGolDir[3], arquibancadaGolDir[4], arquibancadaGolDir[5], arquibancadaGolDir[6], arquibancadaGolDir[7]);
     arquibancada(arquibancadaFront[0], arquibancadaFront[1], arquibancadaFront[2], arquibancadaFront[3], arquibancadaFront[4], arquibancadaFront[5], arquibancadaFront[6], arquibancadaFront[7]);
     arquibancada(arquibancadaBack[0], arquibancadaBack[1], arquibancadaBack[2], arquibancadaBack[3], arquibancadaBack[4], arquibancadaBack[5], arquibancadaBack[6], arquibancadaBack[7]);
}

void Draw()
{
    GLfloat VCampo[8][3] =   {
                            {-2, 2, 0.25}, 
                            {2, 2, 0.25},
                            {2, -2, 0.25},
                            {-2, -2, 0.25},
                            {-2, 2, 0}, 
                            {2, 2, 0},
                            {2, -2, 0},
                            {-2, -2, 0},
                        };
    

    GLfloat t1i[8][3] =   {
                            {-1, 0.2, 0.55},
                            {-0.98, 0.2, 0.55},
                            {-0.98, 0.18, 0.55},
                            {-1, 0.18, 0.55},
                            {-1, 0.2, 0.20},
                            {-0.98, 0.2, 0.20},
                            {-0.98, 0.18, 0.20},
                            {-1, 0.18, 0.20},
                        };
 
    GLfloat t2i[8][3] =   {
                            {-1, -0.2, 0.55},
                            {-0.98, -0.2, 0.55},
                            {-0.98, -0.18, 0.55},
                            {-1, -0.18, 0.55},
                            {-1, -0.2, 0.20},
                            {-0.98, -0.2, 0.20},
                            {-0.98, -0.18, 0.20},
                            {-1, -0.18, 0.20},
                        };
 
    GLfloat t3i[8][3] =   {
                            {-1, -0.2, 0.55},
                            {-0.98, -0.2, 0.55},
                            {-0.98, 0.2, 0.55},
                            {-1, 0.2, 0.55},
                            {-1, -0.2, 0.54},
                            {-0.98, -0.2, 0.54},
                            {-0.98, 0.2, 0.54},
                            {-1, 0.2, 0.54},
                        };
 
    GLfloat t4i[8][3] =   {
                            {1, 0.2, 0.55},
                            {0.98, 0.2, 0.55},
                            {0.98, 0.18, 0.55},
                            {1, 0.18, 0.55},
                            {1, 0.2, 0.20},
                            {0.98, 0.2, 0.20},
                            {0.98, 0.18, 0.20},
                            {1, 0.18, 0.20},
                        };
 
    GLfloat t5i[8][3] =   {
                            {1, -0.2, 0.55},
                            {0.98, -0.2, 0.55},
                            {0.98, -0.18, 0.55},
                            {1, -0.18, 0.55},
                            {1, -0.2, 0.20},
                            {0.98, -0.2, 0.20},
                            {0.98, -0.18, 0.20},
                            {1, -0.18, 0.20},
                        };
 
    GLfloat t6i[8][3] =   {
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
    gluLookAt(Cx, Cy, Cz, Fx+Cx, Fy+Cy, Fz+Cz, Ux, Uy, Uz);
    glPushMatrix();
    Cube(VCampo[0], VCampo[1], VCampo[2], VCampo[3], VCampo[4], VCampo[5], VCampo[6], VCampo[7]);
    trave(t1i[0], t1i[1], t1i[2], t1i[3], t1i[4], t1i[5], t1i[6], t1i[7]);
    trave(t2i[0], t2i[1], t2i[2], t2i[3], t2i[4], t2i[5], t2i[6], t2i[7]);
    trave(t3i[0], t3i[1], t3i[2], t3i[3], t3i[4], t3i[5], t3i[6], t3i[7]);
    trave(t4i[0], t4i[1], t4i[2], t4i[3], t4i[4], t4i[5], t4i[6], t4i[7]);
    trave(t5i[0], t5i[1], t5i[2], t5i[3], t5i[4], t5i[5], t5i[6], t5i[7]);
    trave(t6i[0], t6i[1], t6i[2], t6i[3], t6i[4], t6i[5], t6i[6], t6i[7]);
    arquibancadas();
    bresenham();
    glPopMatrix();
    bola();
 
    displayScore(-0.5f, 8.0f, GLUT_BITMAP_TIMES_ROMAN_24);
 
    glutSwapBuffers();
}
 
void Key(unsigned char ch, int x, int y)
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
            if(Bx < -1.04){
                if((By < 0.28 && By > -0.18)){
                    int tam = strlen(placar)-1;
                    if(placar[tam] - '0' + 1 > 9){
                        placar[tam+1] = (placar[tam] - '0' + 1) % 10 + '0';
                        placar[tam] = (placar[tam] - '0' + 1) / 10 + '0';
                    }
                    else{
                        placar[tam] += 1;
                    }
                    Bx = 0, By = 0, Bz = 0.25;
                }
                else{
                    Bx = 0;
                }
            }
            break;
        case 'd':
            // Altera a velocidade da bola em x
            Bx += 0.03;
            if(Bx > 1.04){
                if((By < 0.28 && By > -0.18)){
                    int tam = 1;
                    if(placar[tam] - '0' + 1 > 9){
 
                        placar[tam-1] = (placar[tam] - '0' + 1) / 10 + '0';
                        placar[tam] = (placar[tam] - '0' + 1) % 10 + '0';
                    }
                    else{
                        placar[tam] += 1;
                    }
                    Bx = 0, By = 0, Bz = 0.25;
                }
                else{
                    Bx = 0;
                }
            }
            break;\
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
            Cz = Cz - 0.1;
            break;
        case 'Z':
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
    MyInit();
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Key);
    glutMainLoop();
    return 0;
}
