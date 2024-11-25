/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 06/07/2015
 * Time: 11:30
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.Data;
using System.Data.SQLite;
using System.Collections.Generic;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosbo;

namespace HFSGuardaDiretorio.objetosdao
{
	/// <summary>
	/// Description of DiretorioDAO.
	/// </summary>
	public sealed class DiretorioDAO
	{
		private static DiretorioDAO instancia = new DiretorioDAO();
		
	    private SQLiteConnection conexao;

	    private SQLiteCommand cmd;
	    
	    private SQLiteDataReader dr = null;
		
		public static DiretorioDAO Instancia {
			get {
				return instancia;
			}
		}
		
		private DiretorioDAO()
		{
		}
		
	    private void fecharSqlPreparado() {
	        if (dr != null) {
	            dr.Close();
	        }
	    }
	
	    private Diretorio novoObjeto(SQLiteDataReader dr) {
	        Diretorio ret = new Diretorio();
	        Aba aba = new Aba();
	        Tipo tipo;
	
	        aba.Codigo = dr.GetInt32(0);
	        ret.Codigo = dr.GetInt32(1);
	        ret.Ordem = dr.GetInt32(2);
	        
	        if (!dr.IsDBNull(3)) {
	            ret.CodDirPai = dr.GetInt32(3);
	        } else {
	            ret.CodDirPai = -1;
	        }

	        if (!dr.IsDBNull(4))
	        	ret.Nome = dr.GetString(4);
	        
        	ret.Tamanho = dr.GetDecimal(5);
	        			
			tipo = new Tipo(dr.GetString(6)[0], "");			
			ret.Modificado = Rotinas.StringToDate(dr.GetString(7));
			if (!dr.IsDBNull(8))
				ret.Atributos = dr.GetString(8);
			if (!dr.IsDBNull(9))
				ret.Caminho = dr.GetString(9);
			if (!dr.IsDBNull(10))
				aba.Nome = dr.GetString(10);
			ret.Aba = aba;
			if (!dr.IsDBNull(11))
				ret.NomePai = dr.GetString(11);
			if (!dr.IsDBNull(12))
				ret.CaminhoPai = dr.GetString(12);
			ret.TamanhoFormatado = 
					DiretorioBO.Instancia.MontaTamanho(ret.Tamanho);
			if (tipo.Codigo == 'D') {
				tipo.Nome = "Diretório";
			} else {
				tipo.Nome = "Arquivo";
			}
			ret.Tipo = tipo;
			ret.ModificadoFormatado = Rotinas.formataDate(
					Rotinas.FORMATO_DATAHORA, ret.Modificado);
					
	        return ret;
	    }
	
	    public int consultarTotal(string sSQL, 
            string sCondicaoTotal) {
	        string sTabela;
	        
	        if (Rotinas.ContainsStr(sSQL, "consultadirpai"))
	            sTabela = "consultadirpai";
	        else if (Rotinas.ContainsStr(sSQL, "consultadirfilho"))
	            sTabela = "consultadirfilho";
	        else if (Rotinas.ContainsStr(sSQL, "consultaarquivo"))
	            sTabela = "consultaarquivo";
	        else
	            sTabela = "Diretorios";
	        
	        sSQL = "select count(*) from " + sTabela;
	        if (sCondicaoTotal.Trim().Length > 0){
	            sSQL += " " + sCondicaoTotal;
	        }
			int total = 0;
	        conexao = Rotinas.getConexao();
			cmd = new SQLiteCommand(sSQL, conexao);	
			dr = cmd.ExecuteReader();
	
	        if (dr.Read()) {
	            total = dr.GetInt32(0);
	        }
	        this.fecharSqlPreparado();
	
	        return total;
	    }
		
	    public List<Diretorio> consultarTudo(String sSQL, 
            String sCondicaoTotal, IProgressoLog progressoLog) {
	        Diretorio obj;
	        List<Diretorio> lista = new List<Diretorio>();
	        Progresso pb;
	        int i = 0;
	        int total = this.consultarTotal(sSQL, sCondicaoTotal);
	
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand(sSQL, conexao);	
			dr = cmd.ExecuteReader();
	        	
	        if (total > 0) {
	            pb = new Progresso();
	            pb.Minimo = 0;
	            pb.Maximo = total - 1;
	            pb.Posicao = 0;
	            pb.Passo = 1;
	
	            while (dr.Read()) {
	                obj = novoObjeto(dr);
	
	                lista.Add(obj);
	
	                pb.Posicao = i;
	
	                if (progressoLog != null) {
	                    progressoLog.ProgressoLog(pb);
	                }
	
	                i++;
	            }
	        }
	
	        this.fecharSqlPreparado();
	
	        return lista;
	    }
		
	    private void atribuirCampos(SQLiteCommand cmd, Diretorio obj) {
	        cmd.Parameters.AddWithValue("@1", obj.Aba.Codigo);
	        cmd.Parameters.AddWithValue("@2", obj.Codigo);
	        cmd.Parameters.AddWithValue("@3", obj.Ordem);
	        cmd.Parameters.AddWithValue("@4", obj.CodDirPai);
	        cmd.Parameters.AddWithValue("@5", obj.Nome);
	        cmd.Parameters.AddWithValue("@6", obj.Tamanho);
	        cmd.Parameters.AddWithValue("@7", obj.Tipo.Codigo.ToString());
			cmd.Parameters.AddWithValue("@8", Rotinas.formataDate(
	        	Rotinas.FORMATO_DATAHORA, obj.Modificado));
	        cmd.Parameters.AddWithValue("@9", obj.Atributos);
	        cmd.Parameters.AddWithValue("@10", obj.Caminho);
	    }
	    
	    public int incluir(Diretorio obj) {
	        int ret;
	        
	       	try {	       		
		        conexao = Rotinas.getConexao();
		        cmd = new SQLiteCommand("insert into Diretorios(aba, cod, ordem, coddirpai, nome, tam,"
	                + " tipo, modificado, atributos, caminho)"
	                + " values (@1,@2,@3,@4,@5,@6,@7,@8,@9,@10)", conexao);	
	        	atribuirCampos(cmd, obj);				        
		        cmd.Prepare();
		        ret = cmd.ExecuteNonQuery();
	        } catch (Exception) {
	       		throw;	       		
	       	}
	        
	        return ret;
	    }
		
	    public int excluir(Aba aba, string sCaminho) {
	        int ret;
	        conexao = Rotinas.getConexao();
			
	        cmd = new SQLiteCommand("delete from Diretorios where caminho like @1 and aba=@2", conexao);
	        cmd.Parameters.AddWithValue("@1", sCaminho + "%");
	        cmd.Parameters.AddWithValue("@2", aba.Codigo);
	        cmd.Prepare();
	        ret = cmd.ExecuteNonQuery();
	        
	        return ret;
	    }
	
	    public int criarTabela() {
	        string sSQL;
	        int ret;
	
	        sSQL = "create table if NOT EXISTS Diretorios("
	                + "aba int not null,"
	                + "cod int not null,"
	                + "ordem int not null,"
	                + "nome varchar(255) not null,"
	                + "tam numeric not null,"
	                + "tipo char(1) not null,"
	                + "modificado date not null,"
	                + "atributos varchar(20) not null,"
	                + "coddirpai int not null,"
	                + "caminho varchar(255) not null,"
	                + "primary key (aba, cod, ordem))";
	
	        conexao = Rotinas.getConexao();
	        cmd = new SQLiteCommand(sSQL, conexao);
	        ret = cmd.ExecuteNonQuery();
	        return ret;
	    }
		
	}
}
