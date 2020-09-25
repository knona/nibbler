# Nibbler

## Structures et classes:

### Snake

Class herite de Element

Attributs:

- direction

Méthodes:

- moveFromTopInput()
- moveFromRightInput()
- moveFromBottomnput()
- moveFromLeftInput()

# AJOUTER DES IDS AUX CLASSES WALL, FOOD ET VERIFIER SNAKE

### Main

- Area area
- Snake snake
- map\<Position, Wall\> Walls
- map\<Position, Food\> Foods
- cycle

## Bibliotheques

3 bibliothèques dynamiques voir :
https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

Elles ont des fichiers communs pour l'affichage.
On aura donc 3 fichiers libA.cpp libB.cpp libC.cpp qui seront compilés avec un même ensemble de fichiers.

Ces 3 libs mettront à disposition certaines fonctions pour pouvoir être utilisées par l'exécutable. Ces fonctions doivent être définies dans le bloc extern c.

Mode de jeu ou les commandes flèches sont inversées
