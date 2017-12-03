#include <iostream>
#include <gl\freeglut.h>
#include <vector>
#include "spline.h"

#pragma comment(lib, "freeglut.lib")

using namespace std;
constexpr int screen_width = 1920;
constexpr int screen_height = 1080;
constexpr int window_width = 640;
constexpr int window_height = 640;

const float point_size = 10.f;

bool hold = false;
bool line_visible = true;
vec2d *hold_point;
Spline spline;

void display_function()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	for (const vec2d& p : spline.get_inter_points())
	{
		glVertex2f(p.x, p.y);
	}
	glEnd();

	if (line_visible)
	{
		glBegin(GL_LINE_STRIP);
		for (const vec2d& p : spline.get_inter_points())
		{
			glVertex2f(p.x, p.y);
		}
		glEnd();
	}

	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	for (float t = 0.f; t < 1.f; t += 0.01)
	{
		vec2d p = spline.calc(t);
		glVertex2f(p.x, p.y);
	}
	glEnd();

	glutSwapBuffers();
}

void mouse_function(int mouse_key, int key_press, int mouse_x, int mouse_y)
{
	if (key_press == GLUT_DOWN && mouse_key == GLUT_LEFT_BUTTON)
	{
		bool add_point = true;
		for (size_t idx = 0; idx != spline.get_inter_points().size(); ++idx)
		{
			float dx = spline.get_inter_points()[idx].x - mouse_x;
			float dy = spline.get_inter_points()[idx].y - mouse_y;
			if (dx * dx + dy * dy < point_size * point_size)
			{
				hold = true;
				add_point = false;
				hold_point = &spline.get_inter_points()[idx];
				break;
			}
		}
		if (add_point)
		{
			spline.add_point(vec2d{ (float)mouse_x, (float)mouse_y });
			hold = true;
			hold_point = &spline.get_inter_points()[spline.get_inter_points().size() - 1];
		}
		glutPostRedisplay();
	}

	if (key_press == GLUT_UP && mouse_key == GLUT_LEFT_BUTTON)
	{
		hold = false;
	}
}

void motion_func(int mouse_x, int mouse_y)
{
	if (hold)
	{
		hold_point->x = mouse_x;
		hold_point->y = mouse_y;
		spline.solve_spline();
	}
	glutPostRedisplay();
}

void keyboard_func(unsigned char key, int mouse_x, int mouse_y)
{
	if (key == ' ')
	{
		glutPostRedisplay();
	}
	if (key == '1')
	{
		line_visible = !line_visible;
		glutPostRedisplay();
	}
	if (key == 27) // Escape key
		glutLeaveMainLoop();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition((screen_width - window_width) / 2, (screen_height - window_height) / 2);
	glutCreateWindow("Cubic Spline");
	glutShowWindow();

	glOrtho(0, window_width, window_height, 0, 0, 1);
	glPointSize(point_size);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(display_function);
	glutMouseFunc(mouse_function);
	glutKeyboardFunc(keyboard_func);
	glutMotionFunc(motion_func);

	glutMainLoop();
}