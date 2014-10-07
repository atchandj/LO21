#ifndef CATEGORIE_H
#define CATEGORIE_H

#include <QString>
/*!
 * \class Categorie
 * \brief Classe Catégorie qui réprensente la Catégorie d'une uv
 */
class Categorie
{
    QString cat; //nom de la catégorie
public:
    /*!
     * \brief Constructeur de la classe
     * \param c : nom/code de la catégorie
     */
    Categorie(const QString& c=""):cat(c){}
    /*!
     * \brief Constructeur de recopie
     * \param c : Objet de type Catégorie dont on doit copier les valeurs
     */
    Categorie(const Categorie& c);
    /*!
     * \brief Surcharge de l'opérateur d'affectation
     * \param c : Objet de type Catégorie dont on doit copier les valeurs
     * \return une réference sur Categorie
     */
    Categorie& operator=(const Categorie& c);
    /*!
     * \brief Méthode qui retourne le nom/code de la catégorie
     * \return une chaine de caractère
     */
    QString CategorieToString() const {return cat;}
    /*!
     * \brief Change la valeur de la variable cat, c'est à dire le nom de la catégorie
     * \param s : nouveau nom de la catégorie
     */
    void StringToCategorie(const QString& s){cat = s; }
    /*!
     * \brief Surchage de l'opérateur !=
     * \param c : Objet de type Catégorie avec qui on fais la comparaison
     * \return un booléen (true ou false)
     */
    bool operator!=(const Categorie& c)
    {
        return this->CategorieToString() != c.CategorieToString();
    }
};



#endif // CATEGORIE_H
