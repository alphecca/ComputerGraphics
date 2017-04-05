#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#define GL_PI 3.141592
using namespace std;

int TH=5000;//threshold milliseconds
float RGB=255.0;
float _angleA = 35.0f;
float _angleB;
float _angleC = 45.0f; 
float tmpx,tmpy,tmpz;
float _cameraAngle = 10.0f;
GLUquadric* qobj;
void update(int value){
  if( glutGet(GLUT_ELAPSED_TIME)>TH){
    _angleA +=2.0f;
    if(_angleA >360)
      _angleA -=360;
  }

  _angleB += 0.05f;
  if(_angleB>360)
    _angleB-=360;

  _angleC += 5;
  if(_angleC>360)
    _angleC-=360;
  glutPostRedisplay();
  glutTimerFunc(25,update,0);
}
void LayerA(){

  glPushMatrix();
  //column
  glPopMatrix();
  glPushMatrix();
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glColor3f(233/RGB, 201/RGB, 40/RGB);
  glTranslatef(0,12,0);//12
  glRotatef(90.0, 1,0,0);
  gluCylinder(qobj, 0.7, 0.7, 10, 50,50);//10
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  
  //floor
  glPopMatrix();
  glPushMatrix();
  glColor3f(255/RGB, 127/RGB, 209/RGB);
  glRotatef(-90.0, 1,0,0);
  gluCylinder(qobj , 6, 6, 2, 50, 50);
  glPopMatrix();
  glPushMatrix();
  glColor3f(255/RGB, 127/RGB, 209/RGB);
  glTranslatef(0,2,0);
  glRotatef(-90.0,1,0,0);
  gluDisk(qobj, 0, 6, 32, 32);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(6,1,0);
  glColor3f(255/RGB,13/RGB,13/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-6,1,0);
  glColor3f(255/RGB,13/RGB,13/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0,1,-6);
  glColor3f(255/RGB,13/RGB,13/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0,1,6);
  glColor3f(255/RGB,13/RGB,13/RGB);
  glutSolidSphere(0.5, 20,20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(4.3,1,4.3);
  glColor3f(255/RGB,0,200/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-4.3,1,-4.3);
  glColor3f(255/RGB,0,200/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-4.3,1,4.3);
  glColor3f(255/RGB,0,200/RGB);
  glutSolidSphere(0.5,20,20);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(4.3,1,-4.3);
  glColor3f(255/RGB,0,200/RGB);
  glutSolidSphere(0.5, 20,20);
  glPopMatrix();

  //ceiling
  float c=10*cos(45);
  GLfloat ceilingVertex[]={
    0,20,0,
    0,10,-8,
    -c,10,-c,
    -8,10,0,
    -c, 10, c,
    0,10,8,
    c, 10, c,
    8,10,0,
    c,10,-c,
  };
  GLubyte ceilingIndex[]={
    0,1,2,
    0,2,3,
    0,3,4,
    0,4,5,
    0,5,6,
    0,6,7,
    0,7,8,
    0,8,1,
  };
  GLfloat ceilingColor[]={
    255/RGB,0,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
    250/RGB,117/RGB,0,
  };
  
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, ceilingVertex);
  glColorPointer(4, GL_FLOAT, 0, ceilingColor);
  glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_BYTE, ceilingIndex);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

}
void LayerB(int flag,float x, float y, float z){
  //column
  glPushMatrix();
  glColor3f(233/RGB, 201/RGB, 40/RGB);
  glTranslatef(x,y-5.1,z);//5
  if(!flag%2) glRotatef(90.0, 0,1,0);
  glRotatef(-90.0, 1,0,0);
  gluCylinder(qobj, 0.3, 0.3, 6.8, 50,50);//8
  glPopMatrix();
  //body
  glPushMatrix();
  if(flag==0) glColor3f(189/RGB,214/RGB,242/RGB);
  if(flag==1)  glColor3f(84/RGB,240/RGB,84/RGB);
  if(flag==2)  glColor3f(233/RGB,95/RGB,255/RGB);
  if(flag==3) glColor3f(182/RGB,121/RGB,16/RGB);

  glTranslatef(x,y-6,z);
  if(flag==1||flag==2) glRotatef(90.0,0,1,0);
  glScalef(2.0,1.0,1.5);
  glutSolidSphere(1, 20,20);
  glPopMatrix();
}
void LayerC(int flag,float x, float y, float z){
  glPushMatrix();//begin
  //head
  if(flag==0){
    glTranslatef(x+1,y-5,z);
      glRotatef(20*cos(_angleC/20),0,1,0);
  }
  if(flag==1){
     glTranslatef(x,y-5,z-1); 
      glRotatef(20*cos(30+_angleC/20),0,1,0);
     glRotatef(90,0,1,0);
  }
  if(flag==2){
    glTranslatef(x,y-5,z+1.5);
      glRotatef(20*cos(60+_angleC/20),0,1,0);
    glRotatef(-90,0,1,0);
  }
  if(flag==3){
    glTranslatef(x-1,y-5,z);
    glRotatef(20*cos(90+_angleC/20), 0,1,0);
    glRotatef(180,0,1,0);
  }
  glRotatef(45.0, 1,1,1);
  glScalef(3,1,1.5);
  glutSolidSphere(0.4,20,20);
  glPopMatrix();
  //Legs1
  glPushMatrix();
  switch(flag){
    case 1:
    case 0:glTranslatef(x+0.5, y-7, z-0.5);
      break;
    case 2:
    case 3:glTranslatef(x-0.5, y-7, z+0.5);
      break;
  }
  glRotatef(_angleC, 1,0,0);
  glScalef(1,1.7,1);
  glutSolidSphere(0.2,20,20);
  glPopMatrix();
  //Legs2
  glPushMatrix();
  switch(flag){
    case 1:
    case 0:glTranslatef(x+0.5, y-7, z+0.5);
      break;
    case 2:
    case 3:glTranslatef(x-0.5, y-7, z-0.5);
      break;
  }
  glRotatef(_angleC, 0,0,1);
  glScalef(1,1.7,1);
  glutSolidSphere(0.2,20,20);
  glPopMatrix();
  //Legs3
  glPushMatrix();
  switch(flag){
    case 1:
    case 0:glTranslatef(x-0.5, y-7, z+0.5);
      break;
    case 2:
    case 3:glTranslatef(x+0.5, y-7, z-0.5);
      break;
  }
  glRotatef(_angleC, 1,0,0);
  glScalef(1,1.7,1);
  glutSolidSphere(0.2,20,20);
  glPopMatrix();
  //Legs4
  glPushMatrix();
  switch(flag){
    case 1:
    case 0:glTranslatef(x-0.5, y-7, z-0.5);
           break;
    case 2:
    case 3:glTranslatef(x+0.5, y-7, z+0.5);
           break;
  }
  glRotatef(_angleC, 0,0,1);
  glScalef(1,1.7,1);
  glutSolidSphere(0.2,20,20);
  glPopMatrix();
}

