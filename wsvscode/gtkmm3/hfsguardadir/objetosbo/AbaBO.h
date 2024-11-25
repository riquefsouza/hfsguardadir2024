#ifndef ABABO_H
#define ABABO_H

#include "hfsguardadir/objetos/Aba.h"
#include "hfsguardadir/comum/Rotinas.h"

using namespace hfsguardadir::objetos;
using namespace hfsguardadir::comum;

namespace hfsguardadir
{

	namespace objetosbo
	{

		class AbaBO
		{
		private:
			AbaBO();
			AbaBO(AbaBO const &);
			AbaBO &operator=(AbaBO const &);
			static AbaBO *instancia;

		public:
			static AbaBO *getInstancia();

			std::vector<Aba> carregarAba(IProgressoLog progressoLog);
			int retMaxCodAba(const std::vector<Aba> &listaLocal);
			Glib::ustring abaToSQL(Aba aba);
			bool incluirAba(Aba aba);
			bool alterarAba(Aba aba);
			bool excluirAba(Aba aba);
			bool criarTabelaAbas();
			Aba *pegaAbaPorOrdem(const std::vector<Aba> &lista, int ordem);
			Aba *getElemento(const std::vector<Aba> &lista, int codigo);
			Aba *pegaAbaPorNome(const std::vector<Aba> &lista, const Glib::ustring &nome);
		};

	}
}

#endif // ABABO_H
