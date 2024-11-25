/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/07/2015
 * Time: 10:45
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Collections.Generic;
using System.Windows.Forms;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosbo;
	
namespace HFSGuardaDiretorio.objetosgui
{
	/// <summary>
	/// Description of Tabela.
	/// </summary>
	public sealed class Tabela
	{
		private static Tabela instancia = new Tabela();
		
		public static Tabela Instancia {
			get {
				return instancia;
			}
		}
		
		private Tabela()
		{
		}
		
		public void AdicionaItemLista(bool bTabelaDir, ListView lvTabela, Diretorio dir,
		                             List<Extensao> extensoes){
			ListViewItem item;
			
			item = lvTabela.Items.Add(dir.Nome);
			if (dir.Tipo.Codigo=='D'){
				item.SubItems.Add("");
				item.ImageIndex = 0;
			} else {
				item.SubItems.Add(dir.TamanhoFormatado);
				item.ImageIndex = ExtensaoBO.Instancia.indiceExtensao(extensoes, dir.Nome);
			}
			item.SubItems.Add(dir.Tipo.Nome);
			item.SubItems.Add(dir.ModificadoFormatado);
			item.SubItems.Add(dir.Atributos);
			item.SubItems.Add(dir.Caminho);
			if (!bTabelaDir){
				item.SubItems.Add(dir.Aba.Nome);
			}			
		}
		
		public void Carregar(bool bTabelaDir, ListView lvTabela, List<Diretorio> diretorios, 
							List<Extensao> extensoes, ProgressBar pb){						
			if (diretorios.Count > 0) {
	            pb.Minimum = 0;
	            pb.Maximum = diretorios.Count;
	            pb.Value = 0;
	            pb.Step = 1;
	
	            foreach (Diretorio dir in diretorios) {    
	            	AdicionaItemLista(bTabelaDir, lvTabela, dir, extensoes);
	            	pb.Value++;
	            }            
			}
		}
		
	    public int encontrarLinha(ListView lvTabela, string nome) {
	        string slinha;
	        int nlinha = 0;
	        for (int i = 0; i < lvTabela.Items.Count; i++) {
	            slinha = lvTabela.Items[i].SubItems[0].Text;
	            if (slinha.Equals(nome)) {
	                nlinha = i;
	                break;
	            }
	        }
	        return nlinha;
	    }
		
	    public Diretorio getLinhaSelecionada(ListView lvTabela, bool bTabelaDir){
	        Diretorio dir = null;
	        
	        if (lvTabela.SelectedItems.Count > 0) {        
	            dir = new Diretorio();
	            dir.Nome = lvTabela.SelectedItems[0].SubItems[0].Text;
	            dir.TamanhoFormatado = lvTabela.SelectedItems[0].SubItems[1].Text;	            
	            dir.Tipo = new Tipo('D', lvTabela.SelectedItems[0].SubItems[2].Text);
	            dir.ModificadoFormatado = lvTabela.SelectedItems[0].SubItems[3].Text;
	            dir.Atributos = lvTabela.SelectedItems[0].SubItems[4].Text;
	            dir.Caminho = lvTabela.SelectedItems[0].SubItems[5].Text;
	            if (bTabelaDir) {                
	                dir.Aba.Nome = lvTabela.SelectedItems[0].SubItems[6].Text;
	            }
	        }
	        
	        return dir;
	    }
		
	}
}
