cprep 🛠️

cprep est un utilitaire léger écrit en C permettant d'automatiser la création de fichiers sources (.c), d'en-têtes (.h) et la génération dynamique de makefile pour vos projets.
📥 Installation

Le projet inclut un makefile avec des règles d'installation système :

pour installer sur le système :

	make install

Désinstaller :

	make uninstall

🚀 Utilisation

La syntaxe est la suivante :

cprep [OPTIONS] [MODULES...]

1. Génération de Modules

Chaque nom passé en argument (sans tiret) génère un couple de fichiers :

    Exemple : cprep math moteur crée math.h/math.c et moteur.h/moteur.c.

    Gardes d'inclusion : Les fichiers .h incluent automatiquement des protections contre l'inclusion multiple (ex: #ifndef MATH_H).

2. Options disponibles
Option	Description
-v	Verbose : Affiche les détails des opérations en console.
-m / -M	Crée ou complète un fichier makefile (minuscule) ou Makefile (Majuscule).
-a [nom]	Définit un nom spécifique pour le fichier main et le génère.
-A	Génère le fichier main avec le nom par défaut (main.c).
-e [nom]	Définit le nom de l'exécutable cible dans le makefile (Défaut: exec).
-r	Ajoute les règles standards (all, clear, gedit) au makefile.
📝 Exemples Pratiques
Initialiser un nouveau projet complet

cprep -vmr -e mon_app -A module1 module2

Résultat :

    Création de main.c, module1.c/.h et module2.c/.h.

    Création d'un makefile avec les règles de compilation pour chaque fichier.

    L'exécutable produit par le makefile s'appellera mon_app.

Ajouter un module à un projet existant
Bash

cprep -m nouveau_module

Cela génère les fichiers du module et ajoute la règle de compilation .o à la fin de votre makefile actuel sans effacer le reste.
