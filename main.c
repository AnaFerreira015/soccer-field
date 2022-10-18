// #include<windows.h>
#include<GL/glut.h>
#include<GL/glut.h>
#include <stdio.h>
#include <string.h>
 
GLfloat Cx = -2, Cy = -4, Cz = 1;
GLfloat Bx = 0, By = 0, Bz = 0.25;
char str[10] = " 0 x 0";
 
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
 
void bola(){
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(Bx,By,Bz+0.02);
    glutSolidSphere(0.02, 10, 10);
    glPopMatrix();
 
}
 
void displayScore(float x, float y, void *font){
    glColor3f(1,1,1);
    
    glRasterPos2f(x,y);
    glutBitmapString(font, str);
}
 
void Draw()
{
    GLfloat V[8][3] =   {
                            {-1, 1, 0.25}, 
                            {1, 1, 0.25},
                            {1, -1, 0.25},
                            {-1, -1, 0.25},
                            {-1, 1, -0.25}, 
                            {1, 1, -0.25},
                            {1, -1, -0.25},
                            {-1, -1, -0.25},
                        };
 
    GLfloat t1i[8][3] =   {
                            {-1, 0.3, 0.55},
                            {-0.98, 0.3, 0.55},
                            {-0.98, 0.28, 0.55},
                            {-1, 0.28, 0.55},
                            {-1, 0.3, 0},
                            {-0.98, 0.3, 0},
                            {-0.98, 0.28, 0},
                            {-1, 0.28, 0},
                        };
 
    GLfloat t2i[8][3] =   {
                            {-1, -0.2, 0.55},
                            {-0.98, -0.2, 0.55},
                            {-0.98, -0.18, 0.55},
                            {-1, -0.18, 0.55},
                            {-1, -0.2, 0},
                            {-0.98, -0.2, 0},
                            {-0.98, -0.18, 0},
                            {-1, -0.18, 0},
                        };
 
    GLfloat t3i[8][3] =   {
                            {-1, -0.2, 0.55},
                            {-0.98, -0.2, 0.55},
                            {-0.98, 0.3, 0.55},
                            {-1, 0.3, 0.55},
                            {-1, -0.2, 0.54},
                            {-0.98, -0.2, 0.54},
                            {-0.98, 0.3, 0.54},
                            {-1, 0.3, 0.54},
                        };
 
    GLfloat t4i[8][3] =   {
                            {1, 0.3, 0.55},
                            {0.98, 0.3, 0.55},
                            {0.98, 0.28, 0.55},
                            {1, 0.28, 0.55},
                            {1, 0.3, 0},
                            {0.98, 0.3, 0},
                            {0.98, 0.28, 0},
                            {1, 0.28, 0},
                        };
 
    GLfloat t5i[8][3] =   {
                            {1, -0.2, 0.55},
                            {0.98, -0.2, 0.55},
                            {0.98, -0.18, 0.55},
                            {1, -0.18, 0.55},
                            {1, -0.2, 0},
                            {0.98, -0.2, 0},
                            {0.98, -0.18, 0},
                            {1, -0.18, 0},
                        };
 
    GLfloat t6i[8][3] =   {
                            {1, -0.2, 0.55},
                            {0.98, -0.2, 0.55},
                            {0.98, 0.3, 0.55},
                            {1, 0.3, 0.55},
                            {1, -0.2, 0.54},
                            {0.98, -0.2, 0.54},
                            {0.98, 0.3, 0.54},
                            {1, 0.3, 0.54},
                        };
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glLoadIdentity();
    gluLookAt(Cx+2, Cy+2, Cz, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
    Cube(V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7]);
    trave(t1i[0], t1i[1], t1i[2], t1i[3], t1i[4], t1i[5], t1i[6], t1i[7]);
    trave(t2i[0], t2i[1], t2i[2], t2i[3], t2i[4], t2i[5], t2i[6], t2i[7]);
    trave(t3i[0], t3i[1], t3i[2], t3i[3], t3i[4], t3i[5], t3i[6], t3i[7]);
    trave(t4i[0], t4i[1], t4i[2], t4i[3], t4i[4], t4i[5], t4i[6], t4i[7]);
    trave(t5i[0], t5i[1], t5i[2], t5i[3], t5i[4], t5i[5], t5i[6], t5i[7]);
    trave(t6i[0], t6i[1], t6i[2], t6i[3], t6i[4], t6i[5], t6i[6], t6i[7]);
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
            By += 0.03;
            By = (By > 1.04) ? 0 : By;
            break;
        case 's':
            By -= 0.03;
            By = (By < -1.04) ? 0 : By;
            break;
        case 'a':
            Bx -= 0.03;
            // printf("%lf\n", By);
            if(Bx < -1.04){
                if((By < 0.28 && By > -0.18)){
                    int tam = strlen(str)-1;
                    if(str[tam] - '0' + 1 > 9){
                        str[tam+1] = (str[tam] - '0' + 1) % 10 + '0';
                        str[tam] = (str[tam] - '0' + 1) / 10 + '0';
                    }
                    else{
                        str[tam] += 1;
                    }
                    Bx = 0, By = 0, Bz = 0.25;
                }
                else{
                    Bx = 0;
                }
            }
            // Bx = (Bx < -1.04) ? ((By < 0.28 && By > -0.18) ? str[strlen(str)-1] = str[strlen(str)-1] + 1, 0 : 0) : Bx;
            // printf("%s\n", str);
            break;
        case 'd':
            Bx += 0.03;
            if(Bx > 1.04){
                if((By < 0.28 && By > -0.18)){
                    int tam = 1;
                    if(str[tam] - '0' + 1 > 9){
 
                        str[tam-1] = (str[tam] - '0' + 1) / 10 + '0';
                        str[tam] = (str[tam] - '0' + 1) % 10 + '0';
                    }
                    else{
                        str[tam] += 1;
                    }
                    Bx = 0, By = 0, Bz = 0.25;
                }
                else{
                    Bx = 0;
                }
            }
            // printf("%lf\n", By);
            // Bx = (Bx > 1.04) ? ((By < 0.28 && By > -0.18) ? str[0] = str[0] + 1, 0 : 0) : Bx;
            // printf("%s\n", str);
            break;\
        case 'W':
            Bz += 0.03;
            Bz = (Bz > 0.7) ? 0.25 : Bz;
            break;
        case 'S':
            Bz -= 0.03;
            Bz = (Bz < 0.25) ? 0.25 : Bz;
            break;
        case 'x':
            Cx = Cx - 0.5;
            break;
        case 'X':
            Cx = Cx + 0.5;
            break;
 
        case 'y':
            Cy = Cy - 0.5;
            break;
        case 'Y':
            Cy = Cy + 0.5;
            break;
 
        case 'z':
            Cz = Cz - 0.5;
            break;
        case 'Z':
            Cz = Cz + 0.5;
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