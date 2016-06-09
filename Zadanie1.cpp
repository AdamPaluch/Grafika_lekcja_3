#include <GL\glut.h>
#include <cmath>
#include <iostream>

//n = 2
/*
N1 = 2^(N+2) --> N1 = 2^4 = 16
N2 = 2^(N+1) --> N2 = 2^3 = 8
N3 = 2^N     --> N3 = 2^2 = 4
*/
#define N1 16
#define N2 8
#define N3 4

GLuint textures[3];

enum{
	SWITCH_TO_NEAREST,
	SWITCH_TO_LINEAR
};

void Generate1DTextures()
{
	unsigned char tex1[N1];
	unsigned char tex2[N2];
	unsigned char tex3[N3];

	char step = 255 / N1;
	for (int i = 0; i < N1; i++)
		tex1[i] = step * i;

	step = 255 / N2;
	for (int i = 0; i < N2; i++)
		tex2[i] = step * i;

	step = 255 / N3;
	for (int i = 0; i < N3; i++)
		tex3[i] = step * i;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(3, textures);

	glBindTexture(GL_TEXTURE_1D, textures[0]);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, 16, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex1);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glBindTexture(GL_TEXTURE_1D, textures[1]);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex2);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glBindTexture(GL_TEXTURE_1D, textures[2]);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, 4, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, tex3);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
}

void Init()
{
	glClearColor(0.7f, 0.2f, 0.3f, 1.0f);
	glEnable(GL_TEXTURE_1D);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_1D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, 0.4f);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, 0.9f);
	glTexCoord1f(1.0f);
	glVertex2f( 1.0f, 0.9f);
	glTexCoord1f(1.0f);
	glVertex2f( 1.0f, 0.4f);
	glEnd();

	glBindTexture(GL_TEXTURE_1D, textures[1]);
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.25f);
	glTexCoord1f(0.0f);	   
	glVertex2f(-1.0f,  0.25f);
	glTexCoord1f(1.0f);	   
	glVertex2f(1.0f,   0.25f);
	glTexCoord1f(1.0f);	   
	glVertex2f( 1.0f, -0.25f);
	glEnd();

	glBindTexture(GL_TEXTURE_1D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.9f);
	glTexCoord1f(0.0f);
	glVertex2f(-1.0f, -0.4f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, -0.4f);
	glTexCoord1f(1.0f);
	glVertex2f(1.0f, -0.9f);
	glEnd();

	glutSwapBuffers();
}

void Menu(int value)
{
	switch (value)
	{
	case SWITCH_TO_NEAREST:
		glBindTexture(GL_TEXTURE_1D, textures[0]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_1D, textures[1]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_1D, textures[2]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;

	case SWITCH_TO_LINEAR:
		glBindTexture(GL_TEXTURE_1D, textures[0]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_1D, textures[1]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_1D, textures[2]);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Okno OpenGL");

	Init();
	Generate1DTextures();

	glutCreateMenu(Menu);
	glutAddMenuEntry("GL_LINEAR", SWITCH_TO_LINEAR);
	glutAddMenuEntry("GL_NEAREST", SWITCH_TO_NEAREST);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(Display);

	glutMainLoop();
	
	return 0;
}
