#include "graphes.hh"
/*
 * Nom  :   TOURE Boubacar Etudiant en Licence 3 Informatique à la faculté de sciences d'Angers
 * Date :   23 Decembre 2020 à 7 h 10 min
 * Email:   boubacartoure123@gmail.com
 * @copyright : Non utilisable pour des fins commerçiales
 *
 */

int main() {
    std::cout << "___________Algo Des Graphes___________\nPensez à renseigner toute l'adresse de votre fichier\nExemple : /home/TBoubacar/...\n" << std::endl;

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
