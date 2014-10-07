#include "include_all.h"

QTextStream& operator<<(QTextStream& f, const UV& uv){
    return f<<uv.getCode()<<", "<<uv.getCategorie().CategorieToString()<<", "<<uv.getNbCredits()<<" credits, "<<uv.getTitre();
}


bool UV::operator!=(const UV& u)
{
    return (code != u.getCode());
}
