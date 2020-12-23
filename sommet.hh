#pragma once
#include <algorithm>
#include <vector>

enum class Couleur {    //J'ai choisi de prendre au maximum 10 couleurs pour représenter mes graphes pas plus (SI VOUS VOULIEZ GERER PLUS DE CAS, VOUS POUVIEZ AUGMENTER LE NOMBRE DE COULEURS)
    vert, jaune, rouge, bleu, blanc, noir, orange, marron, violet, rose
};

class Sommet {
    public:
        Sommet(unsigned int id);
        bool operator==(const Sommet & sommet) const;
        bool operator!=(const Sommet & sommet) const;
        unsigned int getId() const { return _id; }
        Couleur getCouleur() const { return _couleur; }
        void setCouleur(Couleur c) { _couleur = c; }
        std::vector<unsigned int> const & getVoisin() const { return _voisins; }
        Couleur couleurDispo() const { return _couleurDispo.front(); }
        std::vector<unsigned> const & getVoisins() const { return _voisins; }
        void ajouterVoisin(Sommet & sommet);
        bool estVoisin(Sommet const & sommet) const { return std::find(_voisins.begin(), _voisins.end(), sommet._id) != _voisins.end(); }
        void elimineCouleur(Couleur c);         //Permet d'éliminer les couleurs utilisées par les voisins du sommet courant
    private:
        unsigned int    _id;                    //L'identifiant du sommet
        Couleur         _couleur;               //La couleur du sommet
        std::vector<unsigned int> _voisins;     //Les sommets qui sont voisins au sommet courant (on ne considere que l'id des sommets voisins car 2 sommets ne peuvent pas avoir le même id)
        std::vector<Couleur> _couleurDispo;//Ceci correspond à l'ensemble des couleurs qui peut être utiliser par le sommet (à chaque fois qu'un voisin à une couleur, alors on la supprime de la liste)
};
