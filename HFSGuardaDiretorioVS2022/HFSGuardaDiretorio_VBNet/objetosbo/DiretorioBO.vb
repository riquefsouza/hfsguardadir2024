'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 06/07/2015
' * Time: 16:17
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Collections.Generic
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosdao

Namespace objetosbo
	''' <summary>
	''' Description of DiretorioBO.
	''' </summary>
	Public NotInheritable Class DiretorioBO
		Private Shared m_instancia As New DiretorioBO()

		Public Shared ReadOnly SQL_CONSULTA_ARQUIVO As String = "select aba, cod, " + "ordem, coddirpai, nome, tam, tipo, modificado, atributos, " + "caminho, nomeaba, nomepai, caminhopai from consultaarquivo"

		Public Shared ReadOnly Property Instancia() As DiretorioBO
			Get
				Return m_instancia
			End Get
		End Property

		Private Sub New()
		End Sub

		Public Function carregarDiretorio(sSQL As String, progressoLog As IProgressoLog) As List(Of Diretorio)
			Return DiretorioDAO.Instancia.consultarTudo(sSQL, "", progressoLog)
		End Function

		Public Function carregarDiretorio(sSQL As String, sCondicaoTotal As String, progressoLog As IProgressoLog) As List(Of Diretorio)
			Return DiretorioDAO.Instancia.consultarTudo(sSQL, sCondicaoTotal, progressoLog)
		End Function

		Public Function removerDrive(sDiretorio As String) As String
			Dim drives As String() = Directory.GetLogicalDrives()
			Dim i As Integer = 0
			Dim bAchou As Boolean = False
			Dim sArq As String = Rotinas.testaNull(sDiretorio)

			If sArq.Length > 0 Then
				For i = 0 To drives.Length - 1
					If sArq.ToUpper().Contains(drives(i).ToUpper()) Then
						bAchou = True
						Exit For
					End If
				Next
			End If
			sArq = Rotinas.trocaSeparador(sArq)
			If bAchou Then
				Return sArq.Substring(drives(i).Length)
			Else
				Return sArq
			End If
		End Function

		Private Function arquivoAtributos(arquivo As FileInfo, bDiretorio As Boolean) As String
			Dim sAtributos As String = ""

			If bDiretorio Then
				sAtributos += "[DIR]"
			Else
				sAtributos += "[ARQ]"
			End If

			If arquivo IsNot Nothing Then

				If arquivo.Exists Then
					'if (arquivo.Attributes==FileAttributes.Archive) {}		
					If arquivo.IsReadOnly Then
						sAtributos += "[ROL]"
					End If
					If arquivo.Attributes = FileAttributes.Hidden Then
						sAtributos += "[HID]"
					End If
					If arquivo.Attributes = FileAttributes.System Then
						sAtributos += "[SYS]"
					End If
				Else
					'if (arquivo.Directory.Attributes==FileAttributes.Directory) {}
					If arquivo.Directory.Attributes = FileAttributes.Hidden Then
						sAtributos += "[HID]"
					End If
					If arquivo.Directory.Attributes = FileAttributes.System Then
						sAtributos += "[SYS]"
					End If
				End If
			End If
			Return sAtributos
		End Function

		Private Function retCodDirPai(nAba As Integer, sDiretorio As String, listaLocal As List(Of Diretorio)) As Integer
			For Each diretorio As Diretorio In listaLocal
				If diretorio.Aba.Codigo = nAba Then
					If diretorio.Caminho.Equals(sDiretorio) Then
						Return diretorio.Ordem
					End If
				End If
			Next
			Return 0
		End Function

		Public Function MontaTamanho(nTam As Decimal) As String
			Dim nUmKilo As Decimal, nUmMega As Decimal, nUmGiga As Decimal, nUmTera As Decimal, nUmPeta As Decimal
			Dim nTamLocal As Decimal

			nUmKilo = 1024
			nUmMega = nUmKilo * 1024
			nUmGiga = nUmMega * 1024
			nUmTera = nUmGiga * 1024
			nUmPeta = nUmTera * 1024

			If nTam.CompareTo(nUmKilo) = -1 Then
				nTamLocal = nTam
				Return Rotinas.FormatDecimal(nTamLocal) & " Byte(s)"
			ElseIf nTam.CompareTo(nUmKilo) = 1 AndAlso nTam.CompareTo(nUmMega) = -1 Then
				nTamLocal = nTam / nUmKilo
				Return Rotinas.FormatDecimal(nTamLocal) & " KByte(s)"
			ElseIf nTam.CompareTo(nUmMega) = 1 AndAlso nTam.CompareTo(nUmGiga) = -1 Then
				nTamLocal = nTam / nUmMega
				Return Rotinas.FormatDecimal(nTamLocal) & " MByte(s)"
			ElseIf nTam.CompareTo(nUmGiga) = 1 AndAlso nTam.CompareTo(nUmTera) = -1 Then
				nTamLocal = nTam / nUmGiga
				Return Rotinas.FormatDecimal(nTamLocal) & " GByte(s)"
			ElseIf nTam.CompareTo(nUmTera) = 1 AndAlso nTam.CompareTo(nUmPeta) = -1 Then
				nTamLocal = nTam / nUmTera
				Return Rotinas.FormatDecimal(nTamLocal) & " TByte(s)"
			Else
				nTamLocal = nTam / nUmPeta
				Return Rotinas.FormatDecimal(nTamLocal) & " PByte(s)"
			End If
		End Function

		Public Function atribuiDiretorio(nAba As Integer, nCodDirRaiz As Integer, sNomeDirRaiz As String, sDiretorio As String, bDiretorio As Boolean, listaLocal As List(Of Diretorio), _
			arquivo As Arquivo, dirOrdem As DiretorioOrdem) As Diretorio
			Dim nOrdem As Integer = dirOrdem.Ordem
			Dim diretorio As Diretorio
			Dim sCaminho As String, sDir As String
			Dim fCaminho As FileInfo = Nothing

			sCaminho = removerDrive(sDiretorio)
			If sDiretorio.Length > 0 Then
				fCaminho = New FileInfo(sDiretorio)
			End If

			If (sCaminho.Length > 0) AndAlso (sNomeDirRaiz.Length > 0) Then
				If Rotinas.StartsStr(sNomeDirRaiz, sCaminho) Then
					sCaminho = Rotinas.SubString(sCaminho, sNomeDirRaiz.Length + 2, sCaminho.Length)
					sDir = Rotinas.SubString(sDiretorio, sNomeDirRaiz.Length + 2, sDiretorio.Length)
					fCaminho = New FileInfo(sDir)
				Else
					sCaminho = sNomeDirRaiz & Rotinas.BARRA_INVERTIDA & sCaminho
					sDir = sNomeDirRaiz & Rotinas.BARRA_INVERTIDA & sDiretorio
					fCaminho = New FileInfo(sDir)
				End If
			End If

			diretorio = New Diretorio()
			Dim abaLocal As New Aba()
			Dim tipoLocal As New Tipo()

			abaLocal.Codigo = nAba
			diretorio.Codigo = nCodDirRaiz
			diretorio.Ordem = nOrdem
			diretorio.Nome = arquivo.Nome
			diretorio.Tamanho = arquivo.Tamanho
			diretorio.Modificado = arquivo.Modificado
			diretorio.Atributos = arquivoAtributos(fCaminho, bDiretorio)

			If sDiretorio.Length = 0 Then
				diretorio.Caminho = arquivo.Nome
				diretorio.CaminhoPai = ""
			Else
				diretorio.Caminho = sCaminho
				diretorio.CaminhoPai = Rotinas.SubString(diretorio.Caminho, 1, Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA, diretorio.Caminho) - 1)
			End If

			If bDiretorio Then
				tipoLocal.Codigo = "D"C
				If nOrdem = 1 Then
					diretorio.CodDirPai = 0
				Else
					diretorio.CodDirPai = retCodDirPai(abaLocal.Codigo, diretorio.CaminhoPai, listaLocal)
				End If
			Else
				tipoLocal.Codigo = "A"C
				diretorio.CodDirPai = retCodDirPai(abaLocal.Codigo, diretorio.CaminhoPai, listaLocal)
			End If
			abaLocal.Nome = ""
			diretorio.Aba = abaLocal
			diretorio.NomePai = ""
			diretorio.TamanhoFormatado = MontaTamanho(diretorio.Tamanho)
			If tipoLocal.Codigo = "D"C Then
				tipoLocal.Nome = "Diretório"
			Else
				tipoLocal.Nome = "Arquivo"
			End If
			diretorio.Tipo = tipoLocal
			diretorio.ModificadoFormatado = Rotinas.formataDate(Rotinas.FORMATO_DATAHORA, diretorio.Modificado)
			diretorio.CaminhoOriginal = sDiretorio

			nOrdem += 1

			dirOrdem.Ordem = nOrdem

			Return diretorio
		End Function

		Private Function dirPesquisadoToArquivo(dirPesquisado As FileInfo) As Arquivo
			Dim arquivo As New Arquivo()
			arquivo.Nome = dirPesquisado.Name
			If dirPesquisado.Exists Then
				arquivo.Tamanho = dirPesquisado.Length
			Else
				arquivo.Tamanho = 0
			End If
			arquivo.Modificado = dirPesquisado.LastWriteTime
			arquivo.Atributos = arquivoAtributos(dirPesquisado, Not dirPesquisado.Exists)
			Return arquivo
		End Function

		Public Sub atribuiListaDiretorio(nAba As Integer, nCodDirRaiz As Integer, sNomeDirRaiz As String, sDiretorio As String, listaLocal As List(Of Diretorio), dirPesquisado As FileInfo, _
			dirOrdem As DiretorioOrdem, progressoLog As IProgressoLog)
			Dim diretorio As Diretorio
			Dim pb As New Progresso()

			If Rotinas.FileExists(sDiretorio) Then
				diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio, False, listaLocal, _
					dirPesquisadoToArquivo(dirPesquisado), dirOrdem)
				listaLocal.Add(diretorio)

				If progressoLog IsNot Nothing Then
					pb.Log = sDiretorio
					progressoLog.ProgressoLog(pb)
				End If
			ElseIf Rotinas.DirectoryExists(sDiretorio) Then
				If (Not dirPesquisado.Name.Equals(".")) AndAlso (Not dirPesquisado.Name.Equals("..")) Then
					diretorio = atribuiDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio, True, listaLocal, _
						dirPesquisadoToArquivo(dirPesquisado), dirOrdem)
					listaLocal.Add(diretorio)

					If progressoLog IsNot Nothing Then
						pb.Log = sDiretorio
						progressoLog.ProgressoLog(pb)
					End If

					ImportarDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sDiretorio, listaLocal, dirOrdem, _
						progressoLog)
				End If
			End If

		End Sub

		Public Sub ImportarDiretorio(nAba As Integer, nCodDirRaiz As Integer, sNomeDirRaiz As String, sDiretorio As String, listaLocal As List(Of Diretorio), dirOrdem As DiretorioOrdem, _
			progressoLog As IProgressoLog)
			Dim dirPesquisado As FileInfo
			Dim sCaminho As String, sSeparador As String

			If Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).Equals(Path.DirectorySeparatorChar) Then
				sSeparador = ""
			Else
				sSeparador = Path.DirectorySeparatorChar.ToString()
			End If

			sCaminho = sDiretorio & sSeparador

			dirPesquisado = New FileInfo(sCaminho)
			If dirPesquisado.Directory.Exists Then
				For Each dirPesquisado2 As FileInfo In Rotinas.listFiles(dirPesquisado.FullName)
					sCaminho = sDiretorio & sSeparador & dirPesquisado2.Name
					atribuiListaDiretorio(nAba, nCodDirRaiz, sNomeDirRaiz, sCaminho, listaLocal, dirPesquisado2, _
						dirOrdem, progressoLog)
				Next
			End If
		End Sub

		Public Function verificaCodDir(nAba As Integer, sDiretorio As String, listaLocal As List(Of Diretorio)) As Boolean

			If sDiretorio.Length > 0 Then
				For Each diretorio As Diretorio In listaLocal
					If diretorio.Aba.Codigo = nAba Then
						If diretorio.Ordem = 1 Then
							If diretorio.CodDirPai = 0 Then
								If diretorio.Caminho.Equals(sDiretorio) Then
									Return True
								End If
							End If
						End If
					End If
				Next
			End If
			Return False
		End Function

		Public Function retMaxCodDir(nAba As Integer, listaLocal As List(Of Diretorio)) As Integer
			Dim nMaior As Integer = -1

			For Each diretorio As Diretorio In listaLocal
				If diretorio.Aba.Codigo = nAba Then
					If diretorio.Codigo > nMaior Then
						nMaior = diretorio.Codigo
					End If
				End If
			Next
			Return nMaior + 1
		End Function

		Private Function diretorioToSQL(diretorio As Diretorio, bInsert As Boolean) As String
			Dim sSQL As String = ""

			If bInsert Then
				sSQL = "insert into Diretorios(aba, cod, ordem, coddirpai, nome, " & "tam, tipo, modificado, atributos, caminho) values("
			End If

			sSQL += diretorio.Aba.Codigo & ","
			sSQL += diretorio.Codigo & ","
			sSQL += diretorio.Ordem & ","
			sSQL += diretorio.CodDirPai & ","
			sSQL += Rotinas.QuotedStr(diretorio.Nome) & ","
			sSQL += diretorio.Tamanho & ","
			sSQL += Rotinas.QuotedStr(diretorio.Tipo.Codigo) & ","
			sSQL += Rotinas.QuotedStr(diretorio.ModificadoFormatado) & ","
			sSQL += Rotinas.QuotedStr(diretorio.Atributos) & ","
			sSQL += Rotinas.QuotedStr(diretorio.Caminho)

			If bInsert Then
				sSQL += ")"
			End If

			Return sSQL
		End Function

		Public Sub salvarDiretorio(listaDiretorio As List(Of Diretorio), progressoLog As IProgressoLog)
			Dim diretorio As Diretorio
			Dim pb As New Progresso()
			pb.Minimo = 0
			pb.Maximo = listaDiretorio.Count - 1
			pb.Posicao = 0
			pb.Passo = 1

			Try
				For i As Integer = 0 To listaDiretorio.Count - 1
					diretorio = listaDiretorio(i)

					DiretorioDAO.Instancia.incluir(diretorio)
					pb.Log = (i + 1) & " - Salvando Diretório: " & diretorio.Caminho

					pb.Posicao = i

					If progressoLog IsNot Nothing Then
						progressoLog.ProgressoLog(pb)
					End If
				Next
			Catch generatedExceptionName As Exception
				Throw
			End Try

		End Sub

		Public Function excluirDiretorio(aba As Aba, sCaminho As String) As Boolean
			Return (DiretorioDAO.Instancia.excluir(aba, sCaminho) > 0)
		End Function

		Public Sub excluirListaDiretorio(listaDiretorio As List(Of Diretorio), aba As Aba, sCaminho As String)
			Dim diretorio As Diretorio

			For i As Integer = listaDiretorio.Count - 1 To 0 Step -1
				diretorio = listaDiretorio(i)

				If diretorio.Aba.Codigo = aba.Codigo Then
					If sCaminho.Trim().Length > 0 Then
						If Rotinas.StartsStr(sCaminho, diretorio.Caminho) Then
							listaDiretorio.Remove(diretorio)
						End If
					Else
						listaDiretorio.Remove(diretorio)
					End If
				End If
			Next

		End Sub

		Private Function diretorioToCSV(diretorio As Diretorio) As String
			Dim sCSV As String

			sCSV = """"

			sCSV += diretorio.Aba.Nome & """;"""
			sCSV += diretorio.Nome & """;"""
			sCSV += diretorio.Tamanho & """;"""
			sCSV += diretorio.TamanhoFormatado & """;"""
			sCSV += diretorio.Tipo.Nome & """;"""
			sCSV += diretorio.ModificadoFormatado & """;"""
			sCSV += diretorio.Atributos & """;"""
			sCSV += diretorio.Caminho & """"

			Return sCSV
		End Function

		Private Function diretorioToXML(diretorio As Diretorio) As String
			Dim sXML As String, sCR As String, sTAB As String, sTAB2 As String

			sTAB = vbTab
			sTAB2 = vbTab & vbTab
			sCR = vbLf

			sXML = sTAB & "<arquivo>" & sCR

			sXML += sTAB2 & "<aba>" & diretorio.Aba.Codigo & "</aba>" & sCR
			sXML += sTAB2 & "<nomeAba>" & diretorio.Aba.Nome & "</nomeAba>" & sCR
			sXML += sTAB2 & "<codigo>" & diretorio.Codigo & "</codigo>" & sCR
			sXML += sTAB2 & "<ordem>" & diretorio.Ordem & "</ordem>" & sCR
			sXML += sTAB2 & "<nome>" & diretorio.Nome & "</nome>" & sCR
			sXML += sTAB2 & "<tamanho>" & diretorio.Tamanho & "</tamanho>" & sCR
			sXML += sTAB2 & "<tipo>" & diretorio.Tipo.Codigo & "</tipo>" & sCR
			sXML += sTAB2 & "<modificado>" & diretorio.ModificadoFormatado & "</modificado>" & sCR
			sXML += sTAB2 & "<atributos>" & diretorio.Atributos & "</atributos>" & sCR
			sXML += sTAB2 & "<codDirPai>" & diretorio.CodDirPai & "</codDirPai>" & sCR
			sXML += sTAB2 & "<caminho>" & diretorio.Caminho & "</caminho>" & sCR

			sXML += sTAB & "</arquivo>"

			Return sXML
		End Function

		Private Function diretorioToTXT(diretorio As Diretorio) As String
			Dim sTXT As String, sTAB As String

			sTAB = vbTab
			sTXT = ""
			sTXT += diretorio.Aba.Nome & sTAB
			sTXT += diretorio.Nome & sTAB
			sTXT += diretorio.Tamanho & sTAB
			sTXT += diretorio.TamanhoFormatado & sTAB
			sTXT += diretorio.Tipo.Nome & sTAB
			sTXT += diretorio.ModificadoFormatado & sTAB
			sTXT += diretorio.Atributos & sTAB
			sTXT += diretorio.Caminho

			Return sTXT
		End Function

		Private Function diretorioToHTML(diretorio As Diretorio) As String
			Dim sHTML As String, sCR As String, sTAB As String, sTAB2 As String

			sTAB = vbTab
			sTAB2 = vbTab & vbTab
			sCR = vbLf

			sHTML = sTAB & "<tr>" & sCR

			sHTML += sTAB2 & "<td>" & diretorio.Aba.Nome & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & diretorio.Nome & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & diretorio.Tamanho & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & Rotinas.StringReplaceAll(diretorio.TamanhoFormatado, " ", "&nbsp;") & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & diretorio.Tipo.Nome & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & Rotinas.StringReplaceAll(diretorio.ModificadoFormatado, " ", "&nbsp;") & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & diretorio.Atributos & "</td>" & sCR
			sHTML += sTAB2 & "<td>" & diretorio.Caminho & "</td>" & sCR

			sHTML += sTAB & "</tr>"
			Return sHTML
		End Function

		Public Sub exportarDiretorio(tipo As TipoExportar, aba As Aba, sNomeArquivo As String, progressoLog As IProgressoLog)
			Dim sTexto As String = "", sCR As String, sTAB As String, sTAB2 As String, sSQL As String, sCondicaoTotal As String
			Dim abaLocal As New Aba()
			Dim listaLocal As StringList
			Dim listaDiretorio As List(Of Diretorio)

			sTAB = vbTab
			sTAB2 = vbTab & vbTab
			sCR = vbLf

			sCondicaoTotal = " where aba=" & aba.Codigo
			sSQL = SQL_CONSULTA_ARQUIVO & sCondicaoTotal & " order by 1, 2, 3"
			listaDiretorio = carregarDiretorio(sSQL, sCondicaoTotal, progressoLog)

			listaLocal = New StringList()

			Select Case tipo
				Case TipoExportar.teCSV
					If True Then
						sTexto = """Aba"";""Nome"";""TamanhoBytes"";""Tamanho"";" & """Tipo"";""Modificado"";""Atributos"";""Caminho"""
					End If
					Exit Select
				Case TipoExportar.teHTML
					If True Then
						sTexto = "<!DOCTYPE html>" & sCR
						sTexto += "<html>" & sCR
						sTexto += "<body>" & sCR
						sTexto += "<table border=""1"" cellpadding=""5"" cellspacing=""0"">" & sCR
						sTexto += sTAB & "<tr>" & sCR
						sTexto += sTAB2 & "<th>Aba</th>" & sCR
						sTexto += sTAB2 & "<th>Nome</th>" & sCR
						sTexto += sTAB2 & "<th>Tamanho</th>" & sCR
						sTexto += sTAB2 & "<th>Tamanho Formatado</th>" & sCR
						sTexto += sTAB2 & "<th>Tipo</th>" & sCR
						sTexto += sTAB2 & "<th>Modificado</th>" & sCR
						sTexto += sTAB2 & "<th>Atributos</th>" & sCR
						sTexto += sTAB2 & "<th>Caminho</th>" & sCR
						sTexto += sTAB & "</tr>"
					End If
					Exit Select
				Case TipoExportar.teXML
					If True Then
						sTexto = "<diretorio>"
					End If
					Exit Select
				Case TipoExportar.teSQL
					If True Then
						abaLocal.Codigo = listaDiretorio(0).Aba.Codigo
						abaLocal.Nome = listaDiretorio(0).Aba.Nome
						sTexto = AbaBO.Instancia.abaToSQL(abaLocal)
					End If
					Exit Select
			End Select

			If sTexto.Length > 0 Then
				listaLocal.Add(sTexto)
			End If

			For Each diretorio As Diretorio In listaDiretorio
				If diretorio.Aba.Codigo = aba.Codigo Then
					If tipo = TipoExportar.teTXT Then
						sTexto = diretorioToTXT(diretorio)
					ElseIf tipo = TipoExportar.teCSV Then
						sTexto = diretorioToCSV(diretorio)
					ElseIf tipo = TipoExportar.teHTML Then
						sTexto = diretorioToHTML(diretorio)
					ElseIf tipo = TipoExportar.teXML Then
						sTexto = diretorioToXML(diretorio)
					ElseIf tipo = TipoExportar.teSQL Then
						sTexto = diretorioToSQL(diretorio, True) & ";"
					End If

					listaLocal.Add(sTexto)
				End If
			Next

			If tipo = TipoExportar.teHTML Then
				sTexto += sCR & "</table>" & sCR
				sTexto += "</body>" & sCR
				sTexto += "</html>" & sCR
			ElseIf tipo = TipoExportar.teXML Then
				sTexto = "</diretorio>"
			End If
			listaLocal.Add(sTexto)

			listaLocal.SaveToFile(sNomeArquivo)

			listaDiretorio.Clear()
			listaLocal.Clear()
		End Sub

		Public Function criarTabelaDiretorios() As Boolean
			Return (DiretorioDAO.Instancia.criarTabela() > 0)
		End Function

		Private Function XMLParaDiretorio(sTexto As String, nArquivo As Integer, diretorioXML As DiretorioXML) As Integer
			Dim sTagInicio As String = "", sValor As String = "", sTagFim As String = ""
			Dim resultado As Integer

			resultado = nArquivo

			If Rotinas.Pos(">", sTexto) > 0 Then
				sTagInicio = Rotinas.SubString(sTexto, 1, Rotinas.Pos(">", sTexto))
			End If
			If (Rotinas.Pos(">", sTexto) > 0) AndAlso (Rotinas.Pos("</", sTexto) > 1) Then
				sValor = Rotinas.SubString(sTexto, Rotinas.Pos(">", sTexto) + 1, Rotinas.Pos("</", sTexto) - Rotinas.Pos(">", sTexto) - 1)
			End If
			If Rotinas.LastDelimiter(">", sTexto) > 0 Then
				sTagFim = Rotinas.SubString(sTexto, Rotinas.LastDelimiter("<", sTexto), Rotinas.LastDelimiter(">", sTexto))
			End If

			If (nArquivo = 1) AndAlso (Not sTagInicio.Equals("<arquivo>")) Then
				resultado = -1
			End If
			If (nArquivo = 2) AndAlso (Not sTagInicio.Equals("<aba>")) AndAlso (Not sTagFim.Equals("</aba>")) Then
				' diretorio.aba.codigo = StrToInt(sValor);
				resultado = -1
			End If
			If (nArquivo = 3) AndAlso (Not sTagInicio.Equals("<nomeAba>")) AndAlso (Not sTagFim.Equals("</nomeAba>")) Then
				' diretorio.aba.nome = sValor;
				resultado = -1
			End If
			If (nArquivo = 4) AndAlso (sTagInicio.Equals("<codigo>")) AndAlso (sTagFim.Equals("</codigo>")) Then
				diretorioXML.Diretorio.Codigo = Convert.ToInt32(sValor)
			End If
			If (nArquivo = 5) AndAlso (sTagInicio.Equals("<ordem>")) AndAlso (sTagFim.Equals("</ordem>")) Then
				diretorioXML.Diretorio.Ordem = Convert.ToInt32(sValor)
			End If
			If (nArquivo = 6) AndAlso (sTagInicio.Equals("<nome>")) AndAlso (sTagFim.Equals("</nome>")) Then
				diretorioXML.Diretorio.Nome = sValor
			End If
			If (nArquivo = 7) AndAlso (sTagInicio.Equals("<tamanho>")) AndAlso (sTagFim.Equals("</tamanho>")) Then
				diretorioXML.Diretorio.Tamanho = Convert.ToInt64(sValor)
			End If
			If (nArquivo = 8) AndAlso (sTagInicio.Equals("<tipo>")) AndAlso (sTagFim.Equals("</tipo>")) Then
				Dim tp As New Tipo()
				tp.Codigo = sValor(0)
				diretorioXML.Diretorio.Tipo = tp
			End If
			If (nArquivo = 9) AndAlso (sTagInicio.Equals("<modificado>")) AndAlso (sTagFim.Equals("</modificado>")) Then
				diretorioXML.Diretorio.Modificado = Rotinas.StringToDate(sValor)
			End If
			If (nArquivo = 10) AndAlso (sTagInicio.Equals("<atributos>")) AndAlso (sTagFim.Equals("</atributos>")) Then
				diretorioXML.Diretorio.Atributos = sValor
			End If
			If (nArquivo = 11) AndAlso (sTagInicio.Equals("<codDirPai>")) AndAlso (sTagFim.Equals("</codDirPai>")) Then
				diretorioXML.Diretorio.CodDirPai = Convert.ToInt32(sValor)
			End If
			If (nArquivo = 12) AndAlso (sTagInicio.Equals("<caminho>")) AndAlso (sTagFim.Equals("</caminho>")) Then
				diretorioXML.Diretorio.Caminho = sValor
			End If
			If (nArquivo = 13) AndAlso (Not sTagInicio.Equals("</arquivo>")) Then
				resultado = -1
			End If
			If sTagInicio.Equals("</diretorio>") Then
				resultado = -3
			End If

			Return resultado
		End Function

		Public Function importarDiretorioViaXML(aba As Aba, sNomeArquivo As String, listaDirPai As List(Of Diretorio), progressoLog As IProgressoLog) As Integer
			Dim sTexto As String
			Dim nArquivo As Integer, resultado As Integer
			Dim listaLocal As StringList
			Dim diretorioXML As DiretorioXML
			Dim listaDiretorio As List(Of Diretorio)

			resultado = 0
			diretorioXML = New DiretorioXML()
			listaDiretorio = New List(Of Diretorio)()
			listaLocal = New StringList()
			listaLocal.LoadFromFile(sNomeArquivo)

			If Not listaLocal(0).Equals("<diretorio>") Then
				resultado = -1
			Else
				nArquivo = 0
				For Each sTexto1 As String In listaLocal
					sTexto = sTexto1.Trim()

					nArquivo = XMLParaDiretorio(sTexto, nArquivo, diretorioXML)

					If nArquivo = -1 Then
						resultado = -1
						Exit For
					ElseIf nArquivo = 13 Then
						nArquivo = 1
						diretorioXML.Diretorio.Aba = aba
						listaDiretorio.Add(diretorioXML.Diretorio)

						If verificaCodDir(aba.Codigo, diretorioXML.Diretorio.Caminho, listaDirPai) Then
							resultado = -2
							Exit For
						End If

						diretorioXML.Diretorio = New Diretorio()
					ElseIf nArquivo = -3 Then
						resultado = nArquivo
					Else
						nArquivo += 1
					End If
				Next
			End If

			salvarDiretorio(listaDiretorio, progressoLog)
			listaDiretorio.Clear()

			Return resultado
		End Function

		Public Function carregarSubDiretorios(sDiretorio As String, listaLocal As StringList) As Boolean
			Dim dirPesquisado As FileInfo
			Dim sCaminho As String, sSeparador As String

			If Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).Equals(Path.DirectorySeparatorChar) Then
				sSeparador = ""
			Else
				sSeparador = Path.DirectorySeparatorChar.ToString()
			End If

			sCaminho = sDiretorio & sSeparador
			dirPesquisado = New FileInfo(sCaminho)
			If dirPesquisado.Directory.Exists Then
				For Each dirPesquisado2 As FileInfo In Rotinas.listFiles(dirPesquisado.FullName)
					sCaminho = sDiretorio & sSeparador & dirPesquisado2.Name

					If dirPesquisado2.Directory.Exists Then
						If Rotinas.DirectoryExists(sCaminho) Then
							If (Not dirPesquisado2.Name.Equals(".")) AndAlso (Not dirPesquisado2.Name.Equals("..")) Then
								listaLocal.Add(sCaminho)
							End If
						End If
					End If
				Next
			End If

			Return (listaLocal.Count > 0)
		End Function

		Public Function carregarArquivos(sDiretorio As String, listaLocal As StringList) As Boolean
			Dim dirPesquisado As FileInfo
			Dim sCaminho As String, sSeparador As String

			If Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).Equals(Path.DirectorySeparatorChar) Then
				sSeparador = ""
			Else
				sSeparador = Path.DirectorySeparatorChar.ToString()
			End If

			sCaminho = sDiretorio & sSeparador
			dirPesquisado = New FileInfo(sCaminho)
			If dirPesquisado.Directory.Exists Then
				For Each dirPesquisado2 As FileInfo In Rotinas.listFiles(dirPesquisado.FullName)
					sCaminho = sDiretorio & sSeparador & dirPesquisado2.Name

					If dirPesquisado2.Exists Then
						If Rotinas.FileExists(sCaminho) Then
							If (Not dirPesquisado.Name.Equals(".")) AndAlso (Not dirPesquisado.Name.Equals("..")) Then
								listaLocal.Add(sCaminho)
							End If
						End If
					End If
				Next
			End If

			Return (listaLocal.Count > 0)
		End Function

		Public Function carregarTodosArquivos(sDiretorio As String, listaLocal As StringList) As Boolean
			Dim dirPesquisado As FileInfo
			Dim sCaminho As String, sSeparador As String

			If Rotinas.SubString(sDiretorio, sDiretorio.Length, 1).Equals(Path.DirectorySeparatorChar) Then
				sSeparador = ""
			Else
				sSeparador = Path.DirectorySeparatorChar.ToString()
			End If

			sCaminho = sDiretorio & sSeparador
			dirPesquisado = New FileInfo(sCaminho)
			If dirPesquisado.Directory.Exists Then
				sCaminho = sDiretorio & sSeparador & dirPesquisado.Name

				If Rotinas.FileExists(sCaminho) Then
					listaLocal.Add(sCaminho)
				ElseIf Rotinas.DirectoryExists(sCaminho) Then
					If (Not dirPesquisado.Name.Equals(".")) AndAlso (Not dirPesquisado.Name.Equals("..")) Then
						carregarTodosArquivos(sCaminho, listaLocal)
					End If
				End If

				For Each dirPesquisado2 As FileInfo In Rotinas.listFiles(dirPesquisado.FullName)
					sCaminho = sDiretorio & sSeparador & dirPesquisado2.Name

					If Rotinas.FileExists(sCaminho) Then
						listaLocal.Add(sCaminho)
					ElseIf Rotinas.DirectoryExists(sCaminho) Then
						If (Not dirPesquisado2.Name.Equals(".")) AndAlso (Not dirPesquisado2.Name.Equals("..")) Then
							carregarTodosArquivos(sCaminho, listaLocal)
						End If
					End If
				Next
			End If
			Return (listaLocal.Count > 0)
		End Function

		Public Function itensFilhos(lista_pai As List(Of Diretorio), aba As Integer, codDirPai As Integer, codigo As Integer) As List(Of Diretorio)
			Dim lista As New List(Of Diretorio)()

			For Each diretorio As Diretorio In lista_pai
				If diretorio.Aba.Codigo = aba Then
					If diretorio.CodDirPai = codDirPai Then
						If diretorio.Codigo = codigo Then
							lista.Add(diretorio)
						End If
					End If
				End If
			Next
			Return lista
		End Function

	End Class
End Namespace
