#ifndef VISAODAO_H
#define VISAODAO_H

#pragma once

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

	CString sqlVisao(const CString &visao);

public:
	static VisaoDAO* getInstancia();
	BOOL criarVisao(const CString &visao);

};

}
}

#endif // VISAODAO_H

