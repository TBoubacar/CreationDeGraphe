#include "sommet.hh"

Sommet::Sommet(unsigned int id) : _id(id), _couleur(Couleur::vert), _voisins() {
    _couleurDispo.push_back(Couleur::vert); _couleurDispo.push_back(Couleur::jaune);
    _couleurDispo.push_back(Couleur::rouge); _couleurDispo.push_back(Couleur::bleu);
    _couleurDispo.push_back(Couleur::blanc); _couleurDispo.push_back(Couleur::noir);
    _couleurDispo.push_back(Couleur::orange); _couleurDispo.push_back(Couleur::marron);
    _couleurDispo.push_back(Couleur::violet); _couleurDispo.push_back(Couleur::rose);
}

bool Sommet::operator==(const Sommet &sommet) const {
    return (_id == sommet._id && _couleur == sommet._couleur && _voisins == sommet._voisins);
}

bool Sommet::operator!=(const Sommet &sommet) const {
    return !(_id == sommet._id && _couleur == sommet._couleur && _voisins == sommet._voisins);
}

void Sommet::ajouterVoisin(Sommet & sommet) {
    _voisins.push_back(sommet._id); sommet._voisins.push_back(_id);
}

void Sommet::elimineCouleur(Couleur c) {
    for (auto i(_couleurDispo.begin()); i!=_couleurDispo.end(); ++i)
        if ((*i) == c)
            _couleurDispo.erase(i);
    //On efface la couleur de notre liste de couleur disponible
}
