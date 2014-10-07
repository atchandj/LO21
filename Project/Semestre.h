#ifndef SEMESTRE_H
#define SEMESTRE_H

#include"UTProfiler.h"
#include"utprofilerexception.h"

#include <QTextStream>
#include <QString>

/*!
 * \class Semestre
 * \brief Classe qui réprésente un semestre grâce à sa saison et l'année
 */
class Semestre {
    Saison saison;
    unsigned int annee; 
public:
    /*!
     * \brief Constructeur de la classe
     * \param s : Saison (Automne ou Printemps)
     * \param a : Année
     */
    Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
    /*!
     * \brief Nous donne la saison du semestre
     * \return La saison
     */
    Saison getSaison() const { return saison; }
    /*!
     * \brief Nous donne l'année du semestre
     * \return Un entier (année)
     */
    unsigned int getAnnee() const { return annee; }
    /*!
     * \brief Surcharge de l'opérateur ==
     * \param s : Semestre avec lequel on fais l'opération
     * \return un booléen
     */
    bool operator==(const Semestre& s);
    /*!
     * \brief Surcharge de l'opérateur !=
     * \param s : Semestre avec lequel on fais l'opération
     * \return un booléen
     */
    bool operator!=(const Semestre& s);
    /*!
     * \brief Transforme le semestre en chaine de caractères contractée ( exemple : Automne 2012 => A12)
     * \return La chaine de caractères contratée
     */
    QString FormeContracte();
};

/*!
 * \brief Surchage de l'opérator de flux <<
 * \param f : flux à retourner
 * \param s : Objet de type Semestre
 * \return Un flux
 */
inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }

#endif // SEMESTRE_H
