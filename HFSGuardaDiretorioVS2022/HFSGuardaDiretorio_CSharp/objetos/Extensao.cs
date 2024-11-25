/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:58
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.objetos
{
	/// <summary>
	/// Description of Extensao.
	/// </summary>
	public class Extensao
	{
		private int codigo;
		private string nome;
		private int ordem;
		private byte[] bmp16;
		private byte[] bmp32;
		
		public Extensao()
		{
	        this.codigo = 0;
	        this.nome = "";
	        this.ordem = 0;
	        this.bmp16 = null;
	        this.bmp32 = null;			
		}
		
	    public Extensao(int codigo, String nome, int ordem,
	            byte[] bmp16, byte[] bmp32) {
	        this.codigo = codigo;
	        this.nome = nome;
	        this.ordem = ordem;
	        this.bmp16 = bmp16;
	        this.bmp32 = bmp32;
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

		public byte[] Bmp16 {
			get { return bmp16; }
			set { bmp16 = value; }
		}		
		
		public byte[] Bmp32 {
			get { return bmp32; }
			set { bmp32 = value; }
		}		
	}
}
