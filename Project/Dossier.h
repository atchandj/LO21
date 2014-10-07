#ifndef DOSSIER_H
#define DOSSIER_H
#include <Inscription.h>

class Dossier
{
private :
    QList<Inscription*> inscriptions;
    QString file; //nom du fichier dont on a extrait les formations
    QString cursus;
    friend struct Handler;
    /*!
     * \brief The Handler struct
     */
    struct Handler{
        Dossier* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
    /*!
     * \brief Constructeur de la classe
     */
    Dossier();
    /*!
     * \brief Destructeur de la classe
     */
    ~Dossier();
    Inscription* trouverInscription(const QString& c);
public :
    /*!
     * \brief Récupérer l'instance de Dossier
     */
    static Dossier& getInstance();
    /*!
     * \brief Libérer l'instance de FormationManager
     */
    static void libererInstance();
    /*!
     * \brief Charge toutes les inscriptions à partir d'un fichier
     * \param f : nom du fichier à charger
     */
    void load(const QString& f);
    /*!
     * \brief Sauvegarde les inscriptions dansun fichier
     * \param f : nom du fichier dans lequel sauvegarder
     */
    void save(const QString& f);
    /*!
     * \brief Trouve une inscription en appellant la fonction trouverInscription()
     * \param code : code/nom de l'inscription à trouver
     * \return Référence constante sur la inscription
     */
    const Inscription& getInscription(const QString& code) const;
    /*!
     * \brief Trouve une inscription en appellant la fonction trouverInscription()
     * \param code : code/nom de l'a 'inscription à trouver
     * \return Référence sur la inscription
     */
    Inscription& getInscription(const QString& code);
    /*!
     * \brief Trouve une inscription en fonction de i
     * \param i : position de l'inscription dans la liste
     * \return Une inscription
     */
    Inscription getElement(int i){ return *inscriptions[i];}
    /*!
     * \brief Donne la taille de la liste
     * \return Un entier
     */
    int getTaille() {return inscriptions.size();}
    /*!
     * \brief Ajoute une inscription au dossier
     * \param uv : UV où l'on s'est inscrit
     * \param n : Note que l'on a reçu à l'UV
     * \param s : Semestre auquel on s'est inscrit à l'UV
     * \param c : Formation/cursus dans lequel on était lors de l'inscription à l'UV.
     */
    void ajouterInscription(UV& uv, Note n, Semestre& s, const QString& c);
    /*!
     * \brief Donne le nom du fichier où l'on a charger les données
     * \return Nom du fichier
     */
    QString getFile() const {return file;}
    /*!
     * \brief Supprime une inscription
     * \param i : inscription à supprimer
     */
    void supprimerInscription(const Inscription& i);
    /*!
     * \brief Regarde si le dossier est vide
     * \return un booléen (true si elle est vide et false sinon)
     */
    bool isEmpty();
    /*!
     * \brief Choisis le fichier où l'on sauvegardera les données
     * \param f : nom du fichier où l'on sauvegardera les données
     */
    void ChoisirFichier(const QString& f);
    /*!
     * \brief Change le cursus
     * \param c : cursus à changer
     */
    void setCursus(const QString& c) { cursus= c;}
    /*!
     * \brief Donne le cursus du dossier
     * \return Le cursus du dossier
     */
    QString getCursus() { return cursus;}
    /*!
     * \brief Donne la liste des crédits totals du dossier selon une formation donnée
     * \param c : Formation dont on veut récupérer les crédits gagnés
     * \return Un QMap avec avec des clefs de type QString et les valeurs de types unsigned int
     */
    QMap<QString,unsigned int> ListeProfil(const QString& c);
    /*!
     * \brief Liste des cursus suivi
     * \return Liste de QString
     */
    QStringList ListeCursus();
};

#endif // DOSSIER_H
