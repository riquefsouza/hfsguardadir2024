/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:48
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Diretorio.
	/// </summary>
	/// 
	
	public class Diretorio: Arquivo
	{
		private Aba aba;		
		private	int codigo;
		private	int ordem;
		private int codDirPai;	
		private Tipo tipo;
		private string caminho;
		private string nomePai;		
		private string caminhoPai;
		private string tamanhoFormatado;
		private string modificadoFormatado;
		private string caminhoOriginal;
	
		public Diretorio()
		{
	        this.aba = new Aba();        
	        this.codigo = 0;
	        this.ordem = 0;
	        this.codDirPai = 0;
	        this.tipo = new Tipo();
	        this.caminho = "";
	        this.nomePai = "";
	        this.caminhoPai = "";
	        this.tamanhoFormatado = "";
	        this.modificadoFormatado = "";
	        this.caminhoOriginal = "";	        
		}
		
		public Aba Aba {
			get { return aba; }
			set { aba = value; }
		}
				
		public int Codigo {
			get { return codigo; }
			set { codigo = value; }
		}
		
		public int Ordem {
			get { return ordem; }
			set { ordem = value; }
		}
		
		public int CodDirPai {
			get { return codDirPai; }
			set { codDirPai = value; }
		}
		
		public Tipo Tipo {
			get { return tipo; }
			set { tipo = value; }
		}		
		
		public string Caminho {
			get { return caminho; }
			set { caminho = value; }
		}		
		
		public string NomePai {
			get { return nomePai; }
			set { nomePai = value; }
		}		
		
		public string CaminhoPai {
			get { return caminhoPai; }
			set { caminhoPai = value; }
		}		
				
		public string TamanhoFormatado {
			get { return tamanhoFormatado; }
			set { tamanhoFormatado = value; }
		}
		
		public string ModificadoFormatado {
			get { return modificadoFormatado; }
			set { modificadoFormatado = value; }
		}
		
		public string CaminhoOriginal {
			get { return caminhoOriginal; }
			set { caminhoOriginal = value; }
		}
	}
}
