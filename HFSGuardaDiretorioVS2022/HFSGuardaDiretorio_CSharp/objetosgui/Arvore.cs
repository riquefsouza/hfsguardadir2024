/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/07/2015
 * Time: 10:51
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Windows.Forms;

namespace HFSGuardaDiretorio.objetosgui
{
	/// <summary>
	/// Description of Arvore.
	/// </summary>
	public sealed class Arvore
	{
		private static Arvore instancia = new Arvore();
		
		public static Arvore Instancia {
			get {
				return instancia;
			}
		}
		
		private Arvore()
		{
		}

		public TreeNode encontrarCaminhoPorNome(TreeView tvArvore, string[] nomes) {		
			foreach (TreeNode item in tvArvore.Nodes) {
				if (item.Text.Equals(nomes[0])) {
					return encontrarCaminho(item, nomes, 0);
				}
			}
			return null;
		}
		
		public TreeNode encontrarCaminho(TreeNode pai, string[] nomes, int nivel) {
			if (pai.Text.Equals(nomes[nivel])) {
	    		
				if (nivel == (nomes.Length - 1)) {
					return pai;
				}
	    	
				if (pai.GetNodeCount(true) > 0) {
		    		foreach (TreeNode filho in pai.Nodes) {
	    				TreeNode res = encontrarCaminho(filho, nomes, nivel + 1);
	    				
	    				if (res != null){
	    					return res;
	    				}
		    		}
		    	}
			}
   			return null;
		}

	}
}
