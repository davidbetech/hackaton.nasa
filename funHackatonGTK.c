/**
 * @file funHackatonGTK.c
 * @brief Este archivo tiene todas las funciones relacionadas con GTK y C
 */

#include "tiposHackaton.h"
// Prototipos C
void deletePlanet(ref *ap);
void insertLDC(ref *ap, exoP planets);
node *findPlanet(ref *ap, int key);
void guardarDatos(char filename[], ref *apt);

// Prototipos GTK
GtkWidget *CreateWindow(gchar *windowTitle, gpointer CallBackFunction, ref *base);
void event_moveRight(GtkWidget *rightBot, gpointer data);
void event_moveLeft(GtkWidget *leftBot, gpointer data);
void event_saveInfo(GtkWidget *botYes, gpointer data);
void closeTheApp(GtkWidget *window, gpointer data);
void event_mainMenu(GtkWidget *lblStart, gpointer data);
void event_planetInfo(GtkWidget *lblType, gpointer data);
void event_save_exoplanet_list_to_binary(GtkWidget *saveBot, gpointer data);
void event_closeProgram(GtkWidget *botNo, gpointer data);
void closeWindow(GtkButton *button, gpointer data);
void event_InsertPlanet(GtkWidget *bottonInsert, gpointer data);
void event_giantGas(GtkWidget *label2, gpointer data);
void event_terrestrial(GtkWidget *label3, gpointer data);
void event_superEarth(GtkWidget *label4, gpointer data);
void event_neptune(GtkWidget *label5, gpointer data);
void event_unknow(GtkWidget *label6, gpointer data);
/**
 * @brief Función para generar una nueva ventana
 * @param windowTitle, variable de tipo gchar que contiene el nombre de la ventana emergente
 * @param CallBackFunction, contiene la función que requiere para cerrar la ventana emergente
 * @param base, variable de tipo ref que contiene toda la info
 * @authors Daniel Nuño, Salvador Ulibarri, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
GtkWidget *CreateWindow(gchar *windowTitle, gpointer CallBackFunction, ref *base)
{
    GtkWidget *window;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), windowTitle);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 450);
    gtk_container_border_width(GTK_CONTAINER(window), 5);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    // Callback para cuando se desee cerrar la ventana emergente
    gtk_signal_connect(GTK_OBJECT(window), "destroy", GTK_SIGNAL_FUNC(CallBackFunction), base);
    return window;
}

/**
 * @brief Función para desplazarnos a la derecha de la lista doble circular
 * @param rightBot, variable de tipo GtkWidget que contiene el boton que uso para llamar la función
 * @param data, variable de tipo gpointer que sirvira para tomar la referencia de la info.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
extern void event_moveRight(GtkWidget *rightBot, gpointer data)
{
    ref *pNavegador;
    pNavegador = (ref *)data;
    char text[250];
    int num;
    char distanceStr[250]; // Ensure the array is large enough to hold the converted string

    if (pNavegador->aux != NULL)
    {
        pNavegador->aux = pNavegador->aux->right;

        // Actualizando label de nombre planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblNamePlanet), pNavegador->aux->dataExoP.name);
        // Actualizando label de descripcion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDescription), pNavegador->aux->dataExoP.description);
        // Actualizando label de distancia a la tierra
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", pNavegador->aux->dataExoP.distanceEarth);
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDistanceEarth), distanceStr);

        // Actualizando label de tipo de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetClass), pNavegador->aux->dataExoP.planetClass);
        // Actualizando label de radio de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetRadius), pNavegador->aux->dataExoP.planetRadius);
        // Actualizando label de metodo de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryMethod), pNavegador->aux->dataExoP.discoveryMethod);
        // Actualizando label de masa del planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetMass), pNavegador->aux->dataExoP.planetMass);
        // Actualizando label de fecha de descubrimiento
        snprintf(distanceStr, sizeof(distanceStr), "%d", pNavegador->aux->dataExoP.discoveryDate);
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryDate), distanceStr);
        // Actualizando label de Radio orbital
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalRadius), pNavegador->aux->dataExoP.orbitalRadius);
        // Actualizando label de Periodo de orbitacion
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", *(pNavegador->aux->dataExoP.orbitalPeriod));
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalPeriod), distanceStr);
        // Actualizando label de Excentricidad
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", *(pNavegador->aux->dataExoP.eccentricity));
        gtk_label_set_text(GTK_LABEL(pNavegador->lblEccentricity), distanceStr);

        gtk_label_set_text(GTK_LABEL(pNavegador->lblMainStatus), "Moving to the right ...");
    }
    else
    {
        // Actualizando label de nombre de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblNamePlanet), "No Planet to the right yet");
        // Actualizando label de descripcion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDescription), "No description to the right yet");
        // Actualizando label de distancia a la tierra
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDistanceEarth), "No distance to the right yet");
        // Actualizando label de tipo de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetClass), "No type of planet to the right yet");
        // Actualizando label de radio de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetRadius), "No planet radius to the right yet");
        // Actualizando label de metodo de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryMethod), "No discovery method to the right yet");
        // Actualizando label de masa del planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetMass), "No planet mass to the right yet");
        // Actualizando label de fecha de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryDate), "No discovery date to the right yet");
        // Actualizando label de Radio orbital
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalRadius), "No orbital radius to the right yet");
        // Actualizando label de Periodo de orbitacion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalPeriod), "No orbital period to the right yet");
        // Actualizando label de Excentricidad
        gtk_label_set_text(GTK_LABEL(pNavegador->lblEccentricity), "No eccentricity to the right yet");

        sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/nasa.jpg");
        pNavegador->photo = gtk_image_new_from_file(text);

        gtk_label_set_text(GTK_LABEL(pNavegador->lblMainStatus), "No exoplanets inserted yet in the right");
    }

    return;
}
/**
 * @brief Función para desplazarnos a la izquierda de la lista doble circular
 * @param leftBot, variable de tipo GtkWidget que contiene el boton que uso para llamar la función
 * @param data, variable de tipo gpointer que sirvira para tomar la referencia de la info.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
extern void event_moveLeft(GtkWidget *leftBot, gpointer data)
{
    ref *pNavegador;
    pNavegador = (ref *)data;
    char text[250];
    int num;

    if (pNavegador->aux != NULL)
    {
        pNavegador->aux = pNavegador->aux->left;
        char distanceStr[250]; // Ensure the array is large enough to hold the converted string

        // Actualizando label de nombre planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblNamePlanet), pNavegador->aux->dataExoP.name);
        // Actualizando label de descripcion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDescription), pNavegador->aux->dataExoP.description);
        // Actualizando label de distancia a la tierra
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", pNavegador->aux->dataExoP.distanceEarth);
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDistanceEarth), distanceStr);

        // Actualizando label de tipo de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetClass), pNavegador->aux->dataExoP.planetClass);
        // Actualizando label de radio de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetRadius), pNavegador->aux->dataExoP.planetRadius);
        // Actualizando label de metodo de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryMethod), pNavegador->aux->dataExoP.discoveryMethod);
        // Actualizando label de masa del planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetMass), pNavegador->aux->dataExoP.planetMass);
        // Actualizando label de fecha de descubrimiento
        snprintf(distanceStr, sizeof(distanceStr), "%d", pNavegador->aux->dataExoP.discoveryDate);
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryDate), distanceStr);
        // Actualizando label de Radio orbital
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalRadius), pNavegador->aux->dataExoP.orbitalRadius);
        // Actualizando label de Periodo de orbitacion
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", *(pNavegador->aux->dataExoP.orbitalPeriod));
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalPeriod), distanceStr);
        // Actualizando label de Excentricidad
        snprintf(distanceStr, sizeof(distanceStr), "%.2f", *(pNavegador->aux->dataExoP.eccentricity));
        gtk_label_set_text(GTK_LABEL(pNavegador->lblEccentricity), distanceStr);

        gtk_label_set_text(GTK_LABEL(pNavegador->lblMainStatus), "Moving to the left...");
    }
    else
    {
        // Actualizando label de nombre de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblNamePlanet), "No Planet to the left yet");
        // Actualizando label de descripcion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDescription), "No description to the left yet");
        // Actualizando label de distancia a la tierra
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDistanceEarth), "No distance to the left yet");
        // Actualizando label de tipo de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetClass), "No type of planet to the left yet");
        // Actualizando label de radio de planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetRadius), "No planet radius to the left yet");
        // Actualizando label de metodo de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryMethod), "No discovery method to the left yet");
        // Actualizando label de masa del planeta
        gtk_label_set_text(GTK_LABEL(pNavegador->lblPlanetMass), "No planet mass to the left yet");
        // Actualizando label de fecha de descubrimiento
        gtk_label_set_text(GTK_LABEL(pNavegador->lblDiscoveryDate), "No discovery date to the left yet");
        // Actualizando label de Radio orbital
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalRadius), "No orbital radius to the left yet");
        // Actualizando label de Periodo de orbitacion
        gtk_label_set_text(GTK_LABEL(pNavegador->lblOrbitalPeriod), "No orbital period to the left yet");
        // Actualizando label de Excentricidad
        gtk_label_set_text(GTK_LABEL(pNavegador->lblEccentricity), "No eccentricity to the left yet");

        sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/nasa.jpg");
        pNavegador->photo = gtk_image_new_from_file(text);

        gtk_label_set_text(GTK_LABEL(pNavegador->lblMainStatus), "No exoplanets inserted yet in the left");
    }

    return;
}

extern void event_saveInfo(GtkWidget *botYes, gpointer data)
{
    ref *base = (ref *)data;

    guardarDatos("fotos.bin", base);
    // lecturaData("fotos.bin");

    printf("\n\nAll changes have been succesfully saved.\n\n");

    gtk_widget_destroy(base->dialog);
    gtk_main_quit();
    return;
}

/**
 * @brief Función para desplazarnos a la izquierda de la lista doble circular
 * @param leftBot, variable de tipo GtkWidget que contiene el boton que uso para llamar la función
 * @param data, variable de tipo gpointer que sirvira para tomar la referencia de la info.
 * @authors Daniel Nuño, Salvador ullibarri
 * @date
 * @return void
 */

