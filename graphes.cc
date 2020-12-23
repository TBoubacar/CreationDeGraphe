#include "graphes.hh"

/*----------------------------------------------------------------------------------------------
 *                  GRAPHES-MÉTHODE (LECTURE & ECRITURE)
 * Nom  :   TOURE Boubacar Etudiant en Licence 3 Informatique à la faculté de sciences d'Angers
 * Date :   23 Decembre 2020 à 7 h 10 min
 * Email:   boubacartoure123@gmail.com
 * @copyright : Non utilisable pour des fins commerçiales
 *
 *---------------------------------------------------------------------------------------------*/

void Graphe::initialiserGraphe()
{    _ensSommet.clear(); }

unsigned int Graphe::indiceMatrice(unsigned int ligne, unsigned int colonne) const
{   return ligne*_nbSommet+colonne;   }

std::vector<std::string> Graphe::chaineToTable(const std::string &phraseADecouper) const {
    std::istringstream maPhrase(phraseADecouper);       //On doit utiliser un istringstream pour pouvoir traiter les chaines de caractères à l'aide std::getline et des iterators car cela ne marche pas avec les types string
    std::string contenu;                                //Cette variable contiendrait un par un tous les mots dans ma phrase
    std::vector<std::string> tableDeMot;
    while (std::getline(maPhrase,contenu,' '))          //std::getline(<chaineFluxSource>, <ContenuLuEnFonctionDuDelimiteur>, <LeDelimiteur>)
        tableDeMot.push_back(contenu);
    return tableDeMot;
    /*      La fonction chaineToTable renvoi un tableau contenant les mots de notre phrase
     * Exemple :
     *      phraseADecouper = "Je m'appele Boubacar et je viens du Mali"
     *      tableDeMot[0] = "Je", tableDeMot[1] = "m'appele", tableDeMot[2] = "Boubacar", ..., tableDeMot[7] = "Mali"
     *      Le type istringstream était indispensable car on ne pouvait pas utiliser std::getline sur un type string
     *
     */
}


void Graphe::ajouterArete(unsigned int id1, unsigned int id2) {
    auto sommet1 = rechercheSommet(id1);    //On recupere un pointeur sur le sommet dont l'id correspond afin de pouvoir m'être à jour son contenu de maniere automatique
    auto sommet2 = rechercheSommet(id2);
    if (sommet1 != _ensSommet.end() && sommet2 != _ensSommet.end())
        sommet1->ajouterVoisin(*(sommet2));
}

std::vector<Sommet>::iterator Graphe::rechercheSommet(unsigned int id) {
    for (auto i(_ensSommet.begin()); i!=_ensSommet.end(); ++i)
        if ((*i).getId() == id)
            return i;
    return _ensSommet.end();
}

/*____________________QUESTION 1____________________*/
void Graphe::lecture(const std::string &nomFichier) {
    /*------------------------------------------------------
     * CETTE FONCTION DOIT AVOIR UN FICHIER .col EN PARAMETRE
     * AFIN DE POUVOIR GENERER LE GRAPHE CORRESPONDANT
     *------------------------------------------------------*/
    std::ifstream File (nomFichier.c_str());
    if (!File)
        std::cout << "Le fichier (" << nomFichier << ") n'existe pas dans votre répertoire.\nVeuillez vérifier l'adresse du fichier" << std::endl;
    else {
        initialiserGraphe();
        std::string ligne ("");
        while (std::getline(File,ligne)) {  //Lecture ligne par ligne dans le fichier jusqu'à la fin du fichier
            if (ligne[0] == 'p') {
                std::vector<std::string> tabMot (chaineToTable(ligne));         //Ceci contient l'ensemble des mots sur la ligne courant
                _nbSommet = static_cast<unsigned short>(std::stoi(tabMot[2]));  //Attention tabMot[0] = 'p', tabMot[1] = 'edge', ...
                _nbArete =  static_cast<unsigned short>(std::stoi(tabMot[3]));
                for (unsigned int i(1); i <= _nbSommet; ++i)
                    _ensSommet.push_back(Sommet(i));
                //Initialisation de l'ensemble des sommets du graphe V = {1,2,...,n}
            }
            if (ligne[0] == 'e') {
                std::vector<std::string> tabMot (chaineToTable(ligne));
                unsigned int s1 (static_cast<unsigned int>(std::stoi(tabMot[1])));
                unsigned int s2 (static_cast<unsigned int>(std::stoi(tabMot[2])));
                ajouterArete(s1,s2);        //On recupere les identifiants des sommets et on ajoute une arête entre les sommets
            }
        }
    }
    File.close(); //Pas nécessaire mais je le fais cas même (Question d'habitude, même si maintenant elle le fichier se referme tout seul)
}

/*____________________QUESTION 2____________________*/
unsigned int  Graphe::coloriage() {
    unsigned int nbCouleur(0);
    for (auto const & sommetCourant : _ensSommet) {
        for (auto const & idVoisin: sommetCourant.getVoisin()){
            auto voisin = rechercheSommet(idVoisin);                //On recupere à l'aide d'un pointeur, un par un les voisins du sommetCourant afin d'appliquer des modifications en parallele
            if (sommetCourant.getCouleur() == voisin->getCouleur()){
                voisin->elimineCouleur(sommetCourant.getCouleur()); //On elimine la possibilité d'avoir la même couleur entre 2 sommets voisins en eliminant dans la liste des couleurs utilisables par le sommet courant, la couleur utilisée par le voisin sommetCourant
                voisin->setCouleur(voisin->couleurDispo());         //On lui affecte la première couleur disponible parmi la liste de ses couleurs utilisables
                nbCouleur = ((nbChromatique(voisin->getCouleur()) > nbCouleur) ? nbChromatique(voisin->getCouleur()) : nbCouleur);
            }
        }
    }
    return nbCouleur;
}

