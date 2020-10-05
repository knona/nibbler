# Nibbler

features:
- Faire en sorte qu'un wall ne puisse pas spawn a cote des bords de la map
- Optimiser les fonctions pour placer les walls et les foods
- Optimisation générale
- Pour ncurses ne pas render si taille trop petite, afficher un message
- Taille et nombre des walls en fonction de la taille de la map
- Mode jeu sans/avec mur
- Score avec noms des joueurs, sauvegarde des classements
- Vérifier les constructeurs par copie
- faire un menu  new game / walls / scores / exit
- faire des libs des classes qui héritent d'une même interface

bug:


## Bibliotheques

3 bibliothèques dynamiques voir :
https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

Elles ont des fichiers communs pour l'affichage.
On aura donc 3 fichiers libA.cpp libB.cpp libC.cpp qui seront compilés avec un même ensemble de fichiers.

Ces 3 libs mettront à disposition certaines fonctions pour pouvoir être utilisées par l'exécutable. Ces fonctions doivent être définies dans le bloc extern c.

Mode de jeu ou les commandes flèches sont inversées
