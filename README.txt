
Ce projet a été élaboré par Gille Maes, Loic Spigeleer, Nicolas Jeanmenne,
Pierre Denoël, Samuel de Meester et Sébastien Mary.

Ce README contient toutes les informations nécessaires quant à la bonne compréhension du projet.

    1. Structures utilisées

        Toutes nos structures sont définies dans le fichier headers/kmeansStruct.h. Pour plus
        d'informations à leur sujet, consultez le fichier.

        a. point_t : cette structure représente un point.
           Elle est composée d'un vecteur représentant les coordonnées du point ainsi que du centroide
           le plus proche.

        b. kMeans_t : cette structure est composée de toutes les informations nécessaires au déroulement de
           l'algorithme de Lloyd's. Les noms des composantes de cette structure est, selon nous, assez
           clairs pour ne pas expliquer leur fonction.

        c. data_t : cette structure contient les caractéristiques du problème à traiter (dimension et nombre de points)
        ainsi que tous les points provenant du fichier binaire donné en entrée.

    2. Utilisation des threads

        Nous avons implémenter une architecture producteurs/consommateurs. Avant le lancement des threads le
        programme effectue deux opérations importantes.

        a. Extraction des données contenues dans le fichier binaire en entrée.

        b. Calcul des différents centroids de départs. (cet étape aurait pu se voir assigner un thread mais
        on s'est rendu compte en faisant des tests de performance que le temps pris par cette étape était négligeable)

        Producteurs: Nous avons donc une liste reprenant toutes les suites de centroids de départ. De cette manière,
        à chaque instance kMeans à traiter, correspond un indice. On transmet alors à chaque thread producteur
        les indices de début et de fin (fin non comprise). Chaque thread a alors pour mission d'exécuter et résoudre
        toutes les instances du problème kMeans compris entre les indices début et fin (non compris).

        Consommateur: il n'y a qu'un seul thread consommateur qui s'occupe d'écrire dans le fichier de sortie les
        résultats obtenus par le(s) thread(s) producteur(s).

    3. Gestion de la concurrence

        Nous avons donc d'un côté des threads producteurs et de l'autre un thread consommateur. La communication
        entre ces threads s'opère à l'aide d'un buffer. Cependant l'utilisation d'un même objet par plusieurs
        threads est délicat, pour se faire nous avons utiliser:

        Deux sémaphores:

            empty: renseigne le thread consommateur sur la présence d'au moins un élément à consommer sur le buffer

            full: renseigne les threads producteurs sur la présence d'au moins une place disponible sur le buffer

        un mutex: il empêche l'utilisation du buffer par plus d'un thread en simultané. Sans cet élément,
        deux threads producteurs pourraient, par exemple, déposer leurs résultat en même temps
        sur un même emplacement du buffer. Ce qui n'est évidemment pas souhaité.

    4. Tests de performance TODO : faites les tests chez vous et mettez les infos ici pcq chez moi c'est pas optimal

        Ces tests ont été effectués sur le fichier ex5.bin contenant 50 000 points.
        Commande utilisée via la terminal :

        a. Avec 1 thread :
            Python :
            C      :

        b. Avec 2 threads :
            Python :
            C      :

        c. Avec 4 threads :
            Python :
            C      :

        d. Avec 9 threads :
            Python :
            C      :

        Nous pouvons en conclure qu'en moyenne, le programme en C multithreadé s'effectue #TODO ?
        plus vite que le programme python.

    5. Lancement du programme

        Les trois commandes nécessaires pour faire fonctionner le projet sont les suivantes:

            make
            make tests
            make clean

        Pour de plus amples informations concernant leur utilisation, réferez-vous au Makefile.


Si vous avez encore certaines questions concernant le projet, n'hésitez pas à nous contacter aux
adresses suivantes:

- Questions techniques/lancement projet:

    nicolas.jeanmenne@student.uclouvain.be, samuel.demeester@student.uclouvain.be

- Questions sur l'utilisation des threads/concurrence :

    loic.spigeleer@student.uclouvain.be, samuel.demeester@student.uclouvain.be

- Questions sur la structure/design du programme :

    sebastien.mary@student.uclouvain.be

- Pour tout autre renseignement :

    pierre.denoel@student.uclouvain.be, gilles.maes@student.uclouvain.be


Merci à vous de l'attention que vous apportez à ce projet.