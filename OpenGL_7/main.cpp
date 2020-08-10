#include <gl/glut.h>

//各種パラメータ
//光源設定(環境、拡散、鏡面のみ）
GLfloat lightAmb[] = { 0.f,0.f,0.f,1.f };
GLfloat lightDiff[] = { 1.f,1.f,1.f,1.f };
GLfloat lightSpec[] = { 1.f,1.f,1.f,1.f };
GLfloat lightPos[] = { 1.f,1.f,1.f,0.f };//	平行光源

//マテリアル（環境光、拡散光、鏡面光、鏡面指数）
GLfloat pearlAmb[] = { 0.25f,0.20725f,0.20725f,1.f };
GLfloat pearlDiff[] = { 1.f,0.829f,0.829f,1.f };
GLfloat pearlSpe[] = { 0.296648f,0.296648f,0.296648f,1.f };
const GLfloat pearlThin = 10.24f;

//gluオブジェクト
GLUquadricObj* quadric = NULL;

//GLUquadricObjの描画
void DrawQuadricObj()
{
	//シリンダ
	gluQuadricOrientation(quadric, GLU_OUTSIDE);
	gluCylinder(quadric, 0.5, 0.3, 1.0, 20, 15);

	//上面
	glPushMatrix();
	glTranslatef(0.f, 0.f, 1.f);
	gluDisk(quadric, 0, 0.3, 20, 10);
	glPopMatrix();

	//底辺（法線の向きを逆にする）
	gluQuadricOrientation(quadric, GLU_INSIDE);
	gluDisk(quadric, 0, 0.5, 20, 10);
}

//各種コールバック関数

//ディスプレイ
void display()
{
	static int angle = 0;

	//バッファの初期化
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 1.5, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//光源の位置設定
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	//材質設定と描画
	glPushMatrix();
	glRotated(float(angle), 0.f, 1.f, 0.f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,pearlAmb);//環境光
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,pearlDiff);//拡散光
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,pearlSpe);//鏡面光
	glMaterialf(GL_FRONT_AND_BACK, GL_SPECULAR, pearlThin);

	DrawQuadricObj();//描画

	glPopMatrix();

	glutSwapBuffers();

	if (++angle >= 360) {
		angle = 0; //回転角度のリセット
	}
}

//ウィンドウサイズを変更した際
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);//ビューポートの設定

	glMatrixMode(GL_PROJECTION);//射影行列の設定
	glLoadIdentity();
	gluPerspective(30, (double)w / h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); //モデルビュー行列の設定
}

//再描画命令
void idle()
{
	glutPostRedisplay();
}

//その他各種設定
void otherInit()
{
	//カラーバッファの初期化
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);

	//光源設定(環境、拡散、鏡面のみ）
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

	//光源とライティングの有効化
	glEnable(GL_LIGHTING);//光源の設定を有効化
	glEnable(GL_LIGHT0);//0番目の光源を有効化
	glEnable(GL_NORMALIZE);//法線ベクトルの正規化

	//GLUquadricオブジェクトの設定
	quadric = gluNewQuadric();//オブジェクト生成
	gluQuadricDrawStyle(quadric, GLU_FILL);//ポリゴン描画
	gluQuadricNormals(quadric, GLU_SMOOTH);//シェーディング
}

//メイン関数
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); //GLUTの初期化

	//Windowの作成
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //ディスプレイモード
	glutCreateWindow("Light	Material Vertex");


	//コールバック関数登録
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	otherInit();

	glutMainLoop(); //メインループへ

	//不要になったら破棄
	gluDeleteQuadric(quadric);//本来は終了処理部分で記述

	return 0;
}