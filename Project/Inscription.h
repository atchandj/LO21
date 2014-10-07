#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include"uv.h"
#include"Semestre.h"
#include"UTProfiler.h"


/*!
 * \class Inscription
 * \brief Classe qui réprésente l'inscription à une UV
 */
class Inscription {
    UV* uv;
    Semestre semestre; //Semestre durant lequel on a fait l'uv
    Note resultat; //Note que l'on a eu à l'UV
    QString cursus; //Formation où on était au moment de faire l'uv
public:
    /*!
     * \brief Constructeur de la classe
     * \param u : UV à laquelle on s'inscrit
     * \param s :Semestre durant laquel on s'inscrit à l'UV
     * \param res : Résultat à l'UV
     */
    Inscription(UV& u, const Semestre& s,const QString& c, Note res=EC):uv(&u),semestre(s),resultat(res),cursus(c){}
    /*!
     * \brief Récupère l'UV à laquelle on s'est inscrit
     * \return Référence vers un objet de type UV
     */
    UV& getUV() const { return *uv; }
    /*!
     * \brief Récupère le semestre de l'inscription
     * \return Le semestre de l'inscription
     */
    Semestre getSemestre() const { return semestre; }
    /*!
     * \brief Récupère le semestre de le résultat à l'UV
     * \return Le résultat à l'UV
     */
    Note getResultat() const { return resultat; }
    /*!
     * \brief Récupère la formation suivi au moment où l'on s'est inscrit à l'UV
     * \return
     */
    QString getCursus() const { return cursus;}
    /*!
     * \brief Change les résultats à une UV
     * \param newres : Le nouveau résultat
     */
    void setResultat(Note newres) { resultat=newres; }
    /*!
     * \brief Surcharge de l'opérateur !=
     * \param i : inscription avec lequel on fais l'opération
     * \return un boléen
     */
    bool operator!=(const Inscription& i);
};

#endif // INSCRIPTION_H
