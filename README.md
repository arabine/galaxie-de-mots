Galaxie de mots
========

Présentation
------------

Collection de jeux de mots. Bon pour le moment y'en a qu'un :

* Jeu 1 : Mo-mo-motus inspiration Wordle / LeMot)

![alt text](assets/screenshots/motus.png "Jeu Mo-mo-motus")
  
Comment je build pour Linux
----------------

* Il faut SDL 2.20 installé dans /opt/SDL2 (désolé c'était pas forcément nécessaire mais j'ai réutilisé un squelette)
* CMake

Process :

1. mkdir build
2. cmake ..
3. make

Comment je build pour Android
------------------------------

À la racine :

- gradle assembleDebug ou assembleRelease selon la cible désirée ; n'effectue que la construction et la génération du paquet APK
- gradle installDebug ou installRelease : construit et installe sur la cible (vrai téléphone ou émulateur)
- gradlew bundle pour générer le fichier AAB


License
-------

[CC BY SA40.0](LICENSE-CC-BY-SA4.0.txt)


