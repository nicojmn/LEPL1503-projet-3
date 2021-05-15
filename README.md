Ce projet a été élaboré par Gille Maes, Loic Spigeleer, Nicolas Jeanmenne, Pierre Denoël, Samuel de Meester et Sébastien
Mary.

Ce README contient toutes les informations nécessaires quant à la bonne compréhension du projet.

# Lancement du programme

### Commandes nécessaires au fonctionnement du projet :

1. make
1. make tests
1. make clean

### Commande pour l'exécuter avec ses propres arguments : 
Les arguments précédés de "+" sont optionnels.

./kmeans +[−q show_clusters] +[−k n_clusters] +[−p n_combinations_points] [−n n_threads]
+[−d distance_metric] +[−f output_file] +[input_filename]

Par défaut, les clusters ne sont pas repris dans l'output, -k vaut 2, +p vaut la même chose que -k, -n vaut 4, -d vaut
"manhattan", le résultat est écrit sur la sortie standard et l'entrée standard est lue pour l'input. Nous avons ajouté
la possibilité de mettre l'argument -t pour afficher le temps d'exécution.

### Commandes ajoutées :

1. make valgrind
1. make valgrindForTests
1. make helgrind
1. make performances

La première effectue les tests Valgrind (tests sur la gestion de la mémoire) sur le fichier ex3.bin. La deuxième
effectue les tests Valgrind pour les tests unitaires. La troisième effectue les tests Helgrind (test des threads) sur le
fichier ex3.bin. La dernière lance le programme plusieurs fois sur un fichier d'entrée de 50 000 points et avec
différents nombres de threads. Elle produit ensuite une visualisation avec matplotlib dans le dossier
tests_files/test_performances. Notez que cette commande ne fonctionne pas sur le Raspberry car la commande time n'a pas
d'argument sur Raspian.

# Structures utilisées

Toutes nos structures sont définies dans le fichier headers/kmeansStruct.h. Pour plus d'information à leur sujet,
consultez le fichier.

1. point_t : cette structure représente un point. Elle est composée d'un vecteur représentant les coordonnées du point
   ainsi que l'indice du centroïde le plus proche.

1. kMeans_t : cette structure est composée de toutes les informations nécessaires au déroulement de l'algorithme de
   Lloyd's. Le nom des composantes de cette structure est, selon nous, assez clair pour ne pas expliquer leur fonction.

1. data_t : cette structure contient les caractéristiques du problème à traiter (dimension et nombre de points)
   ainsi que tous les points provenant du fichier binaire donné en entrée.

# Utilisation des threads

Nous avons implémenté une architecture producteurs-consommateurs. Avant le lancement des threads le programme effectue
deux opérations importantes.

1. Extraction des données contenues dans le fichier binaire en entrée.

1. Calcul des différents centroids de départs. (cette étape aurait pu se voir assigner un thread mais on s'est rendu
   compte en faisant des tests de performance que le temps pris par cette étape était négligeable)

1. Producteurs : Nous avons donc une liste reprenant toutes les suites de centroids de départ. De cette manière, à chaque
   instance kMeans à traiter, correspond un indice. On transmet alors à chaque thread producteur les indices de début et
   de fin (fin non comprise). Chaque thread a alors pour mission d'exécuter et résoudre toutes les instances du problème
   kMeans compris entre les indices début et fin (non compris).

1. Consommateur : il n'y a qu'un seul thread consommateur qui s'occupe d'écrire dans le fichier de sortie les résultats
   obtenus par le(s) thread(s) producteur(s).

# Gestion de la concurrence

Nous avons donc d'un côté des threads producteurs et de l'autre un thread consommateur. La communication entre ces
threads s'opère à l'aide d'un buffer. Cependant l'utilisation d'un même objet par plusieurs threads est délicat, pour se
faire nous avons utilisé :

### Deux sémaphores :

1. empty: renseigne le thread consommateur sur la présence d'au moins un élément à consommer sur le buffer

1. full: renseigne les threads producteurs sur la présence d'au moins une place disponible sur le buffer

### Un mutex :

Il empêche l'utilisation du buffer par plus d'un thread en simultané. Sans cet élément, deux threads producteurs
pourraient, par exemple, déposer leurs résultats en même temps sur un même emplacement du buffer. Ce qui n'est évidemment
pas souhaité.

# Tests de performance

// TODO : UPDATE Ces tests ont été effectués sur le fichier ex6_dim5.bin contenant 10 000 points en 5 dimensions.

Commandes utilisées via la terminal (pour lancer ces commandes, vous devez vous situer dans le repertoire "groupeD22").

* make
* ./kmeans -k 6 -p 10 -n 2 -q -d euclidean -f output_csv/ex6_dim5.csv input_binary/ex6_dim5.bin

### Résultats sur raspberry :

* 1 thread : 2m28.453s
* 2 threads : 1m17.179s
* 3 threads : 1m15.007s
* 4 threads : 1m14.817s

### Résultats sur un ordinateur portable classique :

* 1 thread : 0m24.382s
* 2 threads : 0m14.896s
* 3 threads : 0m8.904s
* 4 threads : 0m6.359s

On n'arrive plus à améliorer le temps d'exécution sur raspberry au-delà de 2 threads producteurs. Si l'on prend en
compte le thread consommateur et celui derrière l'exécution de main, il fait alors sens que 2 threads producteurs
fournissent le meilleur résultat (puisqu'en réalité 4 threads sont à l'oeuvre). Sur nos machines personnelles, on
observe des gains de performance jusqu'à 7 threads producteurs.

# Questions éventuelles

Si vous avez encore certaines questions concernant le projet, n'hésitez pas à nous contacter aux adresses suivantes :

nicolas.jeanmenne@student.uclouvain.be, samuel.demeester@student.uclouvain.be loic.spigeleer@student.uclouvain.be,
sebastien.mary@student.uclouvain.be pierre.denoel@student.uclouvain.be, gilles.maes@student.uclouvain.be

Merci à vous de l'attention que vous apportez à ce projet.