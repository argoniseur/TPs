/** @file
 * @author Pierre-Antoine Morin
 * @brief Fichier d'entête pour le TP 4 "Chaînes de caractères (dynamiques)"
 * @warning Ce fichier ne doit pas être modifié.
 */
#ifndef TP_STRING_H
/** @brief Gardien du fichier d'entête @ref tp_string.h */
#define TP_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/** @brief Taille d'une chaîne de caractères @em statique pour la fonction @ref swap_static_strings() */
#define STATIC_STRING_LENGTH 32

/** @name Exercice 0
 * @{
 */

/** @brief Crée une copie @em dynamique d'une chaîne de caractères
 * @param [in] str Une chaîne de caractères
 * @return Une chaîne de caractères @em dynamique @b result
 * @post @b result est une copie de @b str.
 * @warning Les ressources mémoire occupées par @b result doivent être libérées en appelant @b free().
 */
char * duplicate(const char * str);

/** @} */

/** @name Exercice 1
 * @{
 */

/** @brief Concatène deux chaînes de caractères vers une nouvelle chaîne @em dynamique
 * @param [in] lhs Une chaîne de caractères (left-hand-side)
 * @param [in] rhs Une chaîne de caractères (right-hand-side)
 * @return Une chaîne de caractères @em dynamique @b result
 * @post @b result est la concaténation de @b lhs et @b rhs (dans cet ordre).
 * @warning Les ressources mémoire occupées par @b result doivent être libérées en appelant @b free().
 */
char * concatenate(const char * lhs, const char * rhs);

/** @brief Fonction test pour l'exercice 1 */
int main_exercise_1(void);

/** @} */

/** @name Exercice 2
 * @{
 */

/** @brief Lit une ligne dans un fichier texte
 * @param [in,out] file Un flux vers le fichier à lire
 * @pre Le flux @b file est ouvert.
 * @return Soit @c NULL, soit une chaîne de caractères @b str
 * @post Le flux @b file est toujours ouvert.
 * @post Si la fonction renvoie @c NULL, alors le flux @b file était déjà à la fin du fichier avant l'appel (rien à lire).
 * @post Sinon, @b str contient tous les caractères depuis la position courante jusqu'au premier saut de ligne suivant (s'il existe) @em exclus, ou jusqu'à la fin du fichier (sinon).
 * @post Dans ce cas, le flux @b file avance d'autant de caractères (placé soit @em après le saut de ligne, soit à la fin du fichier).
 * @warning Si la fonction ne renvoie pas @c NULL, les ressources mémoire occupées par @b str doivent être libérées en appelant @b free().
 * @internal
 * @remarks Cette fonction optimise l'espace mémoire utilisé par @b str (le cas échéant).
 */
char * read_one_line(FILE * file);

/** @brief Enregistre une chaîne de caractères tapée par l'utilisateur
 * @return La chaîne de caractères @b str tapée par l'utilisateur (en console)
 * @warning Les ressources mémoire occupées par @b str doivent être libérées en appelant @b free().
 * @internal
 * @remarks Cette fonction se contente d'appeler @ref read_one_line() avec le flux @b stdin.
 */
char * read_input_string(void);

/** @brief Fonction test pour l'exercice 2 */
int main_exercise_2(void);

/** @} */

/** @name Exercice 3
 * @{
 */

/** @brief Permute deux chaînes de caractères @em statiques
 * @param [in,out] lhs Une chaîne de caractères @em statique (left-hand-side ; passée par adresse)
 * @param [in,out] rhs Une chaîne de caractères @em statique (right-hand-side ; passée par adresse)
 * @pre @b lhs et @b rhs occupent un espace mémoire contenant @ref STATIC_STRING_LENGTH caractères.
 * @post @b lhs et @b rhs sont permutées.
 */
void swap_static_strings(char (*lhs)[STATIC_STRING_LENGTH], char (*rhs)[STATIC_STRING_LENGTH]);

/** @brief Permute deux chaînes de caractères @em dynamiques
 * @param [in,out] lhs Une chaîne de caractères @em dynamique (left-hand-side ; passée par adresse)
 * @param [in,out] rhs Une chaîne de caractères @em dynamique (right-hand-side ; passée par adresse)
 * @post @b lhs et @b rhs sont permutées.
 */
