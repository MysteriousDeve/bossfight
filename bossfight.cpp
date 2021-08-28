#include <stdlib.h>
#include <gl/glut.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Bullet {
private:
	bool isCharacter;
	double posX, posY;
	int angle;
	double speed;
public:
	Bullet(bool isCharacter, double posX, double posY, int angle, double speed) {
		this->isCharacter = isCharacter;
		this->posX = posX;
		this->posY = posY;
		if (speed > 0) this->speed = speed;
		else this->speed = 1.0;
		if (angle >= 0 && angle < 359) this->angle = angle;
		else if (angle >= 360) this->angle = angle % 360;
		else this->angle = 360 - (abs(angle) % 360);
	}

	double outX() {
		return posX;
	}
	double outY() {
		return posY;
	}
	void setX(double posX) {
		this->posX = posX;
	}
	void setY(double posY) {
		this->posY = posY;
	}

	void moveOn() {
		this->posX += sin(angle) * speed;
		this->posY += cos(angle) * speed;
	}

};

class Boss {
private:
	vector <Bullet> vbull;
	int HP = 1000;
	int senx, seny;
public:
	vector <Bullet>::iterator it;

	void getPlayerPos(int senx, int seny) {
		this->senx = senx;
		this->seny = seny;
	}

	vector <Bullet> access() {
		return vbull;
	}

	void activeBullet() {
		int aaaa = 0;
		for (it = vbull.begin(); it != vbull.end(); it++) {
			vbull[aaaa].moveOn();
			aaaa++;
		}
	}

	void checkAndDelete() {
		int bbbb = 0;
		for (it = vbull.begin(); it != vbull.end(); it++) {
			if (this->vbull[bbbb].outX() >= 550 ||
				this->vbull[bbbb].outX() <= 50 ||
				this->vbull[bbbb].outY() >= 550 ||
				this->vbull[bbbb].outY() <= 50) vbull.erase(vbull.begin() + bbbb);
			bbbb++;
		}
	}

	int loseHP(int damage) {
		HP -= damage;
	}

	bool dieCheck() {
		if (HP <= 0) return true;
		return false;
	}

	void singleBulletRelease_follow(int xx, int yy) {
		if (xx == 300 && yy == 300) {
			xx = 200; yy = 400;
		}
		Bullet newBullet(0, 300, 300, atan(senx / double(seny)), 0.5);
		vbull.push_back(newBullet);
	}
};

class Player {
private:
	int cx = 150, cy = 300;

};

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)600, (GLsizei)600);
}

void reshape(int w, int h) {
	glViewport(w < h ? 0 : (w - h) / 2,
			   w > h ? 0 : (h - w) / 2,
			   w < h ? (GLsizei)w : (GLsizei)h,
			   w > h ? (GLsizei)h : (GLsizei)w);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

Boss boss;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	glRectf(0, 0, 600, 600);
	glColor3f(0.0, 0.0, 0.0);
	glRectf(10, 10, 590, 590);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.2, 0.2);
	if (!boss.dieCheck()) glRectf(280, 280, 320, 320);
	glColor3f(0.8, 0.5, 0.3);

	glPopMatrix();

	glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_DOWN);
	else if (key == GLUT_KEY_UP);
	if (key == GLUT_KEY_LEFT);
	else if (key == GLUT_KEY_RIGHT);
}

void shotkey(unsigned char key, int x, int y) {

}

void idleKiller() {
	boss.activeBullet();
	boss.checkAndDelete();
	
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("Bossfight");
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}