'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:44
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Drawing
Imports System.Windows.Forms
Imports System.Collections.Generic
Imports HFSGuardaDiretorio.catalogador
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosbo
Imports HFSGuardaDiretorio.objetosgui

Namespace gui
	''' <summary>
	''' Description of FrmCompararDiretorio.
	''' </summary>
	Public Partial Class FrmCompararDiretorio
		Inherits Form
		Private frmCompararDiretorioProgresso As FrmCompararDiretorioProgresso
		Private ReadOnly catalogador As HFSGuardaDiretorio.catalogador.Catalogador

		Public listaCompara As List(Of Diretorio)

		Public Sub New(frmPrincipal As FrmPrincipal)
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'
			InitializeComponent()

			listaCompara = New List(Of Diretorio)()
			frmCompararDiretorioProgresso = New FrmCompararDiretorioProgresso(Me)
			catalogador = frmPrincipal.Catalogador
			CarregarDados()
			LimparComparacao()
		End Sub

		Private Sub BtnSalvarLogClick(sender As Object, e As EventArgs)
			Dim sLog As String
			Dim listaLocal As StringList

			If listaCompara.Count > 0 Then
				listaLocal = New StringList()
				sLog = Rotinas.ExtractFilePath(Application.ExecutablePath) & Path.DirectorySeparatorChar & Rotinas.formataDate(Rotinas.FORMATO_DHARQUIVO, DateTime.Now) & "_Comparacao.log"

				For Each diretorio As Diretorio In listaCompara
					listaLocal.Add(diretorio.Caminho)
				Next

				listaLocal.SaveToFile(sLog)

				Dialogo.mensagemInfo("Log salvo no mesmo diretório do sistema!")
			End If

		End Sub

		Private Sub BtnCompararDiretoriosClick(sender As Object, e As EventArgs)
			Dim sCaminhoDir1 As String = "", sCaminhoDir2 As String = ""
			Dim bSelecionado As Boolean

			bSelecionado = False
			If tvDiretorio1.SelectedNode.IsSelected Then
				catalogador.LerArvoreDiretorio(tvDiretorio1.SelectedNode, barraStatus)
				sCaminhoDir1 = labStatus2.Text

				If tvDiretorio2.SelectedNode.IsSelected Then
					catalogador.LerArvoreDiretorio(tvDiretorio2.SelectedNode, barraStatus)
					sCaminhoDir2 = labStatus2.Text
					bSelecionado = True
				End If
			End If

			LimparComparacao()

			If bSelecionado Then
				Comparar(sCaminhoDir1, sCaminhoDir2)
			Else
				Dialogo.mensagemInfo("Diretórios não selecionados!")
			End If
		End Sub

		Private Sub CmbAba1SelectedIndexChanged(sender As Object, e As EventArgs)
			Dim aba As Aba

			Cursor = Cursors.WaitCursor

			tvDiretorio1.Nodes.Clear()
			aba = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, cmbAba1.SelectedIndex + 1)
			catalogador.CarregarArvore(tvDiretorio1, aba)
			tvDiretorio1.[Select]()
			LimparComparacao()

			Cursor = Cursors.[Default]
		End Sub

		Private Sub CmbAba2SelectedIndexChanged(sender As Object, e As EventArgs)
			Dim aba As Aba

			Cursor = Cursors.WaitCursor

			tvDiretorio2.Nodes.Clear()
			aba = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, cmbAba2.SelectedIndex + 1)
			catalogador.CarregarArvore(tvDiretorio2, aba)
			tvDiretorio2.[Select]()
			LimparComparacao()

			Cursor = Cursors.[Default]
		End Sub

		Private Sub CarregarDados()
			For Each aba As Aba In catalogador.listaAbas
				cmbAba1.Items.Add(aba.Nome)
				cmbAba2.Items.Add(aba.Nome)
			Next
			cmbAba1.SelectedIndex = 0
			cmbAba2.SelectedIndex = 0
		End Sub

		Private Sub LimparComparacao()
			pb.Value = 0
			lvCompara.Items.Clear()
			btnSalvarLog.Enabled = False
			labStatus2.Text = ""
		End Sub

		Private Function SQLCompara(aba1 As Aba, aba2 As Aba, caminho1 As String, caminho2 As String) As String
			Dim sSQL As String

			sSQL = DiretorioBO.SQL_CONSULTA_ARQUIVO & " WHERE aba=" & aba1.Codigo & " AND caminho LIKE " & Rotinas.QuotedStr(caminho1 & "%") & " AND nome NOT IN (SELECT nome FROM Diretorios " & " WHERE aba=" & aba2.Codigo & " AND caminho LIKE " & Rotinas.QuotedStr(caminho2 & "%") & ")" & " ORDER BY 1, 2, 3"
			Return sSQL
		End Function

		Private Sub Comparar(sCaminhoDir1 As String, sCaminhoDir2 As String)
			Dim sSQL As String
			Dim aba1 As Aba, aba2 As Aba
			Dim tamLista As Integer

			aba1 = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, cmbAba1.SelectedIndex + 1)
			aba2 = AbaBO.Instancia.pegaAbaPorOrdem(catalogador.listaAbas, cmbAba2.SelectedIndex + 1)

			sSQL = SQLCompara(aba1, aba2, sCaminhoDir1, sCaminhoDir2)
			listaCompara = DiretorioBO.Instancia.carregarDiretorio(sSQL, "consultaarquivo", frmCompararDiretorioProgresso)

			If listaCompara.Count > 0 Then
				Tabela.Instancia.Carregar(True, lvCompara, listaCompara, catalogador.listaExtensoes, pb)

				tamLista = listaCompara.Count
				labStatus2.Text = tamLista.ToString()
				btnSalvarLog.Enabled = True
			Else
				Dialogo.mensagemInfo("Nenhuma diferença encontrada!")
			End If
		End Sub

	End Class
End Namespace
