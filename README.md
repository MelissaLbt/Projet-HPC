# Projet-HPC

Sont listés l’ensemble des travaux possibles.

##Travail algorithmique
Dans une première étape, il s’agit de réaliser la chaine de traitement : SD+morpho, en scalaire mono-thread et sans
optimisation afin d’obtenir une version de référence. Dans une seconde étape il s’agit d’optimiser cette chaine de traitement
pour qu’elle soit le plus rapide possible, en codant les opérateurs en SIMD, en paralélisation le code sur les coeurs du
processeur, en appliquant des optimisations logicielles et surtout en appliquant des transformations de haut niveau :
pipeline d’opérateurs, fusion d’opérateurs. Le traitement morphologique à implémenter est la séquence érosion - dilatation
- dilatation - érosion. La séquence d’images à utiliser est car3.pgm.

##Travail d’optimisation
Sont listés dans cette section les différentes optimisations possibles (codage SIMD et pipeline ou fusion sont obligatoire).
L’évaluation se fera sur la performance du code.

##Optimisation SIMD
L’objectif principal est de coder la chaine SD+morpho en SIMD (SSE, AVX, Neon).
3Pour chaque étape de l’algorithme SD, fournir des tests unitaires commentés et validant les différents Design Patterns
(obligatoire).
Les principales évolutions par rapport à cette version de référence sont :
— Augmentation du parallélisme SIMD en codant en AVX2 (256 bits).
— Portage sur une plateforme embarquée en codant en SIMD Neon sur carte ARM Cortex A (RaspberryPi, Nvidia
Jetson, ...)

##Optimisations Domain Specific et fusion / factorisation d’opérateurs
Les opérateurs 2D de morphologie mathématique utilisés sont séparables, factorisables, associatifs et commutatifs :
— Un opérateur avec un élément structurant 2D d × d est séparable en deux opérateurs 1D d’élément structurant
respectif d × 1 et 1 × d et vice-versa. Par exemple (Fig. 3) (3 × 3) ↔ (3 × 1) ◦ (1 × 3) et (5 × 5) ↔ (5 × 1) ◦ (1 × 5) .
— Deux opérateurs d’élément structurant carré de rayon r donnent un opérateur d’élément structurant carré de
rayon 2r et vice-versa.

##Optimisations logicielles : pipeline d’opérateurs
— Une fois que chaque opérateur de morphologie mathématique a été optimisé avec les transformations précédentes,
il est possible d’en optimiser l’enchainement. Plutôt que d’appliquer un opérateur à une image entière puis de
faire de même avec l’opérateur suivant, il est possible de les pipeliner (et de pipeliner la détection avec le post-
traitement).
— Les opérateurs sur les images sont décomposés en opérateurs “ligne”. Ce sont ces opérateurs “ligne” qui sont
pipelinés. Cela permet d’améliorer la persistance des données dans les caches proches du processeurs. Cette opti-
misation est particulièrement efficace dans un contexte multithreadé. On parle alors de Cache Level Parallelism
qui est une version améliorée du Thread Level Parallélism (qui ne s’intéresse qu’aux calculs).
— Cette optimisation est applicable en scalaire et en SIMD et peut nécessiter un prologue et un épilogue.

##Optimisation des formats de calcul et de stockage en mémoire
— En SIMD il est primordial de garder le parallélisme maximal pour l’ensemble des calculs. Cela est faisable pour
la totalité de la chaine de traitement. On a ainsi un parallélisme de 16 en 128 bits, 32 en 256 bits.
— Pour la morphologie mathématique binaire, il est possible de faire mieux : au lieu d’utiliser un octet pour stocker
un pixel, il est possible de stocker 8 pixels binaires par octet. Cela fait 128 pixels en SSE et Neon, 256 en AVX2.
— Cela est aussi applicable en scalaire : 64 pixels binaires peuvent être codés dans un long int (ou plus simplement
un long).
— Enfin, si les données occupent moins de place en mémoire (image 1 bit versus image 8 bits) elles sont plus
rapidement chargées/écrites en mémoire. Cette optimisation permet de réduire le temps de traitement en réduisant
les temps d’accès mémoire.

