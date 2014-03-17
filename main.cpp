/*
 * JASPREET SINGH
 * 2D GAME 
 * GRAPHICS PROJECT
 * 21/01/14
 */


#include <iostream>
#include <cmath>
#include <vector>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(rad) (rad * (180/PI))

// Function Declarations
void drawScene();
void update(int value);
void bulletrecharge(int value);
void drawBox(float len);
void drawBall(float rad);
void drawLine(float x1,float y1, float x2, float y2);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void mousemotion(int x, int y);
void initialize();

// Global Variables
float box_len = 4.0f;
float ball_x = box_len/40;
float ball_y = 0.0f;
float ball_velx = box_len/400;
float ball_vely = box_len/200;
float ball_rad = box_len/20;
float small_box_len = box_len/10;
float spider_len = box_len/40;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 

float r_box_x = (-box_len/2)+box_len/20;              //for red box
float r_box_y = (-box_len/2)+box_len/20+box_len/30;
float r_box_z = 0.0;

float r_left = -box_len/2;
float r_right = box_len/2;

float g_box_x = (+box_len/2)-box_len/20;              //for green box
float g_box_y = (-box_len/2)+box_len/20+box_len/30;
float g_box_z = 0.0;

float g_left = -box_len/2;
float g_right = box_len/2;

float gun_x = 0.0;                                    //for gun
float gun_y = (-box_len/2)+box_len/20+box_len/30;
float gun_z = 0.0;
float up = -box_len/40;

float gun_left = -box_len/2;
float gun_right = box_len/2;

float gun_angle = 0.0f;
float gun_angle_change = (box_len*10)/8;
float pos_x, 
      pos_y, 
      vel;

float mousex,
      mousey,
      mousez;

int w, h;
const void* font=GLUT_BITMAP_TIMES_ROMAN_24;
char s[30]; 

float interval = 1.0;

int color,
    shoot = 1,
    score = 0,
    pause = 0,
    move = 1;

char clr;

int red=0, 
    green=0, 
    blue = 1, 
    max_spiders = 10,
    number_bullets = 0,
    mouseleft = 0,
    mouseright = 0;

struct spider {

  float pos_x;
  float pos_y;
  float pos_z;
  float vel;
  int bottom;
  int checked;
  int clr;            // 0->red 1->green 2->black

};

struct bullet{

  float angle,
        x,
        y,
        hity,
        speed;

  int bullet,
      touched;
};

int gameover=0;

// draw spider variables
float rad_x=0.05*box_len/4;
float rad_y=0.07*box_len/4;

float leg1_x=-1*0.05*box_len/4;
float leg1_y=0.0f;
float leg1_hei=0.1*box_len/4;
float leg1_ele=0.01*box_len/4;

float leg2_x=-0.15*box_len/4;
float leg2_y=0.01*box_len/4;
float leg2_hei=0.1*box_len/4;
float leg2_ele=0.05*box_len/4;

float leg3_x=-0.15*box_len/4;
float leg3_y=-0.03*box_len/4;
float leg3_hei=0.1*box_len/4;
float leg3_ele=-0.05*box_len/4;

float leg4_x=0.05*box_len/4;
float leg4_y=0.0;
float leg4_hei=-0.1*box_len/4;
float leg4_ele=0.01*box_len/4;

float leg5_x=0.15*box_len/4;
float leg5_y=0.01*box_len/4;
float leg5_hei=-0.1*box_len/4;
float leg5_ele=0.05*box_len/4;

float leg6_x=-0.05*box_len/4;
float leg6_y=-0.03*box_len/4;
float leg6_hei=0.1*box_len/4;
float leg6_ele=-0.01*box_len/4;

float leg7_x=0.05*box_len/4;
float leg7_y=-0.03*box_len/4;
float leg7_hei=-0.1*box_len/4;
float leg7_ele=-0.01*box_len/4;

float leg8_x=0.15*box_len/4;
float leg8_y=-0.03*box_len/4;
float leg8_hei=-0.1*box_len/4;
float leg8_ele=-0.05*box_len/4;

float leg9_x=-0.05*box_len/4;
float leg9_y=0.13*box_len/4;
float leg9_hei=-0.05*box_len/4;
float leg9_ele=-0.1*box_len/4;

