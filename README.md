# Lab22_Java_Resolution
Rapport de Laboratoire — JNIDemo
Android NDK et Interface JNI

1. Introduction
Ce laboratoire a pour objectif de comprendre et mettre en œuvre l'interface JNI (Java Native Interface) dans une application Android. JNI permet au code Java d'appeler des fonctions écrites en C++, compilées en bibliothèque native .so via le NDK Android.
L'application JNIDemo réalise quatre démonstrations progressives :

Appel d'une fonction native simple
Calcul natif d'un factoriel avec contrôle d'erreur
Inversion d'une chaîne de caractères
Traitement d'un tableau int[]


2. Architecture du projet
Le flux général de l'application est le suivant :
Java / MainActivity → méthode native → libnative-lib.so → code C++ → résultat → Java → affichage
La capture suivante montre la structure complète du projet généré par Android Studio :
<img width="587" height="968" alt="image" src="https://github.com/user-attachments/assets/828f348d-d2b4-435a-a339-20ac8a0cdc42" />


On y distingue clairement :

Le dossier cpp/ contenant CMakeLists.txt et native-lib.cpp
Le dossier java/ contenant MainActivity.java
Le dossier res/layout/ contenant activity_main.xml


3. Configuration Gradle et NDK
Le fichier app/build.gradle.kts configure la version du NDK et le chemin vers le script CMake :

<img width="1568" height="759" alt="image" src="https://github.com/user-attachments/assets/623ba39f-b78f-4b36-8910-0113e65fb00c" />


Points importants visibles :

ndkVersion = "26.1.10909125" — version stable du NDK forcée
minSdk = 24 — compatibilité Android 7+
La section externalNativeBuild pointe vers CMakeLists.txt


4. Code natif C++
Le fichier native-lib.cpp implémente les 4 fonctions natives :

<img width="1568" height="765" alt="image" src="https://github.com/user-attachments/assets/dabe5e67-2c0d-48c2-9092-88103b1fc356" />


On voit notamment :

Le #define LOG_TAG "JNI_NISRINE" personnalisé
La fonction helloFromJNI avec sa signature JNI complète
L'utilisation de LOGI pour les logs Android natifs
extern "C" pour éviter le name mangling C++


5. Code Java — MainActivity
Le fichier MainActivity.java déclare les méthodes natives et charge la bibliothèque :

<img width="1477" height="812" alt="image" src="https://github.com/user-attachments/assets/9d9b12ac-a460-4dc0-9fd1-baa2b0890b0d" />


6. Résultats de l'exécution
L'application lancée sur l'émulateur Pixel 6 affiche les résultats suivants :

<img width="525" height="870" alt="image" src="https://github.com/user-attachments/assets/817e45e1-98f7-471e-98fb-a27c582bc1fc" />

<img width="480" height="768" alt="image" src="https://github.com/user-attachments/assets/bd65c604-34f7-4e24-a8f7-f0ebdfbf1fd5" />