##Optimisations matérielles combinées SIMD × OpenMP (ou pthread)
Le fait de combiner les deux parallélismes matériels que sont le SIMD et le multi-coeurs nécessite d’optimiser fortement
les accès mémoire car les données vont être consommées à très grande vitesse. Trois possibilités :
4— Diminuer le nombre d’accès mémoire en fusionnant des
SD avec les opérateurs “lignes” de morpho-math.
— Maximiser la persistance des données dans les caches
opérateurs. On peut là aussi envisager de pipeliner des
— Combiner fusion et pipeline. La combinaison “ultime”
morpho 1 bit en SIMD×OpenMP.
3.3
opérateurs. On peut envisager de fusionner des étapes de
pour diminuer la durée des transferts en pipelinant les
étapes de FD les opérateurs “lignes” de morpho-math.
étant la fusion/pipeline de l’ensemble des opérateurs de
Codage
Aucun code C n’est fourni en plus des bibliothèques d’allocation mémoire au format NRC. Néanmoins, nrutil contient
les routines pour lire et écrire des images au format PGM (LoadPGM et MLoadPGM pour la lecture de séquence lorsque
la taille de chaque image est connue).

##Nom et types
Les variables et les tableaux doivent être fortement typés et à la norme NRC. Le nom des variables, des tableaux et des
fonctions doit être simple sans être ambigu. Il est recommandé d’utiliser les mêmes noms de tableaux que ceux utilisés
dans cet énoncé. Voici quelques exemples possibles :
— routine FrameDifference,
— routine FrameDifference SIMD,
— SigmaDelta step0 pour l’initialisation,
— SigmaDelta 1step pour les itérations suivantes.
— SigmaDelta step0 SIMD et SigmaDelta 1step SIMD pour les versions codées en SIMD.
Il en va de même pour les noms de fichiers (obligatoire) :
— mouvement.c contiendra l’ensemble des algorithmes scalaires de détection de mouvement,
— mouvement SIMD.c, pour les implémentation SIMD,
— morpho.c et morpho SIMD.c pour la morphologie mathématique,
— test mouvement.c, test mouvement SIMD.c, test morpho.c, test morpho SIMD.c pour les tests,
— bench mouvement.c, bench mouvement SIMD.c, bench morpho.c, bench morpho SIMD.c pour le benchmarking.

##Codage logique et codage binaire
Il y a deux possibilités pour coder les images de morphologie mathématique. Soit sur {0,1}, soit sur {0,255}. Le second
choix est plus simple car permet une visualisation et une mise-au-point plus rapide. Le premier choix permet du stocker
les images booléennes sur 1 bit. Il est conseillé de faire une fonction de conversion d’un format vers l’autre pour avoir les
deux à la fois et faire du debug.

##Amélioration de la sémantique SIMD
Afin d’améliorer la sémantique du code, il est conseillé d’utiliser des macros C (ou fonction inline C++ ou wrappers
C++) comme
— vec load2(T, i, j), vec store2(T, i, j, x) pour les accès mémoire
— vec or3(x0,x1,x2), vec or5(x0,x1,x2,x3,x4) pour la morpho
— vec left1(a,b), vec right1(b,c) pour les stencils
— vec set(x), pour l’initialisation

##Benchmark quantitatif
Il vous revient les choix pour valider et mettre en valeur les optimisations réalisées. Ce peut être des courbes, des tableaux,
des images. Dans l’optique d’une comparaison avec une implémentation sur FPGA, il est conseillé d’utiliser les métriques
suivantes :
— le temps de traitement en seconde (ou en ms) de chaque opérateur et de la chaine complète,
— le cpp (cycle par point) et le débit (en pixel par seconde)
Il est aussi conseillé de faire varier la taille des images pour analyser les performances des codes SIMD : partir d’images
petites tenant dans les caches à des images trop grandes pour tenir dans les caches. Dans ce cas, ce sont le cpp et le débit
qui sont intéressants à tracer sur une courbe.
La séquence car3 est disponible à l’adresse suivante :
http://www-soc.lip6.fr/~lacas/ImageProcessing/MotionDetection/car3.zip.
