/*
  Audrey Randall's homework 2
  Citations:
    example 26 from class
    http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "CSCIx229.h"
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;
int frame = 1;
double eyeX = 1;
double eyeY = 1;
double eyeZ = 1;
double lookX = 0;
double lookY = 0;
double lookZ = 0;
int th=0;       // Azimuth of view angle
int ph=0;       // Elevation of view angle
int mode=1;     // Dimension (1-4)
double z=0;     // Z variable
double w=1;     // W variable
double dim=2;   // Dimension of orthogonal box
char* text[] = {"","2D","3D constant Z","3D","4D"};  // Dimension display text
int obj; //loads my elf dude that I made in Sculptris. "Object display list."
//More things I copied and don't understand from example 26!
float RGBA[4] = {1,1,1,1};
#define LEN 8192  // Maximum length of text string

void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Increase w by 0.1
   else if (ch == '+')
   {
      if (mode==2)
         z += 0.1;
      else
         w += 0.1;
   }
   //  Decrease w by 0.1
   else if (ch == '-')
   {
      if (mode==2)
         z -= 0.1;
      else
         w -= 0.1;
   }
   //Change parameters
   else if(ch == 'S') {
     s+=1;
   }
   else if(ch == 's') {
     s = s-1;
   }
   else if(ch == 'B') {
      b += 0.1;
   }
   else if(ch == 'b') {
     b = b-0.1;
   }
   else if(ch == 'R') {
      r += 2;
   }
   else if(ch == 'r') {
     r = r - 2;
   }
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void setPoints(){
  int i;
   /*  Coordinates  */
   double x = 1;
   double y = 1;
   double z = 1;
   /*  Time step  */
   double dt = 0.001;

   printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
   /*
    *  Integrate 50,000 steps (50 time units with dt = 0.001)
    *  Explicit Euler integration
    */
  glColor3f(1,1,1);
  glLineWidth(1);
  glPointSize(20);
  glBegin(GL_LINES);
   for (i=0;i<50000;i++)
   {
      glColor3f(0,i/50000., 1-i/50000.);
      glVertex3d(x/30,y/30,z/30);
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      //printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
      glVertex3d(x/30,y/30,z/30);
   }
   glEnd();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph -= 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph += 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

void drawCube() {
    glBegin(GL_POLYGON);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glVertex3d(-1.0f,-1.0f, 1.0f);
    glVertex3d(-1.0f, 1.0f, 1.0f) ;
    glVertex3d(1.0f, 1.0f,-1.0f);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glVertex3d(-1.0f, 1.0f,-1.0f);
    glColor3f(1,0,0);
    glVertex3d(1.0f,-1.0f, 1.0f);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glVertex3d(1.0f,-1.0f,-1.0f);
    glVertex3d(1.0f, 1.0f,-1.0f);
    glVertex3d(1.0f,-1.0f,-1.0f);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glColor3f(0,1,0);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glVertex3d(-1.0f, 1.0f, 1.0f);
    glVertex3d(-1.0f, 1.0f,-1.0f);
    glVertex3d(1.0f,-1.0f, 1.0f);
    glVertex3d(-1.0f,-1.0f, 1.0f);
    glVertex3d(-1.0f,-1.0f,-1.0f);
    glColor3f(0,0,1);
    glVertex3d(-1.0f, 1.0f, 1.0f);
    glVertex3d(-1.0f,-1.0f, 1.0f);
    glVertex3d(1.0f,-1.0f, 1.0f);
    glVertex3d(1.0f, 1.0f, 1.0f);
    glVertex3d(1.0f,-1.0f,-1.0f);
    glVertex3d(1.0f, 1.0f,-1.0f);
    glColor3f(1,0,1);
    glVertex3d(1.0f,-1.0f,-1.0f);
    glVertex3d(1.0f, 1.0f, 1.0f);
    glVertex3d(1.0f,-1.0f, 1.0f);
    glVertex3d(1.0f, 1.0f, 1.0f);
    glVertex3d(1.0f, 1.0f,-1.0f);
    glVertex3d(-1.0f, 1.0f,-1.0f);
    glColor3f(0,1,1);
    glVertex3d(1.0f, 1.0f, 1.0f);
    glVertex3d(-1.0f, 1.0f,-1.0f);
    glVertex3d(-1.0f, 1.0f, 1.0f);
    glVertex3d(1.0f, 1.0f, 1.0f);
    glVertex3d(-1.0f, 1.0f, 1.0f);
    glVertex3d(1.0f,-1.0f, 1.0f);
    glEnd();
    glFlush();
}

void display() {
  //printf("display \n");

  //Lighting variables, taken from example 26
  float Emission[]  = {0.0,0.0,0.0,1.0};
  float Ambient[]   = {0.3,0.3,0.3,1.0};
  float Diffuse[]   = {1.0,1.0,1.0,1.0};
  float Specular[]  = {1.0,1.0,1.0,1.0};
  float Position[]  = {0.9,0.9,0.9};//{2*Cos(zh),Ylight,2*Sin(zh),1.0};
  float Shinyness[] = {16};
  //  Clear the image
  glClear(GL_COLOR_BUFFER_BIT);
  //  Reset previous transforms
  glLoadIdentity();
  //  Set view angle
  glRotated(ph,1,0,0);
  glRotated(th,0,1,0);

  glEnable(GL_NORMALIZE); //Normalizes all the normal vectors.
  glEnable(GL_LIGHTING);
  //  Enable light 0
  glEnable(GL_LIGHT0);
  //  Set ambient, diffuse, specular components and position of light 0
  glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
  glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
  glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
  glLightfv(GL_LIGHT0,GL_POSITION,Position);
  //  Set materials
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,Shinyness);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,RGBA);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,RGBA);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Specular);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

  //Draw elf dude!
  /*glPushMatrix();
  glScaled(0.1,0.1,0.1);
  glCallList(obj);
  glPopMatrix();*/

  //Draw test cube
  drawCube();

  //Draw axes
  glDisable(GL_LIGHTING);
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  glVertex3d(0,0,0);
  glVertex3d(1,0,0);
  glVertex3d(0,0,0);
  glVertex3d(0,1,0);
  glVertex3d(0,0,0);
  glVertex3d(0,0,1);
  glEnd();

  glFlush();
  glutSwapBuffers(); //this is for double buffered window. Single buffered uses glFlush.
  frame++;
}

int main(int argc,char* argv[])
{
  //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with z-buffering
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE| GLUT_DEPTH);
   glEnable(GL_DEPTH_TEST);

   //  Request 500 x 500 pixel window
   glutInitWindowSize(500,500);
   //  Create the window
   glutCreateWindow("Homework 2: Audrey Randall");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //obj = LoadOBJ("elf_obj.obj");
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
