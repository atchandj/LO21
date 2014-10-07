#include "include_all.h"


bool Semestre::operator==(const Semestre& s)
{
    return (annee == s.getAnnee() && saison ==s.getSaison());
}

bool Semestre::operator!=(const Semestre& s)
{
    return (annee != s.getAnnee() || saison !=s.getSaison());
}

QString Semestre::FormeContracte()
{
    QString semestre;
    if(saison == Automne)
        semestre = "A";
    else
        semestre = "P";
    semestre += QString::number(annee%100);
    return semestre;
}
