#ifndef UV_H
#define UV_H

#include <UTProfiler.h>
#include "categorie.h"
#include <QString>
#include <QTextStream>

/*!
 * \class UV
 * \brief Réprésente une uv
 */
class UV {
    QString code;
    QString titre;
    unsigned int nbCredits;
    Categorie categorie;
    bool automne;
    bool printemps;
    /*!
     * \brief Surcharge de l'opérateur d'affectation =
     * \param u : Objet de type uv dont on recopie les valeurs
     * \return Référence sur une uv
     */
    UV& operator=(const UV& u);
    /*!
     * \brief Constructeur de recopie
     * \param u : uv dont on copie les paramêtres
     */
    UV(const UV& u);


    friend class UVManager;
public:
    /*!
     * \brief Constructeur de UV
     * \param c : code de l'uv
     * \param t : titre de l'uv
     * \param nbc : nombre de crédit que l'uv donne
     * \param cat : catégorie de l'u
     * \param a : booléen nous indiquant si l'uv est faite en automne ou non
     * \param p : booléen nous indiquant si l'uv est faite au printemps ou non
     */
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
    /*!
     * \brief Récupère le code de l'uv
     * \return Code de l'uv
     */
    QString getCode() const { return code; }
    /*!
     * \brief Récupère le titre de l'uv
     * \return Titre de l'uv
     */
    QString getTitre() const { return titre; }
    /*!
     * \brief Récupère le nombre de crédits
     * \return Nombre de crédits de l'uv
     */
    unsigned int getNbCredits() const { return nbCredits; }
    /*!
     * \brief Récupère la catégorie d'une uv
     * \return Catégorie d'une uv
     */
    Categorie getCategorie() const { return categorie; }
    /*!
     * \brief Récupère un booléen indiquant si l'uv est ouverte en automne ou non
     * \return Booléen indiquant si l'uv est ouverte en automne ou non
     */
    bool ouvertureAutomne() const { return automne; }
    /*!
     * \brief Récupère un booléen indiquant si l'uv est ouverte au printemps ou non
     * \return Booléen indiquant si l'uv est ouverte au printemps ou non
     */
    bool ouverturePrintemps() const { return printemps; }
    /*!
     * \brief Change le code de l'uv
     * \param c : nouveau code
     */
    void setCode(const QString& c) { code=c; }
    /*!
     * \brief Change titre de l'uv
     * \param t : nouveau titre
     */
    void setTitre(const QString& t) { titre=t; }
    /*!
     * \brief Change nombre de crédit de l'uv
     * \param n : nouveau nombre de crédits
     */
    void setNbCredits(unsigned int n) { nbCredits=n; }
    /*!
     * \brief Change la catégorie de l'uv
     * \param c : nouvelle catégorie
     */
    void setCategorie(Categorie c) { categorie=c; }
    /*!
     * \brief Change si l'uv est ouvert en automne
     * \param b : booléen
     */
    void setOuvertureAutomne(bool b) { automne=b; }
    /*!
     * \brief Change si l'uv est ouvert au printemps
     * \param b : booléen
     */
    void setOuverturePrintemps(bool b) { printemps=b; }
    /*!
     * \brief urcharge de l'opérateur !=
     * \param u : avec lequel on fais l'opération
     * \return un booléen
     */
    bool operator!=(const UV& u);
};

/*!
 * \brief Surcharge de l'opérateur de flux <<
 * \param f : flux à retourner
 * \param uv : Objet de type uv que l'on veut afficher
 * \return Un flux
 */
QTextStream& operator<<(QTextStream& f, const UV& uv);

#endif // UV_H
