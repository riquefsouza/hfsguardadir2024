/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:42
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;
using System.IO;
using System.Data;
using System.Data.SQLite;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;
using HFSGuardaDiretorio.objetos;

namespace HFSGuardaDiretorio.comum
{
	/// <summary>
	/// Description of Rotinas.
	/// </summary>
	public static class Rotinas
	{
	    private static SQLiteConnection db;
	
	    public static readonly string HFSGUARDADIR = "HFSGuardaDir";
	
	    public static readonly string BARRA_NORMAL = "\\";
	
	    public static readonly string BARRA_INVERTIDA = "/";
	    
	    public static readonly string FORMATO_DATA = "dd/MM/yyyy";
	    
	    public static readonly string FORMATO_DATAHORA = "dd/MM/yyyy HH:mm:ss";
	    
	    public static readonly string FORMATO_DHARQUIVO = "yyy-MM-dd_HH_mm_ss";
	
	    public static string EXTENSAO_BMP = "bmp";
	    
	    public static string EXTENSAO_ICO = "ico";
	    
	    public static string EXTENSAO_GIF = "gif";
	    
	    public static string EXTENSAO_JPEG = "jpg";
	    
	    public static string EXTENSAO_PNG = "png";
	    
	    public static string EXTENSAO_TIFF = "tif";		
	    
	    public static string FILTRO_TODOS = "Todos os Arquivos (*.*)|*.*";
	    
	    public static string FILTRO_EXPORTAR = "Arquivo TXT (*.txt)|*.txt|Arquivo CSV (*.csv)|*.csv|Arquivo HTML (*.html)|*.html|Arquivo XML (*.xml)|*.xml|Arquivo SQL (*.sql)|*.sql";
	    
	    public static string FILTRO_IMAGEM = "Arquivo BMP (*.bmp)|*.bmp|Arquivo ICO (*.ico)|*.ico|Arquivo GIF (*.gif)|*.gif|Arquivo JPEG (*.png)|*.png|Arquivo PNG (*.jpg)|*.jpg|Arquivo TIFF (*.tif)|*.tif";
	    			
	    public static int LastDelimiter(string subtexto, string texto) {
	        return texto.LastIndexOf(subtexto) + 1;
	    }
	
	    public static int LastDelimiter(char subtexto, string texto) {
	        return texto.LastIndexOf(subtexto) + 1;
	    }
	
	    public static int Pos(string subtexto, string texto) {
	        return texto.IndexOf(subtexto) + 1;
	    }
	
	    public static int Pos(char subtexto, string texto) {
	        return texto.IndexOf(subtexto) + 1;
	    }
	    
	    public static bool StartsStr(string subtexto, string texto) {
	        return texto.StartsWith(subtexto);
	    }
	
	    public static bool ContainsStr(string texto, string subtexto) {
	        return (Pos(subtexto, texto) > 0);
	    }
	    
	    public static bool EndsStr(string subtexto, string texto) {
	        return (LastDelimiter(subtexto, texto) > 0);
	    }
	
	    public static string SubString(string texto, int inicio, int tamanho) {
			if (tamanho > (texto.Length-inicio)){
				tamanho = texto.Length - inicio + 1;
			}
	        return texto.Substring(inicio - 1, tamanho);
	    }
	
	    public static string StringReplaceAll(string texto, string velho, 
	            string novo){
	        return texto.Replace(velho, novo);
	    }
	    
	    public static string QuotedStr(string texto){
	        return "'" + texto + "'";
	    }
	
	    public static string QuotedStr(char texto){
	        return "'" + texto + "'";
	    }
	    
	    public static string ExtractFilePath(string sCaminho) {
	        string retorno;
	
	        FileInfo fileInfo = new FileInfo(sCaminho);
	        retorno = fileInfo.DirectoryName;
	
	        return retorno;
	    }
	
	    public static string ExtractFileName(string sCaminho) {
	        string retorno;
	
	        FileInfo fileInfo = new FileInfo(sCaminho);
	        retorno = fileInfo.Name;
	
	        return retorno;
	    }
	
	    public static bool FileExists(string sNomeArquivo) {
	        FileInfo fileInfo = new FileInfo(sNomeArquivo);
	        return fileInfo.Exists;
	    }
	    