extern void closeTheApp(GtkWidget *window, gpointer data)
{
    ref *base = (ref *)data;
    GtkWidget *botYes, *botNo, *lblFinal;

    base->dialog = gtk_dialog_new_with_buttons("Cerrando programa", GTK_WINDOW(base->mainWindow), GTK_DIALOG_MODAL, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_dialog_set_has_separator(GTK_DIALOG(base->dialog), TRUE);

    lblFinal = gtk_label_new("Do you want to save any changes?");
    botYes = gtk_button_new_with_label("YES");
    botNo = gtk_button_new_with_label("NO");

    // Si quiero guardar info.
    gtk_signal_connect(GTK_OBJECT(botYes), "clicked", GTK_SIGNAL_FUNC(event_save_exoplanet_list_to_binary), base);

    // No quiero guardar info.
    gtk_signal_connect(GTK_OBJECT(botNo), "clicked", GTK_SIGNAL_FUNC(event_closeProgram), base);

    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(base->dialog)->vbox), lblFinal);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(base->dialog)->vbox), botYes);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(base->dialog)->vbox), botNo);

    gtk_widget_show_all(base->dialog);
    gtk_dialog_run(GTK_DIALOG(base->dialog));

    return;
}

extern void event_mainMenu(GtkWidget *lblStart, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];
    int num;

    

    if (nav->first != NULL)
    {
        // 1° Creación de cajas
        nav->lblEmergentWindow = CreateWindow("ExoPlanet's Catalog", closeWindow, nav);
        nav->vBox2 = gtk_vbox_new(FALSE, 0);
        nav->hBox1 = gtk_hbox_new(FALSE, 0);
        nav->hBox2 = gtk_hbox_new(FALSE, 0);
        nav->hBox3 = gtk_hbox_new(FALSE, 0);
        nav->hBox4 = gtk_hbox_new(FALSE, 0);

        // 2° Generando de Labels y entries

        nav->label1 = gtk_label_new("Welcome to the Exoplanet's catalog");
        // Botones de la LDC
        nav->label2 = gtk_button_new_with_label("Giant Gas");
        nav->label3 = gtk_button_new_with_label("Terrestrial");
        // foto
        sprintf(text, " ");
        nav->photo = gtk_image_new_from_file(text);
        nav->label4 = gtk_button_new_with_label("Super Earth");
        nav->label5 = gtk_button_new_with_label("Neptune");
        nav->label6 = gtk_button_new_with_label("Unknown");

        nav->bottonExit = gtk_button_new_with_label("Exit section");

        //  3° Registro de CallBacks
        gtk_signal_connect(GTK_OBJECT(nav->lblEmergentWindow), "destroy", GTK_SIGNAL_FUNC(closeWindow), nav);

        // Salida de la ventana
        gtk_signal_connect(GTK_OBJECT(nav->bottonExit), "clicked", GTK_SIGNAL_FUNC(closeWindow), nav);

        // Mover a la siguiente foto
        gtk_signal_connect(GTK_OBJECT(nav->label2), "clicked", GTK_SIGNAL_FUNC(event_giantGas), nav);

        // Nueva foto
        gtk_signal_connect(GTK_OBJECT(nav->label3), "clicked", GTK_SIGNAL_FUNC(event_terrestrial), nav);

        // Dar de alta
        gtk_signal_connect(GTK_OBJECT(nav->label4), "clicked", GTK_SIGNAL_FUNC(event_superEarth), nav);

        // Dar de baja
        gtk_signal_connect(GTK_OBJECT(nav->label5), "clicked", GTK_SIGNAL_FUNC(event_neptune), nav);

        // Borrar la última foto
        gtk_signal_connect(GTK_OBJECT(nav->label6), "clicked", GTK_SIGNAL_FUNC(event_unknow), nav);

        // 4° Definiendo la jerarquía de instancias (pack de widgets)

        // 1° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox1), nav->label1);
        // Inserto la 1er caja en la caja principal
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox2), nav->hBox1);

        // 2° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox2), nav->label2);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox2), nav->label3);
        // Inserto la 2da caja en la caja principal
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox2), nav->hBox2);

        // 3° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox3), nav->photo);
        // Inserto la 3era caja en la caja principal
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox2), nav->hBox3);

        // 4° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox4), nav->label4);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox4), nav->label5);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox4), nav->bottonExit);
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox2), nav->hBox4);
    }

    return;
}

