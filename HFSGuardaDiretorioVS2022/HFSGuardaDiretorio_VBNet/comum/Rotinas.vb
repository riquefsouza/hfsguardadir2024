'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:42
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Data
Imports System.Data.SQLite
Imports System.Drawing
Imports System.Drawing.Imaging
Imports System.Collections.Generic
Imports HFSGuardaDiretorio.objetos

Namespace comum
	''' <summary>
	''' Description of Rotinas.
	''' </summary>
	Public NotInheritable Class Rotinas
		Private Sub New()
		End Sub
		Private Shared db As SQLiteConnection

		Public Shared ReadOnly HFSGUARDADIR As String = "HFSGuardaDir"

		Public Shared ReadOnly BARRA_NORMAL As String = "\"

		Public Shared ReadOnly BARRA_INVERTIDA As String = "/"

		Public Shared ReadOnly FORMATO_DATA As String = "dd/MM/yyyy"

		Public Shared ReadOnly FORMATO_DATAHORA As String = "dd/MM/yyyy HH:mm:ss"

		Public Shared ReadOnly FORMATO_DHARQUIVO As String = "yyy-MM-dd_HH_mm_ss"

		Public Shared EXTENSAO_BMP As String = "bmp"

		Public Shared EXTENSAO_ICO As String = "ico"

		Public Shared EXTENSAO_GIF As String = "gif"

		Public Shared EXTENSAO_JPEG As String = "jpg"

		Public Shared EXTENSAO_PNG As String = "png"

		Public Shared EXTENSAO_TIFF As String = "tif"

		Public Shared FILTRO_TODOS As String = "Todos os Arquivos (*.*)|*.*"

		Public Shared FILTRO_EXPORTAR As String = "Arquivo TXT (*.txt)|*.txt|Arquivo CSV (*.csv)|*.csv|Arquivo HTML (*.html)|*.html|Arquivo XML (*.xml)|*.xml|Arquivo SQL (*.sql)|*.sql"

		Public Shared FILTRO_IMAGEM As String = "Arquivo BMP (*.bmp)|*.bmp|Arquivo ICO (*.ico)|*.ico|Arquivo GIF (*.gif)|*.gif|Arquivo JPEG (*.png)|*.png|Arquivo PNG (*.jpg)|*.jpg|Arquivo TIFF (*.tif)|*.tif"

		Public Shared Function LastDelimiter(subtexto As String, texto As String) As Integer
			Return texto.LastIndexOf(subtexto) + 1
		End Function

		Public Shared Function LastDelimiter(subtexto As Char, texto As String) As Integer
			Return texto.LastIndexOf(subtexto) + 1
		End Function

		Public Shared Function Pos(subtexto As String, texto As String) As Integer
			Return texto.IndexOf(subtexto) + 1
		End Function

		Public Shared Function Pos(subtexto As Char, texto As String) As Integer
			Return texto.IndexOf(subtexto) + 1
		End Function

		Public Shared Function StartsStr(subtexto As String, texto As String) As Boolean
			Return texto.StartsWith(subtexto)
		End Function

		Public Shared Function ContainsStr(texto As String, subtexto As String) As Boolean
			Return (Pos(subtexto, texto) > 0)
		End Function

		Public Shared Function EndsStr(subtexto As String, texto As String) As Boolean
			Return (LastDelimiter(subtexto, texto) > 0)
		End Function

		Public Shared Function SubString(texto As String, inicio As Integer, tamanho As Integer) As String
			If tamanho > (texto.Length - inicio) Then
				tamanho = texto.Length - inicio + 1
			End If
			Return texto.Substring(inicio - 1, tamanho)
		End Function

		Public Shared Function StringReplaceAll(texto As String, velho As String, novo As String) As String
			Return texto.Replace(velho, novo)
		End Function

		Public Shared Function QuotedStr(texto As String) As String
			Return "'" & texto & "'"
		End Function

		Public Shared Function QuotedStr(texto As Char) As String
			Return "'" & texto & "'"
		End Function

		Public Shared Function ExtractFilePath(sCaminho As String) As String
			Dim retorno As String

			Dim fileInfo As New FileInfo(sCaminho)
			retorno = fileInfo.DirectoryName

			Return retorno
		End Function

		Public Shared Function ExtractFileName(sCaminho As String) As String
			Dim retorno As String

			Dim fileInfo As New FileInfo(sCaminho)
			retorno = fileInfo.Name

			Return retorno
		End Function

		Public Shared Function FileExists(sNomeArquivo As String) As Boolean
			Dim fileInfo As New FileInfo(sNomeArquivo)
			Return fileInfo.Exists
		End Function

		Public Shared Function DirectoryExists(sNomeArquivo As String) As Boolean
			Dim dirInfo As New DirectoryInfo(sNomeArquivo)
			Return dirInfo.Exists
		End Function

		Public Shared Sub DeleteFile(sNomeArquivo As String)
			Dim fileInfo As New FileInfo(sNomeArquivo)
			fileInfo.Delete()
		End Sub

		Public Shared Sub SaveToFile(imagem As Byte(), sNomeArquivo As String)
			Dim fileStream As FileStream = Nothing
			Try
				fileStream = New FileStream(sNomeArquivo, FileMode.OpenOrCreate, FileAccess.Write)
				fileStream.Write(imagem, 0, imagem.Length)
				fileStream.Flush()
			Catch ioEx As FileNotFoundException
				Console.WriteLine(ioEx.Message)
			Finally
				If fileStream IsNot Nothing Then
					fileStream.Close()
				End If
			End Try
		End Sub

		Public Shared Function LoadFromFile(sNomeArquivo As String) As Byte()
			Dim imagem As Byte() = Nothing
			Dim fileStream As FileStream = Nothing

			Try
				fileStream = New FileStream(sNomeArquivo, FileMode.Open, FileAccess.Read)
				
				imagem = New Byte(fileStream.Length - 1) {}
				Dim numBytesToRead As Integer = CInt(fileStream.Length)
				Dim numBytesRead As Integer = 0
				While numBytesToRead > 0
					Dim n As Integer = fileStream.Read(imagem, numBytesRead, numBytesToRead)
					If n = 0 Then
						Exit While
					End If
					numBytesRead += n
					numBytesToRead -= n

				End While
			Catch ioEx As FileNotFoundException
				Console.WriteLine(ioEx.Message)
			Finally
				If fileStream IsNot Nothing Then
					fileStream.Close()
				End If
			End Try

			Return imagem
		End Function

		Public Shared Function formataDate(formato As String, dt As DateTime) As String
			Dim ds As String = ""

			If dt <> Nothing Then
				ds = dt.ToString(formato)
			End If
			Return ds
		End Function

		Public Shared Function StringToDate(sData As String) As DateTime
			Dim data As DateTime = DateTime.Now

			If sData.Trim().Length > 0 Then
				Try
					If sData.Trim().Length = 10 Then
						data = DateTime.ParseExact(sData, FORMATO_DATA, System.Globalization.CultureInfo.InvariantCulture)
					Else
						data = DateTime.ParseExact(sData, FORMATO_DATAHORA, System.Globalization.CultureInfo.InvariantCulture)

					End If
				Catch ex As Exception
					Console.WriteLine("Erro na rotina StringToDate: " & ex.Message)
				End Try
			End If
			Return data
		End Function

		Public Shared Function FormatLong(formato As String, valor As Long) As String
			Return valor.ToString(formato)
		End Function

		Public Shared Function FormatDecimal(valor As Decimal) As String
			Return valor.ToString("#,##0.00")
		End Function

		Public Shared Function testaNull(res As String) As String
			Return (If(res Is Nothing, "", res.Trim()))
		End Function

		Public Shared Function getConexao() As SQLiteConnection
			Return db
		End Function

		Public Shared Sub Conectar(cp As ConexaoParams)
			Try
				db = New SQLiteConnection("Data Source=" & cp.Nome & ";Version=3;")

				db.Open()
			Catch ex As Exception
				Console.WriteLine(ex.Message)
			End Try
		End Sub

		Public Shared Sub Desconectar()
			Desconectar(db)
		End Sub

		Public Shared Sub Desconectar(con As SQLiteConnection)
			If con IsNot Nothing Then
				con.Close()
			End If
		End Sub

		Public Shared Function trocaSeparador(texto As String) As String
			Dim res As String = ""
			If texto IsNot Nothing AndAlso texto.Length > 0 Then
				Dim pedacos As Char() = texto.ToCharArray()
				For i As Integer = 0 To pedacos.Length - 1
					If pedacos(i) = BARRA_NORMAL(0) Then
						pedacos(i) = BARRA_INVERTIDA(0)
					End If
				Next
				res = New String(pedacos)
			End If
			Return res
		End Function

		Public Shared Function imageToByteArray(imageIn As Image, formato As ImageFormat) As Byte()
			Dim ms As New MemoryStream()
			imageIn.Save(ms, formato)
			Return ms.ToArray()
		End Function

		Public Shared Function byteArrayToImage(byteArrayIn As Byte()) As Image
			Dim ms As New MemoryStream(byteArrayIn)
			Dim returnImage As Image = Image.FromStream(ms)
			Return returnImage
		End Function

		Public Shared Function LerArquivoImagem(sCaminho As String) As Byte()
			Dim imagebytes As Byte() = Nothing
			Dim fs As New FileStream(sCaminho, FileMode.Open, FileAccess.Read)
			Dim br As New BinaryReader(fs)
			imagebytes = br.ReadBytes(1000000)

			'imagebytes.GetLength(0)

			Return imagebytes
		End Function

		Public Shared Function byteArrayToBitmap(byteArrayIn As Byte()) As Bitmap
			Dim ms As New MemoryStream(byteArrayIn)
			Dim bmp As New Bitmap(ms)
			Return bmp
		End Function

		Public Shared Function bitmapToByteArray(bmp As Bitmap) As Byte()
			Dim ms As New MemoryStream()
			bmp.Save(ms, ImageFormat.Bmp)
			Return ms.ToArray()
		End Function


		Private Shared Function GetEncoder(format As ImageFormat) As ImageCodecInfo
			Dim codecs As ImageCodecInfo() = ImageCodecInfo.GetImageDecoders()

			For Each codec As ImageCodecInfo In codecs
				If codec.FormatID = format.Guid Then
					Return codec
				End If
			Next

			Return Nothing
		End Function

		Public Shared Sub SaveJpeg(img As Image, filePath As String, quality As Long)
			Dim encoderParameters As EncoderParameters = New EncoderParameters(1)
			encoderParameters.Param(0) = New EncoderParameter(Encoder.Quality, quality)
			img.Save(filePath, GetEncoder(ImageFormat.Jpeg), encoderParameters)
		End Sub

		Public Shared Sub SaveJpeg(img As Image, stream As Stream, quality As Long)
			Dim encoderParameters As EncoderParameters = New EncoderParameters(1)
			encoderParameters.Param(0) = New EncoderParameter(Encoder.Quality, quality)
			img.Save(stream, GetEncoder(ImageFormat.Jpeg), encoderParameters)
		End Sub

		Public Shared Function BmpParaImagem(imagemBMP As Byte(), formato As [String]) As Byte()

			Dim imagemSaida As Byte() = Nothing

			Dim encoderParameters As EncoderParameters = New EncoderParameters(1)
			encoderParameters.Param(0) = New EncoderParameter(Encoder.Quality, 100L)

			Dim ms As New MemoryStream()
			Dim img As Image = byteArrayToImage(imagemBMP)

			If formato.Equals(EXTENSAO_BMP) Then
				img.Save(ms, GetEncoder(ImageFormat.Bmp), encoderParameters)
			ElseIf formato.Equals(EXTENSAO_JPEG) Then
				img.Save(ms, GetEncoder(ImageFormat.Jpeg), encoderParameters)
			ElseIf formato.Equals(EXTENSAO_ICO) Then
				img.Save(ms, GetEncoder(ImageFormat.Icon), encoderParameters)
			ElseIf formato.Equals(EXTENSAO_GIF) Then
				img.Save(ms, GetEncoder(ImageFormat.Gif), encoderParameters)
			ElseIf formato.Equals(EXTENSAO_PNG) Then
				img.Save(ms, GetEncoder(ImageFormat.Png), encoderParameters)
			ElseIf formato.Equals(EXTENSAO_TIFF) Then
				img.Save(ms, GetEncoder(ImageFormat.Tiff), encoderParameters)
			End If

			imagemSaida = ms.ToArray()

			Return imagemSaida
		End Function

		Public Shared Function listFiles(sCaminho As String) As List(Of FileInfo)
			Dim lista As New List(Of FileInfo)()
			For Each dir As String In Directory.GetDirectories(sCaminho)
				lista.Add(New FileInfo(dir))
			Next
			For Each arq As String In Directory.GetFiles(sCaminho)
				lista.Add(New FileInfo(arq))
			Next
			Return lista
		End Function

	End Class
End Namespace
