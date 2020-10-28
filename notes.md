# Nibbler

features:

- Optimiser les fonctions pour placer les walls et les foods
- Optimisation générale
- Pour ncurses ne pas render si taille trop petite, afficher un message
- Taille et nombre des walls en fonction de la taille de la map
- Vérifier les constructeurs par copie
- Utiliser conan / cmake pour les dépendances ?
- mettre les bonnes valeurs pour la width / height dans le parsing
- pouvoir prendre un paramètre --lib qui lance le jeu avec la lib voulue

Ncurses:
- ajouter des erreurs si par ex init fail
- ecran de win / loose

SDL:
- pour la sdl créer la taille de la fenetre en fonction de la taille de la zone de jeu
- ajouter des textures
- ecran de win / loose

bugs:
- leak quand pas de size donné en argument

## Bibliotheques
https://stackoverflow.com/questions/496664/c-dynamic-shared-library-on-linux

Ajouter une dernière bibliothèque graphique