extern void event_planetInfo(GtkWidget *lblType, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];
    int num;


    if (nav->first != NULL)
    {
        // 1° Creación de cajas
        nav->lblEmergentWindow = CreateWindow("ExoPlanet's Catalog", closeWindow, nav);
        nav->vBox3 = gtk_vbox_new(FALSE, 0);
        nav->hBox5 = gtk_hbox_new(FALSE, 0);
        nav->hBox6 = gtk_hbox_new(FALSE, 0);
        nav->hBox7 = gtk_hbox_new(FALSE, 0);
        nav-> hBox8 = gtk_hbox_new(FALSE, 0);
        // 2° Generando de Labels y entries
        snprintf(text, sizeof(text), "Type: %s", nav->aux->dataExoP.planetClass);
        nav->lblPlanetClass = gtk_label_new(text);

        // Picture
        sprintf(text, " ");
        nav->photo = gtk_image_new_from_file(text);

        // Planet Data
        snprintf(text, sizeof(text), "Name: %s", nav->aux->dataExoP.planetClass);
        nav->lblNamePlanet = gtk_label_new(text);

        snprintf(text, sizeof(text), "Description: %s", nav->aux->dataExoP.description);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Distance: %.2f", nav->aux->dataExoP.distanceEarth);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Radius: %s", nav->aux->dataExoP.planetRadius);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Discovery Method: %s", nav->aux->dataExoP.discoveryMethod);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Planet Mass: %s", nav->aux->dataExoP.planetMass);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Discovery Date: %d", nav->aux->dataExoP.discoveryDate);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Orbital Radius: %s", nav->aux->dataExoP.orbitalRadius);
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Orbital Period: %.2f", *(nav->aux->dataExoP.orbitalPeriod));
        nav->lblDescription = gtk_label_new(text);

        snprintf(text, sizeof(text), "Eccentricity: %.2f", *(nav->aux->dataExoP.eccentricity));
        nav->lblDescription = gtk_label_new(text);

        // Botones

        nav->leftBot = gtk_button_new_with_label("<");
        nav->buttonInsert = gtk_button_new_with_label("Insert");
        nav->buttonErase = gtk_button_new_with_label("Erase");
        nav->buttonMap = gtk_button_new_with_label("View Map");
        nav->buttonExit2 = gtk_button_new_with_label("Return");
        nav->leftBot = gtk_button_new_with_label(">");

        //  3° Registro de CallBacks
        // Salir de la ventana emergente
        gtk_signal_connect(GTK_OBJECT(nav->lblEmergentWindow), "destroy", GTK_SIGNAL_FUNC(closeWindow), nav);
        // Cerrar programa
        gtk_signal_connect(GTK_OBJECT(nav->buttonExit2), "clicked", GTK_SIGNAL_FUNC(closeWindow), nav);
        // Mover Izquierda
        gtk_signal_connect(GTK_OBJECT(nav->leftBot), "clicked", GTK_SIGNAL_FUNC(event_moveLeft), nav);
        // Borrar boton
        gtk_signal_connect(GTK_OBJECT(nav->buttonErase), "clicked", GTK_SIGNAL_FUNC(event_InsertPlanet), nav);
        //
        gtk_signal_connect(GTK_OBJECT(nav->buttonMap), "clicked", GTK_SIGNAL_FUNC(event_InsertPlanet), nav);
        //
        gtk_signal_connect(GTK_OBJECT(nav->buttonExit2), "clicked", GTK_SIGNAL_FUNC(closeWindow), nav);
        //
        gtk_signal_connect(GTK_OBJECT(nav->rightBot), "clicked", GTK_SIGNAL_FUNC(event_moveRight), nav);

        // Insertar un planeta
        gtk_signal_connect(GTK_OBJECT(nav->buttonInsert), "clicked", GTK_SIGNAL_FUNC(event_InsertPlanet), nav);

        // 4° Definiendo la jerarquía de instancias (pack de widgets)

        // 1° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox5), nav->lblPlanetClass);
        // Inserto la 1er caja en la caja principal
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox3), nav->hBox5);

        // 2° Caja vertical
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->photo);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblNamePlanet);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblDescription);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblDistanceEarth);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblPlanetRadius);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblDiscoveryMethod);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblPlanetMass);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblDiscoveryDate);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblOrbitalRadius);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblOrbitalPeriod);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->lblEccentricity);

        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox6), nav->hBox7);

        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox3), nav->hBox6);

        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->leftBot);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->buttonInsert);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->buttonErase);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->buttonMap);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->buttonExit2);
        gtk_box_pack_start_defaults(GTK_BOX(nav->hBox8), nav->rightBot);
        gtk_box_pack_start_defaults(GTK_BOX(nav->vBox3), nav->hBox4);
    }

    return;
}

