/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 06/07/2015
 * Time: 14:53
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosdao;

namespace HFSGuardaDiretorio.objetosbo
{
	/// <summary>
	/// Description of AbaBO.
	/// </summary>
	public sealed class AbaBO
	{
		private static AbaBO instancia = new AbaBO();
		
		public static AbaBO Instancia {
			get {
				return instancia;
			}
		}
		
		private AbaBO()
		{
		}
		
		public List<Aba> carregarAba(IProgressoLog progressoLog) {
			return AbaDAO.Instancia.consultarTudo(progressoLog);
		}

		public int retMaxCodAba(List<Aba> listaLocal) {
			int nMaior = 0;
			foreach (Aba aba in listaLocal) {
				if (aba.Codigo > nMaior) {
					nMaior = aba.Codigo;
				}
			}
			return nMaior + 1;
		}

		public string abaToSQL(Aba aba) {
			return "insert into Abas(cod, nome) values(" + aba.Codigo + ","
					+ Rotinas.QuotedStr(aba.Nome) + ")";
		}

		public bool incluirAba(Aba aba) {
			return (AbaDAO.Instancia.incluir(aba) > 0);
		}

		public bool alterarAba(Aba aba) {
			return (AbaDAO.Instancia.alterar(aba) > 0);
		}

		public bool excluirAba(Aba aba) {
			return (AbaDAO.Instancia.excluir(aba.Codigo) > 0);
		}

		public bool criarTabelaAbas() {
			return (AbaDAO.Instancia.criarTabela() > 0);
		}

		public Aba pegaAbaPorOrdem(List<Aba> lista, int ordem) {
			foreach (Aba aba in lista) {
				if (aba.Ordem == ordem) {
					return aba;
				}
			}
			return null;
		}

		public Aba getElemento(List<Aba> lista, int codigo) {
			foreach (Aba elemento in lista) {
				if (elemento.Codigo == codigo) {
					return elemento;
				}
			}
			return null;
		}

		public Aba pegaAbaPorNome(List<Aba> lista, string nome) {
			foreach (Aba aba in lista) {
				if (aba.Nome.Equals(nome)) {
					return aba;
				}
			}
			return null;
		}
		
	}
}
