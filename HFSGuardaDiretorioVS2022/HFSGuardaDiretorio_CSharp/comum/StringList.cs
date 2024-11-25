/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 03/07/2015
 * Time: 15:19
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of StringList.
	/// </summary>
	public class StringList : List<string>
	{
		public StringList()
		{
		}
		
		public StringList(int capacidadeInicial)
		{
			this.Capacity = capacidadeInicial;
		}
		
	    public StringList(string str, char separador) {	        
	
	        if (str.IndexOf(separador) > 0) {
	            char[] partes = str.ToCharArray();
	            string pedaco = "";
	            for (int i = 0; i < partes.Length; i++) {
	                pedaco += partes[i];
	                if (partes[i] == separador) {
	                    base.Add(pedaco.Substring(0, pedaco.Length - 1));
	                    pedaco = "";
	                }
	            }
	            base.Add(pedaco);
	        }
	    }
		
	    public StringList(string texto) {  
	        string[] pedacos = texto.Split('\n');
	        base.AddRange(pedacos);
	    }
		
	    public string getText() {
	        string ret = "";
	
	        for (int i = 0; i < base.Count; i++) {
	        	ret += this[i];
	        }
	
	        return ret;
	    }
	
		public void LoadFromFile(string arquivo){
			FileStream fileStream = null;     
			StreamReader reader = null;
        	String linha;
        	
			try {        
				fileStream = new FileStream(arquivo, 
					FileMode.Open, FileAccess.Read);      
				reader = new StreamReader(fileStream);
				while ((linha = reader.ReadLine()) != null) {
		            this.Add(linha);
		        }
			} finally {
				if( reader != null ) 
					reader.Close();
			}			
		}
		
		public void SaveToFile(String arquivo){
			FileStream fileStream = null;     
			StreamWriter writer = null;        
			try {        
				fileStream = new FileStream(arquivo, 
					FileMode.OpenOrCreate, FileAccess.Write);      
				writer = new StreamWriter(fileStream);
				foreach (string linha in this) {
					writer.WriteLine(linha);      
					writer.Flush();
				}
			} finally {
				if( writer != null ) 
					writer.Close();
			}
		}
		
	}
}
