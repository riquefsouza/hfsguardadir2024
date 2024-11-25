'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:58
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Drawing
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.catalogador
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosgui
Imports HFSGuardaDiretorio.objetosbo
Imports HFSGuardaDiretorio.comum

Namespace gui
	''' <summary>
	''' Description of FrmCadExtensao.
	''' </summary>
	Public Partial Class FrmCadExtensao
		Inherits Form
		Private ReadOnly catalogador As HFSGuardaDiretorio.catalogador.Catalogador

		Public Sub New(frmPrincipal As FrmPrincipal)
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'
			InitializeComponent()

			odEscolhaArquivo.Filter = Rotinas.FILTRO_IMAGEM

			catalogador = frmPrincipal.Catalogador
			CarregarExtensoesNaGrid()
		End Sub

		Private Sub CarregarExtensoesNaGrid()
			Dim item As ListViewItem

			lvExtensao.Items.Clear()
			imgListExtensao.Images.Clear()

			For Each extensao As Extensao In catalogador.listaExtensoes
				item = lvExtensao.Items.Add(extensao.Nome)
				item.SubItems.Add("icone")
				imgListExtensao.Images.Add(Rotinas.byteArrayToBitmap(extensao.Bmp16))
			Next
		End Sub

		Private Sub LvExtensaoDrawColumnHeader(sender As Object, e As DrawListViewColumnHeaderEventArgs)
			e.DrawDefault = True
		End Sub

		Private Sub LvExtensaoDrawItem(sender As Object, e As DrawListViewItemEventArgs)
			e.DrawBackground()

			If (e.State And ListViewItemStates.Selected) = ListViewItemStates.Selected Then
				e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds)
				e.Item.ForeColor = SystemColors.HighlightText
			Else
				e.Item.ForeColor = SystemColors.WindowText
			End If

			e.DrawText()
		End Sub

		Private Sub LvExtensaoDrawSubItem(sender As Object, e As DrawListViewSubItemEventArgs)
			If e.ColumnIndex > 0 Then
				e.DrawBackground()

				If (e.ItemState And ListViewItemStates.Selected) = ListViewItemStates.Selected Then
					e.Graphics.FillRectangle(SystemBrushes.Highlight, e.Bounds)
					e.SubItem.ForeColor = SystemColors.HighlightText
				Else
					e.SubItem.ForeColor = SystemColors.WindowText
				End If

				Dim rect As New Rectangle(e.SubItem.Bounds.Left + 20, e.SubItem.Bounds.Top, e.SubItem.Bounds.Width, e.SubItem.Bounds.Height)
				e.Graphics.DrawImageUnscaled(imgListExtensao.Images(e.ItemIndex), rect)
			End If
		End Sub


		Private Sub MenuIncluirExtensaoClick(sender As Object, e As EventArgs)
			Dim log As StringList
			Dim retval As DialogResult = odEscolhaArquivo.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(odEscolhaArquivo.FileName)
				If arquivo.Exists Then
					log = New StringList()

					If ExtensaoBO.Instancia.SalvarExtensao(catalogador.listaExtensoes, arquivo.Name, arquivo.FullName, log) Then

						CarregarExtensoesNaGrid()

						Dialogo.mensagemInfo("Extensão salva com sucesso!")
					Else
						Dialogo.mensagemInfo("Extensão já existe cadastrada!")
					End If
				End If
			End If

		End Sub

		Private Sub MenuExcluirExtensaoClick(sender As Object, e As EventArgs)
			Dim extensao As Extensao

			If catalogador.listaExtensoes.Count > 0 Then
				Dim res As Boolean = Dialogo.confirma("Tem Certeza, que você deseja excluir esta extensão?")
				If res Then
					extensao = ExtensaoBO.Instancia.pegaExtensaoPorOrdem(catalogador.listaExtensoes, lvExtensao.SelectedIndices(0) + 1)

					If ExtensaoBO.Instancia.excluirExtensao(catalogador.listaExtensoes, extensao.Codigo) Then
						CarregarExtensoesNaGrid()
						Dialogo.mensagemInfo("Extensão excluída com sucesso!")
					End If
				End If
			End If

		End Sub

		Private Sub MenuExcluirTodasExtensoesClick(sender As Object, e As EventArgs)
			Dim res As Boolean = Dialogo.confirma("Tem Certeza, que você deseja excluir todas as extensões?")
			If res Then
				If ExtensaoBO.Instancia.excluirTodasExtensoes(catalogador.listaExtensoes) Then
					CarregarExtensoesNaGrid()
					Dialogo.mensagemInfo("Extensões excluídas com sucesso!")
				End If
			End If
		End Sub

		Private Sub MenuExportarBitmapClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.teBMP, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuExportarIconeClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.teICO, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuExportarGIFClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.teGIF, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuExportarJPEGClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.teJPG, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuExportarPNGClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.tePNG, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuExportarTIFFClick(sender As Object, e As EventArgs)
			ExtensaoBO.Instancia.ExportarExtensao(TipoExportarExtensao.teTIF, catalogador.listaExtensoes)
		End Sub

		Private Sub MenuImportarIconesArquivosClick(sender As Object, e As EventArgs)
			Dim retval As DialogResult = odEscolhaArquivo.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(odEscolhaArquivo.FileName)
				If arquivo.Exists Then
					ExtensaoBO.Instancia.ImportarExtensao(arquivo.FullName, catalogador.listaExtensoes)
					CarregarExtensoesNaGrid()
				End If
			End If
		End Sub

		Private Sub MenuExtrairIconesArquivosClick(sender As Object, e As EventArgs)
			Dim retval As DialogResult = odEscolhaArquivo.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(odEscolhaArquivo.FileName)
				If arquivo.Exists Then
					ExtensaoBO.Instancia.ExtrairExtensao(arquivo.FullName, catalogador.listaExtensoes)
					CarregarExtensoesNaGrid()
				End If
			End If
		End Sub

		Private Sub BtnIncluirClick(sender As Object, e As EventArgs)
			MenuIncluirExtensaoClick(sender, e)
		End Sub

		Private Sub BtnExcluirClick(sender As Object, e As EventArgs)
			MenuExcluirExtensaoClick(sender, e)
		End Sub
	End Class
End Namespace
