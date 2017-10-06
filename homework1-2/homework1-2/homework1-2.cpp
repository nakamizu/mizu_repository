#include <stdlib.h>
#include <glut.h>
#define KEY_ESC 27
#define N 4

class basic {
	int i;
	double y0, y1, y2, y3;
	double temp[N];
public:
	basic();
	void makeBasicFunc(double t, double *p); /* 基底関数Bn(t)を入力tをもとに与えられた配列に入れる関数*/
};

basic::basic()
{
	y0 = 0.0;
	y1 = 0.0;
	y2 = 0.0;
	y3 = 0.0;
	temp[0] = 0.0;
	temp[1] = 0.0;
	temp[2] = 0.0;
	temp[3] = 0.0;
}

void basic::makeBasicFunc(double t, double *p) {
	y0 = (1.0 - t)*(1.0 - t)*(1.0 - t);
	y1 = 3.0*(1.0 - t)*(1.0 - t)*t;
	y2 = 3.0*(1.0 - t)*t*t;
	y3 = t*t*t;

	temp[0] = y0;
	temp[1] = y1;
	temp[2] = y2;
	temp[3] = y3;

	for (i = 0; i < N; i++) {
		*p = temp[i];
		++p;
	}
}

void printString(float x, float y, char* str, int length) { /* 指定した座標上に文字を表示する関数 */
	float z = -1.0f;
	glRasterPos3f(x, y, z);

	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

void display()
{
	int i, j, k, m;
	double t;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 1.0, 0.0);
		for (i = 0; i < 100; i++) {
			basic ob;

			t = i / 100.0;

			double a[N] = { 0.0, 0.0, 0.0, 0.0 };

			ob.makeBasicFunc(t, a);

			double b[][N] = { a[0], a[1], a[2], a[3] };/* 基底関数Bn(t)を二次元配列に置き換える */

			double q[][2] = { { 1.0, 2.0 },{ 2.0, 3.0 },{ 3.0, 1.0 },{ 5.0, 1.0 } }; /* 制御点 */

			double p[][2] = { 0.0, 0.0 }; /* パラメトリック曲線P(t) */

			for (j = 0; j < 2; j++) {
				for (k = 0; k < 4; k++) {
					p[0][j] += b[0][k] * q[k][j]; /*Pn(t)を求める*/
				}
			}
			glVertex2d(p[0][0], p[0][1]);
		}
	glEnd();

	glBegin(GL_LINES); /* 座標軸の描画 */
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(5.0, 1.0);
		glVertex2f(1.0, 3.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(5.0, 3.0);
		glVertex2f(5.0, 1.0);
		glVertex2f(5.0, 3.0);
		glVertex2f(1.0, 3.0);
	glEnd();

	/*文字の表示*/
	printString(0.90, 0.90, "1", 1);
	printString(2.05, 0.90, "2", 1);
	printString(3.05, 0.90, "3", 1);
	printString(4.05, 0.90, "4", 1);
	printString(5.05, 0.90, "5", 1);

	printString(0.90, 2.99, "3", 1);
	printString(0.90, 1.99, "2", 1);

	glFlush();
}

void myKbd(unsigned char key, int x, int y)
{
	if (key == KEY_ESC) exit(0);
}

void myinit()
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Graph of Parametric curve");

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glutKeyboardFunc(myKbd);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0.5, 5.5, 0.5, 3.5);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
