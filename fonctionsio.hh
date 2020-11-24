#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

using typeListe = unsigned int;
using typeVecteur = bool;
using coordonnee = unsigned int;
using liste = std::list<typeListe>;
using vecteur = std::vector<typeVecteur>;

class Graphe {
    public:
        Graphe () : _liste(), _vecteur(), _nbSommet(0) {}
        void lecture (std::string const & nomFichier);
        void ecriture (std::string const & nomFichier);
        unsigned int taille () const { return _nbSommet*_nbSommet; }
        void ajouterArete (coordonnee x, coordonnee y);
        void affichage () const;
    private:
        unsigned int indice (coordonnee x, coordonnee y) const { return y*_nbSommet+x; }
    private:
        liste   _liste;     //Pour la représentation d'une liste
        vecteur _vecteur;   //Pour la représentation d'une matrice
        unsigned int _nbSommet;
};
std::vector<std::string> decouperPhrase(std::string const & phrase);
