#ifndef FORMATION_H
#define FORMATION_H

#include <QList>
#include <QMap>
#include <QString>

#include <QDomDocument>

//doxygen a verifier

/*!
 * \class Formation
 * \brief Classe Formation avec son profil (nombre de crédits par catégories) et un ensemble de filière (si elles existent)
 */
class Formation
{
    QString code_formation;
    QMap<QString, unsigned int> Profil;
    QMap<QString, unsigned int> Filiere; // Peut-être Null et dans ce cas, il n'y a pas de filière
public:
    /*!
     * \brief Constructeur de la classe formation
     * \param code : code de la formation
     * \param p : Profil minimal qu'il faut obtenir pour achever la formation
     * \param f : Ensemble des filières de la formation
     */
    Formation(const QString code,QMap<QString, unsigned int>p,QMap<QString,unsigned int> f):code_formation(code),Profil(p),Filiere(f){}
    /*!
     * \brief Retourne le code de la formation
     * \return code de la formation
     */
    QString getCode() const {return code_formation;}
    /*!
     * \brief Retourne le nombre de crédits minnimal à obtenir dans une catégorie
     * \param p : catégorie dont on veut obtenir le nombre de crédit à obtenir
     * \return nombre de crédits minimal à obtenir
     */
    unsigned int getProfil(const QString& p) const{return Profil[p];}
    /*!
     * \brief Retourne l'ensemble du profil
     * \return Un QMap avec avec des clefs de type QString et les valeurs de types unsigned int
     */
    QMap<QString, unsigned int> getAllProfil() const{return Profil;}
    /*!
     * \brief Retourne le nombre de crédits minnimal à obtenir dans une filière
     * \param f : filière dont on veut obtenir le nombre de crédit à obtenir
     * \return nombre de crédits minimal à obtenir
     */
    unsigned int getFiliere(const QString& f) const{return Filiere[f];}
    /*!
     * \brief Retourne l'ensemble des filières
     * \return Un QMap avec avec des clefs de type QString et les valeurs de types unsigned int
     */
    QMap<QString, unsigned int> getAllFiliere() const{return Filiere;}
    /*!
     * \brief Modifie le code de la formation
     * \param c : nouveau code
     */
    void setCode(const QString& c) { code_formation = c; }
    /*!
     * \brief Retourne les clef du QMap Profil, c'est à dire toutes les catégories d'UV que l'on doit faire dans le cadre du profil
     * \return QList de chaine de caractères
     */
    QList<QString> ListeProfil() const{ return Profil.keys();}
    /*!
     * \brief Retourne les clef du QMap Profil, c'est à dire toutes les filières que l'on doit faire dans le cadre du profil
     * \return QList de chaine de caractères
     */
    QList<QString> ListeFiliere() const { return Filiere.keys();}
    /*!
     * \brief Retourne le nombre d'élément de la variable Profil
     * \return nombre d'éléement de Profil
     */
    unsigned int getTailleProfil() const {return Profil.size();}
    /*!
     * \brief Retourne le nombre d'élément de la variable Filiere
     * \return nombre d'éléement de Filiere
     */
    unsigned int getTailleFiliere() const{return Filiere.size();}
    /*!
     * \brief Aoute une categorie
     * \param cat : catégorie à ajouter
     * \param credit : crédits minimaux que l'on doit avoir pour cette catégorie
     */
    void ajouterCategorie(const QString& cat, unsigned int credit){Profil[cat] = credit;}
    /*!
     * \brief Ajoute une filiere
     * \param fil : filière à ajouter
     * \param credit : crédits minimaux que l'on doit avoir pour cette filière
     */
    void ajouterFiliere(const QString& fil, unsigned int credit){Filiere[fil] = credit;}
    /*!
     * \brief Supprime une categorie
     * \param cat : catégorie à supprimer
     */
    void supprimerCategorie(const QString& cat);
    /*!
     * \brief Supprime une filiere
     * \param fil : filière à supprimer
     */
    void supprimerFiliere(const QString& fil);
    /*!
     * \brief Regarde si le profil est vide ou non
     * \return un booléen (true si le profil est vide, false sinon)
     */
    bool isEmptyProfil() {return Profil.isEmpty();}
    /*!
     * \brief Regarde si la filière est vide ou non
     * \return un booléen (true si la filière est vide, false sinon)
     */
    bool isEmptyFiliere() {return Filiere.isEmpty();}
};


#endif // FORMATION_H
