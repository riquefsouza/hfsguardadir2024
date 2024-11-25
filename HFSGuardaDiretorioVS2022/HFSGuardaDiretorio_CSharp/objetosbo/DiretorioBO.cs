/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 06/07/2015
 * Time: 16:17
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosdao;

namespace HFSGuardaDiretorio.objetosbo
{
	/// <summary>
	/// Description of DiretorioBO.
	/// </summary>
	public sealed class DiretorioBO
	{
		private static DiretorioBO instancia = new DiretorioBO();
		
	    public static readonly string SQL_CONSULTA_ARQUIVO = "select aba, cod, "
	            + "ordem, coddirpai, nome, tam, tipo, modificado, atributos, "
	            + "caminho, nomeaba, nomepai, caminhopai from consultaarquivo";	
		
		public static DiretorioBO Instancia {
			get {
				return instancia;
			}
		}
		
		private DiretorioBO()
		{
		}
		
		public List<Diretorio> carregarDiretorio(string sSQL, 
				IProgressoLog progressoLog)  {
			return DiretorioDAO.Instancia.consultarTudo(sSQL, "", 
					progressoLog);
		}
		
		public List<Diretorio> carregarDiretorio(string sSQL, 
				string sCondicaoTotal, IProgressoLog progressoLog) 
				 {
			return DiretorioDAO.Instancia.consultarTudo(sSQL, 
					sCondicaoTotal, progressoLog);
		}

		public string removerDrive(string sDiretorio) {
			string[] drives = Directory.GetLogicalDrives();
			int i = 0;
			bool bAchou = false;
			string sArq = Rotinas.testaNull(sDiretorio);

			if (sArq.Length > 0) {
				for (i = 0; i < drives.Length; i++) {
					if (sArq.ToUpper().Contains(
							drives[i].ToUpper())) {
						bAchou = true;
						break;
					}
				}
			}
			sArq = Rotinas.trocaSeparador(sArq);
			if (bAchou) {
				return sArq.Substring(drives[i].Length);
			} else {
				return sArq;
			}
		}

		private string arquivoAtributos(FileInfo arquivo, bool bDiretorio) {
			string sAtributos = "";
			
			if (bDiretorio)
				sAtributos += "[DIR]";
			else
				sAtributos += "[ARQ]";
			
			if (arquivo != null) {
							
				if (arquivo.Exists) {
					//if (arquivo.Attributes==FileAttributes.Archive) {}		
					if (arquivo.IsReadOnly) {
						sAtributos += "[ROL]";
					}
					if (arquivo.Attributes==FileAttributes.Hidden) {
						sAtributos += "[HID]";
					}
					if (arquivo.Attributes==FileAttributes.System) {
						sAtributos += "[SYS]";
					}
				} else {
					//if (arquivo.Directory.Attributes==FileAttributes.Directory) {}
					if (arquivo.Directory.Attributes==FileAttributes.Hidden) {
						sAtributos += "[HID]";
					}
					if (arquivo.Directory.Attributes==FileAttributes.System) {
						sAtributos += "[SYS]";
					}				
				}
			}
			return sAtributos;
		}

		private int retCodDirPai(int nAba, string sDiretorio,
				List<Diretorio> listaLocal) {
			foreach (Diretorio diretorio in listaLocal) {
				if (diretorio.Aba.Codigo == nAba) {
					if (diretorio.Caminho.Equals(sDiretorio)) {
						return diretorio.Ordem;
					}
				}
			}
			return 0;
		}

