# Nibbler

![alt text](https://github.com/knona/nibbler/blob/master/demo.gif?raw=true)

## Description

Nibbler is a C++ project that aims to create a Snake game.
The main idea behind the project is to have a game logic and graphical / input interfaces independent from each other.
Therefore, the main program contains the game logic and there are different dynamic libraries that contains the graphical interface and manage the game inputs.
I decided to have 3 dynamic libraries that use different graphics libraries: Allegro, SDL and SFML. I only use SDL to handle the window and create an Opengl context.
These dynamic libraries inherit from the same interface which allows them to be used in the main program. They are opened and closed at the runtime.

## How to run

Install the dependencies with the `dependencies.bash` script file.
Then build the project with `make` command. You can now run the project with : `./nibbler --with 20 --height 15`.
To see all options, use `./nibbler --help`.

## Game inputs

- Move: **W** / **A** / **S** / **D** or arrow keys
- Pause / resume: **P**
- Change dynamic library: **1**, **2** or **3**

---

## Description

Nibbler est un projet consistant à recréer un snake en C++.
Cependant quelques contraintes sont mises en place.
Le programme principal doit s'occuper du coeur du projet et de toute la logique. D'une autre part, différentes bibliothèques dynamiques permettent l'affichage du jeu et la gestion des événements claviers. Il y a donc dans ce projet 3 bibilothèques dynamiques qui chacune utilise une bibliotèque graphique différente: Allgero, SDL et SFML. La SDL sert ici seulement pour l'ouverture d'une fenêtre et la création d'un contexte Opengl.
Ces bibliothèques dynamiques héritent d'une même interface et sont ouvertes / fermées au cours de l'exécution du programme.

## Lancer le programme

Après l'installation des dépendances se trouvant dans le fichier `dependencies.bash`, il suffit d'utilliser la commande
`make` pour build le projet.
Vous pouvez ensuite lancer le programme avec la commande : `./nibbler --with 20 --height 15`.
Vous pouvez afficher les différentes options du programme avec `./nibbler --help`.

## Commandes en jeu

- Déplacements : **W** / **A** / **S** / **D** ou les flèches directionnelles
- Pause : **P**
- Changer de biblothèque dynamique : **1**, **2** ou **3**
