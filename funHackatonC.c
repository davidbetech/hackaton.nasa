/**
 * @file funHackatonC.c
 * @brief Archivo que contiene las funciones y declaraciones de hackaton.c
 */

#include "tiposHackaton.h"

/**
 * @brief Función que va a estar insertando dinamicamente la lista doble circular a partir de la captura de datos de un usuario.
 * @param *ap, variable de tipo root que contiene la referencia a la lista
 * @param planets, variable de tipo exoP que contiene la informacion del planeta
 * @return void
 * @authors Daniel Nuño, Diego Saldaña, Salvador Ullibari, David Betech & Julio Verdiguel
 * @date 05/10/2024
 */

extern void insertLDC(ref *ap, exoP planets)
{
    node *new;

    new = (node *)malloc(sizeof(node));

    if (new == NULL)
    {
        printf("\nNo memory available.\n");
        exit(1);
    }

    new->dataExoP = planets;

    new->left = NULL;
    new->right = NULL;

    // Case 1, empty list
    if ((ap->first == NULL) && (ap->last == NULL))
    {
        ap->first = new;
        ap->last = new;
        new->right = new;
        new->left = new;
    }
    // Case 2, empty list
    else
    {
        new->right = ap->first;
        new->left = ap->last;
        ap->last->right = new;
        ap->last = new;
    }
    return;
}
/**
 * @brief Función que busca el planeta por su clave única
 * @param ap, Obtenemos la referencia
 */
extern node *findPlanet(ref *ap, int key)
{
    node *current = NULL;
    if (ap == NULL || ap->first == NULL)
    {
        printf("Error there are no exoplanets registered yet");
    }

    current = ap->first;

    do
    {
        if (current->dataExoP.key == key)
        {
            return current;
        }
        current = current->right;
    } while (current != ap->first); // Recorrer circularmente

    return NULL; // No se encontró el planeta
}

/**
 * @brief Función que borra el exoplaneta
 * @param ap, Obtenemos la referencia del planeta
 */
extern void deletePlanet(ref *ap)
{
    node *temp;
    while (ap != NULL)
    {
        temp = ap->aux;
        ap->aux = temp->right;
        free(temp);
    }
}
/**
 * @brief Función que guarda la info en el archivo binario
 * @param filename, variable de tipo char que almacena el nombre del archivo
 * @param apt, es la referencia de la lista
 */
extern void guardarDatos(char filename[], ref *apt)
{
    FILE *fp;
    node *data, *temp;

    temp = apt->first;

    fp = fopen("exoplanets.bin", "w+b");
    if (fp == NULL)
    {
        printf("\nFile not available\n");
        exit(1);
    }

    do
    {
        data->dataExoP = apt->aux->dataExoP;
        data->right = NULL;
        data->left = NULL;

        // printf("\nAlbum: %s\t No. Fotos: %d\n", data1.nomAlbum, data1.numFotos);
        //  printf("\nTodo okkkkk Categorias\n");
        fwrite(&data, sizeof(node), 1, fp);

        temp = temp->right;

    } while (temp != apt->first);

    fclose(fp);

    return;
}