void swap_dynamic_strings(char * (*lhs), char * (*rhs));

/** @brief Fonction test pour l'exercice 3 */
int main_exercise_3(void);

/** @} */

/** @name Exercice 4
 * @{
 */

/** @brief Compare deux chaînes de caractères (critère de tri)
 * @param [in] lhs Une chaîne de caractères (left-hand-side ; passée par adresse via un pointeur générique)
 * @param [in] rhs Une chaîne de caractères (right-hand-side ; passée par adresse via un pointeur générique)
 * @return Un entier @b result dont le @em signe permet de comparer @b lhs et @b rhs :
 * @li Si @b result est @em négatif, alors @b lhs @em précède @b rhs dans l'ordre lexicographique.
 * @li Si @b result est @em nul, alors @b lhs et @b rhs sont @em égales.
 * @li Si @b result est @em positif, alors @b lhs @em suit @b rhs dans l'ordre lexicographique.
 * @note Cette fonction peut être utilisée comme critère de tri par la fonction @b qsort().
 * @internal
 * @remarks Cette fonction se contente d'appeler @b strcmp() en typant et déréférençant @b lhs et @b rhs de manière adéquate.
 */
int qsort_compare_strings(const void * lhs, const void * rhs);

/** @brief Trie et compte des lignes dans un fichier
 * @param [in] in_filename Le nom du fichier à analyser (à lire)
 * @param [out] out_filename Le nom du fichier dans lequel écrire les résultats
 * @pre @b in_filename désigne le nom d'un fichier texte existant.
 * @pre L'extension de @b in_filename et @b out_filename est : <tt>.txt</tt>
 * @note Si le fichier @b out_filename n'existe pas, il est créé, sinon son contenu est effacé.
 * @return Le nombre de lignes lues dans le ficher @b in_filename
 * @post @b out_filename contient les lignes (deux à deux distinctes) du fichier @b in_filename, triées dans l'ordre lexicographique, précédées du nombre d'occurrences dans @b in_filename.
 * @see @ref qsort_compare_strings() (critère de tri des chaînes de caractères lues)
 */
size_t sort_and_count_lines(const char * in_filename, const char * out_filename);

/** @brief Fonction test pour l'exercice 4 */
int main_exercise_4(void);

/** @} */

/** @name Exercice 5
 * @{
 */

/** @brief Fonction test pour l'exercice 5 */
int main_exercise_5(int argc, char * argv[]);

/** @} */

/** @name Exercice 6
 * @{
 */

/** @brief Copie une chaîne de caractères, en remplaçant la première occurrence d'une sous-chaîne par une autre sous-chaîne
 * @param [out] dest La chaîne de caractères résultante
 * @param [in] src La chaîne de caractères initiale
 * @param [in] before La sous-chaîne à rechercher dans @b src
 * @param [in] after La sous-chaîne à substituer à @b before
 * @warning Le comportement de cette fonction est indéfini si @b dest ne peut pas contenir suffisamment de caractères !
 * @retval Vrai (valeur non nulle) Si @b before apparaît au moins une fois dans @b src
 * @retval Faux (valeur nulle) Sinon
 * @post @b dest est une copie de @b src dans laquelle la première occurrence de @b before (si elle existe) est remplacée par @b after.
 */
int replace_first_occurrence(char * dest, const char * src, const char * before, const char * after);

/** @brief Copie une chaîne de caractères, en remplaçant toutes les occurrences d'une sous-chaîne par une autre sous-chaîne
 * @param [out] dest La chaîne de caractères résultante
 * @param [in] src La chaîne de caractères initiale
 * @param [in] before La sous-chaîne à rechercher dans @b src
 * @param [in] after La sous-chaîne à substituer à @b before
 * @warning Le comportement de cette fonction est indéfini si @b dest ne peut pas contenir suffisamment de caractères !
 * @return Le nombre d'occurrences de @b before dans @b src
 * @post @b dest est une copie de @b src dans laquelle toutes les occurrences de @b before (éventuellement aucune) sont remplacées par @b after.
 */
size_t replace_all_occurrences(char * dest, const char * src, const char * before, const char * after);

