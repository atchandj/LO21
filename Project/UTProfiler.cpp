#include "include_all.h"

Saison StringToSaison(const QString& str)
{
    if(str == "Automne") return Automne;
    else
    if(str == "Printemps") return Printemps;
    else
        throw UTProfilerException("Erreur ! Saison "+ str +" inexistante");
}

QString SaisonToString(const Saison s)
{
    if(s == Automne) return "Automne";
    else
    if(s == Printemps) return "Printemps";
    else
        throw UTProfilerException("Erreur ! Saison non traitée !");
}

Note StringToNote(const QString& n)
{
    if(n == "A") return A;
    else
    if(n == "B" ) return B;
    else
    if(n == "C") return C;
    else
    if(n == "D") return D;
    else
    if(n == "E") return E;
    else
    if(n == "F") return F;
    else
    if(n == "FX") return FX;
    else
    if( n == "RES") return RES;
    else
    if( n == "ABS") return ABS;
    else
    if(n == "EC") return EC;
    else
        throw UTProfilerException("Erreur ! Note "+ n +" inexistante");

}

QString NoteToString(const Note n)
{
    switch(n)
    {
        case A : return "A";
                    break;
        case B : return "B";
                    break;
        case C : return "C";
                    break;
        case D : return "D";
                    break;
        case E : return "E";
                    break;
        case F : return "F";
                    break;
        case FX : return "FX";
                    break;
        case RES : return "A";
                    break;
        case ABS : return "ABS";
                    break;
        case EC : return "EC";
                    break;
        default : throw UTProfilerException("Erreur ! Note non traité !");
    }
}


