#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#include <wx/string.h>

namespace hfsguardadir {

namespace catalogador {

class RotuloRaiz
{
private:
    wxString rotulo;

public:
    RotuloRaiz();
    wxString getRotulo();
    void setRotulo(const wxString &rotulo);
};

}
}

#endif // ROTULORAIZ_H
