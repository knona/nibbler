# Nibbler

features:

- Optimiser les fonctions pour placer les walls et les foods
- Optimisation générale
- Pour ncurses ne pas render si taille trop petite, afficher un message
- Taille et nombre des walls en fonction de la taille de la map
- Mode jeu sans/avec mur
- Score avec noms des joueurs, sauvegarde des classements
- Vérifier les constructeurs par copie
- faire un menu new game / walls / scores / exit
- Mode de jeu ou les commandes flèches sont inversées
- Utiliser conan / cmake pour les dépendances ?
- set right values for width / height in parsing
- ajouter des erreurs si par ex init fail dans ncurses

bugs:

## Bibliotheques

3 bibliothèques dynamiques voir :
https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

Elles ont des fichiers communs pour l'affichage.
On aura donc 3 fichiers libA.cpp libB.cpp libC.cpp qui seront compilés avec un même ensemble de fichiers.

Ces 3 libs mettront à disposition certaines fonctions pour pouvoir être utilisées par l'exécutable. Ces fonctions doivent être définies dans le bloc extern c.
