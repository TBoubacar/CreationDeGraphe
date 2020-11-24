#include <iostream>
#include <sstream>
#include "fonctionsio.hh"

int main()
{
    std::cout << "------------------" << std::endl;
    Graphe graphe;
    /*###################################################################################
     *        PENSÉ À RENSEIGNER L'ADRESSE COMPLETE DU FICHIER DEPUIS LA RACINE
     * EXEMPLE : /home/étudiant/...
     *        PENSÉ A BIEN PRECISER L'EXTENSION DES FICHIER DE LECTURE ET D'ECRITURE
     * EXEMPLE : fichierLecture.col et fichierEcriture.dot
     *###################################################################################*/

    graphe.lecture("/home/TBoubacar/AlgoGraphe/TP1/TP1_LectureEcritureGraphe/fichierGraphe1.col");
    graphe.lecture("/home/TBoubacar/AlgoGraphe/TP1/TP1_LectureEcritureGraphe/fichierGraphe2.col");
    graphe.affichage();
    graphe.ecriture("/home/TBoubacar/AlgoGraphe/TP1/TP1_LectureEcritureGraphe/fichierGraphe1.dot");
    graphe.ecriture("/home/TBoubacar/AlgoGraphe/TP1/TP1_LectureEcritureGraphe/fichierGraphe2.dot");
    std::cout << "------------------" << std::endl;
    return 0;
}
