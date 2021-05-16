Ce projet a été élaboré par Gille Maes, Loic Spigeleer, Nicolas Jeanmenne, Pierre Denoël, Samuel de Meester et Sébastien
Mary.

Ce README contient toutes les informations nécessaires quant à la bonne compréhension du projet.

# Lancement du programme

### Commandes nécessaires au fonctionnement du projet :

1. make
2. make tests
3. make clean

### Commande pour l'exécuter avec ses propres arguments : 
Les arguments précédés de "+" sont optionnels.

./kmeans +[−q show_clusters] +[−k n_clusters] +[−p n_combinations_points] [−n n_threads]
+[−d distance_metric] +[−f output_file] +[input_filename]

Par défaut, les clusters ne sont pas repris dans l'output, -k vaut 2, +p vaut la même chose que -k, -n vaut 4, -d vaut
"manhattan", le résultat est écrit sur la sortie standard et l'entrée standard est lue pour l'input. Nous avons ajouté
la possibilité de mettre l'argument -t pour afficher le temps d'exécution.

### Commandes ajoutées :

1. make valgrind
2. make valgrindForTests
3. make helgrind
4. make performances

La première effectue les tests Valgrind (tests sur la gestion de la mémoire) sur le fichier ex3.bin. La deuxième
effectue les tests Valgrind pour les tests unitaires. La troisième effectue les tests Helgrind (test des threads) sur le
fichier ex3.bin. La dernière lance le programme plusieurs fois sur un fichier d'entrée de 10 000 points et avec
différents nombres de threads. Elle produit ensuite une visualisation avec matplotlib dans le dossier
tests_files/test_performances. Notez que cette commande ne fonctionne pas sur le Raspberry car la commande time n'a pas
d'argument sur Raspian.

# Structure du projet

1. headers : ce répertoire contient tous les fichiers.h dans lesquels sont déclarées nos fonctions ainsi que leurs
   **spécifications**.

2. src : ce répertoire comprend tous les fichiers.c nécessaires au bon déroulement du programme (autre que le main.c).

3. input_binary : ce répertoire accueille les différents fichiers.bin donnés en entrée au programme.

4. output_csv : ce répertoire permet de recueillir le fichier csv de sortie du programme.

5. tests_files : ce répertoire contient différents sous dossiers reprenant touts nos fichiers utiles aux déroulements
   des tests, notamment le dossier **src** reprenant la suite de tests. Les autres dossiers s'occupent des tests
   valgrind, helgrind, la comparaison avec le programme python, etc.

# Structures utilisées

Toutes nos structures sont définies dans le fichier headers/kmeansStruct.h.

1. point_t : cette structure représente un point. Elle est composée d'un vecteur représentant les coordonnées du point
   ainsi que l'indice du centroïde le plus proche.

2. kMeans_t : cette structure est composée de toutes les informations nécessaires au déroulement de l'algorithme de
   Lloyd's. Le nom des composantes de cette structure est, selon nous, assez clair pour ne pas expliquer leur fonction.

3. data_t : cette structure contient les caractéristiques du problème à traiter (dimension et nombre de points)
   ainsi que tous les points provenant du fichier binaire donné en entrée.

# Utilisation des threads

Nous avons implémenté une architecture producteurs-consommateurs. Avant le lancement des threads le programme effectue
deux opérations importantes.

1. Extraction des données contenues dans le fichier binaire en entrée.

2. Calcul des différents centroids de départs. (cette étape aurait pu se voir assigner un thread mais on s'est rendu
   compte en faisant des tests de performance que le temps pris par cette étape était négligeable)

3. Producteurs : Nous avons donc une liste reprenant toutes les suites de centroids de départ. De cette manière, à
   chaque instance kMeans à traiter, correspond un indice. On transmet alors à chaque thread producteur les indices de
   début et de fin (fin non comprise). Chaque thread a alors pour mission d'exécuter et résoudre toutes les instances du
   problème kMeans compris entre les indices début et fin (non compris).

3. Consommateur : il n'y a qu'un seul thread consommateur qui s'occupe d'écrire dans le fichier de sortie les résultats
   obtenus par le(s) thread(s) producteur(s).

# Gestion de la concurrence

Nous avons donc d'un côté des threads producteurs et de l'autre un thread consommateur. La communication entre ces
threads s'opère à l'aide d'un buffer. Cependant l'utilisation d'un même objet par plusieurs threads est délicat, pour se
faire nous avons utilisé :

### Deux sémaphores :

1. empty: renseigne le thread consommateur sur la présence d'au moins un élément à consommer sur le buffer

2. full: renseigne les threads producteurs sur la présence d'au moins une place disponible sur le buffer

### Un mutex :

Il empêche l'utilisation du buffer par plus d'un thread en simultané. Sans cet élément, deux threads producteurs
pourraient, par exemple, déposer leurs résultats en même temps sur un même emplacement du buffer. Ce qui n'est
évidemment pas souhaité.

# Tests de performance

Commandes utilisées via la terminal pour lancer notre programme:  
*Pour lancer ces commandes, vous devez vous situer dans le repertoire contenant Makefile. Aussi, changez le fichier
d'entrée pour tester avec différentes tailles de fichiers*

* make performances

Nos tests de performances ont été effectués sur le fichier ex7_50Kpoints_dim5.bin contenant 50 000 points en 5
dimensions.

### Résultats sur raspberry :

* 1 thread : 3m0.517s
* 2 threads : 1m40.913s
* 3 threads : 1m22.046s
* 4 threads : 0m55.054s
* 8 threads : 0m53.222s

### Résultats sur un ordinateur portable classique :

* 1 thread : 0m11.23s
* 2 threads : 0m5.78s
* 3 threads : 0m4.90s
* 4 threads : 0m3.54s
* 8 threads : 0m2.73s

TODO --> Modif cette explication car je sais pas pq ça a changé sur rasp

Le temps d'exécution sur raspberry n'évolue plus linéairement au-delà de 2 threads producteurs. Si l'on prend en compte
le thread consommateur et celui derrière l'exécution de main, il fait alors sens que 2 threads producteurs fournissent
le meilleur résultat (puisqu'en réalité 4 threads sont à l'oeuvre). Sur nos machines personnelles, on observe des gains
de performance jusqu'à 7 threads producteurs.

# Questions éventuelles

Si vous avez encore certaines questions concernant le projet, n'hésitez pas à nous contacter aux adresses suivantes :

nicolas.jeanmenne@student.uclouvain.be, samuel.demeester@student.uclouvain.be loic.spigeleer@student.uclouvain.be,
sebastien.mary@student.uclouvain.be pierre.denoel@student.uclouvain.be, gilles.maes@student.uclouvain.be

Merci à vous de l'attention que vous apportez à ce projet.