float leg10_x=-0.15*box_len/4;
float leg10_y=0.18*box_len/4;
float leg10_hei=-0.1*box_len/4;
float leg10_ele=-0.05*box_len/4;

float leg11_x=0.03*box_len/4;
float leg11_y=0.05*box_len/4;
float leg11_hei=-0.05*box_len/4;
float leg11_ele=0.1*box_len/4;

float leg12_x=0.08*box_len/4;
float leg12_y=0.15*box_len/4;
float leg12_hei=-0.1*box_len/4;
float leg12_ele=0.05*box_len/4;

float leg13_x=-0.02*box_len/4;
float leg13_y=-0.06*box_len/4;
float leg13_hei=0.05*box_len/4;
float leg13_ele=-0.1*box_len/4;

float leg14_x=-0.07*box_len/4;
float leg14_y=-0.15*box_len/4;
float leg14_hei=0.1*box_len/4;
float leg14_ele=-0.05*box_len/4;

float leg15_x=0.02*box_len/4;
float leg15_y=-0.05*box_len/4;
float leg15_hei=-0.05*box_len/4;
float leg15_ele=-0.1*box_len/4;

float leg16_x=0.06*box_len/4;
float leg16_y=-0.14*box_len/4;
float leg16_hei=-0.1*box_len/4;
float leg16_ele=-0.05*box_len/4;


float bullet_speed = 0.07,
      bullet_len = 0.2;

struct spider sp[100];
struct bullet b[100];

void drawleg1(float x1,float y1,float len,float ele)
{
  glBegin(GL_LINES);
  glVertex3f(x1, y1,0.0f);
  glVertex3f(x1-len,y1+ele,0.0f);
  glEnd();

}

void drawleg2(float x1,float y1)
{ 
  glBegin(GL_LINES);
  glVertex3f(x1, y1,0.0f);
  glVertex3f(x1-0.1,y1+0.01,0.0f);
  glEnd();

}

void DrawEllipse(float radiusX, float radiusY)
{
  int i;
  glBegin(GL_TRIANGLE_FAN);
  for(i=0;i<360;i++)
  {
    glVertex2f(cos(DEG2RAD(i))*radiusX, sin(DEG2RAD(i))*radiusY);
  }
  glEnd();
}

void DrawhEllipse(float radiusX, float radiusY)
{
  int i;
  glBegin(GL_LINE_STRIP);
  for(i=0;i<360;i++)
  {
    glVertex2f(cos(DEG2RAD(i))*radiusX, sin(DEG2RAD(i))*radiusY);
  }
  glEnd();
}

//Calculate string length

int string_length(char *pointer)
{
  int c = 0;

  while( *(pointer+c) != '\0' )
    c++;

  return c;
}

//reverse a string
void reverse(char *string) 
{
  int length, c;
  char *begin, *end, temp;

  length = string_length(string);

  begin = string;
  end = string;

  for ( c = 0 ; c < ( length - 1 ) ; c++ )
    end++;

  for ( c = 0 ; c < length/2 ; c++ ) 
  {        
    temp = *end;
    *end = *begin;
    *begin = temp;

    begin++;
    end--;
  }
}

void drawSpider()
{
  int i,l=100;
  for(i=0;i<l;i++)
  {
    glPushMatrix();
    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(0.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {
      glColor3f(0.0f, 0.0f, 0.0f);
    }
    DrawEllipse(rad_x,rad_y);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg1_x,leg1_y,leg1_hei,leg1_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg2_x,leg2_y,leg2_hei,leg2_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg6_x,leg6_y,leg6_hei,leg6_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg3_x,leg3_y,leg3_hei,leg3_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg4_x,leg4_y,leg4_hei,leg4_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg5_x,leg5_y,leg5_hei,leg5_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg7_x,leg7_y,leg7_hei,leg7_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg8_x,leg8_y,leg8_hei,leg8_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg9_x,leg9_y,leg9_hei,leg9_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg10_x,leg10_y,leg10_hei,leg10_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg11_x,leg11_y,leg11_hei,leg11_ele);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {
      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg12_x,leg12_y,leg12_hei,leg12_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg13_x,leg13_y,leg13_hei,leg13_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg14_x,leg14_y,leg14_hei,leg14_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg15_x,leg15_y,leg15_hei,leg15_ele);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(sp[i].pos_x, sp[i].pos_y, sp[i].pos_z);
    if(sp[i].clr==0)
    {
      glColor3f(1.0f, 0.0f, 0.0f);
    }
    else if(sp[i].clr==1)
    {
      glColor3f(0.0f, 1.0f, 0.0f);
    }
    else if(sp[i].clr==2)
    {

      glColor3f(0.0f, 0.0f, 0.0f);
    }
    drawleg1(leg16_x,leg16_y,leg16_hei,leg16_ele);
    glPopMatrix();
  }
}



