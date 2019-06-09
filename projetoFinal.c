#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

static int year = 0, day = 0, days = 0;
int tempo = 150;

float GL_PI = 3.14;

//variáveis que determinam o raio
float gravidade = 5.0;
float gravidadeGreen = 5.5;

//velocidade de atração do raio
float atracao = 0.1;

float radiusNeutronPlanet = 0.2;
float radiusNormalPlanet = 1.0;
bool isRadiusPositive = true;

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 7.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 0.0, 7.0, 5.0 | 0.0, 0.0, 15.0
}

//desenha um planeta vermelha que gira em torno do centro
void redPlanet(void){
	if(gravidade >= 0 & isRadiusPositive == true){
		glColor3f(1.0, 0.0, 0.0); //vermelho
		glPushMatrix();
			glRotatef((GLfloat) day, 0.0, 10.0, 45.0); //rotaciona o objeto no seu próprio eixo.
			glTranslatef(gravidade * 2, 0.0, 0.0); //rotaciona o objeto num eixo determinado
			glutWireSphere(radiusNormalPlanet, 15.0, 8.0);
		glPopMatrix();		
	} else{
		gravidade = 0;
	}
}

//desenha um planeta verde que gira em torno do centro
void greenPlanet(void){
	//float gravidadeGreen = 12.0;
	if(gravidadeGreen >= 0 & isRadiusPositive == true){
		glColor3f(0.3, 1.0, 0.1); //verde
		glPushMatrix();
			glRotatef((GLfloat) days, 0.0, 0.0, 45.0); //rotaciona o objeto no seu próprio eixo.
			glTranslatef(gravidadeGreen, 0.0, 0.0); //rotaciona o objeto num eixo determinado
			glutWireSphere(radiusNormalPlanet, 15.0, 8.0);
		glPopMatrix();		
	} else{
		gravidade = 0;
	}
}

// void orbit(void){
// 	glBegin(GL_LINE_STRIP);
// 		float z = 0.0;
// 		for(float angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f){
// 			float x = 50.0f*sin(angle);
// 			float y = 50.0f*cos(angle);

// 			glVertex3f(x, y, z);
// 		}

// 		// glColor3f(1.0, 1.0, 1.0);
// 		// glVertex3f(gravidadeGreen, 0, 0);
// 		// glVertex3f(gravidadeGreen + 1, 0, 0);
// 		// glVertex3f(gravidadeGreen + 2, 0, 0);
// 		// glVertex3f(gravidadeGreen + 3, 0, 0);
// 		// glVertex3f(gravidadeGreen + 5, 0, 0);
// 	glEnd();	
// }

//Verifica se os dois corpos estão no centro, caso verdadeiro, surge este corpo
void neutronMerge(void){
	if(gravidade <= 0 & gravidadeGreen <= 0){
		glColor3f(1.0, 1.0, 1.0); //branco
		glPushMatrix();
			glRotatef((GLfloat) days * 2, 0.0, 0.0, 90.0); //rotaciona o objeto no seu próprio eixo.
			glTranslatef(0.05, 0.0, 0.0); //rotaciona o objeto num eixo determinado
			glutWireSphere(radiusNeutronPlanet, 30.0, 8.0);
		glPopMatrix();		
	}
}

void starryBackground(void){
	int size = 500;
	float xPosition[size], yPosition[size], zPosition[size];
	float bagckgroundStarPosition [50][50][50];

	for(int i = 0; i < size + 1; i++){
		float upper = 10.0;
		float lower = -10.0;

		float xrandomNumber = (((float)rand() / RAND_MAX) * (upper - lower)) + lower;
		float yrandomNumber = (((float)rand() / RAND_MAX) * (upper - lower)) + lower;
		float zrandomNumber = (((float)rand() / RAND_MAX) * (upper - lower)) + lower;

		xPosition[i] = xrandomNumber;
		yPosition[i] = yrandomNumber;
		zPosition[i] = zrandomNumber;

		printf("xPosition %.2f\n", xPosition[i]);
		printf("yPosition %.2f\n", yPosition[i]);
		printf("zPosition %.2f\n", zPosition[i]);
	}

	int index = 0;
	for (int index = 0; index < size; index++){
		glBegin(GL_POINTS);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(xPosition[index], yPosition[index], zPosition[index]);
		glEnd();		
	}

}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	starryBackground();
	neutronMerge();
	greenPlanet();
//	orbit();
	redPlanet();
 	glutSwapBuffers();
}

void animacao(int x){
	day = (day - 15) % 360; glutPostRedisplay();
	days = (days - 45) % 360; glutPostRedisplay();
	year = (year -5) % 360; glutPostRedisplay(); 
	gravidade = gravidade - atracao; glutPostRedisplay();
	gravidadeGreen = gravidadeGreen - atracao; glutPostRedisplay();
	if(gravidade <= 0 & gravidadeGreen <= 0){
		radiusNeutronPlanet = radiusNeutronPlanet + 0.1;
	}
	if(gravidade < 0 & gravidadeGreen < 0){
		radiusNormalPlanet = radiusNormalPlanet - 0.1;
		if(radiusNormalPlanet <= -0.1){
			isRadiusPositive = false;
		}	
	}
	if(radiusNeutronPlanet >= 2.5){
		radiusNeutronPlanet = 2.5;
	}
	printf("%.2f\n", gravidade);
	display();
	glutTimerFunc(tempo, animacao, 0);
}

void main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Neutron Merge");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	glutTimerFunc(tempo, animacao, 0);
	glutMainLoop();
}