/**
 * @brief Función para guardar la lista circular
 * @param saveBot, variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
extern void event_save_exoplanet_list_to_binary(GtkWidget *saveBot, gpointer data)
{
    node *list = (node *)data;
    node *current = list;

    // Crear el diálogo de selección de archivo
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Guardar lista de exoplanetas", NULL, action, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT, NULL);

    // Configurar nombre de archivo por defecto
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "exoplanets.bin");

    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        // Obtener el nombre del archivo
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);

        // Abrir el archivo en modo binario
        FILE *file = fopen(filename, "wb");
        if (file != NULL)
        {
            // Verificar si la lista es nula
            if (current != NULL)
            {
                do
                {
                    fwrite(&(current->dataExoP), sizeof(exoP), 1, file);
                    current = current->right;
                } while (current != list); // La lista es circular, se detiene cuando vuelve al inicio
            }

            fclose(file);
            g_message("Lista de exoplanetas guardada en %s\n", filename);
        }
        else
        {
            g_error("Error al abrir el archivo para escribir: %s\n", filename);
        }

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

/**
 * @brief Función para crear el callback de event_giantGas
 * @param label2 variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
void event_giantGas(GtkWidget *label2, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];

    // Comprobamos si hay datos disponibles
    if (nav->first != NULL)
    {
        // Creación de la ventana emergente
        nav->lblEmergentWindow = CreateWindow("Giant Gas Planets", closeWindow, nav);
        GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
        GtkWidget *hBox = gtk_hbox_new(FALSE, 0);
        // Bucle para recorrer todos los planetas de tipo "giantGas"
        node *currentNode = nav->first; // Suponiendo que 'inicio' es el primer nodo de la lista

        while (currentNode != NULL)
        {
            if (strcmp(currentNode->dataExoP.planetClass, "Giant Gas") == 0)
            {
                // Aquí generamos los labels y otros widgets para el planeta actual
                sprintf(text, "Planet Name: %s", currentNode->dataExoP.name);
                GtkWidget *lblPlanetName = gtk_label_new(text);

                sprintf(text, "Description: %s", currentNode->dataExoP.description);
                GtkWidget *lblDescription = gtk_label_new(text);

                sprintf(text, "Mass: %s", currentNode->dataExoP.planetMass);
                GtkWidget *lblMass = gtk_label_new(text);

                sprintf(text, "Distance Earth: %f", currentNode->dataExoP.distanceEarth);
                GtkWidget *lblDistanceEarth = gtk_label_new(text);

                sprintf(text, "Planet Class: %s", currentNode->dataExoP.planetClass);
                GtkWidget *lblPlanetClass = gtk_label_new(text);

                sprintf(text, "Planet Radius: %s", currentNode->dataExoP.planetRadius);
                GtkWidget *lblPlanetRadius = gtk_label_new(text);

                sprintf(text, "Discovery Method: %s", currentNode->dataExoP.discoveryMethod);
                GtkWidget *lblDiscoveryMethod = gtk_label_new(text);

                sprintf(text, "Discovery Date: %d", currentNode->dataExoP.discoveryDate);
                GtkWidget *lblDiscoveryDate = gtk_label_new(text);

                sprintf(text, "Orbital Radius: %s", currentNode->dataExoP.orbitalRadius);
                GtkWidget *lblOrbitalRadius = gtk_label_new(text);

                sprintf(text, "Orbital Period: %f", *(currentNode->dataExoP.orbitalPeriod));
                GtkWidget *lblOrbitalPeriod = gtk_label_new(text);

                sprintf(text, "Eccentricity: %f", *(currentNode->dataExoP.eccentricity));
                GtkWidget *lblEccentricity = gtk_label_new(text);

                // Agregar más labels según sea necesario...
                // Empacamos los widgets en la caja vertical
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetName, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDescription, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblMass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDistanceEarth, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetClass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryMethod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryDate, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalPeriod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblEccentricity, TRUE, TRUE, 0);
                // Si necesitas mostrar imagenes, puedes agregar otra lógica aquí
                // Por ejemplo, si hay imágenes asociadas a los planetas:
                sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/%s.jpg", currentNode->dataExoP.name);
                GtkWidget *photo = gtk_image_new_from_file(text);
                gtk_box_pack_start(GTK_BOX(vBox), photo, TRUE, TRUE, 0);
            }
        }

        // Finalizar la configuración de la ventana
        gtk_container_add(GTK_CONTAINER(nav->lblEmergentWindow), vBox);
        gtk_widget_show_all(nav->lblEmergentWindow);

        // Conectar el evento de cierre de ventana
        g_signal_connect(G_OBJECT(nav->lblEmergentWindow), "destroy", G_CALLBACK(closeWindow), nav);
    }
}

/**
 * @brief Función para crear el callback de event_Terrastrial
 * @param label3 variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
void event_terrestrial(GtkWidget *label3, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];

    // Comprobamos si hay datos disponibles
    if (nav->first != NULL)
    {
        // Creación de la ventana emergente
        nav->lblEmergentWindow = CreateWindow("Terrastrial Planets", closeWindow, nav);
        GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
        GtkWidget *hBox = gtk_hbox_new(FALSE, 0);
        // Bucle para recorrer todos los planetas de tipo "giantGas"
        node *currentNode = nav->first; // Suponiendo que 'inicio' es el primer nodo de la lista

        while (currentNode != NULL)
        {
            if (strcmp(currentNode->dataExoP.planetClass, "Terrastrial") == 0)
            {
                // Aquí generamos los labels y otros widgets para el planeta actual
                sprintf(text, "Planet Name: %s", currentNode->dataExoP.name);
                GtkWidget *lblPlanetName = gtk_label_new(text);

                sprintf(text, "Description: %s", currentNode->dataExoP.description);
                GtkWidget *lblDescription = gtk_label_new(text);

                sprintf(text, "Mass: %s", currentNode->dataExoP.planetMass);
                GtkWidget *lblMass = gtk_label_new(text);

                sprintf(text, "Distance Earth: %f", currentNode->dataExoP.distanceEarth);
                GtkWidget *lblDistanceEarth = gtk_label_new(text);

                sprintf(text, "Planet Class: %s", currentNode->dataExoP.planetClass);
                GtkWidget *lblPlanetClass = gtk_label_new(text);

                sprintf(text, "Planet Radius: %s", currentNode->dataExoP.planetRadius);
                GtkWidget *lblPlanetRadius = gtk_label_new(text);

                sprintf(text, "Discovery Method: %s", currentNode->dataExoP.discoveryMethod);
                GtkWidget *lblDiscoveryMethod = gtk_label_new(text);

                sprintf(text, "Discovery Date: %d", currentNode->dataExoP.discoveryDate);
                GtkWidget *lblDiscoveryDate = gtk_label_new(text);

                sprintf(text, "Orbital Radius: %s", currentNode->dataExoP.orbitalRadius);
                GtkWidget *lblOrbitalRadius = gtk_label_new(text);

                sprintf(text, "Orbital Period: %f", *(currentNode->dataExoP.orbitalPeriod));
                GtkWidget *lblOrbitalPeriod = gtk_label_new(text);

                sprintf(text, "Eccentricity: %f", *(currentNode->dataExoP.eccentricity));
                GtkWidget *lblEccentricity = gtk_label_new(text);

                // Agregar más labels según sea necesario...
                // Empacamos los widgets en la caja vertical
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetName, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDescription, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblMass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDistanceEarth, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetClass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryMethod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryDate, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalPeriod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblEccentricity, TRUE, TRUE, 0);
                // Si necesitas mostrar imagenes, puedes agregar otra lógica aquí
                // Por ejemplo, si hay imágenes asociadas a los planetas:
                sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/%s.jpg", currentNode->dataExoP.name);
                GtkWidget *photo = gtk_image_new_from_file(text);
                gtk_box_pack_start(GTK_BOX(vBox), photo, TRUE, TRUE, 0);
            }
        }

        // Finalizar la configuración de la ventana
        gtk_container_add(GTK_CONTAINER(nav->lblEmergentWindow), vBox);
        gtk_widget_show_all(nav->lblEmergentWindow);

        // Conectar el evento de cierre de ventana
        g_signal_connect(G_OBJECT(nav->lblEmergentWindow), "destroy", G_CALLBACK(closeWindow), nav);
    }
}

/**
 * @brief Función para crear el callback de event_giantGas
 * @param label4 variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
void event_superEarth(GtkWidget *label4, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];

    // Comprobamos si hay datos disponibles
    if (nav->first != NULL)
    {
        // Creación de la ventana emergente
        nav->lblEmergentWindow = CreateWindow("Super Earth Planets", closeWindow, nav);
        GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
        GtkWidget *hBox = gtk_hbox_new(FALSE, 0);
        // Bucle para recorrer todos los planetas de tipo "giantGas"
        node *currentNode = nav->first; // Suponiendo que 'inicio' es el primer nodo de la lista

        while (currentNode != NULL)
        {
            if (strcmp(currentNode->dataExoP.planetClass, "Super Earth") == 0)
            {
                // Aquí generamos los labels y otros widgets para el planeta actual
                sprintf(text, "Planet Name: %s", currentNode->dataExoP.name);
                GtkWidget *lblPlanetName = gtk_label_new(text);

                sprintf(text, "Description: %s", currentNode->dataExoP.description);
                GtkWidget *lblDescription = gtk_label_new(text);

                sprintf(text, "Mass: %s", currentNode->dataExoP.planetMass);
                GtkWidget *lblMass = gtk_label_new(text);

                sprintf(text, "Distance Earth: %f", currentNode->dataExoP.distanceEarth);
                GtkWidget *lblDistanceEarth = gtk_label_new(text);

                sprintf(text, "Planet Class: %s", currentNode->dataExoP.planetClass);
                GtkWidget *lblPlanetClass = gtk_label_new(text);

                sprintf(text, "Planet Radius: %s", currentNode->dataExoP.planetRadius);
                GtkWidget *lblPlanetRadius = gtk_label_new(text);

                sprintf(text, "Discovery Method: %s", currentNode->dataExoP.discoveryMethod);
                GtkWidget *lblDiscoveryMethod = gtk_label_new(text);

                sprintf(text, "Discovery Date: %d", currentNode->dataExoP.discoveryDate);
                GtkWidget *lblDiscoveryDate = gtk_label_new(text);

                sprintf(text, "Orbital Radius: %s", currentNode->dataExoP.orbitalRadius);
                GtkWidget *lblOrbitalRadius = gtk_label_new(text);

                sprintf(text, "Orbital Period: %f", *(currentNode->dataExoP.orbitalPeriod));
                GtkWidget *lblOrbitalPeriod = gtk_label_new(text);

                sprintf(text, "Eccentricity: %f", *(currentNode->dataExoP.eccentricity));
                GtkWidget *lblEccentricity = gtk_label_new(text);

                // Agregar más labels según sea necesario...
                // Empacamos los widgets en la caja vertical
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetName, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDescription, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblMass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDistanceEarth, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetClass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryMethod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryDate, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalPeriod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblEccentricity, TRUE, TRUE, 0);
                // Si necesitas mostrar imagenes, puedes agregar otra lógica aquí
                // Por ejemplo, si hay imágenes asociadas a los planetas:
                sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/%s.jpg", currentNode->dataExoP.name);
                GtkWidget *photo = gtk_image_new_from_file(text);
                gtk_box_pack_start(GTK_BOX(vBox), photo, TRUE, TRUE, 0);
            }
        }

        // Finalizar la configuración de la ventana
        gtk_container_add(GTK_CONTAINER(nav->lblEmergentWindow), vBox);
        gtk_widget_show_all(nav->lblEmergentWindow);

        // Conectar el evento de cierre de ventana
        g_signal_connect(G_OBJECT(nav->lblEmergentWindow), "destroy", G_CALLBACK(closeWindow), nav);
    }
}

/**
 * @brief Función para crear el callback de event_Neptune
 * @param label5 variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */
