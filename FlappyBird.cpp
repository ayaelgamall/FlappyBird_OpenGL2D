
#include <iostream>
#include <random>
#include <unordered_set>
#include <stdio.h>
#include <windows.h>
#include<mmsystem.h>
#include <string.h>
#include <iostream>
#include <glut.h>


using namespace std;


//  Methods Signatures
void drawRect(int x, int y, int w, int h);
void drawTriangles(int x, int y, int w, int h);
void drawTriangle(int x, int y, int w, int h);
void drawRectUP(int x, int w, int h); 
void drawRectDown(int x, int w, int h);
void drawCircle(int x, int y, float r);
void spe(int k, int x, int y);
void Timer(int value);
void Display();
void print(int x, int y, char* string);
void drawLine(int x, int y, int w); 
void drawEye(int x, int y, int width);
void drawBackground();



const int WIDTH_SCREEN = 1280;
const int HEIGHT_SCREEN = 720;
const int GAP = 0.4 * HEIGHT_SCREEN;
const int X_Bird = 0.2 * WIDTH_SCREEN;
float birdPosition = HEIGHT_SCREEN / 2;
const int WIDTH_BARRIER = 0.07 * WIDTH_SCREEN;
const int WIDTH_POWERUP = 0.3 * WIDTH_BARRIER;
const int spaceBetween = 3 * WIDTH_BARRIER;
const int Height_Line = 50;
const int WIDTH_BIRD = 0.2 * GAP;
float xSteps = 0.0f;
int setOrder [3];
int set1[3] = { 0.9*HEIGHT_SCREEN,0.7*HEIGHT_SCREEN,0.3* HEIGHT_SCREEN  };
int set2[3] = { 0.5*HEIGHT_SCREEN,0.99*HEIGHT_SCREEN,0.7* HEIGHT_SCREEN  };
int set3[3] = { 0.3*HEIGHT_SCREEN,0.6*HEIGHT_SCREEN,0.8* HEIGHT_SCREEN  };

int LIVES = 3;
int SCORE = 0;
bool powerUp = false;
float birdinc = 3.0f;
float x_inc = 2.0f;
int freq = 30;
bool game = false;
bool won = false;
bool lost = false;
bool hit = false;
bool spower = false;
unordered_set <int> powerUpPosition ;
int poweUpcurr = 0;
int counter = 0;
int counterpower = 0;




class Object
{
public:
	void drawBarrier();
	void drawBird();
	void drawPowerUp();
	float width, height;
	float x, y;
	float r, g, b;

	void SetPosition(float x, float y);
	void SetColor(float r, float g, float b);
	void SetWidthHeight(float width, float height);
};

void Object::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Object::SetColor(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Object::SetWidthHeight(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Object::drawBird()
{
	glPushMatrix();

	glColor3f(0.96f, 0.87f, 0.24f);
	drawRect(x, y, width, width);
	
	drawEye(x, y, width);

	glColor3f(0.96f,  0.165f, 0.05f);
	drawTriangles(x+0.6*width, y + 0.1 * width, 0.4*width, 0.3 * width);

	glColor3f(1.0f, 0.96f, 0.4f);
	drawTriangle(x + 0.1 * width, y + 0.1 * width, 0.4 * width, 0.2 * width);

	glPopMatrix();
}

void Object::drawPowerUp()
{
	glPushMatrix();
	glColor3f(r, g, b);
	drawRect(x, y, width, height);

	glColor3f(r, 1.02*g, 0);
	drawCircle(x+width/2, y+height/2, 0.4*width);

	glPopMatrix();
}

void Object::drawBarrier() {
	glColor3f(r-0.1, g-0.1, b-0.1);
	drawRectUP(x, width, y);
	drawRectDown(x, width, y - GAP);
	
	glColor3f(r, g, b);
	drawRectUP(x+10, width-20, y+10);
	drawRectDown(x+10, width-20, y - GAP-10);

	glColor3f(r - 0.1, g - 0.1, b - 0.1);
	drawLine(x, y + Height_Line, width);
	drawLine(x, y + Height_Line+1, width);
	drawLine(x, y - GAP - Height_Line-1, width);
	drawLine(x, y - GAP - Height_Line-1, width);

}

void drawTriangles(int x,int y, int w, int h) {
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x , y + h/2);
	glVertex2f(x, y+h);
	glVertex2f(x + w, y+h);
	glVertex2f(x , y + h/2);
	glEnd();
	
}
void drawTriangle(int x,int y, int w, int h) {
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + w, y+h);
	glVertex2f(x , y + h);
	glEnd();
	
}
void drawEye(int x,int y, int width) {
	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(x + 0.6 * width, y + 0.7 * width, 0.21 * width);

	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(x + 0.6 * width, y + 0.7 * width, 0.19 * width);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(x + 0.6 * width, y + 0.7 * width, 0.11 * width);
	glColor3f(0.0f, 0.79f, 0.8f);
	drawCircle(x + 0.6 * width, y + 0.7 * width, 0.1 * width);

	glColor3f(0.0f, 0.0f, 0.0f);
	drawCircle(x + 0.6 * width, y + 0.7 * width, 0.05 * width);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(x + 0.6 * width + 0.05 * width, y + 0.7 * width + 0.05 * width, 0.025 * width);
	
}

