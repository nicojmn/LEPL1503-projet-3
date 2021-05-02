
Ce projet a été élaboré par Gille Maes, Loic Spigeleer, Nicolas Jeanmenne,
Pierre Denoël, Samuel de Meester et Sébastien Mary.

Ce README contient toutes les informations nécessaires quant à la bonne compréhension du projet.

    1. Structures utilisées

        Toutes nos structures sont définies dans le fichier headers/kmeansStruct.h. Pour plus
        d'informations à leur sujet, consultez le fichier.

        a. point_t : cette structure represente un point sur le graphique.
           Elle est composée d'un vecteur constitué des coordonnées du point ainsi que du centroide
           le plus proche.

        b. kMeans_t : cette structure est composée de toutes les informations nécessaires au déroulement de
           l'algorithme de Lloyd's. Les noms des composantes de cette structure est, selon nous, assez
           clairs pour ne pas expliquer leur fonction.

        c. data_t : cette structure contient les instances du problèmes ainsi que tous les points du
        fichier d'entrée.

    2. Utilisation des threads

        TODO : Utilisation des threads

    3. Gestion de la concurrence

        TODO : Gestion de la concurrence

    4. Tests de performance TODO : faites les tests chez vous et mettez les infos ici pcq chez moi c'est pas optimal

        Ces tests ont été effectués sur le fichier ex3.bin.
        Commande utilisée via la terminal :

        a. Avec 1 thread :
            Python :
            C      :

        b. Avec 2 threadS :
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

            make kmeans
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