/*
label6 = gtk_button_new_with_label("Unknown");*/
void event_neptune(GtkWidget *label5, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];

    // Comprobamos si hay datos disponibles
    if (nav->first != NULL)
    {
        // Creación de la ventana emergente
        nav->lblEmergentWindow = CreateWindow("Neptune Planets", closeWindow, nav);
        GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
        GtkWidget *hBox = gtk_hbox_new(FALSE, 0);
        // Bucle para recorrer todos los planetas de tipo "giantGas"
        node *currentNode = nav->first; // Suponiendo que 'inicio' es el primer nodo de la lista

        while (currentNode != NULL)
        {
            if (strcmp(currentNode->dataExoP.planetClass, "Neptune") == 0)
            {
                // Aquí generamos los labels y otros widgets para el planeta actual
                sprintf(text, "Planet Name: %s", currentNode->dataExoP.name);
                GtkWidget *lblPlanetName = gtk_label_new(text);

                sprintf(text, "Description: %s", currentNode->dataExoP.description);
                GtkWidget *lblDescription = gtk_label_new(text);

                sprintf(text, "Mass: %s", currentNode->dataExoP.planetMass);
                GtkWidget *lblMass = gtk_label_new(text);

                sprintf(text, "Distance Earth: %f", currentNode->dataExoP.distanceEarth);
                GtkWidget *lblDistanceEarth = gtk_label_new(text);

                sprintf(text, "Planet Class: %s", currentNode->dataExoP.planetClass);
                GtkWidget *lblPlanetClass = gtk_label_new(text);

                sprintf(text, "Planet Radius: %s", currentNode->dataExoP.planetRadius);
                GtkWidget *lblPlanetRadius = gtk_label_new(text);

                sprintf(text, "Discovery Method: %s", currentNode->dataExoP.discoveryMethod);
                GtkWidget *lblDiscoveryMethod = gtk_label_new(text);

                sprintf(text, "Discovery Date: %d", currentNode->dataExoP.discoveryDate);
                GtkWidget *lblDiscoveryDate = gtk_label_new(text);

                sprintf(text, "Orbital Radius: %s", currentNode->dataExoP.orbitalRadius);
                GtkWidget *lblOrbitalRadius = gtk_label_new(text);

                sprintf(text, "Orbital Period: %f", *(currentNode->dataExoP.orbitalPeriod));
                GtkWidget *lblOrbitalPeriod = gtk_label_new(text);

                sprintf(text, "Eccentricity: %f", *(currentNode->dataExoP.eccentricity));
                GtkWidget *lblEccentricity = gtk_label_new(text);

                // Agregar más labels según sea necesario...
                // Empacamos los widgets en la caja vertical
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetName, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDescription, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblMass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDistanceEarth, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetClass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryMethod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryDate, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalPeriod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblEccentricity, TRUE, TRUE, 0);
                // Si necesitas mostrar imagenes, puedes agregar otra lógica aquí
                // Por ejemplo, si hay imágenes asociadas a los planetas:
                sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/%s.jpg", currentNode->dataExoP.name);
                GtkWidget *photo = gtk_image_new_from_file(text);
                gtk_box_pack_start(GTK_BOX(vBox), photo, TRUE, TRUE, 0);
            }
        }

        // Finalizar la configuración de la ventana
        gtk_container_add(GTK_CONTAINER(nav->lblEmergentWindow), vBox);
        gtk_widget_show_all(nav->lblEmergentWindow);

        // Conectar el evento de cierre de ventana
        g_signal_connect(G_OBJECT(nav->lblEmergentWindow), "destroy", G_CALLBACK(closeWindow), nav);
    }
}

