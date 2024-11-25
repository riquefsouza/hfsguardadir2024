'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:39
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Collections.Generic
Imports System.Drawing
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.catalogador
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetosgui

Namespace gui
	''' <summary>
	''' Description of MainForm.
	''' </summary>
	Public Partial Class FrmPrincipal
		Inherits Form
		Private frmPrincipalProgresso As FrmPrincipalProgresso
		Private ReadOnly m_catalogador As HFSGuardaDiretorio.catalogador.Catalogador
		Private colOrdem As Integer

		Public Sub New()
			colOrdem = -1
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'
			InitializeComponent()

			frmPrincipalProgresso = New FrmPrincipalProgresso(Me)
			m_catalogador = New HFSGuardaDiretorio.catalogador.Catalogador(Me)
		End Sub

		Public ReadOnly Property Catalogador() As HFSGuardaDiretorio.catalogador.Catalogador
			Get
				Return m_catalogador
			End Get
		End Property

		Private Sub MenuIncluirNovaAbaClick(sender As Object, e As EventArgs)
			m_catalogador.IncluirNovaAba()
		End Sub

		Private Sub MenuAlterarNomeAbaAtivaClick(sender As Object, e As EventArgs)
			m_catalogador.AlterarNomeAbaAtiva(frmPrincipalProgresso)
		End Sub

		Private Sub MenuExcluirAbaAtivaClick(sender As Object, e As EventArgs)
			m_catalogador.ExcluirAbaAtiva(frmPrincipalProgresso)
		End Sub

		Private Sub MenuImportarDiretorioClick(sender As Object, e As EventArgs)
			m_catalogador.ComecaImportacao(False, frmPrincipalProgresso)
		End Sub

		Private Sub MenuImportarSubDiretoriosClick(sender As Object, e As EventArgs)
			m_catalogador.ComecaImportacao(True, frmPrincipalProgresso)
		End Sub

		Private Sub MenuCadastrarExtensaoArquivoClick(sender As Object, e As EventArgs)
			Dim frmCadExtensao As New FrmCadExtensao(Me)
			frmCadExtensao.ShowDialog()
		End Sub

		Private Sub MenuCompararDiretoriosClick(sender As Object, e As EventArgs)
			Dim frmCompararDiretorio As New FrmCompararDiretorio(Me)
			frmCompararDiretorio.ShowDialog()
		End Sub

		Private Sub MenuSobreCatalogadorClick(sender As Object, e As EventArgs)
			Dim frmSobre As New FrmSobre()
			frmSobre.ShowDialog()
		End Sub

		Private Sub MenuExpandirDiretoriosClick(sender As Object, e As EventArgs)
			m_catalogador.getArvoreAtual().ExpandAll()
		End Sub

		Private Sub MenuColapsarDiretoriosClick(sender As Object, e As EventArgs)
			m_catalogador.getArvoreAtual().CollapseAll()
		End Sub

		Private Sub MenuTXTClick(sender As Object, e As EventArgs)
			m_catalogador.ExportarArquivo(TipoExportar.teTXT, frmPrincipalProgresso)
		End Sub

		Private Sub MenuCSVClick(sender As Object, e As EventArgs)
			m_catalogador.ExportarArquivo(TipoExportar.teCSV, frmPrincipalProgresso)
		End Sub

		Private Sub MenuHTMLClick(sender As Object, e As EventArgs)
			m_catalogador.ExportarArquivo(TipoExportar.teHTML, frmPrincipalProgresso)
		End Sub

		Private Sub MenuXMLClick(sender As Object, e As EventArgs)
			m_catalogador.ExportarArquivo(TipoExportar.teXML, frmPrincipalProgresso)
		End Sub

		Private Sub MenuSQLClick(sender As Object, e As EventArgs)
			m_catalogador.ExportarArquivo(TipoExportar.teSQL, frmPrincipalProgresso)
		End Sub

		Private Sub MenuImportarDiretoriosViaXMLClick(sender As Object, e As EventArgs)
			Dim log As New StringList()
			m_catalogador.ImportarArquivo(log, frmPrincipalProgresso)
		End Sub

		Private Sub MenuMostrarOcultArvoreDirAbaAtivaClick(sender As Object, e As EventArgs)
			m_catalogador.mostrarOcultarArvore()
		End Sub

		Private Sub MenuMostrarOcultarListaItensPesquisadosClick(sender As Object, e As EventArgs)
			spPesquisa.Panel2Collapsed = Not spPesquisa.Panel2Collapsed
		End Sub

		Private Sub BtnImportarDiretorioClick(sender As Object, e As EventArgs)
			MenuImportarDiretorioClick(sender, e)
		End Sub

		Private Sub BtnPesquisarClick(sender As Object, e As EventArgs)
			m_catalogador.Pesquisar()
		End Sub

		Private Sub FrmPrincipalFormClosed(sender As Object, e As FormClosedEventArgs)
			Rotinas.Desconectar()
		End Sub

		Private Sub MenuInformacoesDiretorioArquivoClick(sender As Object, e As EventArgs)
			m_catalogador.InformacoesDiretorioArquivo()
		End Sub

		Private Sub MenuExcluirDiretorioSelecionadoClick(sender As Object, e As EventArgs)
			m_catalogador.ExcluirDiretorioSelecionado(frmPrincipalProgresso)
		End Sub

		Private Sub MenuIconesClick(sender As Object, e As EventArgs)
			m_catalogador.getTabelaAtual().View = View.LargeIcon
		End Sub

		Private Sub MenuListaClick(sender As Object, e As EventArgs)
			m_catalogador.getTabelaAtual().View = View.List
		End Sub

		Private Sub MenuDetalhesClick(sender As Object, e As EventArgs)
			m_catalogador.getTabelaAtual().View = View.Details
		End Sub

		Private Sub MenuIconesPequenosClick(sender As Object, e As EventArgs)
			m_catalogador.getTabelaAtual().View = View.SmallIcon
		End Sub

		Private Sub MenuExpandirDiretorios2Click(sender As Object, e As EventArgs)
			MenuExpandirDiretoriosClick(sender, e)
		End Sub

		Private Sub MenuColapsarDiretorios2Click(sender As Object, e As EventArgs)
			MenuColapsarDiretoriosClick(sender, e)
		End Sub

		Private Sub MenuIncluirNovaAba2Click(sender As Object, e As EventArgs)
			MenuIncluirNovaAbaClick(sender, e)
		End Sub

		Private Sub MenuAlterarNomeAbaAtiva2Click(sender As Object, e As EventArgs)
			MenuAlterarNomeAbaAtivaClick(sender, e)
		End Sub

		Private Sub MenuExcluirAbaAtiva2Click(sender As Object, e As EventArgs)
			MenuExcluirAbaAtivaClick(sender, e)
		End Sub

		Private Sub TabControl1SelectedIndexChanged(sender As Object, e As EventArgs)
			m_catalogador.tabPanelMudou()
		End Sub

		Public Sub LvFixaDoubleClick(sender As Object, e As EventArgs)
			Dim lvTabela As ListView = DirectCast(sender, ListView)

			If lvTabela.SelectedItems.Count > 0 Then
				Dim nome As String = lvTabela.SelectedItems(0).Text
				Dim tipo As String = lvTabela.SelectedItems(0).SubItems(2).Text

				m_catalogador.DuploCliqueLista(nome, tipo)
			End If
		End Sub

		Public Sub LvFixaColumnClick(sender As Object, e As ColumnClickEventArgs)
			Dim lvTabela As ListView = DirectCast(sender, ListView)
			colOrdem = m_catalogador.listaCompara(lvTabela, e.Column, colOrdem)
		End Sub

		Private Sub LvPesquisaColumnClick(sender As Object, e As ColumnClickEventArgs)
			Dim lvTabela As ListView = DirectCast(sender, ListView)
			colOrdem = m_catalogador.listaCompara(lvTabela, e.Column, colOrdem)
		End Sub

		Private Sub LvPesquisaClick(sender As Object, e As EventArgs)
			Dim lvPesquisa As ListView = DirectCast(sender, ListView)

			If lvPesquisa.SelectedItems.Count > 0 Then
				Dim nome As String = lvPesquisa.SelectedItems(0).Text
				Dim caminho As String = lvPesquisa.SelectedItems(0).SubItems(5).Text
				Dim nomeAba As String = lvPesquisa.SelectedItems(0).SubItems(6).Text

				m_catalogador.EncontrarItemLista(nomeAba, nome, caminho)
			End If
		End Sub

		Public Sub TvFixaAfterSelect(sender As Object, e As TreeViewEventArgs)
			Dim lvTabela As ListView = m_catalogador.getTabelaAtual()
			m_catalogador.ListarArquivos(lvTabela, e.Node)
		End Sub

	End Class
End Namespace
