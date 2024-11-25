#ifndef ROTULORAIZ_H
#define ROTULORAIZ_H

#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX (std::numeric_limits<ptrdiff_t>::max())
#endif

#include <glibmm/ustring.h>

namespace hfsguardadir {

namespace catalogador {

class RotuloRaiz
{
private:
    Glib::ustring rotulo;

public:
    RotuloRaiz();
    Glib::ustring getRotulo();
    void setRotulo(const Glib::ustring &rotulo);
};

}
}

#endif // ROTULORAIZ_H