unsigned int Graphe::nbChromatique(Couleur c) const {
    /*
     * CETTE METHODE NOUS PERMET DE SAVOIR QUEL EST LE NOMBRE CHROMATIQUE DE NOTRE
     * GRAPHE, CAR SI NOUS AVONS UN SOMMET AVEC LA COULEUR JAUNE ALORS LE NOMBRE
     * CHROMATIQUE PASSE À 2. PAR CONTRE SI NOUS AVONS UN SOMMET DE COULEURS SUPERIEURE
     * ALORS LE NOMBRE CHROMATIQUE DEVIENT L'INDICE CORRESPONDANT À LA COULEUR EN QUESTION
     * EXEMPLE :
     *      ==> SI LA COULEUR D'UN SOMMET EST noir
     *      ==> ALORS LE NOMBRE CHROMATIQUE EST FORCEMENT = 6 DANS NOTRE GRAPHE
     * MAIS S'IL Y A UN SOMMET AYANT UNE COULEUR SUPÉRIEURE A noir (EXEMPLE rose)
     *      ==> LE NOMBRE CHROMATIQUE DU GRAPHE SERAIT = 10 CAR ON AURAIT UTILISÉ
     *          EXACTEMENT 10 COULEURS DIFFERENTS DANS NOTRE GRAPHES
     */
    switch (c) {
        case Couleur::vert: return 1;
        case Couleur::jaune: return 2;
        case Couleur::rouge: return 3;
        case Couleur::bleu: return 4;
        case Couleur::blanc: return 5;
        case Couleur::noir: return 6;
        case Couleur::orange: return 7;
        case Couleur::marron: return 8;
        case Couleur::violet: return 9;
        default: return 10;
    }
}

/*____________________QUESTION 3____________________*/
void Graphe::colorieSommet(std::ofstream &file, unsigned int id, Couleur c) {
    switch (c) {
        case Couleur::vert: file << "\t" << id << " [shape=circle, style=filled, color=green]\n"; break;
        case Couleur::jaune: file << "\t" << id << " [shape=circle, style=filled, color=yellow]\n"; break;
        case Couleur::rouge: file << "\t" << id << " [shape=circle, style=filled, color=red]\n"; break;
        case Couleur::bleu: file << "\t" << id << " [shape=circle, style=filled, color=blue]\n"; break;
        case Couleur::blanc: file << "\t" << id << " [shape=circle, style=filled, color=white]\n"; break;
        case Couleur::noir: file << "\t" << id << " [shape=circle, style=filled, color=black]\n"; break;
        case Couleur::orange: file << "\t" << id << " [shape=circle, style=filled, color=orange]\n"; break;
        case Couleur::marron: file << "\t" << id << " [shape=circle, style=filled, color=brown]\n"; break;
        case Couleur::violet: file << "\t" << id << " [shape=circle, style=filled, color=purple]\n"; break;
        default: file << "\t" << id << " [shape=circle, style=filled, color=pink]\n";
    }
}

void Graphe::ecriture(const std::string &nomFichierSortie) {
    /* A PARTIR DE LÀ, IL FAUT JUSTE RESPECTER LA SYNTAXE POUR GENERER UN FICHIER .dot C'EST TOUT
     *      \n   -->     correspond à un saut de ligne
     *      \t   -->     correspond à une tabulation (juste pour la representation, mais on peut s'en passer)
     */
    auto nbCouleur = coloriage();           //J'utilise ma méthode ici afin de pouvoir colorier mon graphe et retourner à la fin le nombre Chromatique (nombre de couleur minimum du graphe)
    std::ofstream File (nomFichierSortie.c_str());
    File << "digraph D {\n\trankdir=LR;\n\n";
    for (unsigned int i(1); i<=_nbSommet; ++i){
        auto s = rechercheSommet(i);
        colorieSommet(File,i,s->getCouleur());
    }
    File << "\n";   //Pour faire un sut de ligne entre les deux affichages
    for (unsigned int i(1); i<=_nbSommet; ++i)
        for (unsigned int j(i); j<=_nbSommet; ++j)   //On gere le cas le cas du graphe non orienté en faisant en sorte de parcours uniquement la diagonale (Donc il faut que 'j' soit en fonction de 'i'
            if (_ensSommet.at(i-1).estVoisin(_ensSommet.at(j-1))){
                File << "\t" << i << " -> " << j << " [arrowhead=none]\n";
            }
    File << "}\n";
    File.close();
    std::string commande = "dot -Tpng " + nomFichierSortie + " -o " + nomFichierSortie + ".png";
    std::system(commande.c_str());
    std::cout << "_____Affichage du Fichier.dot généré______\n" << std::ifstream(nomFichierSortie.c_str()).rdbuf() << "\nLE NOMBRE CHROMATIQUE DE NOTRE GRAPHE : " << nbCouleur << "\n";
}

