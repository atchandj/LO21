#ifndef FORMATIONMANAGER_H
#define FORMATIONMANAGER_H

#include "Formation.h"
#include <QList>


/*!
 * \class FormationManager
 * \brief Classe implémenter en singleton gérant toutes les catégories
 */
class FormationManager{

    QList<Formation*> liste; //Liste des formations
    QString file; //nom du fichier dont on a extrait les formations
    /*!
     * \brief Trouvez une catégorie en fonction de son liste/son nom
     * \param c : nom/liste de la Catégorie à chercher
     * \return Ppointeur vers un objet de type catégorie
     */
    Formation* trouverFormation(const QString& c);
    /*!
     * \brief Constructeur de la classe
     */
    FormationManager():file(""){}
    /*!
     * \brief Destructeur de la classe
     */
    ~FormationManager();
    friend struct Handler;
    /*!
     * \brief The Handler struct
     */
    struct Handler{
        FormationManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public :
    /*!
     * \brief Récupérer l'instance de FormationManager
     */
    static FormationManager& getInstance();
    /*!
     * \brief Libérer l'instance de FormationManager
     */
    static void libererInstance();
    /*!
     * \brief Charge toutes les catégories à partir d'un fichier
     * \param f : nom du fichier à charger
     */
    void load(const QString& f);
    /*!
     * \brief Sauvegarde les catégories dansun fichier
     * \param f : nom du fichier dans lequel sauvegarder
     */
    void save(const QString& f);
    /*!
     * \brief Supprimer une catégorie
     * \param f : nom de lacatégorie à supprimer
     */
    void supprimerFormation(const QString& f);
    /*!
     * \brief Modifie le nom/ liste d'une catégorie
     * \param f : nom/liste de la catégorie à modifier
     * \param NewValue : nouvelle valeur de la catégorie
     */
    void modifierFormation(const QString& f,const QString& NewValue);
    /*!
     * \brief Ajoute une catégorie
     * \param c : liste/nom de la catégorie
     */
    void ajouterFormation(const QString& c,QMap<QString, unsigned int> P,QMap<QString, unsigned int> F);
    /*!
     * \brief Trouve une catégorie en appellant la fonction trouverCatégorie()
     * \param liste : liste/nom de la catégorie à trouver
     * \return Référence constante sur la catégorie
     */
    const Formation& getFormation(const QString& liste) const;
    /*!
     * \brief Trouve une catégorie en appellant la fonction trouverCatégorie()
     * \param liste : liste/nom de la catégorie à trouver
     * \return Référence sur la catégorie
     */
    Formation& getFormation(const QString& liste);
    /*!
     * \brief Trouve une catégorie en fonction de i
     * \param i : position de la catégorie dans la liste
     * \return Une catégorie
     */
    Formation& getElement(int i){ return *liste[i];}
    /*!
     * \brief Donne la taille de la liste
     * \return Un entier
     */
    int getTaille() {return liste.size();}
    /*!
     * \brief Donne la liste de toutes les formations
     * \return QList<Formation*>*
     */
    QList<Formation*>* getFormations(){return &liste;}
    /*!
     * \brief Permet de savoir si pour une pour formation donnée, le nombre de crédit requis pour la catégorie à été atteint
     * \param formation : Formation dont on veut le nombre de crédit pour une catégorie
     * \param cat : catégorie dont on veut savoir si le nombre de crédit minimale à été atteint
     * \param nbc : nombre de crédit que l'on veut comparer
     * \return un booléen
     */
    bool isFinished(const QString& formation,const QString cat, unsigned int nbc);

};

#endif // FORMATIONMANAGER_H
