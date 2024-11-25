#ifndef VISAODAO_H
#define VISAODAO_H

#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::comum;

namespace hfsguardadir {

namespace objetosdao {

class VisaoDAO
{
private:
	VisaoDAO();
	VisaoDAO(VisaoDAO const&);
	VisaoDAO& operator=(VisaoDAO const&);
	static VisaoDAO* instancia;

	Glib::ustring sqlVisao(const Glib::ustring &visao);

public:
	static VisaoDAO* getInstancia();
	bool criarVisao(const Glib::ustring &visao);

};

}
}

#endif // VISAODAO_H

