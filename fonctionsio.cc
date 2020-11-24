#include "fonctionsio.hh"
#include <iterator>
#include <algorithm>
/*
 *  NOM     : TOURE Boubacar
 *  DATE    : November 24, 2020
 *  Email   : boubacartoure123@gmail.com
 *  
 */

std::vector<std::string> decouperPhrase(const std::string &phrase) {
    std::vector<std::string> tabMot;
    std::istringstream mots (phrase);   //Impossible d'utiliser la fonction getline ni les iterators sur un std::string, donc on l'ecrit dans un flux pour travailler là-dessus
    std::string contenu("");            //On déclare une variable local dans le but de contenir les mots un par un
    while (std::getline(mots,contenu,' '))
        tabMot.push_back(contenu);      //STOCKAGE DES MOTS SEPARÉS PAR LE SEPARATEUR ' ' DANS LA PHRASE
    return tabMot;
    /*      EXEMPLE : phrase = "Je vais à la maison"
     *      tabMot[0] = Je; tabMot[1] = vais; tabMot[2] = à; ...
     *      Grace à la fonction standard std::getline(<fluxALire>, <contenuMot>, <delimiteur>)
     */
}

void Graphe::lecture(const std::string &nomFichier) {
    /*##################################################################
     *              POUR LIRE LES DONNÉES DANS LE FICHIER
     *##################################################################*/

    std::ifstream file (nomFichier.c_str());    //Pour pouvoir lire le fichier dont le nom est passé en paramètre
    if (!file)
        std::cout << "Le fichier (" << nomFichier << ") n'a pas pu être ouvert !\nVERIFIER LE NOM DU FICHIER ET RÉESSAYER (^_^)" << std::endl;
    else {
        std::string ligne ("");
        while (std::getline(file, ligne)) {
            if (ligne[0] == 'p') {
                std::vector<std::string> tab (decouperPhrase(ligne));       //On recupere les mots dans le tableau
                _nbSommet = static_cast<unsigned int>(std::stoi(tab[2]));   //On recupere le nombre de sommets du graphe
                for (unsigned int i (0); i< taille(); ++i)
                    _vecteur.push_back(false);                              //On initialise les valeurs de la MATRICE à false (0)
            }
            if (ligne[0] == 'e') {
                unsigned int v1(0), v2(0);
                std::vector<std::string> tabVal (decouperPhrase(ligne));        //On recupere le flux contenant la ligne et on le decoupe en plusieurs mots (ATTENTION tabVal[0] = "e")
                v1 = static_cast<unsigned int>(std::stoi(tabVal[1]));           //On recupere la 2e valeur sous forme d'un 'unsigned int' (PREMIER SOMMET)
                v2 = static_cast<unsigned int>(std::stoi(tabVal[2]));           //On recupere la 3e valeur sous forme d'un 'unsigned int' (DEUXIEME SOMMET)
                ajouterArete(v1-1,v2-1);        //ON DECALE CAR LES VALEURS DANS LE VECTEUR COMMENCE À ZERO ET NON 1
            }
        }
    }
    file.close();       //Ce n'est pas utile, mais je le fais cas même
}

void Graphe::ecriture(const std::string &nomFichier) {
    /*##################################################################
     *              POUR ECRIRE LA SOLUTION DANS LE FICHIER
     *##################################################################*/

    std::ofstream file (nomFichier.c_str());
    file << "digraph D {\n" << "\trankdir=LR;\n\n";
    for (coordonnee i(0); i<_nbSommet; ++i)
        file << "\t" << (i+1) << " [shape=circle]\n";       //L'affichage doit commencer à 1 et non 0, voila pourquoi on fait (i+1) et (j+1)
    file << "\n";
    for (coordonnee i(0); i<_nbSommet; ++i)
        for (coordonnee j(0); j<_nbSommet; ++j)
            if (_vecteur.at(indice(i,j)))
                file << "\t" << (i+1) << " -> " << (j+1) << " [arrowhead=none]\n";
    file << "}\n";
    file.close();
}

void Graphe::ajouterArete(coordonnee x, coordonnee y) {
    _vecteur.at(indice(x,y)) = true;                //Je met les valeurs aux indices (x,y) de la MATRICE à true (1)
    _liste.push_back(x+1); _liste.push_back(y+1);   //On fait le decalage ici pour avoir la vraie valeur mise (dans les listes, il n'y a pas de problèmes d'indice)
    /*              EXPLICATION POUR L'USAGE DE LA STRUCTURE LISTE
     * DANS LA METHODE QUE J'UTILISE, JE MET LES SOMMETS QUI FORMENT DES ARETES 2 PAR 2
     * DONC LES 2 PREMIERES VALEURS QUE JE LIRAIS, CORRESPONDERAIENT A DES SOMMETS QUI ONT
     * UNE ARETE EN COMMUN. DONC POUR L'USAGE D'UNE BOUCLE RETOURNANT LES SOMMETS LIÉS PAR UNE ARETE,
     * ON DOIT FAIRE UNE INCREMENTATION PAR PAS DE 2 POUR LES LISTES
     */
}

void Graphe::affichage() const {
    std::cout << "--> AFFICHAGE DU VECTEUR (MATRICE) DE TAILLE \"" << taille() << "\" : " << std::endl;
    coordonnee ligne (1);
    std::cout << "      ";
    for (coordonnee colonne (1); colonne <= _nbSommet; ++colonne)
        std::cout << colonne << "     ";
    std::cout << std::endl;             //POUR L'AFFICHAGE DES ETIQUETTES DE COLONNES

    for (coordonnee i(0); i<_nbSommet; ++i) {
        std::cout << (ligne++) << "     ";  //POUR L'AFFICHAGE DES ETIQUETTES DE LIGNES
        for (coordonnee j(0); j<_nbSommet; ++j)
            std::cout << _vecteur.at(indice(i,j)) << "     ";
        std::cout << std::endl;
    }

    std::cout << "--> AFFICHAGE DE LA LISTE : " << std::endl;
    int compteur (0);
    for (auto i(_liste.begin()); i!=_liste.end(); ++i){
        std::cout << (*i);
        ++compteur;
        if (compteur < 2) std::cout << " -> ";
        else {
            compteur = 0;
            std::cout << std::endl;
        }
    }
}