/** @brief Modifie une chaîne de caractères, en remplaçant toutes les occurrences d'une sous-chaîne par une autre sous-chaîne
 * @param [in,out] str La chaîne de caractères à modifier
 * @param [in] before La sous-chaîne à rechercher dans @b str
 * @param [in] after La sous-chaîne à substituer à @b before
 * @warning Le comportement de cette fonction est indéfini si @b str ne peut pas contenir suffisamment de caractères !
 * @return Le nombre d'occurrences de @b before dans @b str
 * @post Toutes les occurrences de @b before (éventuellement aucune) dans @b str sont remplacées par @b after.
 */
size_t replace_all_occurrences_inplace(char * str, const char * before, const char * after);

/** @brief Fonction test pour l'exercice 6 */
int main_exercise_6(void);

/** @} */

/** @name Exercice 7
 * @{
 */

/** @brief Fonction test pour l'exercice 7 */
int main_exercise_7(void);

/** @} */

/** @name Exercice 8
 * @{
 */

/** @brief Fonction test pour l'exercice 8 */
int main_exercise_8(void);

/** @} */

/** @name Exercice 9
 * @{
 */

/** @brief Enregistre un nombre quelconque de chaînes de caratères tapées par l'utilisateur
 * @param [out] array L'adresse d'un tableau dynamique de chaînes de caratères dynamiques
 * @warning Le pointeur à l'adresse @b array doit être initialisé à @c NULL @em avant l'appel !
 * @return Le nombre de chaînes de caractères (lignes) tapées par l'utilisateur
 * @note La saisie s'arrête lorsque l'utilisateur entre la chaîne de caractères (ligne) vide.
 * @post Le tableau à l'adresse @b array contient les chaînes de caractères tapées par l'utilisateur (en console).
 * @post La fin du tableau à l'adresse @b array est représentée par la valeur @c NULL dans la dernière case.
 * @warning Les ressources mémoire occupées par le tableau à l'adresse @b array doivent être libérées en appelant @ref free_input_array().
 */
size_t read_input_array(char *** array);

/** @brief Libère les ressources mémoire occupées par un tableau dynamique de chaînes de caratères dynamiques
 * @param [in,out] array L'adresse d'un tableau dynamique de chaînes de caratères dynamiques

 * @pre La fin du tableau à l'adresse @b array est représentée par la valeur @c NULL dans la dernière case.
 * @post Les ressources mémoire occupées par le tableau à l'adresse @b array sont libérées.
 * @post La valeur du pointeur à l'adresse @b array est @c NULL.
 */
void free_input_array(char *** array);

/** @brief Affiche des chaînes de caractères stockées dans un tableau
 * @param [in] array L'adresse d'un tableau dynamique de chaînes de caratères dynamiques
 * @pre La fin du tableau @b array est représentée par la valeur @c NULL dans la dernière case.
 * @return Le nombre de chaînes de caractères dans le tableau à l'adresse @b array
 * @post Chaque chaîne de caractères du tableau à l'adresse @b array est affichée sur une ligne (en console).
 */
size_t print_input_array(char *** array);

/** @brief Fonction test pour l'exercice 9 */
int main_exercise_9(void);

/** @} */

#endif /* TP_STRING_H */

/** @mainpage Structures de Données - TP 4
 *
 * @parblock
 * @par Dépôt sur Moodle
 * Vous déposerez votre travail sous la forme d'une archive contenant @b uniquement les quatre fichiers suivants :
 * @li le fichier <tt>tp_string.c</tt> fourni, qui contiendra la totalité de votre code pour ce TP ;
 * @li le fichier <tt>tp_string.h</tt> fourni (que vous ne devez pas modifier) ;
 * @li le fichier <tt>Makefile</tt> fourni (que vous ne devez pas modifier) ;
 * @li le fichier <tt>Doxyfile</tt> fourni (que vous ne devez pas modifier).
 * @endparblock
 *
 * <hr>
 *
 * @parblock
 * @par Makefile
 * Utiliser l'utilitaire <tt>make</tt> pour effectuer les traitements suivants
 * @li Compiler le programme
 * @verbatim $ make [all] @endverbatim
 * @li Tester le programme avec <tt>valgrind</tt>
 * @verbatim $ make test @endverbatim
 * @li Générer cette documentation HTML avec <tt>doxygen</tt>
 * @verbatim $ make doc @endverbatim
 * @li Supprimer les fichiers objets et exécutables (nettoyer)
 * @verbatim $ make clean @endverbatim
 * @li Supprimer les fichiers objets et exécutables ainsi que cette documentation (effacer)
 * @verbatim $ make clear @endverbatim
 * @endparblock
 *
 * <hr>
 *
 * @parblock
 * @see Une documentation des entêtes et fonctions C standards est disponible dans le manuel Unix, section 3. @n
 * @li Pour l'entête <tt>string.h</tt> :
 * @verbatim $ man -s3 string @endverbatim
 * @li Pour la fonction @b printf() :
 * @verbatim $ man -s3 printf @endverbatim
 * Comparer le résultat de la commande précédente avec celui des commandes suivantes :
 * @verbatim $ man printf @endverbatim
 * @verbatim $ man -s1 printf @endverbatim
 * @endparblock
 *
 * <hr>
 *
 * @parblock
 * @see Consulter les <a href="pages.html"><b>pages associées</b></a> de cette documentation pour une description détaillée des exercices.
 * @endparblock
 */