	    public static bool DirectoryExists(string sNomeArquivo) {
	        DirectoryInfo dirInfo = new DirectoryInfo(sNomeArquivo);
	        return dirInfo.Exists;
	    }
	
	    public static void DeleteFile(string sNomeArquivo) {
	        FileInfo fileInfo = new FileInfo(sNomeArquivo);
	        fileInfo.Delete();
	    }
	
	    public static void SaveToFile(byte[] imagem, string sNomeArquivo) {
			FileStream fileStream = null;            
			try {        
				fileStream = new FileStream(sNomeArquivo, 
					FileMode.OpenOrCreate, FileAccess.Write);
				fileStream.Write(imagem, 0, imagem.Length);      
				fileStream.Flush();
			} catch (FileNotFoundException ioEx) {	            
				Console.WriteLine(ioEx.Message);				
			} finally {
				if( fileStream != null ) 
					fileStream.Close();
			}	        
	    }
	
	    public static byte[] LoadFromFile(string sNomeArquivo) {
	    	byte[] imagem = null;
			FileStream fileStream = null;     
			
			try {        
				fileStream = new FileStream(sNomeArquivo, 
					FileMode.Open, FileAccess.Read);

				imagem = new byte[fileStream.Length];
				int numBytesToRead = (int)fileStream.Length;
	            int numBytesRead = 0;
	            while (numBytesToRead > 0)
	            {
	                int n = fileStream.Read(imagem, numBytesRead, numBytesToRead);
	                if (n == 0)
	                    break;	
	                numBytesRead += n;
	                numBytesToRead -= n;
	            }        		
        		
			} catch (FileNotFoundException ioEx) {	            
				Console.WriteLine(ioEx.Message);
			} finally {
				if( fileStream != null ) 
					fileStream.Close();
			}			
	
	        return imagem;
	    }
	
	    public static string formataDate(string formato, DateTime dt) {
	        string ds = "";
	        
	        if (dt != null) {	            
	            ds = dt.ToString(formato);
	        }
	        return ds;
	    }
	
	    public static DateTime StringToDate(string sData) {
	        DateTime data = DateTime.Now;
	        
	        if (sData.Trim().Length > 0) {
	            try {
	                if (sData.Trim().Length == 10)
	                    data = DateTime.ParseExact(sData, FORMATO_DATA,
                                       System.Globalization.CultureInfo.InvariantCulture);
	                else
	                    data = DateTime.ParseExact(sData, FORMATO_DATAHORA,
                                       System.Globalization.CultureInfo.InvariantCulture);
	                    
	            } catch (Exception ex) {
	        		Console.WriteLine("Erro na rotina StringToDate: "
	                        +ex.Message);
	            }
	        }
	        return data;
	    }
	
	    public static string FormatLong(string formato, long valor) {
	        return valor.ToString(formato);
	    }

	    public static string FormatDecimal(decimal valor) {
	        return valor.ToString("#,##0.00");
	    }
	    
	    public static string testaNull(string res) {
	        return (res == null ? "" : res.Trim());
	    }
		
	    public static SQLiteConnection getConexao() {
	        return db;
	    }	
	
	    public static void Conectar(ConexaoParams cp) {
			try	{
				db = new SQLiteConnection("Data Source="+cp.Nome+";Version=3;");
				db.Open();
	
			} catch (Exception ex) {
				Console.WriteLine(ex.Message);
			}
	    }
	
	    public static void Desconectar() {
	        Desconectar(db);
	    }
	
	    public static void Desconectar(SQLiteConnection con) {
	        if (con != null) {
	            con.Close();
	        }
	    }
	
	    public static string trocaSeparador(string texto) {
	        string res = "";
	        if (texto != null && texto.Length > 0) {
	            char[] pedacos = texto.ToCharArray();
	            for (int i = 0; i < pedacos.Length; i++) {
	            	if (pedacos[i] == BARRA_NORMAL[0]) {
	            		pedacos[i] = BARRA_INVERTIDA[0];
	                }
	            }
	            res = new string(pedacos);
	        }
	        return res;
	    }
	    
