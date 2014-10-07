#ifndef CATEGORIEMANAGER_H
#define CATEGORIEMANAGER_H

#include <QList>
#include "include_all.h"
#include <QString>

/*!
 * \class CategorieManager
 * \brief Classe implémenter en singleton gérant toutes les catégories
 */
class CategorieManager{
    QList<Categorie*> code; //Liste des catégories
    QString file; //nom du fichier dont on a extrait les catégories
    /*!
     * \brief Trouvez une catégorie en fonction de son code/son nom
     * \param c : nom/code de la Catégorie à chercher
     * \return Pointeur vers un objet de type catégorie
     */
    Categorie* trouverCategorie(const QString& c);
    /*!
     * \brief Constructeur de la classe
     */
    CategorieManager():file(""){}
    /*!
     * \brief Destructeur de la classe
     */
    ~CategorieManager();
    friend struct Handler;
    /*!
     * \brief The Handler struct
     */
    struct Handler{
        CategorieManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
public :
    /*!
     * \brief Récupérer l'instance de CategorieManager
     */
    static CategorieManager& getInstance();
    /*!
     * \brief Libérer l'instance de CategorieManager
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
    void supprimerCategorie(const QString& f);
    /*!
     * \brief Modifie le nom/code d'une catégorie
     * \param f : nom/code de la catégorie à modifier
     * \param NewValue : nouvelle valeur de la catégorie
     */
    void modifierCategorie(const QString& f,const QString& NewValue);
    /*!
     * \brief Ajoute une catégorie
     * \param c : code/nom de la catégorie
     */
    void ajouterCategorie(const QString& c);
    /*!
     * \brief Trouve une catégorie en appellant la fonction trouverCatégorie()
     * \param code : code/nom de la catégorie à trouver
     * \return Référence constante sur la catégorie
     */
    const Categorie& getCategorie(const QString& code) const;
    /*!
     * \brief Trouve une catégorie en appellant la fonction trouverCatégorie()
     * \param code : code/nom de la catégorie à trouver
     * \return Référence sur la catégorie
     */
    Categorie& getCategorie(const QString& code);
    /*!
     * \brief Trouve une catégorie en fonction de i
     * \param i : position de la catégorie dans la liste
     * \return Une catégorie
     */
    Categorie getElement(int i){ return *code[i];}
    /*!
     * \brief Donne la taille de la liste
     * \return Un entier (taille de la liste)
     */
    int getTaille() {return code.size();}

};
#endif // CATEGORIEMANAGER_H
