#pragma once
#include <iostream>
#include <fstream>      //Pour l'usage des fichiers (std::ifstrem & std::ofstream)
#include <sstream>      //Pour l'usage de flux de type chaine de caractères et manipulation (std::stringstream)
#include <string>       //Pour l'usage des chaines de caractères (std::string)
#include <vector>
#include "sommet.hh"

using typeVecteur = Sommet;
using vecteur = std::vector<typeVecteur>;

class Graphe {
    public:
        Graphe() : _ensSommet(), _nbSommet(0), _nbArete(0) {}
        /*____________________QUESTION 1____________________*/
        void lecture(const std::string & nomFichier);
        /*____________________QUESTION 2____________________*/
        unsigned int coloriage();
        unsigned int nbChromatique(Couleur c) const;
        /*____________________QUESTION 3____________________*/
        void ecriture(const std::string &nomFichierSortie);
    private:
        void initialiserGraphe();
        void ajouterArete (unsigned int id1, unsigned int id2);                     //Vu qu'il est impossible pour 2 sommets d'avoir les mêmes id, alors cette méthode est le plus appropriée
        std::vector<Sommet>::iterator rechercheSommet(unsigned int id);
        unsigned int indiceMatrice(unsigned int ligne, unsigned int colonne) const;         //Attention, les indices doivent forcement commencer par 0 et non 1 donc il faudra gerer le cas
        std::vector<std::string> chaineToTable (const std::string & phraseADecouper) const; //Prend une phrase en paramètre et le découpe en un tableau de mot en fonction du délimiteur ' ' (espace)
        void colorieSommet(std::ofstream & file, unsigned int id, Couleur c);
    private:
        vecteur _ensSommet;             //L'ensemble des sommets du graphe
        unsigned short  _nbSommet;      //Le nombre de sommets du graphe
        unsigned int    _nbArete;       //Le nombre d'arêtes du graphe
};