/** @page exercice_0 Exercice 0
 * @brief Exercice préliminaire ; dupliquer une chaîne de caractères
 * @section question_0_1 Question 0.1
 * Implémenter la fonction @ref duplicate().
 * @note Les fonctions suivantes peuvent être utiles: @b strlen(), @b strcpy()
 * @note L'unique fonction d'allocation nécessaire est @b malloc().
 * @remarks Cette fonction pourra servir à initialiser des chaînes de caractères dynamiques dans les fonctions associées aux exercices suivants.
 * @remarks Penser à libérer la mémoire en appelant @b free() !
 */

/** @page exercice_1 Exercice 1
 * @brief Concaténer des chaînes de caractères
 * @section question_1_1 Question 1.1
 * Implémenter la fonction @ref concatenate().
 * @note Les fonctions suivantes peuvent être utiles: @b strlen(), @b strcpy(), @b strcat()
 * @note L'unique fonction d'allocation nécessaire est @b malloc().
 * @section question_1_2 Question 1.2
 * Tester la fonction précédente via la fonction @ref main_exercise_1().
 */

/** @page exercice_2 Exercice 2
 * @brief Redimensionner la mémoire
 * @section question_2_1 Question 2.1
 * Implémenter la fonction @ref read_one_line().
 * @note Les caractères seront lus un à un.
 * @note La taille de l'espace mémoire occupé par la chaîne de caractère renvoyée sera ajustée à chaque lecture d'un nouveau caractère, de sorte à pouvoir contenir un caractère supplémentaire.
 * @note La fonction suivante peut être utile: @b fgetc()
 * @note Certains caractères spéciaux doivent être pris en compte: @b EOF, @c '@\n'
 * @note L'unique fonction d'allocation nécessaire est @b realloc().
 * @section question_2_2 Question 2.2
 * Implémenter la fonction @ref read_input_string(), en une seule ligne, en appelant uniquement la fonction précédente.
 * @see Remarques finales dans la documentation de la fonction @ref read_input_string()
 * @section question_2_3 Question 2.3
 * Tester la fonction précédente via la fonction @ref main_exercise_2().
 */

/** @page exercice_3 Exercice 3
 * @brief Permuter des chaînes de caractères
 * @section question_3_1 Question 3.1
 * Implémenter la fonction @ref swap_static_strings().
 * @note La fonction suivante peut être utile: @b strncpy()
 * @section question_3_2 Question 3.2
 * Implémenter la fonction @ref swap_dynamic_strings().
 * @section question_3_3 Question 3.3
 * Tester les fonctions précédentes via la fonction @ref main_exercise_3().
 */

/** @page exercice_4 Exercice 4
 * @brief Trier et compter des lignes dans un fichier
 * @warning Nécessite d'avoir terminé l'@ref exercice_2 "exercice 2".
 * @section question_4_1 Question 4.1
 * Implémenter la fonction @ref qsort_compare_strings(), en une seule ligne, en appelant uniquement la fonction @b strcmp().
 * @see Remarques finales dans la documentation de la fonction @ref qsort_compare_strings()
 * @section question_4_2 Question 4.2
 * Implémenter la fonction @ref sort_and_count_lines().
 * @note Les fonctions suivantes peuvent être utiles: @b fopen(), @b fclose(), @b fprintf(), @b qsort(); également @ref read_one_line() et @ref qsort_compare_strings()
 * @section question_4_3 Question 4.3
 * Tester la fonction précédente via la fonction @ref main_exercise_4() ; les noms des fichiers d'entrée (à créer manuellement) et de sortie (créé par le programme) seront codés en dur dans le programme.
 */

