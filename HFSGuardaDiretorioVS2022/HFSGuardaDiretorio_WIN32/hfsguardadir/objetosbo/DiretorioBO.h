#ifndef DIRETORIOBO_H
#define DIRETORIOBO_H

#include "hfsguardadir/objetos/Diretorio.h"
#include "hfsguardadir/objetos/DiretorioOrdem.h"
#include "hfsguardadir/comum/Rotinas.h"
#include "hfsguardadir/comum/DiretorioXML.h"

extern const String DiretorioBO_SQL_CONSULTA_ARQUIVO;

ListaDiretorio DiretorioBO_carregarDiretorio(String sSQL,
								   IProgressoLog progressoLog);
ListaDiretorio DiretorioBO_carregarDiretorio(String sSQL,
								   String sCondicaoTotal,
								   IProgressoLog progressoLog);
String DiretorioBO_removerDrive(String sDiretorio);
//String DiretorioBO_arquivoAtributos(wxFileName &info);
int DiretorioBO_retCodDirPai(int nAba, String sDiretorio,
							  ListaDiretorio listaLocal);
Diretorio DiretorioBO_atribuiDiretorio(int nAba, int nCodDirRaiz,
		String sNomeDirRaiz, String sDiretorio, BOOL bDiretorio,
		ListaDiretorio listaLocal, Arquivo arquivo,
		DiretorioOrdem *dirOrdem);
//Arquivo DiretorioBO_wxFileNameToArquivo(wxFileName &info);
void DiretorioBO_atribuiListaDiretorio(int nAba, int nCodDirRaiz,
		String sNomeDirRaiz, String sDiretorio, ListaDiretorio *listaLocal,
		Arquivo info, DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
void DiretorioBO_ImportarDiretorio(int nAba, int nCodDirRaiz,
		String sNomeDirRaiz, String sDiretorio, ListaDiretorio *listaLocal,
		DiretorioOrdem *dirOrdem, IProgressoLog progressoLog);
BOOL DiretorioBO_verificaCodDir(int nAba, String sDiretorio,
		ListaDiretorio listaLocal);
int DiretorioBO_retMaxCodDir(int nAba, ListaDiretorio listaLocal);
String DiretorioBO_diretorioToSQL(Diretorio diretorio, BOOL bInsert);
void DiretorioBO_salvarDiretorio(ListaDiretorio listaDiretorio,
		IProgressoLog progressoLog);
BOOL DiretorioBO_excluirDiretorio(Aba aba, String sCaminho);
void DiretorioBO_excluirListaDiretorio(ListaDiretorio *listaDiretorio,
		Aba aba, String sCaminho);
void DiretorioBO_exportarDiretorio(TipoExportar tipo, Aba aba,
		String sNomeArquivo, IProgressoLog progressoLog);
BOOL DiretorioBO_criarTabelaDiretorios();
int DiretorioBO_XMLParaDiretorio(String sTexto, int nArquivo,
		DiretorioXML *diretorioXML);
int DiretorioBO_importarDiretorioViaXML(Aba aba, String sNomeArquivo,
		ListaDiretorio listaDirPai,
		IProgressoLog progressoLog);
BOOL DiretorioBO_carregarSubDiretorios(String sDiretorio,
		ListaString listaLocal);
BOOL DiretorioBO_carregarArquivos(String sDiretorio,
		ListaString listaLocal);
BOOL DiretorioBO_carregarTodosArquivos(String sDiretorio,
		ListaString listaLocal);
ListaDiretorio DiretorioBO_itensFilhos(ListaDiretorio lista_pai,
		int aba, int codDirPai, int codigo);
		
String DiretorioBO_diretorioToCSV(Diretorio diretorio);
String DiretorioBO_diretorioToXML(Diretorio diretorio);
String DiretorioBO_diretorioToTXT(Diretorio diretorio);
String DiretorioBO_diretorioToHTML(Diretorio diretorio);

#endif
