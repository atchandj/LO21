#include "include_all.h"

bool Inscription::operator!=(const Inscription& i)
{

    return (i.getUV() != *uv || semestre != i.getSemestre());
}