/** @page exercice_5 Exercice 5
 * @brief Passer des paramètres en ligne de commande
 * @warning Nécessite d'avoir terminé l'@ref exercice_4 "exercice 4".
 * @section question_5_1 Question 5.1
 * Tester la fonction @ref sort_and_count_lines() via la fonction @ref main_exercise_5(). @n
 * Contrairement à la fonction @ref main_exercise_4(), les noms des fichiers d'entrée (à créer manuellement) et de sortie (créé par le programme) seront des paramètres du programme, passés en ligne de commande.
 */

/** @page exercice_6 Exercice 6
 * @brief Rechercher et remplacer des sous-chaînes de caractères
 * @section question_6_1 Question 6.1
 * Implémenter la fonction @ref replace_first_occurrence().
 * @note Les fonctions suivantes peuvent être utiles: @b strlen(), @b strcpy(), @b strstr()
 * @section question_6_2 Question 6.2
 * Implémenter la fonction @ref replace_all_occurrences().
 * @note Les fonctions suivantes peuvent être utiles: @b strlen(), @b strcpy(), @b strstr()
 * @section question_6_3 Question 6.3
 * Implémenter la fonction @ref replace_all_occurrences_inplace().
 * @note Les fonctions suivantes peuvent être utiles: @b strlen(), @b memcpy(), @b memmove(), @b strstr()
 * @section question_6_4 Question 6.4
 * Tester les fonctions précédentes via la fonction @ref main_exercise_6().
 */

/** @page exercice_7 Exercice 7
 * @brief Identifier les zones mémoire d'un programme
 *
 * Suivre pas à pas l'énoncé du TP 4. @n
 * La fonction @ref main_exercise_7() contiendra l'ensemble du code produit pour cet exercice. @n
 * Commenter votre code, en précisant notamment où (c'est-à-dire dans quelle zone mémoire du programme : pile, tas, ...) est située chaque entité.
 * @note La fonction suivante peut être utile: @b toupper()
 */

/** @page exercice_8 Exercice 8
 * @brief Copier des chaînes de caractères embarquées dans des structures
 *
 * Suivre pas à pas l'énoncé du TP 4. @n
 * Les structures seront déclarées et définies juste avant la fonction @ref main_exercise_8(), qui contiendra le code testé. @n
 * Insérer les réponses aux questions sous forme de commentaires.
 * @note Pour la question 2, les copies seront réalisées via le code suivant.
@code
    v12 = v11;
    v22 = v21;
@endcode
 */

/** @page exercice_9 Exercice 9
 * @brief Gérer dynamiquement une collection d'éléments dynamiques
 * @warning Nécessite d'avoir terminé l'@ref exercice_2 "exercice 2".
 * @par Collection de taille variable : une représentation possible
 * En C, les chaînes de caractères sont des tableaux d'éléments de type @c char, dont la fin est signalée par le caractère nul, i.e. @c '@\0'. @n
 * Dans cet exercice, l'objectif est de manipuler des tableaux @em dynamiques contenant des chaînes de caractères @em dynamiques en nombre variable. @n
 * Une convention de représentation possible est la suivante : manipuler des tableaux d'éléments de type <c>char *</c>, dont la fin est signalée par le pointeur nul, i.e. @c NULL. @n
 * Un tel tableau sera représenté par une variable de type <c>char **</c> ; l'adresse d'un tel tableau sera stockée dans une variable de type <c>char ***</c>.
 * @section question_9_1 Question 9.1
 * Implémenter la fonction @ref read_input_array().
 * @note La fonction suivante peut être utile: @ref read_input_string()
 * @note Pour gérer la taille du tableau, l'unique fonction d'allocation nécessaire est @b realloc().
 * @section question_9_2 Question 9.2
 * Implémenter la fonction @ref free_input_array().
 * @section question_9_3 Question 9.3
 * Implémenter la fonction @ref print_input_array().
 * @section question_9_4 Question 9.4
 * Tester les fonctions précédentes via la fonction @ref main_exercise_9().
 */
