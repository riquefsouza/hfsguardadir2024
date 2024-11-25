/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:51
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Aba.
	/// </summary>
	public class Aba
	{
		private int codigo;
		private string nome;
		private int ordem;

		public Aba()
		{
	        this.codigo = 0;
	        this.nome = "";
	        this.ordem = 0;
		}
		
	    public Aba(int codigo, string nome, int ordem) {
	        this.codigo = codigo;
	        this.nome = nome;
	        this.ordem = ordem;
	    }
		
		public int Codigo {
			get { return codigo; }
			set { codigo = value; }
		}				
		
		public string Nome {
			get { return nome; }
			set { nome = value; }
		}				
		
		public int Ordem {
			get { return ordem; }
			set { ordem = value; }
		}
			
	}
}
