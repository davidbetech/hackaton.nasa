/**
 * @file tiposHackaton.h
 * @brief Archivo que va a contener las bibliotecas que se usarán para hackaton.c y funHackaton.c
 */
#include <gtk-2.0/gtk/gtk.h>
#include <stdio_ext.h>

// STRUCTS
// Estructura contiene la informacion basica de un exoplaneta
struct exoplanet
{
    int key;
    char name[50];
    char description[50];
    float distanceEarth;
    char planetClass[50];
    char planetRadius[50];
    char discoveryMethod[50];
    char planetMass[50];
    int discoveryDate;
    char orbitalRadius[50];
    float orbitalPeriod[50];
    float eccentricity[50];
    char nomArch[25];
};
typedef struct exoplanet exoP;

// LDC lista doble circular
struct LDC
{
    exoP dataExoP;
    struct LDC *right, *left;
};
typedef struct LDC node;

// Referencia
struct referencia
{
    node *first, *last, *aux;

    // GTK
    GtkWidget *mainWindow;
    GtkWidget *vBox;
    GtkWidget *leftBot;
    GtkWidget *rightBot;
    GtkWidget *buttonInsert;
    GtkWidget *buttonClose;
    GtkWidget *buttonErase;
    GtkWidget *buttonMap;
    GtkWidget *label;
    GtkWidget *lblMainStatus;
    GtkWidget *lblNamePlanet, *lblDescription, *lblDistanceEarth, *lblSize, *lblPlanetClass, *lblPlanetRadius, *lblDiscoveryMethod, *lblPlanetMass, *lblDiscoveryDate, *lblOrbitalRadius, *lblOrbitalPeriod, *lblEccentricity, *lblEmergentWindow, *lblDialog;
    GtkWidget *photo, *saveBot, *botonGiantGas, *dialog;
    GtkWidget *entryNewExoPlanet;
    GtkWidget *lblStart;
    GtkWidget *vBox2, *hBox1, *hBox2, *hBox3, *hBox4;
    GtkWidget *label1, *label2, *label3, *label4, *label5, *label6, *bottonExit;
    GtkWidget *vBox3, *hBox5, *hBox6, *hBox7, *hBox8;
    GtkWidget *label7, *label8, *label9, *label10, *label11, *buttonExit2;
    char filename[50];

};
typedef struct referencia ref;
