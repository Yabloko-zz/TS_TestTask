#include <Windows.h>
#include "figures.h"

int WINDOW_HEIGHT = 480;
int WINDOW_WIDTH = 640;
bool motionStart = false;
double defaultSize = 10;
double figsize = 10;
int cit = 1;
std::vector<std::vector<double>> colors = {
	std::vector<double> {0.0, 0.0, 0.0}, //black
	std::vector<double> {1.0, 1.0, 1.0}, //white
	std::vector<double> {1.0, 0.0, 0.0}, //red
	std::vector<double> {0.0, 1.0, 0.0}, //green
	std::vector<double> {0.0, 0.0, 1.0}, //blue
	std::vector<double> {1.0, 0.0, 1.0}, //magenta
	std::vector<double> {1.0, 1.0, 0.0}, //yellow
	std::vector<double> {0.0, 1.0, 1.0}, //cyan
	std::vector<double> {1.0, 0.5, 0.0}, //orange
};

std::vector<Figure*> Figures;
enum FigType { square, triangle, circle };
FigType CurrentFig = square;

void display()
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -100, 100); //
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	for (size_t f = 0; f < Figures.size(); f++)
	{
		Figures[f]->draw();
	}
	

	glFlush();
	glutSwapBuffers();
}

void key()
{

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': 
		//std::cout << "selected squares" << std::endl;
		CurrentFig = square;
		break;
	case '2':
		//std::cout << "selected triangles" << std::endl;
		CurrentFig = triangle;
		break;
	case '3':
		//std::cout << "selected circles" << std::endl;
		CurrentFig = circle;
		break;
	case 'c':
		//std::cout << "deleting all objects" << std::endl;
		for (auto f : Figures)
		{
			delete f;
		}
		Figures.clear();
		break;
	case 'p':
		//std::cout << "figure size +2" << std::endl;
		figsize += 2;
		break;
	case 'o':
		//std::cout << "figure size -2" << std::endl;
		if(figsize > 10)
			figsize -= 2;
		break;
	case 'k':
		if (cit == 0)
			cit = colors.size() - 1;
		else
			cit--;
		break;
	case 'l':
		if (cit == colors.size() - 1)
			cit = 0;
		else
			cit++;
		break;

	}
	glutPostRedisplay();
}

void addFig(double figsize, int x_, int y_, std::vector < double > cc)
{
	if (CurrentFig == square)
		Figures.push_back(new Square(vec2f(x_, y_), figsize,cc));
	if (CurrentFig == triangle)
		Figures.push_back(new Triangle(vec2f(x_, y_), figsize,cc));
	if (CurrentFig == circle)
		Figures.push_back(new Circle(vec2f(x_, y_), figsize, 15,cc));
}

void mouse(int button, int state, int x, int y)
{

	if (state == GLUT_DOWN)
	{
		motionStart = true;

		int x_ = x;
		int y_ = 480-y;

		addFig(figsize, x_, y_, colors[cit]);
	}
	else
	{
		motionStart = false;
	}

	glutPostRedisplay();
}

void motion(int x, int y)
{
	if (motionStart)
	{
		int x_ = x;
		int y_ = 480 - y;
		addFig(figsize, x_, y_, colors[cit]);
	}
	glutPostRedisplay();
}

DWORD previousTime = GetTickCount();
void idle(void)
{
	key();
	DWORD dt = GetTickCount64();
	if (dt - previousTime > 10)
	{
		previousTime = dt;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{
	std::cout << "Controls" << std::endl <<
		"Paint - LMB/RMB/wheel" << std::endl <<
		"Clear everything - c" << std::endl << 
		"Draw in squares - 1 (default)" << std::endl << 
		"Draw in triangles - 2" << std::endl << 
		"Draw in circles - 3"
		"Figure size down/up - o/p" << std::endl << 
		"Change color (iterate) - k/l" << std::endl;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("TestTask");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutIdleFunc(idle);

	glutMainLoop();
}