/**
 * @brief Función para crear el callback de event_Neptune
 * @param label6 variable de tipo GtkWidget que contiene el botón que se usa para llamar la función
 * @param data, variable de tipo gpointer que sirve para tomar la referencia de la lista de exoplanetas.
 * @authors Daniel Nuño, Salvador Ullibari, Diego Saldaña, Julio Verdiguel y David Betech
 * @date 05/10/2024
 * @return void
 */

void event_unknow(GtkWidget *label6, gpointer data)
{
    // Typecast de referencia de información
    ref *nav = (ref *)data;
    char text[250];

    // Comprobamos si hay datos disponibles
    if (nav->first != NULL)
    {
        // Creación de la ventana emergente
        nav->lblEmergentWindow = CreateWindow("Unknown Planets", closeWindow, nav);
        GtkWidget *vBox = gtk_vbox_new(FALSE, 0);
        GtkWidget *hBox = gtk_hbox_new(FALSE, 0);
        // Bucle para recorrer todos los planetas de tipo "giantGas"
        node *currentNode = nav->first; // Suponiendo que 'inicio' es el primer nodo de la lista

        while (currentNode != NULL)
        {
            if (strcmp(currentNode->dataExoP.planetClass, "Unknown") == 0)
            {
                // Aquí generamos los labels y otros widgets para el planeta actual
                sprintf(text, "Planet Name: %s", currentNode->dataExoP.name);
                GtkWidget *lblPlanetName = gtk_label_new(text);

                sprintf(text, "Description: %s", currentNode->dataExoP.description);
                GtkWidget *lblDescription = gtk_label_new(text);

                sprintf(text, "Mass: %s", currentNode->dataExoP.planetMass);
                GtkWidget *lblMass = gtk_label_new(text);

                sprintf(text, "Distance Earth: %f", currentNode->dataExoP.distanceEarth);
                GtkWidget *lblDistanceEarth = gtk_label_new(text);

                sprintf(text, "Planet Class: %s", currentNode->dataExoP.planetClass);
                GtkWidget *lblPlanetClass = gtk_label_new(text);

                sprintf(text, "Planet Radius: %s", currentNode->dataExoP.planetRadius);
                GtkWidget *lblPlanetRadius = gtk_label_new(text);

                sprintf(text, "Discovery Method: %s", currentNode->dataExoP.discoveryMethod);
                GtkWidget *lblDiscoveryMethod = gtk_label_new(text);

                sprintf(text, "Discovery Date: %d", currentNode->dataExoP.discoveryDate);
                GtkWidget *lblDiscoveryDate = gtk_label_new(text);

                sprintf(text, "Orbital Radius: %s", currentNode->dataExoP.orbitalRadius);
                GtkWidget *lblOrbitalRadius = gtk_label_new(text);

                sprintf(text, "Orbital Period: %f", *(currentNode->dataExoP.orbitalPeriod));
                GtkWidget *lblOrbitalPeriod = gtk_label_new(text);

                sprintf(text, "Eccentricity: %f", *(currentNode->dataExoP.eccentricity));
                GtkWidget *lblEccentricity = gtk_label_new(text);

                // Agregar más labels según sea necesario...
                // Empacamos los widgets en la caja vertical
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetName, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDescription, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblMass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDistanceEarth, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetClass, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblPlanetRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryMethod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblDiscoveryDate, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalRadius, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblOrbitalPeriod, TRUE, TRUE, 0);
                gtk_box_pack_start(GTK_BOX(vBox), lblEccentricity, TRUE, TRUE, 0);
                // Si necesitas mostrar imagenes, puedes agregar otra lógica aquí
                // Por ejemplo, si hay imágenes asociadas a los planetas:
                sprintf(text, "/mnt/c/Users/John Harrison/Documents/A University/Progra VS/Hackaton/hackaton/%s.jpg", currentNode->dataExoP.name);
                GtkWidget *photo = gtk_image_new_from_file(text);
                gtk_box_pack_start(GTK_BOX(vBox), photo, TRUE, TRUE, 0);
            }
        }

        // Finalizar la configuración de la ventana
        gtk_container_add(GTK_CONTAINER(nav->lblEmergentWindow), vBox);
        gtk_widget_show_all(nav->lblEmergentWindow);

        // Conectar el evento de cierre de ventana
        g_signal_connect(G_OBJECT(nav->lblEmergentWindow), "destroy", G_CALLBACK(closeWindow), nav);
    }
}