		public static byte[] imageToByteArray(Image imageIn, ImageFormat formato){
			MemoryStream ms = new MemoryStream();
			imageIn.Save(ms, formato);
			return  ms.ToArray();
		}	

		public static Image byteArrayToImage(byte[] byteArrayIn)
		{
		     MemoryStream ms = new MemoryStream(byteArrayIn);
		     Image returnImage = Image.FromStream(ms);
		     return returnImage;
		}
		
		public static byte[] LerArquivoImagem(string sCaminho)
		{
			byte[] imagebytes = null; 
			FileStream fs = new FileStream(sCaminho, FileMode.Open, FileAccess.Read);
			BinaryReader br = new BinaryReader(fs);
			imagebytes = br.ReadBytes(1000000);
			
			//imagebytes.GetLength(0)
			
			return imagebytes;
		}		

		public static Bitmap byteArrayToBitmap(byte[] byteArrayIn)
		{
		     MemoryStream ms = new MemoryStream(byteArrayIn);
		     Bitmap bmp = new Bitmap(ms);
		     return bmp;
		}

		public static byte[] bitmapToByteArray(Bitmap bmp){
			MemoryStream ms = new MemoryStream();
			bmp.Save(ms, ImageFormat.Bmp);
			return  ms.ToArray();
		}	
		
		
		private static ImageCodecInfo GetEncoder(ImageFormat format)
	    {
	        ImageCodecInfo[] codecs = ImageCodecInfo.GetImageDecoders();
	
	        foreach (ImageCodecInfo codec in codecs)
	        {
	            if (codec.FormatID == format.Guid)
	            {
	                return codec;
	            }
	        }
	
	        return null;
	    }	
			
		public static void SaveJpeg(Image img, string filePath, long quality)
	    {
	        EncoderParameters encoderParameters = new EncoderParameters(1);
	        encoderParameters.Param[0] = new EncoderParameter(Encoder.Quality, quality);
	        img.Save(filePath, GetEncoder(ImageFormat.Jpeg), encoderParameters);
	    }
	
	    public static void SaveJpeg(Image img, Stream stream, long quality)
	    {
	        EncoderParameters encoderParameters = new EncoderParameters(1);
	        encoderParameters.Param[0] = new EncoderParameter(Encoder.Quality, quality);
	        img.Save(stream, GetEncoder(ImageFormat.Jpeg), encoderParameters);
	    }
    
	    public static byte[] BmpParaImagem(byte[] imagemBMP, String formato) {
	        
	        byte[] imagemSaida = null;

	        EncoderParameters encoderParameters = new EncoderParameters(1);
	        encoderParameters.Param[0] = new EncoderParameter(Encoder.Quality, 100L);
	        
	        MemoryStream ms = new MemoryStream();	        
	        Image img = byteArrayToImage(imagemBMP);
	        
	        if (formato.Equals(EXTENSAO_BMP))
				img.Save(ms, GetEncoder(ImageFormat.Bmp), encoderParameters);
	        else if (formato.Equals(EXTENSAO_JPEG))
				img.Save(ms, GetEncoder(ImageFormat.Jpeg), encoderParameters);
			else if (formato.Equals(EXTENSAO_ICO))
				img.Save(ms, GetEncoder(ImageFormat.Icon), encoderParameters);
			else if (formato.Equals(EXTENSAO_GIF))
				img.Save(ms, GetEncoder(ImageFormat.Gif), encoderParameters);				
			else if (formato.Equals(EXTENSAO_PNG))
				img.Save(ms, GetEncoder(ImageFormat.Png), encoderParameters);
			else if (formato.Equals(EXTENSAO_TIFF))
				img.Save(ms, GetEncoder(ImageFormat.Tiff), encoderParameters);
				
	        imagemSaida = ms.ToArray();
						
	        return imagemSaida;
	    }

		public static List<FileInfo> listFiles(string sCaminho) 
		{
			List<FileInfo> lista = new List<FileInfo>();
			foreach (string dir in Directory.GetDirectories(sCaminho)) {
				lista.Add(new FileInfo(dir));
			}
			foreach (string arq in Directory.GetFiles(sCaminho)) {
				lista.Add(new FileInfo(arq));
			}
			return lista;
		}
		
	}
}
