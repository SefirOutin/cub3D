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

# Parcourir tous les fichiers dans le dossier et les sous-dossiers
find "$1" -type f | while read fichier; do
    # Obtenir le nom du fichier sans le chemin d'accès
    nom_fichier=$(basename "$fichier")
    
    # Obtenir le chemin d'accès du dossier contenant le fichier
    dossier_contenant=$(dirname "$fichier")

    # Créer le nouveau nom de fichier avec "_bonus" ajouté
    nouveau_nom="${nom_fichier%.*}_bonus.${nom_fichier##*.}"

    # Renommer le fichier
    mv "$fichier" "$dossier_contenant/$nouveau_nom"
    echo "Renommage: $fichier -> $dossier_contenant/$nouveau_nom"
done

echo "Renommage terminé."
