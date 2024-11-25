#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#include "../objetos/Diretorio.h"
#include "../objetos/DiretorioOrdem.h"
#include "../comum/Rotinas.h"
#include "../comum/DiretorioXML.h"

GString *DiretorioBO_sqlConsultaArquivo();
ListaDiretorio DiretorioBO_carregarDiretorio(GString *sSQL,
								   GString *sCondicaoTotal,
								   IProgressoLog progressoLog);
GString* DiretorioBO_removerDrive(GString *sDiretorio);
int DiretorioBO_retCodDirPai(int nAba, GString *sDiretorio,
							  ListaDiretorio listaLocal);
Diretorio DiretorioBO_atribuiDiretorio(int nAba, int nCodDirRaiz,
		GString *sNomeDirRaiz, GString *sDiretorio, gboolean bDiretorio,
		ListaDiretorio listaLocal, Arquivo arquivo,
		DiretorioOrdem *dirOrdem);
void DiretorioBO_atribuiListaDiretorio(int nAba, int nCodDirRaiz,
		GString *sNomeDirRaiz, GString *sDiretorio, ListaDiretorio *listaLocal,
		Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
void DiretorioBO_ImportarDiretorio(int nAba, int nCodDirRaiz,
		GString *sNomeDirRaiz, GString *sDiretorio, ListaDiretorio *listaLocal,
		DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
gboolean DiretorioBO_verificaCodDir(int nAba, GString *sDiretorio,
		ListaDiretorio listaLocal);
int DiretorioBO_retMaxCodDir(int nAba, ListaDiretorio listaLocal);
GString* DiretorioBO_diretorioToSQL(Diretorio diretorio, gboolean bInsert);
void DiretorioBO_salvarDiretorio(ListaDiretorio listaDiretorio,
		IProgressoLog progressoLog);
gboolean DiretorioBO_excluirDiretorio(Aba aba, GString *sCaminho);
void DiretorioBO_excluirListaDiretorio(ListaDiretorio *listaDiretorio,
		Aba aba, GString *sCaminho);
void DiretorioBO_exportarDiretorio(TipoExportar tipo, Aba aba,
		GString *sNomeArquivo, IProgressoLog progressoLog);
gboolean DiretorioBO_criarTabelaDiretorios();
int DiretorioBO_XMLParaDiretorio(GString *sTexto, int nArquivo,
		DiretorioXML *diretorioXML);
int DiretorioBO_importarDiretorioViaXML(Aba aba, GString *sNomeArquivo,
		ListaDiretorio listaDirPai,
		IProgressoLog progressoLog);
gboolean DiretorioBO_carregarSubDiretorios(GString *sDiretorio,
		ListaString listaLocal);
gboolean DiretorioBO_carregarArquivos(GString *sDiretorio,
		ListaString listaLocal);
gboolean DiretorioBO_carregarTodosArquivos(GString *sDiretorio,
		ListaString listaLocal);
ListaDiretorio DiretorioBO_itensFilhos(ListaDiretorio lista_pai,
		int aba, int codDirPai, int codigo);

GString* DiretorioBO_diretorioToCSV(Diretorio diretorio);
GString* DiretorioBO_diretorioToXML(Diretorio diretorio);
GString* DiretorioBO_diretorioToTXT(Diretorio diretorio);
GString* DiretorioBO_diretorioToHTML(Diretorio diretorio);

#endif
