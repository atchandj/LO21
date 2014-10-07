#include "include_all.h"

Categorie::Categorie(const Categorie& c)
{
    this->cat = c.CategorieToString();
}

Categorie& Categorie::operator=(const Categorie& c)
{
    this->cat = c.CategorieToString();
    return *this;
}
