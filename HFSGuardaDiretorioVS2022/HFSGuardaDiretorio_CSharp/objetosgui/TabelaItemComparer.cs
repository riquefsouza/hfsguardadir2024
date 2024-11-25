/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 09/07/2015
 * Time: 17:06
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections;
using System.Windows.Forms;

namespace HFSGuardaDiretorio.objetosgui
{
	/// <summary>
	/// Description of TabelaItemComparer.
	/// </summary>
	public class TabelaItemComparer: IComparer {
	    private int col;
	    private SortOrder ordem;

	    public TabelaItemComparer() {
	        col=0;
	        ordem = SortOrder.Ascending;
	    }

	    public TabelaItemComparer(int coluna, SortOrder ordem)
	    {
	        col=coluna;
	        this.ordem = ordem;
	    }

	    public int Compare(object x, object y)
	    {
	        int retornoVal = -1;
	        retornoVal = String.Compare(((ListViewItem)x).SubItems[col].Text,
	        	((ListViewItem)y).SubItems[col].Text);
			
	        if (ordem == SortOrder.Ascending) {
	            retornoVal *= -1;        
	        }
	        
	        return retornoVal;
	    }
	}
}
