#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

// ============================================================

// Projet  : JNIDemo — Démonstrations JNI avec Android NDK
// Description : Ce fichier implémente 4 fonctions natives C++

#define LOG_TAG "JNI_NIS"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// ------------------------------------------------------------
// Retourne une chaîne créée côté C++ et envoyée vers Java.
// Montre le mécanisme de base du pont JNI.
// ------------------------------------------------------------
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_helloFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    LOGI("helloFromJNI : fonction native appelée avec succès");
    return env->NewStringUTF("Bonjour depuis le C++ — JNI fonctionne !");
}

// ------------------------------------------------------------
// Fonction 2 : factorial
// Calcule n! en natif avec deux cas d'erreur :
//   -1 si n est négatif
//   -2 si le résultat dépasse INT_MAX (overflow)
// ------------------------------------------------------------
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_factorial(
        JNIEnv* env,
        jobject /* this */,
        jint n) {

    // Vérification : on refuse les valeurs négatives
    if (n < 0) {
        LOGE("factorial : valeur négative reçue (%d)", n);
        return -1;
    }

    long long resultat = 1;
    for (int i = 1; i <= n; i++) {
        resultat *= i;
        // Détection d'overflow avant de continuer
        if (resultat > INT_MAX) {
            LOGE("factorial : overflow détecté à l'étape i=%d", i);
            return -2;
        }
    }

    LOGI("factorial(%d) = %lld", n, resultat);
    return static_cast<jint>(resultat);
}

// ------------------------------------------------------------
// Fonction 3 : reverseString
// Reçoit une String Java, la convertit en std::string C++,
// l'inverse avec std::reverse, puis la renvoie vers Java.
// Attention : toujours libérer avec ReleaseStringUTFChars.
// ------------------------------------------------------------
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_reverseString(
        JNIEnv* env,
        jobject /* this */,
        jstring javaString) {

    // Garde-fou : chaîne nulle
    if (javaString == nullptr) {
        LOGE("reverseString : chaîne nulle reçue");
        return env->NewStringUTF("Erreur : chaîne nulle");
    }

    // Conversion Java String → C string
    const char* chars = env->GetStringUTFChars(javaString, nullptr);
    if (chars == nullptr) {
        LOGE("reverseString : échec de GetStringUTFChars");
        return env->NewStringUTF("Erreur JNI interne");
    }

    std::string texte(chars);

    // Libération immédiate après copie — bonne pratique JNI
    env->ReleaseStringUTFChars(javaString, chars);

    // Inversion de la chaîne
    std::reverse(texte.begin(), texte.end());

    LOGI("reverseString : résultat = %s", texte.c_str());
    return env->NewStringUTF(texte.c_str());
}

// ------------------------------------------------------------
// Fonction 4 : sumArray
// Reçoit un tableau int[] Java, accède à ses éléments en natif,
// calcule la somme et la retourne.
// Codes d'erreur : -1 tableau nul, -2 accès impossible, -3 overflow
// ------------------------------------------------------------
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_sumArray(
        JNIEnv* env,
        jobject /* this */,
        jintArray tableau) {

    // Vérification : tableau nul
    if (tableau == nullptr) {
        LOGE("sumArray : tableau nul reçu");
        return -1;
    }

    jsize longueur = env->GetArrayLength(tableau);
    jint* elements = env->GetIntArrayElements(tableau, nullptr);

    if (elements == nullptr) {
        LOGE("sumArray : impossible d'accéder aux éléments");
        return -2;
    }

    long long somme = 0;
    for (jsize i = 0; i < longueur; i++) {
        somme += elements[i];
    }

    // Libération du tableau natif — 0 = copier et libérer
    env->ReleaseIntArrayElements(tableau, elements, 0);

    // Vérification overflow final
    if (somme > INT_MAX) {
        LOGE("sumArray : overflow sur la somme totale");
        return -3;
    }

    LOGI("sumArray : somme = %lld pour %d éléments", somme, longueur);
    return static_cast<jint>(somme);
}