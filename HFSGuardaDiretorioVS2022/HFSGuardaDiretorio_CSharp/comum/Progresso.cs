/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 15:12
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of Progresso.
	/// </summary>
	public class Progresso
	{
	    private int minimo;	    
	    private int maximo;	    
	    private int posicao;	    
	    private int passo;	    
	    private string log;	    
		
		public Progresso()
		{
			this.log = "";
		}
		
		public int Minimo {
			get { return minimo; }
			set { minimo = value; }
		}
		
		public int Maximo {
			get { return maximo; }
			set { maximo = value; }
		}
		
		public int Posicao {
			get { return posicao; }
			set { posicao = value; }
		}
		
		public int Passo {
			get { return passo; }
			set { passo = value; }
		}
		
		public string Log {
			get { return log; }
			set { log = value; }
		}
		
	}
}
