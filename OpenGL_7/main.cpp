#include <gl/glut.h>

//�e��p�����[�^
//�����ݒ�(���A�g�U�A���ʂ̂݁j
GLfloat lightAmb[] = { 0.f,0.f,0.f,1.f };
GLfloat lightDiff[] = { 1.f,1.f,1.f,1.f };
GLfloat lightSpec[] = { 1.f,1.f,1.f,1.f };
GLfloat lightPos[] = { 1.f,1.f,1.f,0.f };//	���s����

//�}�e���A���i�����A�g�U���A���ʌ��A���ʎw���j
GLfloat pearlAmb[] = { 0.25f,0.20725f,0.20725f,1.f };
GLfloat pearlDiff[] = { 1.f,0.829f,0.829f,1.f };
GLfloat pearlSpe[] = { 0.296648f,0.296648f,0.296648f,1.f };
const GLfloat pearlThin = 10.24f;

//glu�I�u�W�F�N�g
GLUquadricObj* quadric = NULL;

//GLUquadricObj�̕`��
void DrawQuadricObj()
{
	//�V�����_
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric, 0.5, 0.3, 1.0, 20, 15);

	//���
	glPushMatrix();
	glTranslatef(0.f, 0.f, 1.f);
	gluDisk(quadric, 0, 0.3, 20, 10);
	glPopMatrix();

	//��Ӂi�@���̌������t�ɂ���j
	gluQuadricOrientation(quadric, GLU_INSIDE);
	gluDisk(quadric, 0, 0.5, 20, 10);
}

//�e��R�[���o�b�N�֐�

//�f�B�X�v���C
void display()
{
	static int angle = 0;

	//�o�b�t�@�̏�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 1.5, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//�����̈ʒu�ݒ�
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//�ގ��ݒ�ƕ`��
	glPushMatrix();
	glRotated(float(angle), 0.f, 1.f, 0.f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,pearlAmb);//����
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,pearlDiff);//�g�U��
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,pearlSpe);//���ʌ�
	glMaterialf(GL_FRONT_AND_BACK, GL_SPECULAR, pearlThin);

	DrawQuadricObj();//�`��

	glPopMatrix();

	glutSwapBuffers();

	if (++angle >= 360) {
		angle = 0; //��]�p�x�̃��Z�b�g
	}
}

//�E�B���h�E�T�C�Y��ύX������
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);//�r���[�|�[�g�̐ݒ�

	glMatrixMode(GL_PROJECTION);//�ˉe�s��̐ݒ�
	glLoadIdentity();
	gluPerspective(30, (double)w / h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); //���f���r���[�s��̐ݒ�
}

//�ĕ`�施��
void idle()
{
	glutPostRedisplay();
}

//���̑��e��ݒ�
void otherInit()
{
	//�J���[�o�b�t�@�̏�����
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);

	//�����ݒ�(���A�g�U�A���ʂ̂݁j
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

	//�����ƃ��C�e�B���O�̗L����
	glEnable(GL_LIGHTING);//�����̐ݒ��L����
	glEnable(GL_LIGHT0);//0�Ԗڂ̌�����L����
	glEnable(GL_NORMALIZE);//�@���x�N�g���̐��K��

	//GLUquadric�I�u�W�F�N�g�̐ݒ�
	quadric = gluNewQuadric();//�I�u�W�F�N�g����
	gluQuadricDrawStyle(quadric, GLU_FILL);//�|���S���`��
	gluQuadricNormals(quadric, GLU_SMOOTH);//�V�F�[�f�B���O
}

//���C���֐�
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //GLUT�̏�����

	//Window�̍쐬
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //�f�B�X�v���C���[�h
	glutCreateWindow("Light	Material Vertex");


	//�R�[���o�b�N�֐��o�^
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();

	glutMainLoop(); //���C�����[�v��

	//�s�v�ɂȂ�����j��
	gluDeleteQuadric(quadric);//�{���͏I�����������ŋL�q

	return 0;
}