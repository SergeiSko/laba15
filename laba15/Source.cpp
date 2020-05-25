#include <GL\glut.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define loaughtGraf 50 //максимальная ширина графика 
#define xAxisSize 500
#define yAxisSize 500
#define gragSize2 180*8*2

static GLint X0 = 30, Y0 = 30;
static GLdouble xCor1 = 0.4, yCor1 = 40000, xMove1 = 0, yMove1 = 0;
static GLdouble xCor2 = 5, yCor2 = 30, graphEasy = 1, xMove2 = 0, yMove2 = yAxisSize/2;
GLdouble xAxis[4], yAxis[4], markerSize = 10;
GLdouble* xM1 = (GLdouble*)malloc(sizeof(GLdouble) * loaughtGraf);//массивы координат ...
GLdouble* yM1 = (GLdouble*)malloc(sizeof(GLdouble) * loaughtGraf);//... точек графика
GLdouble* xM2 = (GLdouble*)malloc(sizeof(GLdouble) * ((int)gragSize2));//массивы координат ...
GLdouble* yM2 = (GLdouble*)malloc(sizeof(GLdouble) * ((int)gragSize2));//... точек графика
GLdouble* xM3 = (GLdouble*)malloc(sizeof(GLdouble) * loaughtGraf);//массивы координат ...
GLdouble* yM3 = (GLdouble*)malloc(sizeof(GLdouble) * loaughtGraf);//... точек графика

void init() {
  glClearColor(1.0, 1.0, 0.6, 0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 600, 0, 600);
}

void graph1() {
  GLdouble t;
  //GLdouble temp;
  for (int i = 0; i < loaughtGraf; i++) {
    //y= x^4 - 2x^3 - x^2 + x (формула которую нужно сделать)
    //t = i / 57.3;//перевод градусов в радианы (остался кастыль из прошлой лабы)
    t = i;
    xM1[i] = (i) / xCor1;//вычисление X коорд. точки i на графике ф-ии
    yM1[i] = (pow(i, 4) - 2 * pow(i, 3) - pow(i, 2) + i) / yCor1+2;//вычисление Y коорд.

    printf("x1[%d] =   %f, y1[%d] =   %f\n", i, xM1[i], i, yM1[i]);//вывод коорд. в консоль для отладки и наблюдения графика в цифрах
    if (xM1[i] > xAxisSize || yM1[i] > yAxisSize) break;//прекращение вычисленя графика при выходе за определенные рамки
  }
}

void graph2() {
  GLdouble t;
  for (int i = 0; i < gragSize2; i+=graphEasy) {
    //r(t) = e ^ sin(t) - 2 * cos(4*t) + (sin^5)((2t - PI)/24) (формула которую нужно сделать)
    //t - {-8*PI, 8*PI}
    
    t = i/57.3;
    xM2[i] = (i) / xCor2;//вычисление X коорд. точки i на графике ф-ии
    yM2[i] = (pow(2.71, sin(t)) - 2 * cos(4 * t) + (pow(sin((2*t - 180/57.3) / 24), 5)))*yCor2 + 2;//вычисление Y коорд.

    printf("x2[%d] =   %f, y2[%d] =   %f\n", i, xM2[i], i, yM2[i]);//вывод коорд. в консоль для отладки и наблюдения графика в цифрах
    if (xM2[i] > xAxisSize || yM2[i] > yAxisSize) break;//прекращение вычисленя графика при выходе за определенные рамки
  }
}

void axis(int x, int y) {
  xAxis[0] = xAxisSize/2 + x;
  yAxis[0] = yAxisSize + y;
  xAxis[1] = xAxisSize/2 + x;
  yAxis[1] = y;
  xAxis[2] = x;
  yAxis[2] = yAxisSize / 2 + y;
  xAxis[3] = xAxisSize + x;
  yAxis[3] = yAxisSize / 2 + y;
}

void draw() {
  int temp;
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(X0, Y0, xAxisSize, yAxisSize);
  glLineWidth(2);
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0, 0);
  graph1();
  for (int i = 0; i < loaughtGraf; i++) {//построение графика по вычеслинным координатам
    glVertex2d(xM1[i] + xAxisSize / 2, yM1[i] + yAxisSize / 2);
    //ntf("IN DROW(): x =   %f, y =   %f\n", xM[i], yM[i]);//тоже для отладки
  }
  glEnd();
  axis(0, 0);
  glLineWidth(1);
  //glViewport(X0, Y0, xAxisSize, yAxisSize);
  for (int i = 0; i < 4; i+=2) {
    glBegin(GL_LINE_STRIP);
    glColor3f(0, 0, 0);
    glVertex2d(xAxis[i], yAxis[i]);
    glVertex2d(xAxis[i+1], yAxis[i+1]);
    glEnd();
  }

  //glViewport(X0, Y0, xAxisSize, yAxisSize);
  for (int i = 0; i < xAxisSize / 10; i++) {
    glBegin(GL_LINE_STRIP);// Ось X
    temp = (i + 1) * 10;
    glVertex2d(temp, markerSize/2 + yAxisSize / 2);
    glVertex2d(temp, -markerSize/2 + yAxisSize / 2);
    glEnd();
    glBegin(GL_LINE_STRIP);// Ось Y
    temp = (i + 1) * 10;
    glVertex2d(markerSize/2 + xAxisSize / 2, temp);
    glVertex2d(-markerSize/2 + xAxisSize / 2, temp);
    glEnd();
  }
  //^^ первый график ^^ 
  //--------------------
  glViewport(X0, Y0, xAxisSize, yAxisSize);
  graph2();
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0, 0);
  for (int i = 0; i < gragSize2; i += graphEasy) {
    glVertex2f(xM2[i]+xMove2, yM2[i]+yMove2);
  }
  glEnd();
  glFlush();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_MULTISAMPLE | GLUT_STENCIL | GLUT_ACCUM);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Graphics");
  init();
  glutDisplayFunc(draw);
  glutMainLoop();
}