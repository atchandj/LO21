#ifndef UTPROFILEREXCEPTION_H
#define UTPROFILEREXCEPTION_H

#include<Qstring>

class UTProfilerException{
public:
    /*!
     * \brief Constructeur de la classe
     * \param message : Message que l'on retournera lorsque l'exception sera déclenchée
     * \param f : fichier dans lequel cettte exception a été levée
     * \param l : ligne du fichier à laquelle cette exception a été levée
     */
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0):
        info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a été levée.
    /*!
     * \brief Retourne le fichier dans lequel cettte exception a été levée
     * \return nom du fichier
     */
    QString getFile() const { return file; }
    // retourne la ligne du fichier à laquelle cette exception a été levée.
    /*!
     * \brief Retourne la ligne du fichier à laquelle cette exception a été levée.
     * \return ligne du fichier
     */
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

#endif // UTPROFILEREXCEPTION_H
