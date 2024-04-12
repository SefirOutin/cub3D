#!/bin/bash

# Vérification que le script est utilisé correctement
if [ $# -ne 1 ]; then
    echo "Usage: $0 <dossier>"
    exit 1
fi

# Vérification que le dossier existe
if [ ! -d "$1" ]; then
    echo "Erreur: Le dossier $1 n'existe pas."
    exit 1
fi

# Parcourir tous les fichiers C dans le dossier et les sous-dossiers
find "$1" -type f -name "*.c" | while read fichier; do
    # Vérifier si le fichier est lisible
    if [ ! -r "$fichier" ]; then
        echo "Erreur: Impossible de lire le fichier $fichier."
        continue
    fi

    # Ajouter "_bonus" à la quatrième ligne juste avant le premier point rencontré
    sed -i '4s/\./_bonus./' "$fichier"

    # Supprimer 6 espaces juste après les caractères ".c" sur la quatrième ligne
    sed -i '4s/\.c      /.c/' "$fichier"

    echo "Modifications apportées à $fichier"
done

echo "Opération terminée."

