# Nibbler

## Structures et classes:

### Type

Enum

- Wall
- Food
- Snake

### Direction

Enum

- Top
- Right
- Bottom
- Left

### Size

Struct

Attributs:

- int width
- int height

### Position

Struct

Attributs:

- int x
- int y

### IElement

Class

Protected:

- list\<Position\> positions
- Type type

### Snake

Class herite de Element

Attributs:

- direction

Méthodes:

- moveFromTopInput()
- moveFromRightInput()
- moveFromBottomnput()
- moveFromLeftInput()

### Wall

Class herite de Element

### Walls

Class herite de map\<Position, Wall\>

Méthodes:

- void addRandomWall(area)
- void removeWall(, area)

### Food

Class herite de Element

### Foods

Class herite de map\<Position, Food\>

Méthodes:

- void addRandomFood(area)
- void removeFood(, area)

### Area

Class hérite de unique_ptr<unsigned char[]>

- constructeur prend en paramètre une size
- surchage opérateur [] pour prendre aussi une position en param
- overload de la fonction size qui peut renvoyer une Size

Méthodes:

- vector\<Position\> getFreePositions()
- bool isFree(Position)
- bool isFood(Position)
- bool isSnake(Position)
- bool isWall(Position)
- bool isDur(Position)

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