void event_closeProgram(GtkWidget *botNo, gpointer data)
{
    ref *base = (ref *)data;

    gtk_widget_destroy(base->dialog);
    printf("\nPrograma terminado\n\n");
    gtk_main_quit();
    return;
}

/**
 * @brief Función para cerrar las ventanas emergentes
 * @param button, variable de tipo GtkWidget que contiene el boton que uso para llamar la función
 * @param data, variable de tipo gpointer que sirvira para tomar la referencia de la info.
 * @authors Daniel Nuño, Salvador Ulibarri, Diego Saldaña,
 * @date 06/mayo/2024
 * @return void
 */
void closeWindow(GtkButton *button, gpointer data)
{
    ref *info = (ref *)data;

    gtk_window_set_modal(GTK_WINDOW(info->lblEmergentWindow), FALSE);
    gtk_widget_destroy(GTK_WIDGET(info->lblEmergentWindow));
}
/**
 *
 */
void event_InsertPlanet(GtkWidget *bottonInsert, gpointer data)
{
    ref *base = (ref *)data;
    node data1;
    char text[250];

    strcpy(text, gtk_entry_get_text(GTK_ENTRY(base->entryNewExoPlanet)));
    strcpy(data1.dataExoP.nomArch, text);
    base->dialog = gtk_dialog_new_with_buttons("Creating New Exoplanet", GTK_WINDOW(base->lblEmergentWindow), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, NULL);
    gtk_dialog_set_has_separator(GTK_DIALOG(base->dialog), TRUE);

    data1.right = NULL;
    data1.left = NULL;

    insertLDC(base, data1.dataExoP);

    base->aux = base->first;

    // printf("%s\t%d", data1.nomAlbum, data1.numFotos);
    // printf("\nSe guardo bien la categoría ingresada\n");

    closeWindow(GTK_BUTTON(bottonInsert), base);

    gtk_label_set_text(GTK_LABEL(base->lblMainStatus), "Exoplaneta Insertado Correctamente");
    return;
}