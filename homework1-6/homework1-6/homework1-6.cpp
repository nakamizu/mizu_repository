#include <stdlib.h>
#include <glut.h>
#include <iostream>
using namespace std;
#define KEY_ESC 27
#define N 4

class basic {
	int i;
	double y0, y1, y2, y3;
	double temp[N];
public:
	basic();
	void makeBasicFunc(double t, double *p); /* ���֐�Bn(t)�����t�����Ƃɗ^����ꂽ�z��ɓ����֐�*/
};

basic::basic() /*�R���X�g���N�^*/
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

void printString(float x, float y, char* str, int length) {
	float z = -1.0f;
	glRasterPos3f(x, y, z);

	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
	}
}

void display()
{
	basic ob1, ob2, ob3, ob4, ob5;
	int i, j, k, m, n, l;
	double t, y0, y1, y2, y3;
	float x, y;

	double a[N] = { 0.0, 0.0, 0.0, 0.0 };
	double b[N] = { 0.0, 0.0, 0.0, 0.0 };
	double c[N] = { 0.0, 0.0, 0.0, 0.0 };
	double d[N] = { 0.0, 0.0, 0.0, 0.0 };


	glClear(GL_COLOR_BUFFER_BIT);

	ob1.makeBasicFunc(0.0, a);
	ob2.makeBasicFunc(0.2, b);
	ob3.makeBasicFunc(0.6, c);
	ob4.makeBasicFunc(1.0, d);

	double e[][N * 2] = { { 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 } };

	double e_reverse[][N] = { { 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0, 0.0 } };

	for (m = 0; m < N; m++)
	{
		e[0][m] = a[m];
		e[1][m] = b[m];
		e[2][m] = c[m];
		e[3][m] = d[m];
	}

	double pivot, mul;

	//��������t�s������߂�|���o���@�J�n

	// �Ίp������1�Ő��K�����ꂽ�K�i�s������
	for (i = 0; i < N; ++i)
	{
		// �Ίp�����̑I���A���̒l�ōs�����𐳋K��
		pivot = e[i][i];
		for (j = 0; j < N * 2; ++j)
		{
			e[i][j] = (1 / pivot) * e[i][j];
		}

		// �K�i�s������ׂɁA���݂̍s��艺�̍s�ɂ�
		// i��ڂ̐�����0�ɂȂ�悤�Ȋ�{�ό`������
		for (k = i + 1; k < N; ++k)
		{
			mul = e[k][i];
			for (n = i; n < N * 2; ++n)
			{
				e[k][n] = e[k][n] - mul * e[i][n];
			}
		}
	}

	// �������Ɍ������ĊȖ�
	for (i = N - 1; i > 0; --i)
	{
		for (k = i - 1; k >= 0; --k)
		{
			mul = e[k][i];
			for (n = i; n < N * 2; ++n)
			{
				e[k][n] = e[k][n] - mul * e[i][n];
			}
		}
	}

	for (i = 0; i < N; i++) {
		for (j = N; j < 2 * N; j++) {
			e_reverse[i][j - N] = e[i][j];
		}
	}

	//�|���o���@�I��

	double r[][2] = { { 1.0, 2.0 },{ 2.0, 3.0 },{ 3.0, 1.0 },{ 5.0, 1.0 } }; //�ʉߓ_

	double q[][2] = { { 0.0, 0.0 },{ 0.0, 0.0 },{ 0.0, 0.0 },{ 0.0, 0.0 } }; //����_������񎟌��z��

	glPointSize(5.0);
	glBegin(GL_POINTS);
		glColor3f(1.0, 0.0, 0.0);
		for (i = 0; i < 4; i++) {
			cout << "( ";
			for (j = 0; j < 2; j++) {
				for (k = 0; k < 4; k++) {
					q[i][j] += e_reverse[i][k] * r[k][j]; //���߂����֐��̋t�s��ƒʉߓ_�̍s��̐ς��琧��_�����߂�
				}
				cout << q[i][j] << " ";
			}
			cout << ")\n";
			glVertex2d(q[i][0], q[i][1]); /*����_�̕`��*/
		}
	glEnd();

	glPointSize(1.0);

	glBegin(GL_LINE_STRIP);
		glColor3f(1.0, 1.0, 0.0);


		double bn[][N] = { 0.0, 0.0, 0.0, 0.0 };

		for (i = 0; i <= 100; i++) { //����_�����܂����̂ł�������ƂɋȐ��̕`��
			basic ob5;

			t = i / 100.0;

			double temp[N] = { 0.0, 0.0, 0.0, 0.0 };

			ob5.makeBasicFunc(t, temp);

			double bn[][N] = { temp[0], temp[1], temp[2], temp[3] };

			double p[][2] = { 0.0, 0.0 };

			for (j = 0; j < 2; j++) {
				for (k = 0; k < 4; k++) {
					p[0][j] += bn[0][k] * q[k][j];
				}
			}
			glVertex2d(p[0][0], p[0][1]);
		}
	glEnd();

	glPointSize(1.0); /*���W���̕\��*/
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(0.0, -3.0);
	glVertex2f(5.0, -3.0);
	glVertex2f(0.0, 6.0);
	glVertex2f(0.0, -3.0);
	glVertex2f(5.0, 6.0);
	glVertex2f(5.0, -3.0);
	glVertex2f(5.0, 6.0);
	glVertex2f(0.0, 6.0);
	glEnd();

	glEnable(GL_LINE_STIPPLE); /*�j���ŃO���b�h�̕\��*/
	glLineStipple(1, 0xF0F0);

	glBegin(GL_LINES);
		for (x = 1.0; x < 5.0; x++) {
			glVertex2f(x, -3.0);
			glVertex2f(x, 6.0);
		}
		for (y = -2.0; y < 6.0; y++) {
			glVertex2f(0.0, y);
			glVertex2f(5.0, y);
		}
	glEnd();

	glDisable(GL_LINE_STIPPLE);

	glColor3f(1.0, 1.0, 1.0); /*���W�l�\��*/
	printString(0.00, -3.35, "0", 1);
	printString(1.00, -3.35, "1", 1);
	printString(2.00, -3.35, "2", 1);
	printString(3.00, -3.35, "3", 1);
	printString(4.00, -3.35, "4", 1);
	printString(5.00, -3.35, "5", 1);

	printString(-0.15, 6.00, "6", 1);
	printString(-0.15, 5.00, "5", 1);
	printString(-0.15, 4.00, "4", 1);
	printString(-0.15, 3.00, "3", 1);
	printString(-0.15, 2.00, "2", 1);
	printString(-0.15, 1.00, "1", 1);
	printString(-0.15, 0.00, "0", 1);
	printString(-0.25, -1.00, "-1", 2);
	printString(-0.25, -2.00, "-2", 2);
	printString(-0.25, -3.00, "-3", 3);

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
	gluOrtho2D(-0.5, 5.5, -3.5, 6.5);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}



