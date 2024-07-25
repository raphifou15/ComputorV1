# ComputorV1

## Description

- Computer V1 est un programme qui résout des équations polynomiales de degré 2 ou inférieur. Ce projet utilise une bibliothèque mathématique personnalisée, développée en C, qui utilise des chaînes de caractères (char \*) pour les calculs au lieu des types numériques classiques comme int ou float. Cela permet de maintenir une précision maximale, en évitant les erreurs d'arrondi.

## Fonctionnalités

- Résolution d'équations polynomiales : Calcul des solutions pour des équations de degré 2 ou inférieur.
- Affichage de la forme réduite : Présentation de l'équation sous une forme simplifiée.
- Détermination du degré du polynôme : Identification et affichage du degré de l'équation.
- Calcul et affichage du discriminant : Indication de la nature des racines en fonction de la valeur du discriminant.
- Gestion des exceptions : Détection des cas spéciaux, tels que les équations sans solution ou avec des solutions infinies.
- Affichage de solutions en fractions irréductibles : (Bonus) Présente les solutions sous forme de fractions irréductibles lorsqu'il est pertinent.
- Affichage des étapes intermédiaires : (Bonus) Montre les calculs étape par étape pour une meilleure compréhension.
- Gestion des erreurs d'entrée : (Bonus) Traite les erreurs de syntaxe et de format dans les équations fournies.

## Exemples

### Exemple 1

```
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0
Polynomial degree: 2
delta = 164.8
Discriminant is strictly positive
The two solutions are:
0.9052389907905897859738434128844292278779232413428776708112461416455033180633343402498574290432717374
-0.4751314639088693558663165311639991203510415209127701439295257115379764363429042327229757086131642105
```

### Exemple 2

```
./computor "5 * X^0 + 4 * X^1 = 4 * X^0"
Reduced form: 1 * X^0 + 4 * X^1 = 0
Polynomial degree: 1
The solution is:
-0.25
```

### exemple bonus

```
./computorBonus "5 + 4 * X + X^2= X^2"
Calcul : 1X^2 - 1X^2
Intermediate Step  5 + 4X + 0X^2 = 0
Reduced form: 5 + 4X = 0
Polynomial degree: 1
The solution is:
-1.25
res fraction: -5 / 4
```

## Installation

### Prérequis

- Un compilateur C (par exemple, GCC)
- make

### Étapes d'installation

1.  Clonez le dépôt :

```
  git clone git@github.com:raphifou15/ComputorV1.git
  cd ComputorV1
```

2. Compilez le projet :

```
  make
  ou
  make bonus
```

Exécutez le programme :

sans le bonus il doit etre sous cette forme un espace entre les characteres puissance sous la forme X^0 (pour le normal)

```
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
```

ou

```
./computorBonus "5 + 4 * X = X^2"
```

## Structure du Projet

- main.c : Point d'entrée du programme, gère les entrées utilisateur et l'affichage des résultats.
- La library math.a : Contient les fonctions mathématiques pour la manipulation des chaînes de caractères et le calcul des solutions.

## Détails Techniques

- La bibliothèque mathématique utilise des chaînes de caractères pour éviter les erreurs d'arrondi associées aux types numériques standards. Cette méthode garantit une manipulation précise des nombres, essentielle pour les calculs nécessitant une grande exactitude.

## Calcul du Discriminant (Δ)

- Δ=b 2 −4ac
  En fonction de la valeur de Δ
  Δ, nous avons différentes situations :
  Si Δ > 0 : L'équation a deux solutions réelles distinctes.
  Si Δ = 0 : L'équation a une solution réelle double.
  Si Δ < 0 : L'équation n'a pas de solution réelle, mais deux solutions complexes conjugées.
  Formules des solutions
  Pour Δ > 0 : 𝑥1 = (−𝑏+√Δ)/(2𝑎), 𝑥2 = (−𝑏 -√Δ)/(2𝑎)
  Pour Δ = 0 : x = (-b) / 2a
  Pour Δ < 0 : x1 = (-b + i√Δ)/2a, x2 = (-b-i√Δ)/2a

# Auteurs

raphael khelif - Développeur principal

# Licence

- Ce projet est sous licence MIT, ce qui signifie qu'il est libre d'utilisation, de modification et de distribution.
