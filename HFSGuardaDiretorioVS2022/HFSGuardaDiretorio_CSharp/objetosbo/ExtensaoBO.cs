/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 06/07/2015
 * Time: 15:02
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using HFSGuardaDiretorio.comum;
using HFSGuardaDiretorio.objetos;
using HFSGuardaDiretorio.objetosdao;

namespace HFSGuardaDiretorio.objetosbo
{
	/// <summary>
	/// Description of ExtensaoBO.
	/// </summary>
	public sealed class ExtensaoBO
	{
		private static ExtensaoBO instancia = new ExtensaoBO();
		
		private byte[] diretorioBMP;
    	private byte[] arquivoBMP;
		
		public static ExtensaoBO Instancia {
			get {
				return instancia;
			}
		}
		
		private ExtensaoBO()
		{
			//diretorioBMP = Rotinas.LerArquivoImagem("imagens"+Path.DirectorySeparatorChar+"diretorio.bmp");
    	    //arquivoBMP = Rotinas.LerArquivoImagem("imagens"+Path.DirectorySeparatorChar+"arquivo.bmp");
		}
		
		public List<Extensao> carregarExtensao(IProgressoLog progressoLog) {
			return ExtensaoDAO.Instancia.consultarTudo(progressoLog);
		}
		
		public void carregarExtensoes(List<Extensao> lista, 
			ImageList listaImg16, ImageList listaImg32){
			Bitmap bmp16, bmp32;
			
			diretorioBMP = Rotinas.imageToByteArray(listaImg16.Images[0], ImageFormat.Bmp);
			arquivoBMP = Rotinas.imageToByteArray(listaImg16.Images[2], ImageFormat.Bmp);
			
			foreach (Extensao extensao in lista) {
				bmp16 = Rotinas.byteArrayToBitmap(extensao.Bmp16);
				bmp32 = Rotinas.byteArrayToBitmap(extensao.Bmp32);
				
				listaImg16.Images.Add(bmp16);
				listaImg32.Images.Add(bmp32);
			}
		}

		public bool existeExtensao(string sExtensao,
				List<Extensao> listaLocal) {
			if (sExtensao.Trim().Length > 0) {
				foreach (Extensao extensao in listaLocal) {
					if (extensao.Nome.Trim().ToLower().Equals(
							sExtensao.Trim().ToLower())) {
						return true;
					}
				}
			}
			return false;
		}

		public int retMaxCodExtensao(List<Extensao> listaLocal) {
			int nMaior = 0;
			foreach (Extensao extensao in listaLocal) {
				if (extensao.Codigo > nMaior) {
					nMaior = extensao.Codigo;
				}
			}
			return nMaior + 1;
		}

		public bool incluirExtensao(Extensao extensao)  {
			return (ExtensaoDAO.Instancia.incluir(extensao) > 0);
		}

		public bool SalvarExtensao(List<Extensao> listaExtensao,
				string sNomeDiretorio, string sCaminhoOriginal, StringList log)
		{
			string sExtensao;
			Extensao extensao;

			if (Rotinas.LastDelimiter(".", sNomeDiretorio) > 0) {
				sExtensao = Rotinas.SubString(sNomeDiretorio,
						Rotinas.LastDelimiter(".", sNomeDiretorio) + 1,
						sNomeDiretorio.Length);
				if (!existeExtensao(sExtensao, listaExtensao)) {
					extensao = new Extensao();
					extensao.Codigo = retMaxCodExtensao(listaExtensao);
					extensao.Nome = sExtensao.ToLower();
					extensao.Ordem = listaExtensao.Count+1;
					extensao.Bmp16 = Rotinas.LerArquivoImagem(sCaminhoOriginal);
					extensao.Bmp32 = Rotinas.LerArquivoImagem(sCaminhoOriginal);
					incluirExtensao(extensao);                
					listaExtensao.Add(extensao);
					log.Add("Salvando Extensão: " + extensao.Nome);
					return true;
				}
			}
			return false;
		}

