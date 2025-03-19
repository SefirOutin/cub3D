# cub3D - Moteur de Jeu 3D Raycasting 🎮

[![Note du Projet](https://img.shields.io/badge/Note-110%2F100-success?style=for-the-badge)]()

## 🎯 À Propos

cub3D est un projet de moteur graphique 3D développé à l'École 42, inspiré du légendaire jeu Wolfenstein 3D. Ce projet implémente des techniques de raycasting pour créer une perspective 3D dans une carte 2D.

https://user-images.githubusercontent.com/dda24966-9488-44d6-90b2-9f193bb37abd

## 🌟 Fonctionnalités

- Rendu 3D en temps réel utilisant le raycasting
- Murs texturés avec différentes faces (Nord, Sud, Est, Ouest)
- Mouvements et rotations fluides du joueur
- Affichage d'une mini-carte
- Détection des collisions
- Résolution et textures configurables
- Analyse des fichiers de configuration de carte

## 🛠️ Installation

### Prérequis

```bash
# Installation des paquets nécessaires
sudo apt-get install -y libx11-dev xorg-dev libbsd-dev clang make
```

### Compilation

```bash
# Cloner le dépôt
git clone <repository-url>
cd cub3D

# Compiler le projet
make
```

## 🎮 Utilisation

```bash
./cub3D maps/map.cub
```

### Contrôles

- `W` `A` `S` `D` - Déplacement
- `←` `→` - Rotation de la caméra
- `ESC` - Quitter le jeu

## 🗺️ Configuration de la Carte

Les cartes sont définies dans des fichiers `.cub` avec le format suivant :

```
NO ./chemin_texture_nord
SO ./chemin_texture_sud
WE ./chemin_texture_ouest
EA ./chemin_texture_est

F R,G,B    # Couleur du sol
C R,G,B    # Couleur du plafond

# Structure de la carte
111111
100101
101001
1000N1
111111
```

Où :
- `0` - Espace vide
- `1` - Mur
- `N/S/E/W` - Position et orientation de départ du joueur

## 👥 Auteurs

- [Bilou0412](https://github.com/Bilou0412)
- [SefirOutin](https://github.com/SefirOutin)

