#ifndef UVMANAGER_H
#define UVMANAGER_H

#include <uv.h>
#include <QString>
#include <QList>

/*! \class UVManager
 * \brief Classe implémentée en singleton qui gère les UVs.
 * On utilisera le Design Patern Iterator pour pouvoir traverser tous les éléments de la liste des UVs.
 */
class UVManager {
private:
    QString file;
    UV** uvs;
    unsigned int nbUV; //Nombre d'UV dans le tableau uvs
    unsigned int nbMaxUV; //Taille du tableau uvs
    /*!
     *  \brief Ajoute un objet de type UV à la liste des UVs
     *  \param uv : UV à ajouter
     */
    void addItem(UV* uv);
    bool modification; //Savoir si il y a eu une modification ou Ajout d'UV
    QString path;
     //nom du fichier
    /*!
     *  \brief Trouvez une UV en fonction de son code
     *  \param c : Code de l'UV à trouver
     *  \return Pointeur sur l'UV trouvé si elle existe
     */
    UV* trouverUV(const QString& c) const;


    /*!
     *  \brief Constructeur de la classe UVManager
     */
    UVManager();
    /*!
     *  \brief Constructeur de recopie de la classe UVManager
     *  \param um : Attribut de type UVManager duquel on copiera les paramètres
     */
    UVManager(const UVManager& um);
    /*!
     *  \brief Surchage de l'operateur d'affectation
     *  \param um : Attribut de type UVManager duquel on copiera les paramètres
     */
    UVManager& operator=(const UVManager& um);
    /*!
     *  \brief Destructeur de la classe UVManager
     */
    ~UVManager();
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:
    /*!
     *  \brief Charge la liste des UVs à partir d'un fichier
     *  \param f : Nom du fichier
     */
    void load(const QString& f);
    /*!
     *  \brief Sauvegarde les UVs dans un fichier
     *  \param f : Nom du fichier
     */
    void save(const QString& f);
    UV** getUVs(){return uvs;}
    /*!
     *  \brief Récupérer l'instance d'UVManager
     */
    static UVManager& getInstance();
    /*!
     *  \brief Libérer l'instance d'UVManager
     */
    static void libererInstance();
    /*!
     *  \brief Ajoute une UV après avoir créer la variable de type UV et en appelant la fonction addItem()
     *  \param c : Code de l'UV
     *  \param t : Titre de l'UV
     *  \param nbc : Nombre de crédits
     *  \param cat : Catégorie de l'UV
     *  \param a : Booléen = True si l'UV est faites en Automne, False sinon
     *  \param b : Booléen = True si l'UV est faites au Printemps, False sinon
     */
    void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    /*!
     *  \brief Trouve une uv en appellant la fonction trouverUV()
     *  \param code : Code de l'UV à trouver
     *  \return Référence constante sur un objet de type UV
     */
    const UV& getUV(const QString& code) const;
    /*!
     *  \brief Trouve une uv en appellant la fonction trouverUV()
     *  \param code : Code de l'UV à trouver
     *  \return Référence sur un objet de type UV
     */
    UV& getUV(const QString& code);
    /*!
     *  \brief Accéder au nombre d'uvs
     *  \return Nombre d'uvs
     */
    unsigned int getNbUV() const{return nbUV;}
    /*!
     *  \brief Supprime une uv
     *  \param c : Code de l'UV à supprimer
     */
    void deleteUV(const QString& code);
    /*!
     *  \brief Accéder à path
     *  \return Retourne path
     */
    QString getPath() const {return path;}
    /*!
     *  \brief Définir le workspace et créer .ini avec path des xml
     */
    void setWorkspace();
    /*!
     *  \brief Teste si le fichier .ini existe
     *  \return Bool sur l'existence du fichier .ini
     */
    bool loadIni();
    /*!
     *  \brief Test l'existence des fichiers xml nécessaires
     *  \param path : chemin des fichiers testés
     *  \return Bool sur l'existence des xml
     */
    bool testPresenceFichiers(QString path);

    /*!
     * \class Iterator
     * \brief Permet de passer d'un élément d'UVManager à un autre
     */
    class iterator {
        UV** current;
        iterator(UV** u):current(u){}
        friend class UVManager;
    public:
        /*!
         * \brief Constructeur de la classe
         */
        iterator():current(0){}
        /*!
         * \brief Surcharge de l'opérateur * : retourne la valeur de current
         * \return une reférence à un objet de type UV
         */
        UV& operator*() const { return **current; }
        /*!
         * \brief Surcharge de l'opérateur !=
         * \param it : iterator avec lequel on fais la comparaison
         * \return un booléen (true : s'il est différent de it, false sinon)
         */
        bool operator!=(iterator it) const { return current!=it.current; }
        /*!
         * \brief Surcharge de l'opérateur ++ : Va au prochain élément de la variable current
         * \return l'iterator qui a appeler la fonction
         */
        iterator& operator++(){ ++current; return *this; }
    };
    /*!
     * \brief Crée un iterator qui pointe vers le debut de la variable uvs
     * \return un iterator
     */
    iterator begin() { return iterator(uvs); }
    /*!
     * \brief Créer un iterator qui pointe vers la fin de la variable uvs
     * \return un iterator
     */
    iterator end() { return iterator(uvs+nbUV); }
};

#endif // UVMANAGER_H
