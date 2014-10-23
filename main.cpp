#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

void display();
GLfloat adaptHoriz(float pos);

// structure définissant les rectangles représentant les voitures
struct rect {
    int posX, posY, tailleX, tailleY;
    bool couleur, exists = false;
};

struct rect voiture[10];

void setup() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    voiture[0].posX = 0;
    voiture[0].posY = 0;
    voiture[0].tailleX = 1;
    voiture[0].tailleY = 2;
    voiture[0].couleur = true;
    voiture[0].exists = true;

    voiture[1].posX = 2;
    voiture[1].posY = 2;
    voiture[1].tailleX = 2;
    voiture[1].tailleY = 1;
    voiture[1].couleur = false;
    voiture[1].exists = true;

}

int main(int argc, char *argv[])
{
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       glutInitWindowSize(800,600);
       glutCreateWindow("Projet algo ENSIBS1 - Vincent Rocher - Embouteillages");

       setup();
       glutDisplayFunc(display);

       glutMainLoop();
       return 0;
}

void display() {    // fonction se chargeant du dessin des voitures (des rectangles)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // - découpage de la grille en 6 lignes et 6 colonnes
    // - position allant de "-1.0f" à "1.0f"
    // -> un "pas" = (1/3)
    const float pas = 0.3333;
    // dessin des lignes de la grille
    for(int j=0; j<=6; j++){
        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(adaptHoriz(j*pas-1-0.005), GLfloat(-1), adaptHoriz(j*pas-1+0.005), GLfloat(1));
        glRectf(adaptHoriz(-1), GLfloat(j*pas-1-0.005), adaptHoriz(1), GLfloat(j*pas-1+0.005));
    }

    // dessin des voitures
    int i=0;
    while(voiture[i].exists) {
        // dessin du rectangle de la voiture i
        glColor3f(0.0f, 0.0f, 0.0f);
        glRectf(adaptHoriz(voiture[i].posX*pas-1+0.01), GLfloat(voiture[i].posY*pas-1+0.01), adaptHoriz((voiture[i].posX+voiture[i].tailleX)*pas-1-0.01), GLfloat((voiture[i].posY+voiture[i].tailleY)*pas-1-0.01));

        if(voiture[i].couleur == true) glColor3f(1.0f, 1.0f, 0.0f); // si le retangle est la voiture du joueur, l'afficher en jaune
        else glColor3f(0.0f, 0.0f, 1.0f); // sinon, l'afficher en bleu
        glRectf(adaptHoriz(voiture[i].posX*pas-1+0.02), GLfloat(voiture[i].posY*pas-1+0.02), adaptHoriz((voiture[i].posX+voiture[i].tailleX)*pas-1-0.02), GLfloat((voiture[i].posY+voiture[i].tailleY)*pas-1-0.02));

        i++;
    }

    // dessin des boutons

    glutSwapBuffers();

}
GLfloat adaptHoriz(float pos){
    const float zoneHorizDessin = 0.75;
    return pos*zoneHorizDessin-(1-zoneHorizDessin);
}