void getCoord( int x, int y)
{
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLfloat winX, winY, winZ;
  GLdouble posX, posY, posZ;
  glGetIntegerv(GL_VIEWPORT, viewport);
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  winX = (float)x;
  winY = (float)viewport[3] - (float)y;
  glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
  //winZ=0;
  gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
  mousex=posX*100/2;
  mousey=(posY*100)/2;
  mousez=0.0f;//posZ*100;
  glutPostRedisplay();
}


void setOrthographicProjection() {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, w, 0, h);
  glScalef(1, -1, 1);
  glTranslatef(0, -h, 0);
  glMatrixMode(GL_MODELVIEW);
}
void resetPerspectiveProjection() {
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
void renderBitmapString(float x, float y, void *font,const char *string){
  const char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
} 
int main(int argc, char **argv) {

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  int w = glutGet(GLUT_SCREEN_WIDTH);
  int h = glutGet(GLUT_SCREEN_HEIGHT);
  int windowWidth = w * 2 / 3;
  int windowHeight = h * 2 / 3;

  glutInitWindowSize(windowWidth, windowHeight);
  glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

  glutCreateWindow("Arachnophobia");  // Setup the window
  initRendering();

  // Register callbacks
  glutDisplayFunc(drawScene);
  glutIdleFunc(drawScene);
  glutKeyboardFunc(handleKeypress1);
  glutSpecialFunc(handleKeypress2);
  glutMouseFunc(handleMouseclick);
  glutMotionFunc(mousemotion);
  glutReshapeFunc(handleResize);
  initialize();
  glutTimerFunc(10, update, 0);
  glutTimerFunc(1000, bulletrecharge, 0);
  glutMainLoop();
  return 0;
}


void initialize() {

  for(int i=0;i<100;i++) {

    sp[i].pos_x = (box_len/2) - (rand()%10 + 1)*(box_len/10) + box_len/20;
    sp[i].pos_y = box_len/2 + i * interval;                               //interval used
    sp[i].pos_z = 0.0f;
    sp[i].clr = rand()%3;
    sp[i].vel = 0.002 * ((rand()%5) +1);
    sp[i].bottom = 0;
    sp[i].checked = 0;
  }
}

// Function to draw objects on the screen
void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();

  // Draw Box
  glTranslatef(0.0f, 0.0f, -5.0f);
  glColor3f(0.0f, 0.0f, 0.0f);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  drawBox(box_len);

  //Draw bottom-line
  drawLine(-box_len/2,(-box_len/2)+box_len/10,box_len/2,(-box_len/2)+box_len/10);

  //Draw Small Red Box
  glPushMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glTranslatef(r_box_x, r_box_y, r_box_z );
  glColor3f(1.0f, 0.0f, 0.0f);
  drawBox(small_box_len);
  glTranslatef(0.0,box_len/20,0.0);
  if(red == 1)
    DrawEllipse(box_len/20,box_len/80);
  else
    DrawhEllipse(box_len/20,box_len/80);
  glColor3f(1.0f, 0.0f, 0.0f);
  glTranslatef(0.0,-box_len/10,0.0);
  DrawEllipse(box_len/20,box_len/40);
  
  glPopMatrix();

  //Draw Small Green Box
  glPushMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glTranslatef(g_box_x,g_box_y, g_box_z);
  glColor3f(0.0f, 1.0f, 0.0f);
  drawBox(small_box_len);
  glTranslatef(0.0,box_len/20,0.0);
  if(green == 1)
    DrawEllipse(box_len/20,box_len/80);
  else
    DrawhEllipse(box_len/20,box_len/80);
  glColor3f(0.0f, 1.0f, 0.0f);
  glTranslatef(0.0,-box_len/10,0.0);
  DrawEllipse(box_len/20,box_len/40);
  glPopMatrix();

  //Draw gun
  glPushMatrix();
  glTranslatef(gun_x, gun_y, gun_z);
  glRotatef(gun_angle,0.0f,0.0f,1.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  drawBall(ball_rad);
  glColor3f(0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, ball_rad, 0.0f);
    
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  
  glRectf(-box_len/80,box_len/40, box_len/80, up/*-box_len/40*/);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glRectf(-box_len/80,up/*box_len/40*/, box_len/80, -box_len/40);
  if(blue == 0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  
  
  glTranslatef(0.0,-ball_rad,0.0f);
  
  
  glRectf(-box_len/40-box_len/20,box_len/200,box_len/40+box_len/20,-box_len/200);
  glTranslatef(-box_len/20-box_len/40,0.0,0.0);
  if(blue == 0)
    DrawhEllipse(box_len/80,box_len/20);
  else
    DrawEllipse(box_len/80,box_len/20);
  glTranslatef(box_len/10+box_len/40+box_len/40,0.0,0.0);
  if(blue == 0)
    DrawhEllipse(box_len/80,box_len/20);
  else
    DrawEllipse(box_len/80,box_len/20);

  
  glPopMatrix();

  //print score
  glPushMatrix();
  setOrthographicProjection();
  glLoadIdentity();
  renderBitmapString(4*(box_len/20-box_len/40),-8*(box_len/40),(void *)font,"score");
  char scr[40];

  /*
   * int len=0;
   int negative = 0;
   */


  sprintf(scr,"%d",score);
  renderBitmapString(4*(box_len/20-box_len/40),-7*(box_len/40), (void*)font, scr);
  resetPerspectiveProjection();
  glPopMatrix();


  // if(shoot == 1)
  // glLineWidth(3);

  //Draw bullet
  for(int i=0;i<number_bullets;i++)
  {
    if(b[i].bullet == 1)
    {
      float px = b[i].x + bullet_len * sin(DEG2RAD(-b[i].angle));

      float dx = bullet_len * sin(DEG2RAD(-b[i].angle));
      float dy = bullet_len * cos(DEG2RAD(b[i].angle));

      float fx = b[i].x;
      float fy = b[i].y;

      float kx = 0.0;
      float ky = 0.0;

      glPushMatrix();
      glTranslatef(b[i].x,b[i].y,gun_z);

      if((fx >= box_len/2 || fx <= -box_len/2) && b[i].touched == 1)
        b[i].bullet = 0;

      //  Handle Reflection

      if(b[i].touched == 1)
      {
        if(px >= box_len/2 && fx <= box_len/2)
        {
          float length = (sqrt(pow(fx - box_len/2,2)+pow(fy-b[i].hity,2)));

          dx = (length) * (sin(DEG2RAD(-b[i].angle)));
          dy = (length) * (cos(DEG2RAD(-b[i].angle)));
        }
        if(px <= -box_len/2 && fx >= -box_len/2)
        {
          float length = (sqrt(pow(fx + box_len/2,2)+pow(fy-b[i].hity,2)));

          dx = (length) * (sin(DEG2RAD(-b[i].angle)));
          dy = (length) * (cos(DEG2RAD(-b[i].angle)));
        }
      }
      else
      {
        if(fx < -box_len/2 && px > -box_len/2)
        {
          kx = (fx + box_len/2)*(sin(DEG2RAD(-b[i].angle)));
          ky = (fx + box_len/2)*(cos(DEG2RAD(-b[i].angle)));
        }
        if(fx > box_len/2 && px <box_len/2)
        {
          kx = (fx - box_len/2)*(sin(DEG2RAD(-b[i].angle)));
          ky = (fx - box_len/2)*(cos(DEG2RAD(-b[i].angle)));
        }
      }


      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(kx, ky, 0.0);   // b[i].x,b[i].y
      glVertex3f(dx, dy, 0.0);
      glEnd();
      glPopMatrix();
    }
  }

  
  if(move == 0 && pause == 1)
  {
    renderBitmapString(-0.6,0.0,(void *)font,"Game Over !! :(");
    if(gameover == 0)
      system("aplay go.wav  &");
    gameover=1;
  }

  drawSpider();


  glPopMatrix();
  glutSwapBuffers();
}


void bulletrecharge(int value) {

  if(shoot==0)
  {
  system("aplay gun-cocking-01.wav  &");
  }
  shoot = 1;
  glutTimerFunc(1000, bulletrecharge, 0);
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {


  if(pause == 0)
  {
    if(up<=box_len/40)
      up+=(box_len/20)/100;
    else
    {
      if(shoot == 0)
        up=-box_len/40;
    }for(int i=0;i<number_bullets;i++)
    {

      float px = b[i].x + bullet_len * sin(DEG2RAD(-b[i].angle));
      float py = b[i].y + bullet_len * cos(DEG2RAD(b[i].angle));

      float fx = b[i].x;
      //float fy = b[i].y;
      if(py > box_len/2)
      {
        b[i].bullet = 0;
      }

      b[i].x += b[i].speed*sin(DEG2RAD(-b[i].angle ));
      b[i].y += b[i].speed*cos(DEG2RAD(b[i].angle ));


      if(b[i].touched == 0 && b[i].bullet == 1)
      {
        if(px >= box_len/2 && fx <= box_len/2)
        {
          // b[i].bullet = 0;       //reflection;
          b[number_bullets].bullet = 1;
          b[number_bullets].x = b[i].x+2*( bullet_len * sin(DEG2RAD(-b[i].angle)));
          b[number_bullets].y = b[i].y;
          b[number_bullets].angle = -b[i].angle;
          b[number_bullets].speed = bullet_speed;
          b[number_bullets].touched = 0;
          number_bullets++;
          b[i].hity = py;
          b[i].touched =1;

        }
        if(px <= -box_len/2 && fx >= -box_len/2)
        {
          // b[i].bullet = 0;      //reflection
          b[number_bullets].bullet = 1;
          b[number_bullets].x = b[i].x-2*( bullet_len * sin(DEG2RAD(-b[i].angle)));
          b[number_bullets].y = b[i].y;
          b[number_bullets].angle = -b[i].angle;
          b[number_bullets].speed = bullet_speed;
          b[number_bullets].touched = 0;
          number_bullets++;
          b[i].touched =1;
          b[i].hity = py;
        }
      }
    }


    for(int i=0;i<100;i++) {

      if(sp[i].pos_y > -box_len/2 + box_len/10 - box_len/20 && sp[i].pos_y < 100)
      {
        sp[i].pos_y -= sp[i].vel;
      }
      else                                // also includes the spiders eaten by red and green boxes and those hit by cannon 
      {
        sp[i].bottom = 1;
        if(sp[i].pos_y < 100)
        {
          if(sp[i].checked == 0)
          {
            score-=5;
            if(sp[i].pos_x < r_box_x)
            {
              if(r_left < sp[i].pos_x)
                r_left = sp[i].pos_x+box_len/20;
            }
            if(sp[i].pos_x > r_box_x)
            {
              if(r_right > sp[i].pos_x)
                r_right = sp[i].pos_x-box_len/20;
            }
            if(sp[i].pos_x < g_box_x)
            {
              if(g_left < sp[i].pos_x)
                g_left = sp[i].pos_x+box_len/20;
            }
            if(sp[i].pos_x > g_box_x)
            {
              if(g_right > sp[i].pos_x)
                g_right = sp[i].pos_x-box_len/20;
            }
            if(sp[i].pos_x < gun_x)
            {
              if(gun_left < sp[i].pos_x)
                gun_left = sp[i].pos_x+box_len/20;
            }
            if(sp[i].pos_x > gun_x)
            {
              if(gun_right > sp[i].pos_x)
                gun_right = sp[i].pos_x-box_len/20;
            }
            sp[i].checked = 1;
          }
        }
      }
    }

    for(int i=0;i<100;i++) {

      for(int j=0;j<number_bullets;j++)
      {
        float px = b[j].x + bullet_len * sin(DEG2RAD(-b[j].angle));
        float py = b[j].y + bullet_len * cos(DEG2RAD(b[j].angle));

        float fx = b[j].x;
        float fy = b[j].y;

        if(b[j].bullet == 1)
        {
          if((px <= sp[i].pos_x+box_len/20 && px >=sp[i].pos_x-box_len/20 && py >  sp[i].pos_y  - box_len/30 && py < sp[i].pos_y -box_len/30 + box_len/10) || (fx <= sp[i].pos_x+box_len/20 && fx >=sp[i].pos_x-box_len/20 && fy >  sp[i].pos_y  - box_len/30 && fy < sp[i].pos_y -box_len/30 + box_len/10))
          {
            if(sp[i].bottom == 0)
            {
              sp[i].pos_y = 1000.0f;
              b[j].bullet = 0;
              if(sp[i].clr == 2)
              {
                system("aplay grenade.wav &");
                score += 1 ;
              }
              if(sp[i].clr == 0 || sp[i].clr == 1)
              {
                score -= 1 ;
              }
            }
          }
        }
      }

      // red box catch
      if(red == 1 && sp[i].bottom == 0) {

        if(r_box_x < sp[i].pos_x+box_len/20 && r_box_x > sp[i].pos_x - box_len/20 && r_box_y > sp[i].pos_y - box_len/10)
        {
          if(sp[i].clr == 0)
          {
            system("aplay dp.wav  &");
            score += 1;
          }
          else
          {
            score -= 1;
          }
          sp[i].pos_y = 1000.0;
        }
      }

      //green box catch
      if(green == 1  && sp[i].bottom == 0) {

        if(g_box_x < sp[i].pos_x+box_len/20 && g_box_x > sp[i].pos_x - box_len/20 && g_box_y > sp[i].pos_y - box_len/10)
        {
          if(sp[i].clr == 1)
          {
            system("aplay dp.wav  &");
            score +=1;
          }
          else
            score -= 1;

          sp[i].pos_y = 1000.0;
        }
      }

      if(sp[i].bottom == 0 && sqrt(pow(sp[i].pos_x-gun_x,2) + pow(sp[i].pos_y-gun_y,2) <  box_len/20))
      {
        move = 0;
        pause = 1;
      }
    }
  }
  glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

  glBegin(GL_QUADS);
  glVertex2f(-len / 2, -len / 2);
  glVertex2f(len / 2, -len / 2);
  glVertex2f(len / 2, len / 2);
  glVertex2f(-len / 2, len / 2);
  glEnd();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawLine(float x1, float y1, float x2, float y2) {

  glColor3f(1.0,0.0,0.0); 
  glLineWidth(2);
  glBegin(GL_LINES);
  glVertex2f(x1,y1);
  glVertex2f(x2,y2);
  glEnd();

}

void drawBall(float rad) {

  if(blue == 0)
    glBegin(GL_LINE_LOOP);
  else
    glBegin(GL_TRIANGLE_FAN);
  for(int i=0 ; i<360 ; i++) {
    glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
  }
  glEnd();
}

void drawTriangle() {

  glBegin(GL_TRIANGLES);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

  glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
  glEnable(GL_COLOR_MATERIAL);    // Enable coloring
  glClearColor(1.0f, 1.0f, 1.0f, 0.5f);   // Setting a background color

//  glColor3f(174/255, 174/255, 174/255,0.5f);
}

// Function called when the window is resized
void handleResize(int w, int h) {

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

  if (key == 27 || key == 'q') {
    exit(0);     // escape key is pressed
  }
  if (key == 82 || key == 114) {
    red = 1; 
    green = 0;
    blue = 0;
  }
  if (key == 71 || key == 103) {
    green = 1;
    red = 0;
    blue = 0;
  }
  if (key == 66 || key == 98) {
    blue = 1;
    red = 0;
    green = 0;
  }
  if(key == ' ' && shoot == 1 && blue == 1 && up>=box_len/40) {
    shoot = 0;
    system("aplay silencer.wav  &");
    up=-box_len/40;
    b[number_bullets].bullet = 1;
    b[number_bullets].x = gun_x;
    b[number_bullets].y = gun_y;
    b[number_bullets].angle = gun_angle;
    b[number_bullets].speed = bullet_speed;
    b[number_bullets].touched = 0;
    number_bullets++;
  }
  if(key == 'p' || key == 'P') {

    if(move)
    {
      if(pause == 0)
        pause = 1;
      else
        pause = 0;
    }
  }
}

void handleKeypress2(int key, int x, int y) {

  if (key == GLUT_KEY_LEFT)
  {
    if(red == 1 && fabs(r_box_x-box_len/10) < fabs(box_len/2)   && r_left <= r_box_x - box_len/10 && move)
      r_box_x -= box_len/10;
    if(green == 1 && fabs(g_box_x-box_len/10) < fabs(box_len/2)   && g_left <= g_box_x - box_len/10 && move)
      g_box_x -= box_len/10;
    if(blue == 1 && fabs(gun_x-box_len/20) < fabs(box_len/2)   && gun_left <= gun_x- box_len/20 && move)
      gun_x -= 0.1;
  }
  if (key == GLUT_KEY_RIGHT)
  {
    if(red == 1 && fabs(r_box_x+box_len/10) < fabs(box_len/2)   && r_right >= r_box_x + box_len/10 && move)
      r_box_x += box_len/10;
    if(green == 1 && fabs(g_box_x+box_len/10) < fabs(box_len/2)   && g_right >= g_box_x + box_len/10 && move)
      g_box_x += box_len/10;
    if(blue == 1 && fabs(gun_x+box_len/20) < fabs(box_len/2)   && gun_right >= gun_x + box_len/20 && move)
      gun_x += 0.1;
  }
  if (key == GLUT_KEY_UP)
  {
    if(blue == 1)
    {
      if(gun_angle - gun_angle_change >= -75)
        gun_angle-=gun_angle_change;
    }
  }
  if(key == GLUT_KEY_DOWN)
  {
    if(blue == 1)
    {
      if(gun_angle + gun_angle_change <= 75)
        gun_angle+=gun_angle_change;
    }
  }
}

void handleMouseclick(int button, int state, int x, int y) {

  if (state == GLUT_DOWN)
  {
    if (button == GLUT_LEFT_BUTTON)
    {
      mouseleft = 1;
      if(move == 1 && pause == 0)
      {
        getCoord(x,y);
        if(sqrt(pow((mousex-gun_x),2)+pow((mousey-gun_y),2)) < box_len/20 )
        {
          blue = 1;
          red = green = 0;
        }
        if(sqrt(pow((mousex-r_box_x),2)+pow((mousey-r_box_y),2)) < box_len/20 )
        {
          red = 1;
          blue = green = 0;
        }
        if(sqrt(pow((mousex-g_box_x),2)+pow((mousey-g_box_y),2)) < box_len/20 )
        {
          green = 1;
          blue = red = 0;
        }
      }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
     getCoord(x,y);
     mouseright = 1;
     blue=1;
     red=0;
     green=0;
    }
  }
  else
  {
    mouseleft=0;
    mouseright=0;
    blue=0;
    red=0;
    green=0;
  }
}

void mousemotion(int x, int y)
{
  getCoord(x,y);
  if(mouseleft == 1)
  {
    if(blue == 1 && mousex < box_len/2-box_len/20 && mousex > -box_len/2+box_len/20 && gun_left <= mousex && gun_right >= mousex)
      gun_x = mousex;
    if(red == 1 && mousex < box_len/2-box_len/20 && mousex > -box_len/2+box_len/20 && r_left <= mousex && r_right >= mousex)
      r_box_x = mousex;
    if(green == 1 && mousex < box_len/2-box_len/20 && mousex > -box_len/2+box_len/20 && g_left <= mousex && g_right >= mousex)
      g_box_x = mousex;
  }
  if (mouseright == 1)
  { 
     getCoord(x,y);
     if(blue == 1)
     {
       if(RAD2DEG(atan2(mousey-gun_y,mousex-gun_x))-90<=75 && RAD2DEG(atan2(mousey-gun_y,mousex-gun_x))-90 >= -75)
          gun_angle=RAD2DEG(atan2(mousey-gun_y,mousex-gun_x))-90;
     }
   }
}