		public void salvarExtensoes(List<Diretorio> listaDiretorio,
				List<Extensao> listaExtensao, 
				IProgressoLog progressoLog)  {
			StringList log = new StringList();
			Diretorio diretorio;
			Progresso pb = new Progresso();

			pb.Minimo = 0;
			pb.Maximo = listaDiretorio.Count - 1;
			pb.Posicao = 0;
			pb.Passo = 1;

			for (int i = 0; i < listaDiretorio.Count; i++) {
				diretorio = listaDiretorio[i];

				if (diretorio.Tipo.Codigo == 'A') {
					SalvarExtensao(listaExtensao, diretorio.Nome,
							diretorio.CaminhoOriginal, log);
					if (log.Count > 0){
						pb.Log = log[0];
						log.Clear();
					}
				}

				pb.Posicao = i;

				if (progressoLog != null) {
					progressoLog.ProgressoLog(pb);
				}
			}
		}

		public bool excluirExtensao(List<Extensao> listaExtensao,
				int codigo)  {
			Extensao extensao;

			if (ExtensaoDAO.Instancia.excluir(codigo) > 0) {
				for (int i = 0; i < listaExtensao.Count; i++) {
					extensao = listaExtensao[i];
					if (extensao.Codigo == codigo) {
						listaExtensao.Remove(extensao);
						break;
					}
				}
				return true;
			} else {
				return false;
			}
		}

		public bool excluirTodasExtensoes(List<Extensao> listaExtensao)
				 {
			if (ExtensaoDAO.Instancia.excluirTudo() > 0) {
				listaExtensao.Clear();
				return true;
			} else {
				return false;
			}
		}

		public bool criarTabelaExtensoes()  {
			return (ExtensaoDAO.Instancia.criarTabela() > 0);
		}

		public int indiceExtensao(List<Extensao> lista,
				string nomeExtensao) {
			nomeExtensao = Rotinas.SubString(nomeExtensao,
					Rotinas.LastDelimiter(".", nomeExtensao) + 1,
					nomeExtensao.Length);

			foreach (Extensao extensao in lista) {
				if (extensao.Nome.Trim().ToLower().Equals(
						nomeExtensao.Trim().ToLower())) {
					return (extensao.Ordem + 2);
				}
			}
			return -1;
		}

		public Extensao pegaExtensaoPorOrdem(List<Extensao> lista,
				int ordem) {
			foreach (Extensao extensao in lista) {
				if (extensao.Ordem == ordem) {
					return extensao;
				}
			}
			return null;
		}

		public Extensao pegaExtensaoPorCodigo(List<Extensao> lista,
				int codigo) {
			foreach (Extensao extensao in lista) {
				if (extensao.Codigo == codigo) {
					return extensao;
				}
			}
			return null;
		}

		public Extensao pegaExtensaoPorNome(List<Extensao> lista,
				string nome, string tipo) {
			Extensao ext = null;
			
			if (tipo.Equals("Diretório")){
				ext = new Extensao();
				ext.Bmp16 = diretorioBMP;
			} else {        
				if (lista != null && lista.Count > 0) {
					foreach (Extensao extensao in lista) {
						if (extensao.Nome.ToLower().Equals(
								nome.ToLower())) {
							return extensao;
						}
					}
				}
				if (tipo.Equals("Arquivo")){
					ext = new Extensao();
					ext.Bmp16 = arquivoBMP;
				}            
			}
			return ext;
		}
		