void drawRectDown(int x, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, 0);
	glVertex2f(x + w, 0);
	glVertex2f(x + w, h);
	glVertex2f(x, h);
	glEnd();
}

void drawRectUP(int x, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2f(x, HEIGHT_SCREEN);
	glVertex2f(x + w, HEIGHT_SCREEN);
	glVertex2f(x + w,  h);
	glVertex2f(x, h);
	glEnd();
}

void drawRect(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

void drawLine(int x, int y, int w) {
	
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x+w, y);
	glEnd();
}



void drawCircle(int x, int y, float r) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	GLUquadric* quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
	glPopMatrix();
}

void Timer(int val)
{
	if (game) {
		SCORE++;
		xSteps += x_inc;

		birdPosition -= birdinc;


		glutPostRedisplay();

		glutTimerFunc(freq, Timer, 0);
	}
	
}


void Display() {

	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(0.4f, 0.7f,  0.0f);
	if (hit) {
		counter++;
		if (counter > 1000 / freq) {
			PlaySound(TEXT("sounds/Background.wav"), NULL, SND_FILENAME | SND_ASYNC); hit = false;
		}
	}if (spower) {
		counterpower++;
		if (counterpower > 1000 / freq) {
			PlaySound(TEXT("sounds/Background.wav"), NULL, SND_FILENAME | SND_ASYNC); spower = false;
		}
	}

	if (game ) {

		for (size_t i = 0; i < 3; i++)
		{
			int* set = (setOrder[i] == 1) ? set1 : (setOrder[i] == 2) ? set2 : set3;
			for (size_t j = 0; j < 3; j++)
			{

				Object barrier;
				barrier.SetPosition((WIDTH_SCREEN / 2 + j * spaceBetween + i * (4 * spaceBetween)) - xSteps, set[j]);

				!powerUp ? barrier.SetColor(0.4f, 0.7f, 0.0f) : barrier.SetColor(0.659f, 0.8f, 0.0f);
				barrier.SetWidthHeight(WIDTH_BARRIER, 360);
				barrier.drawBarrier();

				if (!powerUp && j == 0 && powerUpPosition.find(i) != powerUpPosition.end()) {
					Object power;
					power.SetPosition(barrier.x + 0.3 * barrier.width, (0.7 * (GAP)) + barrier.y - GAP);
					power.SetWidthHeight(WIDTH_POWERUP, WIDTH_POWERUP);
					power.SetColor(0.99f, 0.9f, 0.1f);
					power.drawPowerUp();
					if (X_Bird + WIDTH_BIRD >= power.x && X_Bird <= power.x + power.width) {
						if ((birdPosition) <= power.y + power.height && (birdPosition)+WIDTH_BIRD >= power.y) {
							powerUp = true; poweUpcurr = i;
							PlaySound(TEXT("sounds/power.wav"), NULL, SND_FILENAME | SND_ASYNC); spower = true; counterpower = 0;
						}
					}

				}



				if (!powerUp)
					if (X_Bird + WIDTH_BIRD >= barrier.x && X_Bird <= barrier.x + barrier.width) {

						if ((birdPosition) <= barrier.y - GAP || (birdPosition)+WIDTH_BIRD >= barrier.y) {
							LIVES--;
							birdPosition = ((GAP) / 2) - (WIDTH_BIRD / 2) + barrier.y - GAP;

							PlaySound(TEXT("sounds/Hit.wav"), NULL, SND_FILENAME | SND_ASYNC); hit = true; counter = 0;
						}
					}
				if (j == 2 && barrier.x + WIDTH_BARRIER < X_Bird) {
					if (powerUp && poweUpcurr == i)powerUp = false;
					if (i == 2) {
						won = true; game = false;
					}
				}


			}

		}

		Object bird;
		bird.SetPosition(X_Bird, birdPosition);
		bird.SetColor(1, 0, 0);
		bird.SetWidthHeight(WIDTH_BIRD, WIDTH_BIRD);
		bird.drawBird();

		if (birdPosition < 0) { lost = true; game = false; }
		if (birdPosition +WIDTH_BIRD>HEIGHT_SCREEN) { lost = true; game = false; }
		if (LIVES<0) { lost = true; game = false; }


		glColor3f(0.0f, 0.0f, 0.0f);
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", SCORE);
		print(WIDTH_SCREEN * 0.05, HEIGHT_SCREEN * 0.95, (char*)p0s);
		sprintf((char*)p0s, "Lives: %d", LIVES);
		print(WIDTH_SCREEN * 0.9, HEIGHT_SCREEN * 0.95, (char*)p0s);
		if (lost || won) {
			if (lost) {
				print(WIDTH_SCREEN * 0.4, HEIGHT_SCREEN * 0.80, "GAME OVERRRRR");
				PlaySound(TEXT("sounds/Directed.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}


			if (won) {
				print(WIDTH_SCREEN * 0.4, HEIGHT_SCREEN * 0.80, "YOU HAVE WONNNNNNNN");
				PlaySound(TEXT("sounds/Victory.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}

			glColor3f(0.0f, 0.0f, 0.0f);
			sprintf((char*)p0s, "Score: %d", SCORE);
			print(WIDTH_SCREEN * 0.5, HEIGHT_SCREEN * 0.90, (char*)p0s);
			sprintf((char*)p0s, "Lives: %d", LIVES);
			//print(WIDTH_SCREEN * 0.9, HEIGHT_SCREEN * 0.95, (char*)p0s);
			//
		}
	}
	else {
		glColor3f(0.0f, 0.0f, 0.0f);
		if (!lost && !won)print(WIDTH_SCREEN * 0.3, HEIGHT_SCREEN * 0.5, " Press any key to start the game");

	}
	

	glFlush();
}

void Key(unsigned char key, int x, int y) {
	if (!won && !lost) {
		if (!game) {
			game = true; won = false;

			glutTimerFunc(0, Timer, 0);
		}

		if (key == ' ')
		{
			birdPosition += 10 * birdinc;
		}
	}
}

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);


	glutInitWindowSize(WIDTH_SCREEN, HEIGHT_SCREEN);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Crazy Bird");
	glutDisplayFunc(Display);

	//glutSpecialFunc(spe);

	glutKeyboardFunc(Key);
	glutTimerFunc(0, Timer, 0);


	
	srand(time(0));
	int rand1 = rand() % 3 ;
	int rand2 = rand() % 3 ;
	while (rand1 == rand2) {
		rand2 = rand() % 3;
	}
	int rand3 = (rand1 == 1 && rand2 == 2 || rand1 == 2 && rand2 == 1) ? 0 : (rand1 == 0 && rand2 == 1 || rand1 == 1 && rand2 == 0) ? 2 : 1;
	setOrder[0] = rand1++;
	setOrder[1] = rand2++;
	setOrder[2] = rand3++;

	int randno = rand() % 3;
	for (size_t i = 0; i < randno+1; i++)
	{
		int rand1 = rand() % 3; 
		if (powerUpPosition.find(rand1) == powerUpPosition.end())
			powerUpPosition.insert(rand1);
		else {
			int rand2 = rand() % 3;
			while (rand1 == rand2 && powerUpPosition.find(rand2) != powerUpPosition.end()) {
				rand2 = rand() % 3;
			}
			powerUpPosition.insert(rand2);
		}
	}
	
	PlaySound(TEXT("sounds/Background.wav"), NULL, SND_FILENAME | SND_ASYNC );
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glEnable(GL_TEXTURE_2D);
	//loadBMP(&texID, "textures/box.bmp", false);
	glClearColor(0.722f, 0.885f, 0.982f, 1.0f);
	gluOrtho2D(0.0, WIDTH_SCREEN, 0.0, HEIGHT_SCREEN);

	glutMainLoop();
}