		public string MontaTamanho(decimal nTam) {
			decimal nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta;
			decimal nTamLocal;

			nUmKilo = 1024;
			nUmMega = nUmKilo * 1024;
			nUmGiga = nUmMega * 1024;
			nUmTera = nUmGiga * 1024;
			nUmPeta = nUmTera * 1024;

			if (nTam.CompareTo(nUmKilo) == -1) {
				nTamLocal = nTam;
				return Rotinas.FormatDecimal(nTamLocal) + " Byte(s)";
			} else if (nTam.CompareTo(nUmKilo) == 1 && nTam.CompareTo(nUmMega) == -1) {
				nTamLocal = nTam / nUmKilo;
				return Rotinas.FormatDecimal(nTamLocal) + " KByte(s)";
			} else if (nTam.CompareTo(nUmMega) == 1 && nTam.CompareTo(nUmGiga) == -1) {
				nTamLocal = nTam / nUmMega;
				return Rotinas.FormatDecimal(nTamLocal) + " MByte(s)";
			} else if (nTam.CompareTo(nUmGiga) == 1 && nTam.CompareTo(nUmTera) == -1) {
				nTamLocal = nTam / nUmGiga;
				return Rotinas.FormatDecimal(nTamLocal) + " GByte(s)";
			} else if (nTam.CompareTo(nUmTera) == 1 && nTam.CompareTo(nUmPeta) == -1) {
				nTamLocal = nTam / nUmTera;
				return Rotinas.FormatDecimal(nTamLocal) + " TByte(s)";
			} else {
				nTamLocal = nTam / nUmPeta;
				return Rotinas.FormatDecimal(nTamLocal) + " PByte(s)";
			}
		}

		public Diretorio atribuiDiretorio(int nAba, int nCodDirRaiz,
				string sNomeDirRaiz, string sDiretorio, bool bDiretorio,
				List<Diretorio> listaLocal, Arquivo arquivo,
				DiretorioOrdem dirOrdem) {
			int nOrdem = dirOrdem.Ordem;
			Diretorio diretorio;
			string sCaminho, sDir;
			FileInfo fCaminho = null;

			sCaminho = removerDrive(sDiretorio);
			if (sDiretorio.Length > 0){
				fCaminho = new FileInfo(sDiretorio);
			}

			if ((sCaminho.Length > 0) && (sNomeDirRaiz.Length > 0)) {
				if (Rotinas.StartsStr(sNomeDirRaiz, sCaminho)) {
					sCaminho = Rotinas.SubString(sCaminho, sNomeDirRaiz.Length+2, 
								sCaminho.Length);
					sDir = Rotinas.SubString(sDiretorio, sNomeDirRaiz.Length+2, 
								sDiretorio.Length);
					fCaminho = new FileInfo(sDir);
				} else {
					sCaminho = sNomeDirRaiz + Rotinas.BARRA_INVERTIDA + sCaminho;
					sDir = sNomeDirRaiz + Rotinas.BARRA_INVERTIDA + sDiretorio;
					fCaminho = new FileInfo(sDir);
				}
			}

			diretorio = new Diretorio();
			Aba abaLocal = new Aba();
			Tipo tipoLocal = new Tipo();

			abaLocal.Codigo = nAba;
			diretorio.Codigo = nCodDirRaiz;
			diretorio.Ordem = nOrdem;
			diretorio.Nome = arquivo.Nome;
			diretorio.Tamanho = arquivo.Tamanho;
			diretorio.Modificado = arquivo.Modificado;
			diretorio.Atributos = arquivoAtributos(fCaminho, bDiretorio);

			if (sDiretorio.Length == 0) {
				diretorio.Caminho = arquivo.Nome;
				diretorio.CaminhoPai = "";
			} else {
				diretorio.Caminho = sCaminho;
				diretorio.CaminhoPai = Rotinas.SubString(diretorio.Caminho, 1,
						Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA,
								diretorio.Caminho) - 1);
			}

			if (bDiretorio) {
				tipoLocal.Codigo = 'D';
				if (nOrdem == 1) {
					diretorio.CodDirPai = 0;
				} else {
					diretorio.CodDirPai = retCodDirPai(abaLocal.Codigo,
							diretorio.CaminhoPai, listaLocal);
				}
			} else {
				tipoLocal.Codigo = 'A';
				diretorio.CodDirPai = retCodDirPai(abaLocal.Codigo,
						diretorio.CaminhoPai, listaLocal);
			}
			abaLocal.Nome = "";
			diretorio.Aba = abaLocal;
			diretorio.NomePai = "";
			diretorio.TamanhoFormatado = MontaTamanho(diretorio.Tamanho);
			if (tipoLocal.Codigo == 'D') {
				tipoLocal.Nome = "Diretório";
			} else {
				tipoLocal.Nome = "Arquivo";
			}
			diretorio.Tipo = tipoLocal;			
			diretorio.ModificadoFormatado = Rotinas.formataDate(
					Rotinas.FORMATO_DATAHORA, diretorio.Modificado);
			diretorio.CaminhoOriginal = sDiretorio;

