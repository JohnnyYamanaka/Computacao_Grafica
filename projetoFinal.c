#include <GL/glut.h>

static int year = 0, day = 0;
GLfloat xRotaciona, yRotaciona, zRotaciona;
int tempo = 100;

//variavel para atrair os planetas
float gravidade = 5.0;

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
	gluLookAt (0.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();

	//Planeta amarelo
	glPushMatrix();
		glColor3f(1.0, 1.0, 0.0);
		glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
		glTranslatef(gravidade, 0.0, 0.0);
		glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
		glutSolidSphere(1.0, 15, 8);
	glPopMatrix();
	 	 	
	//Planeta azul
 	glPushMatrix();
		//glColor3f(1.0, 0.27, 0.0);
		glColor3f(0.28, 0.24, 0.55);
		glRotatef((GLfloat) -year * 2, 0.0, 5.0, 0.0);
		glTranslatef(gravidade, 0.0, 0.0);
		glRotatef((GLfloat) day, 0.0, 2.0, 0.0);
		glutSolidSphere(1.0, 15, 8);
	glPopMatrix();

 	glPopMatrix();
 	glutSwapBuffers();
}

void animacao(int x){
	day = (day - 10) % 360; glutPostRedisplay();
	year = (year -5) % 360; glutPostRedisplay(); 
	display();
	glutTimerFunc(tempo, animacao, 0);
}

void main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);

	glutTimerFunc(tempo, animacao, 0);

	glutMainLoop();
}


/*
glutTimerFunc(33, Timer, 1); 
estabelece a função Timer previamente definida como a função callback de animação. 
Seu protótipo é: void glutTimerFunc(unsigned int msecs, void (*func)(int value), int value);. 
Esta função faz a GLUT esperar msecs milisegundos antes de chamar a função func. 
É possível passar um valor definido pelo usuário no parâmetro value. 
Como esta função é "disparada" apenas uma vez, para se ter uma animação contínua é necessário reinicializar o timer novamente na função Timer.
*/