void handleKeypress(unsigned char key, int x, int y){
  switch(key){
    case 27: exit(0);
  }
}
void handleResize(int w, int h){
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();//reset camera
  gluPerspective(45.0, (double)w/(double)h, 1.0, 200.0);
}
void initRendering(){
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_NORMALIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glFrontFace(GL_CCW);

  glClearColor(98.0/RGB, 217/RGB, 247.0/RGB, 1.0f);
  qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH);
}
void drawScene(){
  GLfloat ambientColor[] = {0.8f, 0.6f, 0.6f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {0.0f, 10.0f, 0.0f, 1.0f}; //Positioned at
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();//reset drawing per.

  gluLookAt(
      0.0f, 13.0f, 30.0f,
      0.0f, 6.0f, -20.0f,
      0.0f, 1.0f, 0.0f
      );
  //spin itself

  glPushMatrix();

  glRotatef(_angleA, 0, 1, 0);
  LayerA();
  glPushMatrix();//save

  glTranslatef(0,sin(_angleB),0);
  LayerB(0,0,10,5);
  glPushMatrix();
  glColor3f(189/RGB,214/RGB,242/RGB); 
  LayerC(0,0,10,5);
  glPopMatrix();

  glTranslatef(0,sin(_angleB+30),0);
  LayerB(1,5,10,0);
  glPushMatrix();
  glColor3f(84/RGB,240/RGB,84/RGB);
  LayerC(1,5,10,0);
  glPopMatrix();

  glTranslatef(0,sin(_angleB+60),0);
  LayerB(2,-5,10,0);
  glPushMatrix();
  glColor3f(233/RGB,95/RGB,255/RGB);
  LayerC(2,-5,10,0);
  glPopMatrix();

  glTranslatef(0,sin(_angleB+90),0);
  LayerB(3,0,10,-5);
  glPushMatrix();
  glColor3f(182/RGB,121/RGB,16/RGB);
  LayerC(3,0,10,-5);
  glPopMatrix();

  glPopMatrix();
  glPopMatrix();
  glutSwapBuffers();
  glFlush();//for background
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);                 // Initialize GLUT
  glutCreateWindow("Graphics HW1"); // Create a window with the given title
	//for more advanced opengl options
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	if (GLEW_ARB_vertex_program)
		fprintf(stdout, "Status: ARB vertex programs available.\n");

	if (glewGetExtension("GL_ARB_fragment_program"))
		fprintf(stdout, "Status: ARB fragment programs available.\n");

	if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
		fprintf(stdout, "Status: ARB point sprites available.\n");
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);   // Set the window's initial width & height
  glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

  initRendering();
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);

  glutTimerFunc(25,update,0);
   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}