		public bool ExportarExtensao(TipoExportarExtensao tipo,
				List<Extensao> listaExtensao) {
			string sCaminho, sImg16, sImg32, sExtensao;
			
			if (listaExtensao.Count > 0) {
				sCaminho = Rotinas.ExtractFilePath(Application.ExecutablePath) +
						Rotinas.BARRA_INVERTIDA;

				if (tipo == TipoExportarExtensao.teBMP) {
					sExtensao = "." + Rotinas.EXTENSAO_BMP;
				} else if (tipo == TipoExportarExtensao.teICO) {
					sExtensao = "." + Rotinas.EXTENSAO_ICO;
				} else if (tipo == TipoExportarExtensao.teGIF) {
					sExtensao = "." + Rotinas.EXTENSAO_GIF;
				} else if (tipo == TipoExportarExtensao.teJPG) {
					sExtensao = "." + Rotinas.EXTENSAO_JPEG;
				} else if (tipo == TipoExportarExtensao.tePNG) {
					sExtensao = "." + Rotinas.EXTENSAO_PNG;
				} else if (tipo == TipoExportarExtensao.teTIF) {
					sExtensao = "." + Rotinas.EXTENSAO_TIFF;
				} else {
					sExtensao = ".img";
				}

				foreach (Extensao extensao in listaExtensao) {
					sImg16 = sCaminho + extensao.Nome + "16" + sExtensao;
					if (Rotinas.FileExists(sImg16)) {
						Rotinas.DeleteFile(sImg16);
					}

					sImg32 = sCaminho + extensao.Nome + "32" + sExtensao;
					if (Rotinas.FileExists(sImg32)) {
						Rotinas.DeleteFile(sImg32);
					}

					switch (tipo) {
						case TipoExportarExtensao.teBMP: {
							Rotinas.SaveToFile(extensao.Bmp16, sImg16);
							Rotinas.SaveToFile(extensao.Bmp32, sImg32);
						}
						break;
						case TipoExportarExtensao.teICO: {
							if (extensao.Bmp16 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp16,
										Rotinas.EXTENSAO_ICO), sImg16);
							}
							if (extensao.Bmp32 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp32,
										Rotinas.EXTENSAO_ICO), sImg32);
							}
						}
						break;
						case TipoExportarExtensao.teGIF: {
							if (extensao.Bmp16 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp16,
										Rotinas.EXTENSAO_GIF), sImg16);
							}
							if (extensao.Bmp32 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp32,
										Rotinas.EXTENSAO_GIF), sImg32);
							}
						}
						break;
						case TipoExportarExtensao.teJPG: {
							if (extensao.Bmp16 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp16,
										Rotinas.EXTENSAO_JPEG), sImg16);
							}
							if (extensao.Bmp32 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp32,
										Rotinas.EXTENSAO_JPEG), sImg32);
							}
						}
						break;
						case TipoExportarExtensao.tePNG: {
							if (extensao.Bmp16 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp16,
										Rotinas.EXTENSAO_PNG), sImg16);
							}
							if (extensao.Bmp32 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp32,
										Rotinas.EXTENSAO_PNG), sImg32);
							}
						}
						break;
						case TipoExportarExtensao.teTIF: {
							if (extensao.Bmp16 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp16,
										Rotinas.EXTENSAO_TIFF), sImg16);
							}
							if (extensao.Bmp32 != null) {
								Rotinas.SaveToFile(
										Rotinas.BmpParaImagem(extensao.Bmp32,
										Rotinas.EXTENSAO_TIFF), sImg32);
							}
						}
						break;
					}

				}
				return true;
			}
			return false;
		}

		public void ImportarExtensao(string caminho,
				List<Extensao> listaExtensao) {
			StringList listaArquivos, log;
			listaArquivos = new StringList();
			log = new StringList();
			
			if (DiretorioBO.Instancia.carregarArquivos(caminho, listaArquivos)) {
				foreach (string sArquivo in listaArquivos) {
					SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo),
							sArquivo, log);
				}
			}

		}

		public void ExtrairExtensao(string caminho,
				List<Extensao> listaExtensao)  {
			StringList listaArquivos, log;
			listaArquivos = new StringList();
			log = new StringList();

			if (DiretorioBO.Instancia.carregarTodosArquivos(caminho, listaArquivos)) {
				foreach (string sArquivo in listaArquivos) {
					SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo),
							sArquivo, log);
				}
			}
		}
		
	}
}