			nOrdem++;

			dirOrdem.Ordem = nOrdem;

			return diretorio;
		}

		private Arquivo dirPesquisadoToArquivo(FileInfo dirPesquisado) {
			Arquivo arquivo = new Arquivo();
			arquivo.Nome = dirPesquisado.Name;
			if (dirPesquisado.Exists)
				arquivo.Tamanho = dirPesquisado.Length;
			else
				arquivo.Tamanho = 0;
			arquivo.Modificado = dirPesquisado.LastWriteTime;
			arquivo.Atributos = arquivoAtributos(dirPesquisado, !dirPesquisado.Exists);
			return arquivo;
		}

		public void atribuiListaDiretorio(int nAba, int nCodDirRaiz,
				string sNomeDirRaiz, string sDiretorio, List<Diretorio> listaLocal,
				FileInfo dirPesquisado, DiretorioOrdem dirOrdem, IProgressoLog progressoLog) {
			Diretorio diretorio;
			Progresso pb = new Progresso();

			if (Rotinas.FileExists(sDiretorio)) {
				diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
						sDiretorio, false, listaLocal, dirPesquisadoToArquivo(dirPesquisado),
						dirOrdem);
				listaLocal.Add(diretorio);
				
				if (progressoLog != null) {
					pb.Log = sDiretorio;
					progressoLog.ProgressoLog(pb);
				}             
			} else if (Rotinas.DirectoryExists(sDiretorio)) {
				if ((!dirPesquisado.Name.Equals(".")) && (!dirPesquisado.Name.Equals(".."))) {
					diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
							sDiretorio, true, listaLocal, dirPesquisadoToArquivo(dirPesquisado),
							dirOrdem);
					listaLocal.Add(diretorio);

					if (progressoLog != null) {
						pb.Log = sDiretorio;
						progressoLog.ProgressoLog(pb);
					}

					ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio,
							listaLocal, dirOrdem, progressoLog);
				}
			}

		}

		public void ImportarDiretorio(int nAba, int nCodDirRaiz,
				string sNomeDirRaiz, string sDiretorio, List<Diretorio> listaLocal,
				DiretorioOrdem dirOrdem, IProgressoLog progressoLog) {
			FileInfo dirPesquisado;
			string sCaminho, sSeparador;

			if (Rotinas.SubString(sDiretorio,
					sDiretorio.Length, 1).Equals(Path.DirectorySeparatorChar)) {
				sSeparador = "";
			} else {
				sSeparador = Path.DirectorySeparatorChar.ToString();
			}

			sCaminho = sDiretorio + sSeparador;

			dirPesquisado = new FileInfo(sCaminho);
			if (dirPesquisado.Directory.Exists) {
				foreach (FileInfo dirPesquisado2 in Rotinas.listFiles(dirPesquisado.FullName)) {
					sCaminho = sDiretorio + sSeparador + dirPesquisado2.Name;
					atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz,
							sCaminho, listaLocal, dirPesquisado2, dirOrdem, 
							progressoLog);
				}
			}
		}

		public bool verificaCodDir(int nAba, string sDiretorio,
				List<Diretorio> listaLocal) {

			if (sDiretorio.Length > 0) {
				foreach (Diretorio diretorio in listaLocal) {
					if (diretorio.Aba.Codigo == nAba) {
						if (diretorio.Ordem == 1) {
							if (diretorio.CodDirPai == 0) {
								if (diretorio.Caminho.Equals(sDiretorio)) {
									return true;
								}
							}
						}
					}
				}
			}
			return false;
		}

		public int retMaxCodDir(int nAba, List<Diretorio> listaLocal) {
			int nMaior = -1;

			foreach (Diretorio diretorio in listaLocal) {
				if (diretorio.Aba.Codigo == nAba) {
					if (diretorio.Codigo > nMaior) {
						nMaior = diretorio.Codigo;
					}
				}
			}
			return nMaior + 1;
		}

		private string diretorioToSQL(Diretorio diretorio, bool bInsert) {
			string sSQL = "";

			if (bInsert) {
				sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, "
						+ "tam, tipo, modificado, atributos, caminho) values(";
			}

			sSQL += diretorio.Aba.Codigo + ",";
			sSQL += diretorio.Codigo + ",";
			sSQL += diretorio.Ordem + ",";
			sSQL += diretorio.CodDirPai + ",";
			sSQL += Rotinas.QuotedStr(diretorio.Nome) + ",";
			sSQL += diretorio.Tamanho + ",";
			sSQL += Rotinas.QuotedStr(diretorio.Tipo.Codigo) + ",";
			sSQL += Rotinas.QuotedStr(diretorio.ModificadoFormatado) + ",";
			sSQL += Rotinas.QuotedStr(diretorio.Atributos) + ",";
			sSQL += Rotinas.QuotedStr(diretorio.Caminho);

			if (bInsert) {
				sSQL += ")";
			}

			return sSQL;
		}

		public void salvarDiretorio(List<Diretorio> listaDiretorio,
				IProgressoLog progressoLog)  {
			Diretorio diretorio;
			Progresso pb = new Progresso();
			pb.Minimo = 0;
			pb.Maximo = listaDiretorio.Count - 1;
			pb.Posicao = 0;
			pb.Passo = 1;

			try {							
				for (int i = 0; i < listaDiretorio.Count; i++) {
					diretorio = listaDiretorio[i];
	
					DiretorioDAO.Instancia.incluir(diretorio);
					pb.Log = (i + 1) + " - Salvando Diretório: "
							+ diretorio.Caminho;
	
					pb.Posicao = i;
	
					if (progressoLog != null) {
						progressoLog.ProgressoLog(pb);
					}
				}
			} catch (Exception) {				
				throw;
			}
				
		}

		public bool excluirDiretorio(Aba aba, string sCaminho) {
			return (DiretorioDAO.Instancia.excluir(aba, sCaminho) > 0);
		}

		public void excluirListaDiretorio(List<Diretorio> listaDiretorio,
				Aba aba, string sCaminho) {
			Diretorio diretorio;

			for (int i = listaDiretorio.Count - 1; i >= 0; i--) {
				diretorio = listaDiretorio[i];

				if (diretorio.Aba.Codigo == aba.Codigo) {
					if (sCaminho.Trim().Length > 0) {
						if (Rotinas.StartsStr(sCaminho, diretorio.Caminho)) {
							listaDiretorio.Remove(diretorio);
						}
					} else {
						listaDiretorio.Remove(diretorio);
					}
				}
			}

		}

		private string diretorioToCSV(Diretorio diretorio) {
			string sCSV;

			sCSV = "\"";

			sCSV += diretorio.Aba.Nome + "\";\"";
			sCSV += diretorio.Nome + "\";\"";
			sCSV += diretorio.Tamanho + "\";\"";
			sCSV += diretorio.TamanhoFormatado + "\";\"";
			sCSV += diretorio.Tipo.Nome + "\";\"";
			sCSV += diretorio.ModificadoFormatado + "\";\"";
			sCSV += diretorio.Atributos + "\";\"";
			sCSV += diretorio.Caminho + "\"";

			return sCSV;
		}

		private string diretorioToXML(Diretorio diretorio) {
			string sXML, sCR, sTAB, sTAB2;

			sTAB = "\t";
			sTAB2 = "\t\t";
			sCR = "\n";

			sXML = sTAB + "<arquivo>" + sCR;

			sXML += sTAB2 + "<aba>" + diretorio.Aba.Codigo
					+ "</aba>" + sCR;
			sXML += sTAB2 + "<nomeAba>" + diretorio.Aba.Nome
					+ "</nomeAba>" + sCR;
			sXML += sTAB2 + "<codigo>" + diretorio.Codigo
					+ "</codigo>" + sCR;
			sXML += sTAB2 + "<ordem>" + diretorio.Ordem
					+ "</ordem>" + sCR;
			sXML += sTAB2 + "<nome>" + diretorio.Nome + "</nome>" + sCR;
			sXML += sTAB2 + "<tamanho>" + diretorio.Tamanho
					+ "</tamanho>" + sCR;
			sXML += sTAB2 + "<tipo>" + diretorio.Tipo.Codigo
					+ "</tipo>" + sCR;
			sXML += sTAB2 + "<modificado>" + diretorio.ModificadoFormatado
					+ "</modificado>" + sCR;
			sXML += sTAB2 + "<atributos>" + diretorio.Atributos
					+ "</atributos>" + sCR;
			sXML += sTAB2 + "<codDirPai>" + diretorio.CodDirPai
					+ "</codDirPai>" + sCR;
			sXML += sTAB2 + "<caminho>" + diretorio.Caminho
					+ "</caminho>" + sCR;

			sXML += sTAB + "</arquivo>";

			return sXML;
		}

		private string diretorioToTXT(Diretorio diretorio) {
			string sTXT, sTAB;

			sTAB = "\t";
			sTXT = "";
			sTXT += diretorio.Aba.Nome + sTAB;
			sTXT += diretorio.Nome + sTAB;
			sTXT += diretorio.Tamanho + sTAB;
			sTXT += diretorio.TamanhoFormatado + sTAB;
			sTXT += diretorio.Tipo.Nome + sTAB;
			sTXT += diretorio.ModificadoFormatado+ sTAB;
			sTXT += diretorio.Atributos+ sTAB;
			sTXT += diretorio.Caminho;

			return sTXT;
		}

		private string diretorioToHTML(Diretorio diretorio) {
			string sHTML, sCR, sTAB, sTAB2;

			sTAB = "\t";
			sTAB2 = "\t\t";
			sCR = "\n";

			sHTML = sTAB + "<tr>" + sCR;

			sHTML += sTAB2 + "<td>" + diretorio.Aba.Nome + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + diretorio.Nome + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + diretorio.Tamanho + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + Rotinas.StringReplaceAll(
					diretorio.TamanhoFormatado, " ", "&nbsp;") + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + diretorio.Tipo.Nome + "</td>" + sCR;
			sHTML += sTAB2 + "<td>"
					+ Rotinas.StringReplaceAll(diretorio.ModificadoFormatado,
							" ", "&nbsp;") + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + diretorio.Atributos + "</td>" + sCR;
			sHTML += sTAB2 + "<td>" + diretorio.Caminho + "</td>" + sCR;

			sHTML += sTAB + "</tr>";
			return sHTML;
		}

		public void exportarDiretorio(TipoExportar tipo, Aba aba,
				string sNomeArquivo, IProgressoLog progressoLog)
		{
			string sTexto = "", sCR, sTAB, sTAB2, sSQL, sCondicaoTotal;
			Aba abaLocal = new Aba();
			StringList listaLocal;
			List<Diretorio> listaDiretorio;

			sTAB = "\t";
			sTAB2 = "\t\t";
			sCR = "\n";

			sCondicaoTotal = " where aba=" + aba.Codigo;
			sSQL = SQL_CONSULTA_ARQUIVO + sCondicaoTotal + " order by 1, 2, 3";
			listaDiretorio = carregarDiretorio(sSQL, sCondicaoTotal, progressoLog);

			listaLocal = new StringList();

			switch (tipo) {
				case TipoExportar.teCSV: {
					sTexto = "\"Aba\";\"Nome\";\"TamanhoBytes\";\"Tamanho\";"
							+ "\"Tipo\";\"Modificado\";\"Atributos\";\"Caminho\"";
				}
				break;
				case TipoExportar.teHTML: {
					sTexto = "<!DOCTYPE html>" + sCR;
					sTexto += "<html>" + sCR;
					sTexto += "<body>" + sCR;
					sTexto += "<table border=\"1\" cellpadding=\"5\" cellspacing=\"0\">"
							+ sCR;
					sTexto += sTAB + "<tr>" + sCR;
					sTexto += sTAB2 + "<th>Aba</th>" + sCR;
					sTexto += sTAB2 + "<th>Nome</th>" + sCR;
					sTexto += sTAB2 + "<th>Tamanho</th>" + sCR;
					sTexto += sTAB2 + "<th>Tamanho Formatado</th>" + sCR;
					sTexto += sTAB2 + "<th>Tipo</th>" + sCR;
					sTexto += sTAB2 + "<th>Modificado</th>" + sCR;
					sTexto += sTAB2 + "<th>Atributos</th>" + sCR;
					sTexto += sTAB2 + "<th>Caminho</th>" + sCR;
					sTexto += sTAB + "</tr>";
				}
				break;
				case TipoExportar.teXML: {
					sTexto = "<diretorio>";
				}
				break;
				case TipoExportar.teSQL: {
					abaLocal.Codigo = listaDiretorio[0].Aba.Codigo;
					abaLocal.Nome = listaDiretorio[0].Aba.Nome;
					sTexto = AbaBO.Instancia.abaToSQL(abaLocal);
				}
				break;
			}
			
			if (sTexto.Length > 0){
				listaLocal.Add(sTexto);
			}

			foreach (Diretorio diretorio in listaDiretorio) {
				if (diretorio.Aba.Codigo == aba.Codigo) {
					if (tipo == TipoExportar.teTXT) {
						sTexto = diretorioToTXT(diretorio);
					} else if (tipo == TipoExportar.teCSV) {
						sTexto = diretorioToCSV(diretorio);
					} else if (tipo == TipoExportar.teHTML) {
						sTexto = diretorioToHTML(diretorio);
					} else if (tipo == TipoExportar.teXML) {
						sTexto = diretorioToXML(diretorio);
					} else if (tipo == TipoExportar.teSQL) {
						sTexto = diretorioToSQL(diretorio, true) + ";";
					}

					listaLocal.Add(sTexto);
				}
			}

			if (tipo == TipoExportar.teHTML) {
				sTexto += sCR + "</table>" + sCR;
				sTexto += "</body>" + sCR;
				sTexto += "</html>" + sCR;
			} else if (tipo == TipoExportar.teXML) {
				sTexto = "</diretorio>";
			}
			listaLocal.Add(sTexto);

			listaLocal.SaveToFile(sNomeArquivo);

			listaDiretorio.Clear();
			listaLocal.Clear();
		}

		public bool criarTabelaDiretorios()  {
			return (DiretorioDAO.Instancia.criarTabela() > 0);
		}

		private int XMLParaDiretorio(string sTexto, int nArquivo, 
				DiretorioXML diretorioXML) {
			string sTagInicio = "", sValor = "", sTagFim = "";
			int resultado;                

			resultado = nArquivo;

			if (Rotinas.Pos(">", sTexto) > 0) {
				sTagInicio = Rotinas.SubString(sTexto, 1, Rotinas.Pos(">", sTexto));
			}
			if ((Rotinas.Pos(">", sTexto) > 0) && (Rotinas.Pos("</", sTexto) > 1)) {
				sValor = Rotinas.SubString(sTexto, Rotinas.Pos(">", sTexto) + 1,
						Rotinas.Pos("</", sTexto) - Rotinas.Pos(">", sTexto) - 1);
			}
			if (Rotinas.LastDelimiter(">", sTexto) > 0) {
				sTagFim = Rotinas.SubString(sTexto,
						Rotinas.LastDelimiter("<", sTexto),
						Rotinas.LastDelimiter(">", sTexto));
			}

			if ((nArquivo == 1) && (!sTagInicio.Equals("<arquivo>"))) {
				resultado = -1;
			}
			if ((nArquivo == 2) && (!sTagInicio.Equals("<aba>"))
					&& (!sTagFim.Equals("</aba>"))) {
				// diretorio.aba.codigo = StrToInt(sValor);
				resultado = -1;
			}
			if ((nArquivo == 3) && (!sTagInicio.Equals("<nomeAba>"))
					&& (!sTagFim.Equals("</nomeAba>"))) {
				// diretorio.aba.nome = sValor;
				resultado = -1;
			}
			if ((nArquivo == 4) && (sTagInicio.Equals("<codigo>"))
					&& (sTagFim.Equals("</codigo>"))) {
				diretorioXML.Diretorio.Codigo =  Convert.ToInt32(sValor);
			}
			if ((nArquivo == 5) && (sTagInicio.Equals("<ordem>"))
					&& (sTagFim.Equals("</ordem>"))) {
				diretorioXML.Diretorio.Ordem = Convert.ToInt32(sValor);
			}
			if ((nArquivo == 6) && (sTagInicio.Equals("<nome>"))
					&& (sTagFim.Equals("</nome>"))) {
				diretorioXML.Diretorio.Nome = sValor;
			}
			if ((nArquivo == 7) && (sTagInicio.Equals("<tamanho>"))
					&& (sTagFim.Equals("</tamanho>"))) {
				diretorioXML.Diretorio.Tamanho = Convert.ToInt64(sValor);
			}
			if ((nArquivo == 8) && (sTagInicio.Equals("<tipo>"))
					&& (sTagFim.Equals("</tipo>"))) {
				Tipo tp = new Tipo();
				tp.Codigo = sValor[0];
				diretorioXML.Diretorio.Tipo = tp; 
			}
			if ((nArquivo == 9) && (sTagInicio.Equals("<modificado>"))
					&& (sTagFim.Equals("</modificado>"))) {
				diretorioXML.Diretorio.Modificado = 
						Rotinas.StringToDate(sValor);
			}
			if ((nArquivo == 10) && (sTagInicio.Equals("<atributos>"))
					&& (sTagFim.Equals("</atributos>"))) {
				diretorioXML.Diretorio.Atributos = sValor;
			}
			if ((nArquivo == 11) && (sTagInicio.Equals("<codDirPai>"))
					&& (sTagFim.Equals("</codDirPai>"))) {
				diretorioXML.Diretorio.CodDirPai = Convert.ToInt32(sValor);
			}
			if ((nArquivo == 12) && (sTagInicio.Equals("<caminho>"))
					&& (sTagFim.Equals("</caminho>"))) {
				diretorioXML.Diretorio.Caminho = sValor;
			}
			if ((nArquivo == 13) && (!sTagInicio.Equals("</arquivo>"))) {
				resultado = -1;
			}
			if (sTagInicio.Equals("</diretorio>")) {
				resultado = -3;
			}
			
			return resultado;
		}

		public int importarDiretorioViaXML(Aba aba, string sNomeArquivo,
				List<Diretorio> listaDirPai, 
				IProgressoLog progressoLog)  {
			string sTexto;
			int nArquivo, resultado;
			StringList listaLocal;
			DiretorioXML diretorioXML;
			List<Diretorio> listaDiretorio;        

			resultado = 0;
			diretorioXML = new DiretorioXML();        
			listaDiretorio = new List<Diretorio>();
			listaLocal = new StringList();
			listaLocal.LoadFromFile(sNomeArquivo);

			if (!listaLocal[0].Equals("<diretorio>")) {
				resultado = -1;
			} else {
				nArquivo = 0;
				foreach (string sTexto1 in listaLocal) {
					sTexto = sTexto1.Trim();
					
					nArquivo = XMLParaDiretorio(sTexto, nArquivo, diretorioXML);

					if (nArquivo == -1) {
						resultado = -1;
						break;
					} else if (nArquivo == 13) {
						nArquivo = 1;
						diretorioXML.Diretorio.Aba = aba;
						listaDiretorio.Add(diretorioXML.Diretorio);

						if (verificaCodDir(aba.Codigo, 
								diretorioXML.Diretorio.Caminho,
								listaDirPai)) {
							resultado = -2;
							break;
						}
						
						diretorioXML.Diretorio = new Diretorio();
					} else if (nArquivo == -3) {
						resultado = nArquivo;
					} else {
						nArquivo++;
					}
				}
			}

			salvarDiretorio(listaDiretorio, progressoLog);
			listaDiretorio.Clear();

			return resultado;
		}

		public bool carregarSubDiretorios(string sDiretorio,
				StringList listaLocal) {
			FileInfo dirPesquisado;
			string sCaminho, sSeparador;

			if (Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).
					Equals(Path.DirectorySeparatorChar)) {
				sSeparador = "";
			} else {
				sSeparador = Path.DirectorySeparatorChar.ToString();
			}

			sCaminho = sDiretorio + sSeparador;
			dirPesquisado = new FileInfo(sCaminho);
			if (dirPesquisado.Directory.Exists) {
				foreach (FileInfo dirPesquisado2 in Rotinas.listFiles(dirPesquisado.FullName)) {
					sCaminho = sDiretorio + sSeparador + dirPesquisado2.Name;

					if (dirPesquisado2.Directory.Exists) {
						if (Rotinas.DirectoryExists(sCaminho)) {
							if ((!dirPesquisado2.Name.Equals("."))
									&& (!dirPesquisado2.Name.Equals(".."))) {
								listaLocal.Add(sCaminho);
							}
						}
					}
				}
			}

			return (listaLocal.Count > 0);
		}

		public bool carregarArquivos(string sDiretorio, StringList listaLocal) {
			FileInfo dirPesquisado;
			string sCaminho, sSeparador;

			if (Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).
					Equals(Path.DirectorySeparatorChar)) {
				sSeparador = "";
			} else {
				sSeparador = Path.DirectorySeparatorChar.ToString();
			}

			sCaminho = sDiretorio + sSeparador;
			dirPesquisado = new FileInfo(sCaminho);
			if (dirPesquisado.Directory.Exists) {
				foreach (FileInfo dirPesquisado2 in Rotinas.listFiles(dirPesquisado.FullName)) {
					sCaminho = sDiretorio + sSeparador + dirPesquisado2.Name;

					if (dirPesquisado2.Exists) {
						if (Rotinas.FileExists(sCaminho)) {
							if ((!dirPesquisado.Name.Equals("."))
									&& (!dirPesquisado.Name.Equals(".."))) {
								listaLocal.Add(sCaminho);
							}
						}
					}
				}
			}

			return (listaLocal.Count > 0);
		}

		public bool carregarTodosArquivos(string sDiretorio,
				StringList listaLocal) {
			FileInfo dirPesquisado;
			string sCaminho, sSeparador;

			if (Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).
					Equals(Path.DirectorySeparatorChar)) {
				sSeparador = "";
			} else {
				sSeparador = Path.DirectorySeparatorChar.ToString();
			}

			sCaminho = sDiretorio + sSeparador;
			dirPesquisado = new FileInfo(sCaminho);
			if (dirPesquisado.Directory.Exists) {
				sCaminho = sDiretorio + sSeparador + dirPesquisado.Name;

				if (Rotinas.FileExists(sCaminho)) {
					listaLocal.Add(sCaminho);
				} else if (Rotinas.DirectoryExists(sCaminho)) {
					if ((!dirPesquisado.Name.Equals("."))
							&& (!dirPesquisado.Name.Equals(".."))) {
						carregarTodosArquivos(sCaminho, listaLocal);
					}
				}

				foreach (FileInfo dirPesquisado2 in Rotinas.listFiles(dirPesquisado.FullName)) {
					sCaminho = sDiretorio + sSeparador + dirPesquisado2.Name;

					if (Rotinas.FileExists(sCaminho)) {
						listaLocal.Add(sCaminho);
					} else if (Rotinas.DirectoryExists(sCaminho)) {
						if ((!dirPesquisado2.Name.Equals("."))
								&& (!dirPesquisado2.Name.Equals(".."))) {
							carregarTodosArquivos(sCaminho, listaLocal);
						}
					}
				}
			}
			return (listaLocal.Count > 0);
		}
		
		public List<Diretorio> itensFilhos(List<Diretorio> lista_pai,
				int aba, int codDirPai, int codigo) {
			List<Diretorio> lista = new List<Diretorio>();

			foreach (Diretorio diretorio in lista_pai) {
				if (diretorio.Aba.Codigo == aba) {
					if (diretorio.CodDirPai == codDirPai) {
						if (diretorio.Codigo == codigo) {
							lista.Add(diretorio);
						}
					}
				}
			}
			return lista;
		}
		
	}
}
