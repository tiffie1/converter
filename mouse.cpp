#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>

int vertexCount;
float oldX[3], oldY[3];
float newX[3], newY[3];
float red, green, blue;
int windowWidth, windowHeight;

void initialize() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  red = green = blue = 1.0;
  oldX[0] = 0.0;
  oldY[0] = 0.75;
  oldX[1] = -0.75;
  oldY[0] = -0.75;
  oldX[2] = 0.75;
  oldY[2] = -0.75;
  vertexCount = 3;
}

void drawImage() {
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(red, green, blue);
  glLoadIdentity();
  glBegin(GL_POLYGON);
  for (i = 0; i < 3; i++)
    glVertex3f(oldX[i], oldY[i], -5.0);
  glEnd();
  glFlush();
}

void reshapeWindow(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  windowWidth = width;
  windowHeight = height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
  glMatrixMode(GL_MODELVIEW);
}

void handleMouse(int button, int state, int x, int y) {
  int i;
  if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
    if (vertexCount == 3) {
      vertexCount = 0;
    }
    newX[vertexCount] = 2.0 * (float)x / windowWidth - 1.0;
    newY[vertexCount] = 1.0 - 2.0 * (float)y / windowHeight;
    vertexCount++;
    printf("You clicked in: (%d, %d). Vertex #: %i.\n", x, y, vertexCount);
    printf("Vertex: (%f, %f)!\n", newX[vertexCount], newY[vertexCount]);
    if (vertexCount == 3) {
      for (i = 0; i < 3; i++) {
        oldX[i] = newX[i];
        oldY[i] = newY[i];
      }
      glutPostRedisplay();
    }
  }
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 'r':
  case 'R':
    red = 1.0;
    green = 0.5;
    blue = 0.0;
    break;
  case 'g':
  case 'G':
    red = 0.5;
    green = 0.0;
    blue = 0.5;
    break;
  case 'b':
  case 'B':
    red = 0.5;
    green = 0.0;
    blue = 1.0;
    break;
  case 'w':
  case 'W':
    red = 1.0;
    green = 1.0;
    blue = 1.0;
    break;
  case 'q':
  case 'Q':
    exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(300, 300);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Example");

  initialize();

  glutDisplayFunc(drawImage);
  glutReshapeFunc(reshapeWindow);
  glutMouseFunc(handleMouse);
  glutKeyboardFunc(handleKeyboard);
  glutMainLoop();
  return 0;
}
