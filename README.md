Ce projet a été élaboré par Gille Maes, Loic Spigeleer, Nicolas Jeanmenne, Pierre Denoël, Samuel de Meester et Sébastien
Mary.

Ce README contient toutes les informations nécessaires quant à la bonne compréhension du projet.

# Structures utilisées

Toutes nos structures sont définies dans le fichier headers/kmeansStruct.h. Pour plus d'information à leur sujet,
consultez le fichier.

1. point_t : cette structure représente un point. Elle est composée d'un vecteur représentant les coordonnées du point
   ainsi que celles du centroïde le plus proche.

1. kMeans_t : cette structure est composée de toutes les informations nécessaires au déroulement de l'algorithme de
   Lloyd's. Le nom des composantes de cette structure est, selon nous, assez clair pour ne pas expliquer leur fonction.

1. data_t : cette structure contient les caractéristiques du problème à traiter (dimension et nombre de points)
   ainsi que tous les points provenant du fichier binaire donné en entrée.

# Utilisation des threads

Nous avons implémenté une architecture producteurs/consommateurs. Avant le lancement des threads le programme effectue
deux opérations importantes.

1. Extraction des données contenues dans le fichier binaire en entrée.

1. Calcul des différents centroids de départs. (cette étape aurait pu se voir assigner un thread mais on s'est rendu
   compte en faisant des tests de performance que le temps pris par cette étape était négligeable)

1. Producteurs: Nous avons donc une liste reprenant toutes les suites de centroids de départ. De cette manière, à chaque
   instance kMeans à traiter, correspond un indice. On transmet alors à chaque thread producteur les indices de début et
   de fin (fin non comprise). Chaque thread a alors pour mission d'exécuter et résoudre toutes les instances du problème
   kMeans compris entre les indices début et fin (non compris).

1. Consommateur: il n'y a qu'un seul thread consommateur qui s'occupe d'écrire dans le fichier de sortie les résultats
   obtenus par le(s) thread(s) producteur(s).

# Gestion de la concurrence

Nous avons donc d'un côté des threads producteurs et de l'autre un thread consommateur. La communication entre ces
threads s'opère à l'aide d'un buffer. Cependant l'utilisation d'un même objet par plusieurs threads est délicat, pour se
faire nous avons utilisé:

## Deux sémaphores:

1. empty: renseigne le thread consommateur sur la présence d'au moins un élément à consommer sur le buffer

1. full: renseigne les threads producteurs sur la présence d'au moins une place disponible sur le buffer

un mutex: il empêche l'utilisation du buffer par plus d'un thread en simultané. Sans cet élément, deux threads
producteurs pourraient, par exemple, déposer leurs résultat en même temps sur un même emplacement du buffer. Ce qui
n'est évidemment pas souhaité.

# Tests de performance

Ces tests ont été effectués sur le fichier ex5.bin contenant 50 000 points. Commande utilisée via la terminal :
(Paramètres utilisés : -k 3 -p 6 -n 4 -q -d euclidean)

* Python : 2m39.422s

1. Avec 1 thread :
   * C      : 0m3.660s

1. Avec 2 threads :
   * C      : 0m1.994s

1. Avec 3 threads :
   * C      : 0m1.869s

1. Avec 4 threads :
   * C      : 0m1.891s

Nous pouvons en conclure qu'en moyenne, le programme en C multithreadé s'effectue #TODO ? plus vite que le programme
python.

# Lancement du programme

## Les trois commandes nécessaires pour faire fonctionner le projet sont les suivantes:

1. make
1. make tests
1. make clean

On a ajouté deux autres commandes :

1. make valgrind : effectue les tests avec valgrind
1. make helgrind : effectue les tests avec helgrind

Pour de plus amples informations concernant leur utilisation, référez-vous au Makefile.

# Questions éventuelles

Si vous avez encore certaines questions concernant le projet, n'hésitez pas à nous contacter aux adresses suivantes:

nicolas.jeanmenne@student.uclouvain.be, samuel.demeester@student.uclouvain.be loic.spigeleer@student.uclouvain.be,
sebastien.mary@student.uclouvain.be pierre.denoel@student.uclouvain.be, gilles.maes@student.uclouvain.be

Merci à vous de l'attention que vous apportez à ce projet.