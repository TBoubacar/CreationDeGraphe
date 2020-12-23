#include "graphes.hh"

int main() {
    std::cout << "___________Algo Des Graphes___________\nPensez à rensigner toute l'adresse de votre fichier\nExemple : /home/TBoubacar/...\n" << std::endl;

    Graphe monGraphe;
    monGraphe.lecture("/home/etudiant/ProjetAlgoGraphe/myciel3.col");
    monGraphe.ecriture("/home/etudiant/ProjetAlgoGraphe/myciel3.dot");
    monGraphe.lecture("/home/etudiant/ProjetAlgoGraphe/myciel4.col");
    monGraphe.ecriture("/home/etudiant/ProjetAlgoGraphe/myciel4.dot");
    monGraphe.lecture("/home/etudiant/ProjetAlgoGraphe/myciel6.col");
    monGraphe.ecriture("/home/etudiant/ProjetAlgoGraphe/myciel6.dot");

    std::cout << "___________FIN DE L'ALGORITHME___________" << std::endl;

    return 0;
}
