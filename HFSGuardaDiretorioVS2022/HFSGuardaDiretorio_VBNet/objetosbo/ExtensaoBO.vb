'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 06/07/2015
' * Time: 15:02
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Collections.Generic
Imports System.Drawing
Imports System.Drawing.Imaging
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosdao

Namespace objetosbo
	''' <summary>
	''' Description of ExtensaoBO.
	''' </summary>
	Public NotInheritable Class ExtensaoBO
		Private Shared m_instancia As New ExtensaoBO()

		Private diretorioBMP As Byte()
		Private arquivoBMP As Byte()

		Public Shared ReadOnly Property Instancia() As ExtensaoBO
			Get
				Return m_instancia
			End Get
		End Property

				'diretorioBMP = Rotinas.LerArquivoImagem("imagens"+Path.DirectorySeparatorChar+"diretorio.bmp");
				'arquivoBMP = Rotinas.LerArquivoImagem("imagens"+Path.DirectorySeparatorChar+"arquivo.bmp");
		Private Sub New()
		End Sub

		Public Function carregarExtensao(progressoLog As IProgressoLog) As List(Of Extensao)
			Return ExtensaoDAO.Instancia.consultarTudo(progressoLog)
		End Function

		Public Sub carregarExtensoes(lista As List(Of Extensao), listaImg16 As ImageList, listaImg32 As ImageList)
			Dim bmp16 As Bitmap, bmp32 As Bitmap

			diretorioBMP = Rotinas.imageToByteArray(listaImg16.Images(0), ImageFormat.Bmp)
			arquivoBMP = Rotinas.imageToByteArray(listaImg16.Images(2), ImageFormat.Bmp)

			For Each extensao As Extensao In lista
				bmp16 = Rotinas.byteArrayToBitmap(extensao.Bmp16)
				bmp32 = Rotinas.byteArrayToBitmap(extensao.Bmp32)

				listaImg16.Images.Add(bmp16)
				listaImg32.Images.Add(bmp32)
			Next
		End Sub

		Public Function existeExtensao(sExtensao As String, listaLocal As List(Of Extensao)) As Boolean
			If sExtensao.Trim().Length > 0 Then
				For Each extensao As Extensao In listaLocal
					If extensao.Nome.Trim().ToLower().Equals(sExtensao.Trim().ToLower()) Then
						Return True
					End If
				Next
			End If
			Return False
		End Function

		Public Function retMaxCodExtensao(listaLocal As List(Of Extensao)) As Integer
			Dim nMaior As Integer = 0
			For Each extensao As Extensao In listaLocal
				If extensao.Codigo > nMaior Then
					nMaior = extensao.Codigo
				End If
			Next
			Return nMaior + 1
		End Function

		Public Function incluirExtensao(extensao As Extensao) As Boolean
			Return (ExtensaoDAO.Instancia.incluir(extensao) > 0)
		End Function

		Public Function SalvarExtensao(listaExtensao As List(Of Extensao), sNomeDiretorio As String, sCaminhoOriginal As String, log As StringList) As Boolean
			Dim sExtensao As String
			Dim extensao As Extensao

			If Rotinas.LastDelimiter(".", sNomeDiretorio) > 0 Then
				sExtensao = Rotinas.SubString(sNomeDiretorio, Rotinas.LastDelimiter(".", sNomeDiretorio) + 1, sNomeDiretorio.Length)
				If Not existeExtensao(sExtensao, listaExtensao) Then
					extensao = New Extensao()
					extensao.Codigo = retMaxCodExtensao(listaExtensao)
					extensao.Nome = sExtensao.ToLower()
					extensao.Ordem = listaExtensao.Count + 1
					extensao.Bmp16 = Rotinas.LerArquivoImagem(sCaminhoOriginal)
					extensao.Bmp32 = Rotinas.LerArquivoImagem(sCaminhoOriginal)
					incluirExtensao(extensao)
					listaExtensao.Add(extensao)
					log.Add("Salvando Extensão: " & extensao.Nome)
					Return True
				End If
			End If
			Return False
		End Function

		Public Sub salvarExtensoes(listaDiretorio As List(Of Diretorio), listaExtensao As List(Of Extensao), progressoLog As IProgressoLog)
			Dim log As New StringList()
			Dim diretorio As Diretorio
			Dim pb As New Progresso()

			pb.Minimo = 0
			pb.Maximo = listaDiretorio.Count - 1
			pb.Posicao = 0
			pb.Passo = 1

			For i As Integer = 0 To listaDiretorio.Count - 1
				diretorio = listaDiretorio(i)

				If diretorio.Tipo.Codigo = "A"C Then
					SalvarExtensao(listaExtensao, diretorio.Nome, diretorio.CaminhoOriginal, log)
					If log.Count > 0 Then
						pb.Log = log(0)
						log.Clear()
					End If
				End If

				pb.Posicao = i

				If progressoLog IsNot Nothing Then
					progressoLog.ProgressoLog(pb)
				End If
			Next
		End Sub

		Public Function excluirExtensao(listaExtensao As List(Of Extensao), codigo As Integer) As Boolean
			Dim extensao As Extensao

			If ExtensaoDAO.Instancia.excluir(codigo) > 0 Then
				For i As Integer = 0 To listaExtensao.Count - 1
					extensao = listaExtensao(i)
					If extensao.Codigo = codigo Then
						listaExtensao.Remove(extensao)
						Exit For
					End If
				Next
				Return True
			Else
				Return False
			End If
		End Function

		Public Function excluirTodasExtensoes(listaExtensao As List(Of Extensao)) As Boolean
			If ExtensaoDAO.Instancia.excluirTudo() > 0 Then
				listaExtensao.Clear()
				Return True
			Else
				Return False
			End If
		End Function

		Public Function criarTabelaExtensoes() As Boolean
			Return (ExtensaoDAO.Instancia.criarTabela() > 0)
		End Function

		Public Function indiceExtensao(lista As List(Of Extensao), nomeExtensao As String) As Integer
			nomeExtensao = Rotinas.SubString(nomeExtensao, Rotinas.LastDelimiter(".", nomeExtensao) + 1, nomeExtensao.Length)

			For Each extensao As Extensao In lista
				If extensao.Nome.Trim().ToLower().Equals(nomeExtensao.Trim().ToLower()) Then
					Return (extensao.Ordem + 2)
				End If
			Next
			Return -1
		End Function

		Public Function pegaExtensaoPorOrdem(lista As List(Of Extensao), ordem As Integer) As Extensao
			For Each extensao As Extensao In lista
				If extensao.Ordem = ordem Then
					Return extensao
				End If
			Next
			Return Nothing
		End Function

		Public Function pegaExtensaoPorCodigo(lista As List(Of Extensao), codigo As Integer) As Extensao
			For Each extensao As Extensao In lista
				If extensao.Codigo = codigo Then
					Return extensao
				End If
			Next
			Return Nothing
		End Function

		Public Function pegaExtensaoPorNome(lista As List(Of Extensao), nome As String, tipo As String) As Extensao
			Dim ext As Extensao = Nothing

			If tipo.Equals("Diretório") Then
				ext = New Extensao()
				ext.Bmp16 = diretorioBMP
			Else
				If lista IsNot Nothing AndAlso lista.Count > 0 Then
					For Each extensao As Extensao In lista
						If extensao.Nome.ToLower().Equals(nome.ToLower()) Then
							Return extensao
						End If
					Next
				End If
				If tipo.Equals("Arquivo") Then
					ext = New Extensao()
					ext.Bmp16 = arquivoBMP
				End If
			End If
			Return ext
		End Function

		Public Function ExportarExtensao(tipo As TipoExportarExtensao, listaExtensao As List(Of Extensao)) As Boolean
			Dim sCaminho As String, sImg16 As String, sImg32 As String, sExtensao As String

			If listaExtensao.Count > 0 Then
				sCaminho = Rotinas.ExtractFilePath(Application.ExecutablePath) & Rotinas.BARRA_INVERTIDA

				If tipo = TipoExportarExtensao.teBMP Then
					sExtensao = "." & Rotinas.EXTENSAO_BMP
				ElseIf tipo = TipoExportarExtensao.teICO Then
					sExtensao = "." & Rotinas.EXTENSAO_ICO
				ElseIf tipo = TipoExportarExtensao.teGIF Then
					sExtensao = "." & Rotinas.EXTENSAO_GIF
				ElseIf tipo = TipoExportarExtensao.teJPG Then
					sExtensao = "." & Rotinas.EXTENSAO_JPEG
				ElseIf tipo = TipoExportarExtensao.tePNG Then
					sExtensao = "." & Rotinas.EXTENSAO_PNG
				ElseIf tipo = TipoExportarExtensao.teTIF Then
					sExtensao = "." & Rotinas.EXTENSAO_TIFF
				Else
					sExtensao = ".img"
				End If

				For Each extensao As Extensao In listaExtensao
					sImg16 = sCaminho & extensao.Nome & "16" & sExtensao
					If Rotinas.FileExists(sImg16) Then
						Rotinas.DeleteFile(sImg16)
					End If

					sImg32 = sCaminho & extensao.Nome & "32" & sExtensao
					If Rotinas.FileExists(sImg32) Then
						Rotinas.DeleteFile(sImg32)
					End If

					Select Case tipo
						Case TipoExportarExtensao.teBMP
							If True Then
								Rotinas.SaveToFile(extensao.Bmp16, sImg16)
								Rotinas.SaveToFile(extensao.Bmp32, sImg32)
							End If
							Exit Select
						Case TipoExportarExtensao.teICO
							If True Then
								If extensao.Bmp16 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp16, Rotinas.EXTENSAO_ICO), sImg16)
								End If
								If extensao.Bmp32 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp32, Rotinas.EXTENSAO_ICO), sImg32)
								End If
							End If
							Exit Select
						Case TipoExportarExtensao.teGIF
							If True Then
								If extensao.Bmp16 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp16, Rotinas.EXTENSAO_GIF), sImg16)
								End If
								If extensao.Bmp32 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp32, Rotinas.EXTENSAO_GIF), sImg32)
								End If
							End If
							Exit Select
						Case TipoExportarExtensao.teJPG
							If True Then
								If extensao.Bmp16 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp16, Rotinas.EXTENSAO_JPEG), sImg16)
								End If
								If extensao.Bmp32 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp32, Rotinas.EXTENSAO_JPEG), sImg32)
								End If
							End If
							Exit Select
						Case TipoExportarExtensao.tePNG
							If True Then
								If extensao.Bmp16 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp16, Rotinas.EXTENSAO_PNG), sImg16)
								End If
								If extensao.Bmp32 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp32, Rotinas.EXTENSAO_PNG), sImg32)
								End If
							End If
							Exit Select
						Case TipoExportarExtensao.teTIF
							If True Then
								If extensao.Bmp16 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp16, Rotinas.EXTENSAO_TIFF), sImg16)
								End If
								If extensao.Bmp32 IsNot Nothing Then
									Rotinas.SaveToFile(Rotinas.BmpParaImagem(extensao.Bmp32, Rotinas.EXTENSAO_TIFF), sImg32)
								End If
							End If
							Exit Select

					End Select
				Next
				Return True
			End If
			Return False
		End Function

		Public Sub ImportarExtensao(caminho As String, listaExtensao As List(Of Extensao))
			Dim listaArquivos As StringList, log As StringList
			listaArquivos = New StringList()
			log = New StringList()

			If DiretorioBO.Instancia.carregarArquivos(caminho, listaArquivos) Then
				For Each sArquivo As String In listaArquivos
					SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo), sArquivo, log)
				Next
			End If

		End Sub

		Public Sub ExtrairExtensao(caminho As String, listaExtensao As List(Of Extensao))
			Dim listaArquivos As StringList, log As StringList
			listaArquivos = New StringList()
			log = New StringList()

			If DiretorioBO.Instancia.carregarTodosArquivos(caminho, listaArquivos) Then
				For Each sArquivo As String In listaArquivos
					SalvarExtensao(listaExtensao, Rotinas.ExtractFileName(sArquivo), sArquivo, log)
				Next
			End If
		End Sub

	End Class
End Namespace
