/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:41
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Arquivo.
	/// </summary>
	public class Arquivo
	{
		private string nome;	
		private decimal tamanho;	
		private DateTime modificado;		
		private string atributos;
		
		public Arquivo()
		{
	        this.nome = "";
	        this.tamanho = 0;
	        this.modificado = DateTime.Now;
	        this.atributos = "";			
		}
		
	    public Arquivo(string nome, decimal tamanho, DateTime modificado, string atributos) {
	        this.nome = nome;
	        this.tamanho = tamanho;
	        this.modificado = modificado;
	        this.atributos = atributos;
	    }
		
		public string Nome {
			get { return nome; }
			set { nome = value; }
		}

		public decimal Tamanho {
			get { return tamanho; }
			set { tamanho = value; }
		}
		
		public DateTime Modificado {
			get { return modificado; }
			set { modificado = value; }
		}

		public string Atributos {
			get { return atributos; }
			set { atributos = value; }
		}
		
		
	}
}
