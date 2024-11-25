'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 07/07/2015
' * Time: 11:02
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Drawing
Imports System.Collections.Generic
Imports System.Windows.Forms
Imports HFSGuardaDiretorio.comum
Imports HFSGuardaDiretorio.objetos
Imports HFSGuardaDiretorio.objetosbo
Imports HFSGuardaDiretorio.objetosdao
Imports HFSGuardaDiretorio.gui
Imports HFSGuardaDiretorio.objetosgui

Namespace catalogador
	''' <summary>
	''' Description of Catalogador.
	''' </summary>
	Public Class Catalogador
		Implements ICatalogador
		Private Shared ReadOnly CONSULTA_DIR_PAI As String = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " + "atributos, caminho, nomeaba, nomepai, caminhopai " + "from consultadirpai " + "order by 1,2,3,4"
		Private Shared ReadOnly CONSULTA_DIR_FILHO As String = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " + "atributos, caminho, nomeaba, nomepai, caminhopai " + "from consultadirfilho " + "order by 1,2,3,4"
		Public Shared ReadOnly CONSULTA_ARQUIVO As String = "select aba, cod, ordem, coddirpai, nome, tam, tipo, modificado, " + "atributos, caminho, nomeaba, nomepai, caminhopai " + "from consultaarquivo " + "order by tipo desc, ordem"

		Private Shared ReadOnly NO_RAIZ As String = "Raiz"

		Private Shared ReadOnly log As New ArquivoLog()
		'Logger.getLogger(Rotinas.HFSGUARDADIR);
		Private listaDiretorioFilho As List(Of Diretorio)
		Private listaArquivos As List(Of Diretorio)

		Public diretorioOrdem As DiretorioOrdem

		Public listaAbas As List(Of Aba)
		Public listaDiretorioPai As List(Of Diretorio)
		Public listaExtensoes As List(Of Extensao)

		Private nodeRaiz As TreeNode

		Private ReadOnly form As FrmPrincipal

		Public Sub New(form As FrmPrincipal)
			Me.form = form

			diretorioOrdem = New DiretorioOrdem()

			listaAbas = New List(Of Aba)()
			listaExtensoes = New List(Of Extensao)()
			listaDiretorioPai = New List(Of Diretorio)()
			listaDiretorioFilho = New List(Of Diretorio)()
			listaArquivos = New List(Of Diretorio)()

			form.spPesquisa.Panel2Collapsed = True

			form.Cursor = Cursors.WaitCursor
			Dim frmSplash As New FrmSplash()
			Dim frmSplashProgresso As New FrmSplashProgresso(frmSplash)

			frmSplash.Show()
			frmSplash.Update()
			CarregarDados(frmSplashProgresso, True, True)
			CarregarAbas()
			tabPanelMudou()

			frmSplash.Close()
			frmSplash.Dispose()

			form.Cursor = Cursors.[Default]
		End Sub

		Public Shared Sub iniciarSistema()
			Dim aba As Aba
			Dim sBanco As String = Rotinas.ExtractFilePath(Application.ExecutablePath) & Path.DirectorySeparatorChar & "GuardaDir.db"
			Dim cp As New ConexaoParams()
			cp.Nome = sBanco

			If Not Rotinas.FileExists(sBanco) Then
				Rotinas.Conectar(cp)

				AbaBO.Instancia.criarTabelaAbas()

				aba = New Aba(1, "DISCO1", 0)
				AbaBO.Instancia.incluirAba(aba)

				ExtensaoBO.Instancia.criarTabelaExtensoes()
				DiretorioBO.Instancia.criarTabelaDiretorios()
				VisaoDAO.Instancia.criarVisao("consultadirpai")
				VisaoDAO.Instancia.criarVisao("consultadirfilho")
				VisaoDAO.Instancia.criarVisao("consultaarquivo")
			Else
				Rotinas.Conectar(cp)
			End If

		End Sub

		Public Sub CarregarDados(pLog As IProgressoLog, bExtensao As Boolean, bDiretorio As Boolean)
			listaAbas = AbaBO.Instancia.carregarAba(pLog)
			If bExtensao Then
				listaExtensoes = ExtensaoBO.Instancia.carregarExtensao(pLog)
				ExtensaoBO.Instancia.carregarExtensoes(listaExtensoes, form.imageList1, form.imageList2)
			End If
			If bDiretorio Then
				listaDiretorioPai = DiretorioBO.Instancia.carregarDiretorio(CONSULTA_DIR_PAI, "consultadirpai", pLog)
				listaDiretorioFilho = DiretorioBO.Instancia.carregarDiretorio(CONSULTA_DIR_FILHO, "consultadirfilho", pLog)
				listaArquivos = DiretorioBO.Instancia.carregarDiretorio(CONSULTA_ARQUIVO, "consultaarquivo", pLog)
			End If
		End Sub

		Public Sub ExcluirDados(aba As Aba, sCaminho As String)
			DiretorioBO.Instancia.excluirListaDiretorio(listaDiretorioPai, aba, sCaminho)
			DiretorioBO.Instancia.excluirListaDiretorio(listaDiretorioFilho, aba, sCaminho)
			DiretorioBO.Instancia.excluirListaDiretorio(listaArquivos, aba, sCaminho)
		End Sub

		Private Sub AddItemArvore(tv As TreeView, diretorio As Diretorio, Nivel As Integer, node1 As TreeNode)
			Dim listaFilhos As List(Of Diretorio)
			Dim node2 As TreeNode

			If Nivel = 0 Then
				node1 = tv.Nodes.Add(diretorio.Nome)
			End If

			listaFilhos = DiretorioBO.Instancia.itensFilhos(listaDiretorioFilho, diretorio.Aba.Codigo, diretorio.Ordem, diretorio.Codigo)

			For Each filho As Diretorio In listaFilhos
				node2 = node1.Nodes.Add(filho.Nome)
				AddItemArvore(tv, filho, System.Threading.Interlocked.Increment(Nivel), node2)
			Next
		End Sub

		Public Sub IncluirNovaAba()
			Dim aba As Aba
			Dim sAba As String = Dialogo.entrada("Digite o Nome da Nova Aba?")
			If (sAba IsNot Nothing) AndAlso (sAba.Trim().Length > 0) Then
				aba = New Aba()
				aba.Codigo = AbaBO.Instancia.retMaxCodAba(listaAbas)
				aba.Nome = Rotinas.SubString(sAba, 1, 10)
				aba.Ordem = listaAbas.Count + 1
				AbaBO.Instancia.incluirAba(aba)
				IncluirNovaAba(aba.Nome)
				listaAbas.Add(aba)
			End If
		End Sub

		Public Sub AlterarNomeAbaAtiva(pLog As IProgressoLog)
			Dim aba As Aba = getAbaAtual()
			Dim sAba As String = Dialogo.entrada("Digite o Novo Nome da Aba Ativa?", aba.Nome)
			If (sAba IsNot Nothing) AndAlso (sAba.Trim().Length > 0) Then
				aba.Nome = Rotinas.SubString(sAba, 1, 10)
				AbaBO.Instancia.alterarAba(aba)
				form.tabControl1.SelectedTab.Text = sAba
				CarregarDados(pLog, False, True)
			End If
		End Sub

		Public Sub ExcluirAbaAtiva(pLog As IProgressoLog)
			Dim aba As Aba
			Dim indiceSel As Integer = form.tabControl1.SelectedIndex
			If indiceSel > 0 Then
				Dim res As Boolean = Dialogo.confirma("Tem Certeza, que você deseja excluir esta aba, " & vbLf & "isto implicará na destruição de todos os seus itens catalogados?")
				If res Then
					form.Cursor = Cursors.WaitCursor

					aba = getAbaAtual()
					ExcluirDados(aba, "")
					AbaBO.Instancia.excluirAba(aba)
					form.tabControl1.Controls.RemoveAt(indiceSel)

					CarregarDados(pLog, False, False)

					form.barraStatus.Items(1).Text = ""

					form.Cursor = Cursors.[Default]
				End If
			Else
				Dialogo.mensagemErro("A primeira Aba não pode ser excluída!")
			End If
		End Sub

		Private Sub IncluirNovaAba(nomeAba As String)
			Dim tabPage1 As TabPage
			Dim arvore As TreeView
			Dim sp As SplitContainer
			Dim tabela As ListView
			Dim columnHeader15 As ColumnHeader
			Dim columnHeader14 As ColumnHeader
			Dim columnHeader13 As ColumnHeader
			Dim columnHeader12 As ColumnHeader
			Dim columnHeader11 As ColumnHeader
			Dim columnHeader10 As ColumnHeader


			tabPage1 = New TabPage()
			sp = New SplitContainer()
			arvore = New TreeView()
			tabela = New ListView()
			columnHeader10 = New ColumnHeader()
			columnHeader11 = New ColumnHeader()
			columnHeader12 = New ColumnHeader()
			columnHeader13 = New ColumnHeader()
			columnHeader14 = New ColumnHeader()
			columnHeader15 = New ColumnHeader()

			' 
			' tabPage1
			' 
			tabPage1.Controls.Add(sp)
			tabPage1.ImageIndex = 0
			tabPage1.Location = New Point(4, 23)
			tabPage1.Name = "tabPage" & nomeAba
			tabPage1.Padding = New Padding(3)
			tabPage1.Size = New Size(876, 267)
			tabPage1.TabIndex = 0
			tabPage1.Text = nomeAba
			tabPage1.UseVisualStyleBackColor = True
			' 
			' sp
			' 
			sp.Dock = DockStyle.Fill
			sp.Location = New Point(3, 3)
			sp.Name = "sp" & nomeAba
			' 
			' sp.Panel1
			' 
			sp.Panel1.Controls.Add(arvore)
			' 
			' sp.Panel2
			' 
			sp.Panel2.Controls.Add(tabela)
			sp.Size = New Size(870, 261)
			sp.SplitterDistance = 290
			sp.TabIndex = 0
			' 
			' arvore
			' 
			arvore.Dock = DockStyle.Fill
			arvore.ImageIndex = 0
			arvore.ImageList = form.imageList1
			arvore.Location = New Point(0, 0)
			arvore.Name = "arvore" & nomeAba
			arvore.SelectedImageIndex = 1
			arvore.Size = New Size(290, 261)
			arvore.TabIndex = 0
			AddHandler arvore.AfterSelect, New TreeViewEventHandler(AddressOf form.TvFixaAfterSelect)
			' 
			' tabela
			' 
			tabela.Columns.AddRange(New ColumnHeader() {columnHeader10, columnHeader11, columnHeader12, columnHeader13, columnHeader14, columnHeader15})
			tabela.Dock = DockStyle.Fill
			tabela.FullRowSelect = True
			tabela.GridLines = True
			tabela.LargeImageList = form.imageList2
			tabela.Location = New Point(0, 0)
			tabela.MultiSelect = False
			tabela.Name = "tabela" & nomeAba
			tabela.Size = New Size(576, 261)
			tabela.SmallImageList = form.imageList1
			tabela.TabIndex = 1
			tabela.UseCompatibleStateImageBehavior = False
			tabela.View = View.Details
			AddHandler tabela.ColumnClick, New ColumnClickEventHandler(AddressOf form.LvFixaColumnClick)
			AddHandler tabela.DoubleClick, New System.EventHandler(AddressOf form.LvFixaDoubleClick)
			' 
			' columnHeader10
			' 
			columnHeader10.Text = "Nome"
			columnHeader10.Width = 300
			' 
			' columnHeader11
			' 
			columnHeader11.Text = "Tamanho"
			columnHeader11.Width = 100
			' 
			' columnHeader12
			' 
			columnHeader12.Text = "Tipo"
			columnHeader12.Width = 70
			' 
			' columnHeader13
			' 
			columnHeader13.Text = "Modificado"
			columnHeader13.Width = 120
			' 
			' columnHeader14
			' 
			columnHeader14.Text = "Atributos"
			columnHeader14.Width = 90
			' 
			' columnHeader15
			' 
			columnHeader15.Text = "Caminho"
			columnHeader15.Width = 300


			form.tabControl1.Controls.Add(tabPage1)
		End Sub

		Public Function getArvoreAtual() As TreeView
			Return getArvoreAtual(form.tabControl1.SelectedIndex)
		End Function

		Public Function getArvoreAtual(nIndicePagina As Integer) As TreeView
			Dim tabPage As TabPage = form.tabControl1.TabPages(nIndicePagina)
			Dim split As SplitContainer = DirectCast(tabPage.Controls(0), SplitContainer)
			Dim arvore As TreeView = DirectCast(split.Panel1.Controls(0), TreeView)
			Return arvore
		End Function

		Public Function getSplitAtual() As SplitContainer
			Dim tabPage As TabPage = form.tabControl1.SelectedTab
			Dim split As SplitContainer = DirectCast(tabPage.Controls(0), SplitContainer)
			Return split
		End Function

		Public Function getTabelaAtual() As ListView
			Dim tabPage As TabPage = form.tabControl1.SelectedTab
			Dim split As SplitContainer = DirectCast(tabPage.Controls(0), SplitContainer)
			Dim tabela As ListView = DirectCast(split.Panel2.Controls(0), ListView)
			Return tabela
		End Function

		Public Sub mostrarOcultarArvore()
			getSplitAtual().Panel1Collapsed = Not getSplitAtual().Panel1Collapsed
		End Sub

		Public Sub CarregarArvore(tvAba As TreeView, aba As Aba)
			tvAba.Nodes.Clear()
				
			tvAba.BeginUpdate()

			nodeRaiz = New TreeNode(NO_RAIZ)
			For Each diretorio As Diretorio In listaDiretorioPai
				If diretorio.Aba.Codigo = aba.Codigo Then
					AddItemArvore(tvAba, diretorio, 0, nodeRaiz)
				End If
			Next

			tvAba.EndUpdate()
		End Sub

		Public Sub CarregarAbas()
			Dim tvAba As TreeView

			form.pb.Minimum = 0
			form.pb.Maximum = listaAbas.Count - 1
			form.pb.Value = 0

			For i As Integer = 0 To listaAbas.Count - 1
				If i > 0 Then
					IncluirNovaAba(listaAbas(i).Nome)
				End If
				tvAba = getArvoreAtual(i)
				CarregarArvore(tvAba, listaAbas(i))
				form.pb.Value = i
			Next
		End Sub

		Private Function getAbaAtual() As Aba
			Return AbaBO.Instancia.pegaAbaPorOrdem(listaAbas, form.tabControl1.SelectedIndex + 1)
		End Function

		Public Sub CarregarArquivosLista(bLista1 As Boolean, lvArquivos As ListView, sCaminho As String)
			Dim sPaiCaminho As String
			Dim listaLocal As List(Of Diretorio)
			Dim nAba As Integer

			listaLocal = New List(Of Diretorio)()
			lvArquivos.Items.Clear()

			If bLista1 Then
				sPaiCaminho = sCaminho
				If Not Rotinas.SubString(sCaminho, sCaminho.Length, 1).Equals(Rotinas.BARRA_INVERTIDA) Then
					sCaminho = sCaminho & Rotinas.BARRA_INVERTIDA
				End If
				nAba = getAbaAtual().Codigo
				For Each diretorio As Diretorio In listaArquivos
					If diretorio.Aba.Codigo = nAba Then
						If diretorio.CaminhoPai.Equals(sPaiCaminho) Then
							If Rotinas.StartsStr(sCaminho, diretorio.Caminho) Then
								listaLocal.Add(diretorio)
							End If
						End If
					End If
				Next
			Else
				For Each diretorio As Diretorio In listaArquivos
					If Rotinas.ContainsStr(diretorio.Caminho.ToUpper(), sCaminho.ToUpper()) Then
						listaLocal.Add(diretorio)
					End If
				Next
			End If
			Tabela.Instancia.Carregar(bLista1, lvArquivos, listaLocal, listaExtensoes, form.pb.ProgressBar)

		End Sub

		Public Sub TamTotalDiretorio(sCaminho As String)
			Dim conta As Long
			Dim nAba As Integer
			Dim soma As Decimal, tam As Decimal

			conta = 0
			soma = 0

			For Each diretorio As Diretorio In listaArquivos
				nAba = getAbaAtual().Codigo
				If diretorio.Aba.Codigo = nAba Then
					If diretorio.Tipo.Codigo <> "D"C Then
						If sCaminho.Trim().Length > 0 Then
							If Rotinas.StartsStr(sCaminho, diretorio.Caminho) Then
								conta += 1
								tam = diretorio.Tamanho
								soma = soma + tam
							End If
						Else
							conta += 1
							tam = diretorio.Tamanho
							soma = soma + tam
						End If
					End If
				End If
			Next


			form.barraStatus.Items(0).Text = "Quantidade Total: " & Rotinas.FormatLong("0000", conta) & ", Tamanho Total: " & DiretorioBO.Instancia.MontaTamanho(soma)
		End Sub

		Private Function testaSeparadorArquivo(sDir As String) As Boolean
			sDir = Rotinas.SubString(sDir, sDir.Length, 1)
			If sDir.Equals(Rotinas.BARRA_INVERTIDA) OrElse sDir.Equals(Rotinas.BARRA_NORMAL) OrElse sDir.Equals(Rotinas.BARRA_INVERTIDA) Then
				Return True
			Else
				Return False
			End If
		End Function

		Private Function montaCaminho(sCaminho As String, bRemover As Boolean) As StringList
			'sCaminho = NO_RAIZ + Rotinas.BARRA_INVERTIDA + sCaminho;
			Dim sl As New StringList(sCaminho, Rotinas.BARRA_INVERTIDA(0))
			If sl(sl.Count - 1).Trim().Length = 0 Then
				sl.RemoveAt(sl.Count - 1)
			End If
			If bRemover Then
				sl.RemoveAt(sl.Count - 1)
			End If
			Return sl
		End Function

		Public Sub Pesquisar()
			Dim arvoreLocal As TreeView = getArvoreAtual()
			If arvoreLocal.VisibleCount > 0 Then
				If form.edtPesquisa.Text.Length >= 2 Then
					form.spPesquisa.Panel2Collapsed = False
					CarregarArquivosLista(False, form.lvPesquisa, form.edtPesquisa.Text)
					form.lvPesquisa.Items(0).Selected = True
				Else
					form.spPesquisa.Panel2Collapsed = True
					form.lvPesquisa.Clear()
					Dialogo.mensagemInfo("A pesquisa só é feita com pelo menos 2 caracteres!")
				End If
			End If
		End Sub

		Public Sub PesquisarArvoreDiretorio(sCaminho As String, aba As Aba)
			form.tabControl1.SelectedIndex = aba.Ordem - 1
			Dim arvore__1 As TreeView = getArvoreAtual()
			Dim sl As StringList = montaCaminho(sCaminho, False)
			' Verifica Diretorio
			Dim node As TreeNode = Arvore.Instancia.encontrarCaminhoPorNome(arvore__1, sl.ToArray())

			If node Is Nothing Then
				sl.Insert(1, sl(1) & Rotinas.BARRA_INVERTIDA)
				node = Arvore.Instancia.encontrarCaminhoPorNome(arvore__1, sl.ToArray())

				If node Is Nothing Then
					sl.Clear()
					sl = montaCaminho(sCaminho, True)
					' Verifica Arquivo
					node = Arvore.Instancia.encontrarCaminhoPorNome(arvore__1, sl.ToArray())

					If node Is Nothing Then
						sl.Insert(1, sl(1) & Rotinas.BARRA_INVERTIDA)
						node = Arvore.Instancia.encontrarCaminhoPorNome(arvore__1, sl.ToArray())
					End If
				End If
			End If

			node.Expand()
			arvore__1.SelectedNode = node
		End Sub

		Public Sub LerArvoreDiretorio(node As TreeNode, barraStatus As StatusStrip)
			Dim NodeAnterior As TreeNode
			Dim sSep As String, sCaminho As String

			sCaminho = node.Text
			NodeAnterior = node.Parent

			While NodeAnterior IsNot Nothing
				If Rotinas.SubString(NodeAnterior.Text, NodeAnterior.Text.Length, 1) = Rotinas.BARRA_INVERTIDA Then
					sSep = ""
				Else
					sSep = Rotinas.BARRA_INVERTIDA
				End If

				sCaminho = NodeAnterior.Text & sSep & sCaminho

				NodeAnterior = NodeAnterior.Parent
			End While

			form.barraStatus.Items(1).Text = sCaminho
		End Sub

		Public Sub ListarArquivos(lvTabela As ListView, node As TreeNode)
			If node IsNot Nothing Then
				If node.IsSelected Then
					LerArvoreDiretorio(node, form.barraStatus)
					CarregarArquivosLista(True, lvTabela, form.barraStatus.Items(1).Text)
					TamTotalDiretorio(form.barraStatus.Items(1).Text)
				End If
			End If
		End Sub

		Public Sub tabPanelMudou()
			Dim arvore As TreeView = getArvoreAtual()
			Dim lvTabela As ListView = getTabelaAtual()

			arvore.[Select]()
			If arvore.Nodes.Count > 0 Then
				ListarArquivos(lvTabela, arvore.Nodes(0))
			End If
		End Sub

		Public Function getAbaSelecionada() As Aba Implements ICatalogador.getAbaSelecionada
			Return getAbaAtual()
		End Function


		Public Sub DuploCliqueLista(nome As String, tipo As String) Implements ICatalogador.DuploCliqueLista
			If tipo.Equals("Diretório") Then
				form.Cursor = Cursors.WaitCursor
				Dim sCaminho As String = form.barraStatus.Items(1).Text
				If testaSeparadorArquivo(sCaminho) Then
					sCaminho += nome
				Else
					sCaminho += Rotinas.BARRA_INVERTIDA & nome
				End If

				PesquisarArvoreDiretorio(sCaminho, getAbaAtual())

				form.Cursor = Cursors.[Default]
			End If
		End Sub


		Public Sub EncontrarItemLista(nomeAba As String, nome As String, caminho As String) Implements ICatalogador.EncontrarItemLista
			form.Cursor = Cursors.WaitCursor
			Dim aba As Aba = AbaBO.Instancia.pegaAbaPorNome(listaAbas, nomeAba)
			PesquisarArvoreDiretorio(caminho, aba)

			Dim tabela As ListView = getTabelaAtual()

			Dim lvi As ListViewItem = tabela.FindItemWithText(nome, False, 0, False)
			If lvi IsNot Nothing Then
				tabela.FocusedItem = lvi
				tabela.[Select]()
			End If
			form.Cursor = Cursors.[Default]
		End Sub

		Public Function verificaNomeDiretorio(sCaminho As String, sRotuloRaiz As RotuloRaiz) As Integer
			sRotuloRaiz.Rotulo = DiretorioBO.Instancia.removerDrive(sCaminho)
			If sRotuloRaiz.Rotulo.Length = 0 Then

				sRotuloRaiz.Rotulo = Dialogo.entrada("Este diretório não possui um nome." & vbLf & "Digite o nome do diretório!")

				If (sRotuloRaiz.Rotulo IsNot Nothing) AndAlso (sRotuloRaiz.Rotulo.Trim().Length > 0) Then
					sRotuloRaiz.Rotulo = sRotuloRaiz.Rotulo.Trim()

					If sRotuloRaiz.Rotulo.Length > 0 Then
						Return 1
					Else
						Dialogo.mensagemInfo("Nenhum nome de diretório informado!")
						Return 0
					End If
				Else
					Return 0
				End If
			ElseIf Rotinas.Pos(Rotinas.BARRA_INVERTIDA, sRotuloRaiz.Rotulo) > 0 Then
				sRotuloRaiz.Rotulo = Rotinas.SubString(sRotuloRaiz.Rotulo, Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA, sRotuloRaiz.Rotulo) + 1, sRotuloRaiz.Rotulo.Length)
				Return 2
			Else
				Return 3
			End If
		End Function

		Public Sub ExportarArquivo(tipo As TipoExportar, pLog As IProgressoLog)
			Dim sExtensao As String = ""

			Select Case tipo
				Case TipoExportar.teTXT
					sExtensao = "txt"
					Exit Select
				Case TipoExportar.teCSV
					sExtensao = "csv"
					Exit Select
				Case TipoExportar.teHTML
					sExtensao = "html"
					Exit Select
				Case TipoExportar.teXML
					sExtensao = "xml"
					Exit Select
				Case TipoExportar.teSQL
					sExtensao = "sql"
					Exit Select
			End Select


			Dim aba As Aba = getAbaAtual()
			form.sdExportar.InitialDirectory = Rotinas.ExtractFilePath(Application.ExecutablePath)
			form.sdExportar.FileName = aba.Nome & "."C & sExtensao
			form.sdExportar.Filter = Rotinas.FILTRO_EXPORTAR
			Dim retval As DialogResult = form.sdExportar.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(form.sdExportar.FileName)
				If Not arquivo.Exists Then
					form.Cursor = Cursors.WaitCursor
					DiretorioBO.Instancia.exportarDiretorio(tipo, getAbaAtual(), arquivo.FullName, pLog)
					form.Cursor = Cursors.[Default]

					Dialogo.mensagemErro("Exportação realizada com sucesso!")
				End If
			End If
		End Sub

		Public Sub ExcluirDiretorioSelecionado(pLog As IProgressoLog)
			Dim arvore As TreeView = getArvoreAtual()
			Dim path As TreeNode = arvore.SelectedNode

			If path.Text.Length > 0 Then
				Dim tabela As ListView = getTabelaAtual()
				Dim res As Boolean = Dialogo.confirma("Tem Certeza, que você deseja excluir este diretório, isto implicará na destruição de todos os seus items catalogados?")
				If res Then
					form.Cursor = Cursors.WaitCursor

					DiretorioBO.Instancia.excluirDiretorio(getAbaAtual(), path.Text)
					ExcluirDados(getAbaAtual(), path.Text)

					path.Remove()
					tabela.Clear()

					CarregarDados(pLog, False, False)

					form.Cursor = Cursors.[Default]
				End If
			End If
		End Sub

		Public Sub ImportarArquivo(log As StringList, pLog As IProgressoLog)
			Dim nResultado As Integer

			form.odImportar.Filter = "Arquivo XML (*.xml)|*.xml"
			Dim retval As DialogResult = form.odImportar.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(form.odImportar.FileName)
				If arquivo.Exists Then
					form.Cursor = Cursors.WaitCursor
					nResultado = DiretorioBO.Instancia.importarDiretorioViaXML(getAbaAtual(), arquivo.FullName, listaDiretorioPai, pLog)
					If nResultado = -1 Then
						Dialogo.mensagemErro("Importação não realizada!")
					ElseIf nResultado = -2 Then
						Dialogo.mensagemErro("Este diretório já existe no catálogo!")
					Else
						FinalizaImportacao(pLog)
					End If
					form.Cursor = Cursors.[Default]
				End If
			End If
		End Sub

		Public Function ImportarDiretorios(listaCaminho As StringList, bSubDiretorio As Boolean, frmImportarDiretorio As FrmImportarDiretorio) As Boolean
			Dim nAba As Integer, nRotuloRaiz As Integer, nCodDirRaiz As Integer
			Dim sRotuloRaiz As New RotuloRaiz()
			Dim sCaminhoSemDrive As String
			Dim importar As New Importar()

			nAba = getAbaAtual().Codigo
			nCodDirRaiz = DiretorioBO.Instancia.retMaxCodDir(nAba, listaDiretorioPai)

			For Each sCaminho As String In listaCaminho
				nRotuloRaiz = verificaNomeDiretorio(sCaminho, sRotuloRaiz)
				If nRotuloRaiz > 0 Then
					importar = New Importar()
					importar.Aba = nAba
					importar.CodDirRaiz = nCodDirRaiz
					importar.RotuloRaiz = sRotuloRaiz.Rotulo
					If nRotuloRaiz = 1 Then
						importar.NomeDirRaiz = sRotuloRaiz.Rotulo
					ElseIf nRotuloRaiz = 2 Then
						sCaminhoSemDrive = DiretorioBO.Instancia.removerDrive(sCaminho)
						importar.NomeDirRaiz = Rotinas.SubString(sCaminhoSemDrive, 1, Rotinas.LastDelimiter(Rotinas.BARRA_INVERTIDA, sCaminhoSemDrive) - 1)
					ElseIf nRotuloRaiz = 3 Then
						importar.NomeDirRaiz = ""
					End If
					importar.Caminho = sCaminho

					frmImportarDiretorio.listaImportar.Add(importar)
					nCodDirRaiz += 1
				End If
			Next

			frmImportarDiretorio.bSubDiretorio = bSubDiretorio

			If bSubDiretorio Then
				frmImportarDiretorio.ShowDialog()
				Return True
			Else
				If Not DiretorioBO.Instancia.verificaCodDir(importar.Aba, importar.RotuloRaiz, listaDiretorioPai) Then
					frmImportarDiretorio.ShowDialog()
					Return True
				Else
					Dialogo.mensagemErro("Este diretório já existe no catálogo!")

					Return False
				End If
			End If

		End Function

		Public Sub FinalizaImportacao(pLog As IProgressoLog)
			Dim tvAba As TreeView

			form.Cursor = Cursors.WaitCursor

			CarregarDados(pLog, True, True)
			tvAba = getArvoreAtual()
			CarregarArvore(tvAba, getAbaAtual())
			tabPanelMudou()

			form.Cursor = Cursors.[Default]
			Dialogo.mensagemInfo("Importação do(s) diretório(s) realizada com sucesso!")

		End Sub


		Public Sub ComecaImportacao(bSubDiretorios As Boolean, pLog As IProgressoLog)
			Dim sCaminho As String
			Dim listaCaminho As StringList
			Dim frmImportarDiretorio As FrmImportarDiretorio

			Dim retval As DialogResult = form.escolherDir.ShowDialog()
			If retval = DialogResult.OK Then
				Dim arquivo As New FileInfo(form.escolherDir.SelectedPath)
				If arquivo.Directory.Exists Then
					form.Cursor = Cursors.WaitCursor
					sCaminho = arquivo.FullName

					frmImportarDiretorio = New FrmImportarDiretorio(form)
					listaCaminho = New StringList()

					If bSubDiretorios Then
						DiretorioBO.Instancia.carregarSubDiretorios(sCaminho, listaCaminho)
					Else
						listaCaminho.Add(sCaminho)
					End If

					If ImportarDiretorios(listaCaminho, bSubDiretorios, frmImportarDiretorio) Then
						FinalizaImportacao(pLog)
					End If

					form.Cursor = Cursors.[Default]
				End If
			End If

		End Sub

		Public Sub InformacoesDiretorioArquivo()
			Dim frmInfo As FrmInfoDiretorio
			Dim tabela__1 As ListView = getTabelaAtual()
			If tabela__1.SelectedItems.Count > 0 Then
				frmInfo = New FrmInfoDiretorio()
				Dim aba As Aba = getAbaSelecionada()
				Dim dir As Diretorio = Tabela.Instancia.getLinhaSelecionada(tabela__1, False)
				dir.Aba.Nome = aba.Nome
				frmInfo.setDiretorio(dir)
				frmInfo.ShowDialog()
			End If
		End Sub

		Public Function listaCompara(lvTabela As ListView, coluna As Integer, colOrdem As Integer) As Integer
			If coluna <> colOrdem Then
				colOrdem = coluna
				lvTabela.Sorting = SortOrder.Ascending
			Else
				If lvTabela.Sorting = SortOrder.Ascending Then
					lvTabela.Sorting = SortOrder.Descending
				Else
					lvTabela.Sorting = SortOrder.Ascending
				End If
			End If

			lvTabela.Sort()
			lvTabela.ListViewItemSorter = New TabelaItemComparer(coluna, lvTabela.Sorting)
			Return colOrdem
		End Function
	End Class
End Namespace
