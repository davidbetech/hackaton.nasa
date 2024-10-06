/**
 * @file hackaton.c
 * @brief Este es el archivo main que contiene todas las llamadas de funciones a GTK
 */
#include "tiposHackaton.h"

// Prototytpes GTK

void event_giantGas(GtkWidget *label2, gpointer data);
GtkWidget *CreateWindow(gchar *windowTitle, gpointer CallBackFunction, ref *base);
void event_moveRight(GtkWidget *rightBot, gpointer data);
void event_moveLeft(GtkWidget *leftBot, gpointer data);
void event_saveInfo(GtkWidget *botYes, gpointer data);
void closeTheApp(GtkWidget *window, gpointer data);
void event_mainMenu(GtkWidget *lblStart, gpointer data);
void event_planetInfo(GtkWidget *lblType, gpointer data);
void save_exoplanet_list_to_binary(GtkWidget *saveBot, gpointer data);

// Prototypes C
void insertLDC(ref *ap, exoP planets);
node findPlanet(ref *ap, int key);
void deletePlanet(ref *ap);

int main(int argc, char *argv[])
{
    FILE *fp;
    ref pointers;
    node data;
    char text[250];
    GtkWidget *lblStart, *lblExit, *lblPrim, *lblMenu, *lblImage;
    GtkWidget *vBox, *hBox1, *hBox2, *hBox3, *hBox4;
    if ((argc >= 1) && (argc <= 2))
    {
        if (argc == 2)
        {
            fp = fopen(argv[1], "r+b");
            if (fp == NULL)
            {
                printf("\nFile NO available\n");
                exit(1);
            }
            while (fread(&data, sizeof(node), 1, fp) == 1)
            {
                insertLDC(&pointers, pointers.first->dataExoP);
            }
            if (pointers.first == pointers.last) // Only one node in the list
            {
                pointers.aux = pointers.first;
            }
            else
            {
                pointers.aux = pointers.first->right;
            }
            pointers.aux->right = NULL;
            pointers.aux->left = NULL;

            fclose(fp);
            printf("\nCarga exitosa\n");
        }
        else
        {
            strcpy(pointers.filename, "exoplanets.bin");
        }
        pointers.aux = pointers.first;
    }
    else
    {
        printf("\n!!Execution Error!!\n");
        printf("\nTo execute this program you must do it in the following way: \n");
        printf("\n./hackaton.exe exoplanets.bin (to load the information)\n");
        printf("\n./hackaton.exe\n");
    }
    // Inicialize GTK
    gtk_init(&argc, &argv);

    // Create Principal Window
    pointers.mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    pointers.vBox = gtk_vbox_new(TRUE, 10);
    hBox1 = gtk_hbox_new(TRUE, 5);
    hBox2 = gtk_hbox_new(TRUE, 5);
    hBox3 = gtk_hbox_new(TRUE, 5);
    hBox4 = gtk_hbox_new(TRUE, 5);
    // Generando los labels generales

    lblPrim = gtk_label_new("Welcome to the Exoplanet's Catalog by Daniel, Salvador, Diego, Julio & David");
    lblMenu = gtk_label_new("Exoplanet");

    sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/nasa.jpg");
    lblImage = gtk_image_new_from_file(text);

    lblStart = gtk_button_new_with_label("START");
    lblExit = gtk_button_new_with_label("EXIT");
    gtk_window_set_title(GTK_WINDOW(pointers.mainWindow), "Exoplanet's Catalog");

    pointers.lblMainStatus = gtk_label_new(" ");

    /*3. Registro de los Callbacks */

    // Destroy
    gtk_signal_connect(GTK_OBJECT(pointers.mainWindow), "destroy", GTK_SIGNAL_FUNC(closeTheApp), &pointers);

    // Start program
    gtk_signal_connect(GTK_OBJECT(lblStart), "clicked", GTK_SIGNAL_FUNC(event_mainMenu), &pointers);

    // Salida del programa
    gtk_signal_connect(GTK_OBJECT(lblExit), "clicked", GTK_SIGNAL_FUNC(closeTheApp), &pointers);

    /* 4. Define jerarquia de instancias (pack the widgets)*/

    // 1° Caja vertical
    gtk_box_pack_start_defaults(GTK_BOX(hBox1), lblPrim);
    gtk_box_pack_start_defaults(GTK_BOX(hBox1), lblMenu);
    // Inserto la 1er caja en la caja principal
    gtk_box_pack_start_defaults(GTK_BOX(pointers.vBox), hBox1);

    // 2 Caja
    gtk_box_pack_start_defaults(GTK_BOX(hBox2), lblImage);
    // Inserto la 2da caja en la caja principal
    gtk_box_pack_start_defaults(GTK_BOX(pointers.vBox), hBox2);

    // 3 Caja
    gtk_box_pack_start_defaults(GTK_BOX(hBox3), lblStart);
    gtk_box_pack_start_defaults(GTK_BOX(hBox3), lblExit);

    // Inserto la 3ra caja en la caja principal
    gtk_box_pack_start_defaults(GTK_BOX(pointers.vBox), hBox3);

    // Inserto la 4ta caja en la caja principal
    gtk_box_pack_start_defaults(GTK_BOX(pointers.vBox), hBox3);

    // Inserto el label en la caja vertical
    gtk_box_pack_start_defaults(GTK_BOX(pointers.vBox), pointers.lblMainStatus);

    // Insertando todo a la ventana principal
    gtk_container_add(GTK_CONTAINER(pointers.mainWindow), pointers.vBox);

    /* 5. Show up all widgets */
    gtk_widget_show_all(pointers.mainWindow);

    /* 6. Leaving the program in a loop */
    gtk_main();
    return 0;
}