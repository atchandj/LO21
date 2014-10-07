#include "include_all.h"

#include <QDomDocument>
#include <QtXml>

void Formation::supprimerCategorie(const QString& cat)
{
    QMap<QString, unsigned int>::iterator it = Profil.find(cat);
    Profil.erase(it);
}

void Formation::supprimerFiliere(const QString& fil)
{
   QMap<QString, unsigned int>::iterator it = Filiere.find(fil);
    Filiere.erase(it);
}

