'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:39
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmPrincipal
		''' <summary>
		''' Designer variable used to keep track of non-visual components.
		''' </summary>
		Private components As System.ComponentModel.IContainer = Nothing

		''' <summary>
		''' Disposes resources used by the form.
		''' </summary>
		''' <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		Protected Overrides Sub Dispose(disposing As Boolean)
			If disposing Then
				If components IsNot Nothing Then
					components.Dispose()
				End If
			End If
			MyBase.Dispose(disposing)
		End Sub

		''' <summary>
		''' This method is required for Windows Forms designer support.
		''' Do not change the method contents inside the source code editor. The Forms designer might
		''' not be able to load this method if it was changed manually.
		''' </summary>
		Private Sub InitializeComponent()
			Me.components = New System.ComponentModel.Container()
			Dim resources As New System.ComponentModel.ComponentResourceManager(GetType(FrmPrincipal))
			Me.barraMenu = New System.Windows.Forms.MenuStrip()
			Me.menuAba = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuIncluirNovaAba = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuAlterarNomeAbaAtiva = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExcluirAbaAtiva = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuDiretorio = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuImportarDiretorio = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuImportarSubDiretorios = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuCompararDiretorios = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuCadastrarExtensaoArquivo = New System.Windows.Forms.ToolStripMenuItem()
			Me.toolStripSeparator1 = New System.Windows.Forms.ToolStripSeparator()
			Me.menuExpandirDiretorios = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuColapsarDiretorios = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarDiretoriosAbaAtiva = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuTXT = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuCSV = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuHTML = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuXML = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuSQL = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuImportarDiretoriosViaXML = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuGravarLogImportacao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuVisao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuMostrarOcultArvoreDirAbaAtiva = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuMostrarOcultarListaItensPesquisados = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuModoExibicao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuIcones = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuLista = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuDetalhes = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuIconesPequenos = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuSobre = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuSobreCatalogador = New System.Windows.Forms.ToolStripMenuItem()
			Me.barraFerra = New System.Windows.Forms.ToolStrip()
			Me.btnImportarDiretorio = New System.Windows.Forms.ToolStripButton()
			Me.pb = New System.Windows.Forms.ToolStripProgressBar()
			Me.edtPesquisa = New System.Windows.Forms.ToolStripTextBox()
			Me.btnPesquisar = New System.Windows.Forms.ToolStripButton()
			Me.spPesquisa = New System.Windows.Forms.SplitContainer()
			Me.tabControl1 = New System.Windows.Forms.TabControl()
			Me.popupMenu = New System.Windows.Forms.ContextMenuStrip(Me.components)
			Me.menuInformacoesDiretorioArquivo = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExcluirDiretorioSelecionado = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExpandirDiretorios2 = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuColapsarDiretorios2 = New System.Windows.Forms.ToolStripMenuItem()
			Me.toolStripSeparator2 = New System.Windows.Forms.ToolStripSeparator()
			Me.menuIncluirNovaAba2 = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuAlterarNomeAbaAtiva2 = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExcluirAbaAtiva2 = New System.Windows.Forms.ToolStripMenuItem()
			Me.tabPage1 = New System.Windows.Forms.TabPage()
			Me.sp = New System.Windows.Forms.SplitContainer()
			Me.tvFixa = New System.Windows.Forms.TreeView()
			Me.imageList1 = New System.Windows.Forms.ImageList(Me.components)
			Me.lvFixa = New System.Windows.Forms.ListView()
			Me.columnHeader10 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader11 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader12 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader13 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader14 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader15 = New System.Windows.Forms.ColumnHeader()
			Me.imageList2 = New System.Windows.Forms.ImageList(Me.components)
			Me.imageList3 = New System.Windows.Forms.ImageList(Me.components)
			Me.lvPesquisa = New System.Windows.Forms.ListView()
			Me.columnHeader1 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader2 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader3 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader4 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader5 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader6 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader7 = New System.Windows.Forms.ColumnHeader()
			Me.barraStatus = New System.Windows.Forms.StatusStrip()
			Me.labStatus1 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.labStatus2 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.odImportar = New System.Windows.Forms.OpenFileDialog()
			Me.sdExportar = New System.Windows.Forms.SaveFileDialog()
			Me.escolherDir = New System.Windows.Forms.FolderBrowserDialog()
			Me.barraMenu.SuspendLayout()
			Me.barraFerra.SuspendLayout()
			DirectCast(Me.spPesquisa, System.ComponentModel.ISupportInitialize).BeginInit()
			Me.spPesquisa.Panel1.SuspendLayout()
			Me.spPesquisa.Panel2.SuspendLayout()
			Me.spPesquisa.SuspendLayout()
			Me.tabControl1.SuspendLayout()
			Me.popupMenu.SuspendLayout()
			Me.tabPage1.SuspendLayout()
			DirectCast(Me.sp, System.ComponentModel.ISupportInitialize).BeginInit()
			Me.sp.Panel1.SuspendLayout()
			Me.sp.Panel2.SuspendLayout()
			Me.sp.SuspendLayout()
			Me.barraStatus.SuspendLayout()
			Me.SuspendLayout()
			' 
			' barraMenu
			' 
			Me.barraMenu.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuAba, Me.menuDiretorio, Me.menuVisao, Me.menuSobre})
			Me.barraMenu.Location = New System.Drawing.Point(0, 0)
			Me.barraMenu.Name = "barraMenu"
			Me.barraMenu.Size = New System.Drawing.Size(884, 24)
			Me.barraMenu.TabIndex = 0
			Me.barraMenu.Text = "menuStrip1"
			' 
			' menuAba
			' 
			Me.menuAba.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuIncluirNovaAba, Me.menuAlterarNomeAbaAtiva, Me.menuExcluirAbaAtiva})
			Me.menuAba.Name = "menuAba"
			Me.menuAba.Size = New System.Drawing.Size(40, 20)
			Me.menuAba.Text = "&Aba"
			' 
			' menuIncluirNovaAba
			' 
			Me.menuIncluirNovaAba.Name = "menuIncluirNovaAba"
			Me.menuIncluirNovaAba.Size = New System.Drawing.Size(215, 22)
			Me.menuIncluirNovaAba.Text = "Incluir Nova Aba"
			AddHandler Me.menuIncluirNovaAba.Click, New System.EventHandler(AddressOf Me.MenuIncluirNovaAbaClick)
			' 
			' menuAlterarNomeAbaAtiva
			' 
			Me.menuAlterarNomeAbaAtiva.Name = "menuAlterarNomeAbaAtiva"
			Me.menuAlterarNomeAbaAtiva.Size = New System.Drawing.Size(215, 22)
			Me.menuAlterarNomeAbaAtiva.Text = "Alterar Nome da Aba Ativa"
			AddHandler Me.menuAlterarNomeAbaAtiva.Click, New System.EventHandler(AddressOf Me.MenuAlterarNomeAbaAtivaClick)
			' 
			' menuExcluirAbaAtiva
			' 
			Me.menuExcluirAbaAtiva.Name = "menuExcluirAbaAtiva"
			Me.menuExcluirAbaAtiva.Size = New System.Drawing.Size(215, 22)
			Me.menuExcluirAbaAtiva.Text = "Excluir Aba Ativa"
			AddHandler Me.menuExcluirAbaAtiva.Click, New System.EventHandler(AddressOf Me.MenuExcluirAbaAtivaClick)
			' 
			' menuDiretorio
			' 
			Me.menuDiretorio.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuImportarDiretorio, Me.menuImportarSubDiretorios, Me.menuCompararDiretorios, Me.menuCadastrarExtensaoArquivo, Me.toolStripSeparator1, Me.menuExpandirDiretorios, _
				Me.menuColapsarDiretorios, Me.menuExportarDiretoriosAbaAtiva, Me.menuImportarDiretoriosViaXML, Me.menuGravarLogImportacao})
			Me.menuDiretorio.Name = "menuDiretorio"
			Me.menuDiretorio.Size = New System.Drawing.Size(65, 20)
			Me.menuDiretorio.Text = "&Diretório"
			' 
			' menuImportarDiretorio
			' 
			Me.menuImportarDiretorio.Name = "menuImportarDiretorio"
			Me.menuImportarDiretorio.Size = New System.Drawing.Size(241, 22)
			Me.menuImportarDiretorio.Text = "Importar Diretório"
			AddHandler Me.menuImportarDiretorio.Click, New System.EventHandler(AddressOf Me.MenuImportarDiretorioClick)
			' 
			' menuImportarSubDiretorios
			' 
			Me.menuImportarSubDiretorios.Name = "menuImportarSubDiretorios"
			Me.menuImportarSubDiretorios.Size = New System.Drawing.Size(241, 22)
			Me.menuImportarSubDiretorios.Text = "Importar SubDiretórios"
			AddHandler Me.menuImportarSubDiretorios.Click, New System.EventHandler(AddressOf Me.MenuImportarSubDiretoriosClick)
			' 
			' menuCompararDiretorios
			' 
			Me.menuCompararDiretorios.Name = "menuCompararDiretorios"
			Me.menuCompararDiretorios.Size = New System.Drawing.Size(241, 22)
			Me.menuCompararDiretorios.Text = "Comparar Diretórios"
			AddHandler Me.menuCompararDiretorios.Click, New System.EventHandler(AddressOf Me.MenuCompararDiretoriosClick)
			' 
			' menuCadastrarExtensaoArquivo
			' 
			Me.menuCadastrarExtensaoArquivo.Name = "menuCadastrarExtensaoArquivo"
			Me.menuCadastrarExtensaoArquivo.Size = New System.Drawing.Size(241, 22)
			Me.menuCadastrarExtensaoArquivo.Text = "Cadastrar Extensão de Arquivo"
			AddHandler Me.menuCadastrarExtensaoArquivo.Click, New System.EventHandler(AddressOf Me.MenuCadastrarExtensaoArquivoClick)
			' 
			' toolStripSeparator1
			' 
			Me.toolStripSeparator1.Name = "toolStripSeparator1"
			Me.toolStripSeparator1.Size = New System.Drawing.Size(238, 6)
			' 
			' menuExpandirDiretorios
			' 
			Me.menuExpandirDiretorios.Name = "menuExpandirDiretorios"
			Me.menuExpandirDiretorios.Size = New System.Drawing.Size(241, 22)
			Me.menuExpandirDiretorios.Text = "Expandir Diretórios"
			AddHandler Me.menuExpandirDiretorios.Click, New System.EventHandler(AddressOf Me.MenuExpandirDiretoriosClick)
			' 
			' menuColapsarDiretorios
			' 
			Me.menuColapsarDiretorios.Name = "menuColapsarDiretorios"
			Me.menuColapsarDiretorios.Size = New System.Drawing.Size(241, 22)
			Me.menuColapsarDiretorios.Text = "Colapsar Diretórios"
			AddHandler Me.menuColapsarDiretorios.Click, New System.EventHandler(AddressOf Me.MenuColapsarDiretoriosClick)
			' 
			' menuExportarDiretoriosAbaAtiva
			' 
			Me.menuExportarDiretoriosAbaAtiva.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuTXT, Me.menuCSV, Me.menuHTML, Me.menuXML, Me.menuSQL})
			Me.menuExportarDiretoriosAbaAtiva.Name = "menuExportarDiretoriosAbaAtiva"
			Me.menuExportarDiretoriosAbaAtiva.Size = New System.Drawing.Size(241, 22)
			Me.menuExportarDiretoriosAbaAtiva.Text = "Exportar Diretórios da Aba Ativa"
			' 
			' menuTXT
			' 
			Me.menuTXT.Name = "menuTXT"
			Me.menuTXT.Size = New System.Drawing.Size(107, 22)
			Me.menuTXT.Text = "TXT"
			AddHandler Me.menuTXT.Click, New System.EventHandler(AddressOf Me.MenuTXTClick)
			' 
			' menuCSV
			' 
			Me.menuCSV.Name = "menuCSV"
			Me.menuCSV.Size = New System.Drawing.Size(107, 22)
			Me.menuCSV.Text = "CSV"
			AddHandler Me.menuCSV.Click, New System.EventHandler(AddressOf Me.MenuCSVClick)
			' 
			' menuHTML
			' 
			Me.menuHTML.Name = "menuHTML"
			Me.menuHTML.Size = New System.Drawing.Size(107, 22)
			Me.menuHTML.Text = "HTML"
			AddHandler Me.menuHTML.Click, New System.EventHandler(AddressOf Me.MenuHTMLClick)
			' 
			' menuXML
			' 
			Me.menuXML.Name = "menuXML"
			Me.menuXML.Size = New System.Drawing.Size(107, 22)
			Me.menuXML.Text = "XML"
			AddHandler Me.menuXML.Click, New System.EventHandler(AddressOf Me.MenuXMLClick)
			' 
			' menuSQL
			' 
			Me.menuSQL.Name = "menuSQL"
			Me.menuSQL.Size = New System.Drawing.Size(107, 22)
			Me.menuSQL.Text = "SQL"
			AddHandler Me.menuSQL.Click, New System.EventHandler(AddressOf Me.MenuSQLClick)
			' 
			' menuImportarDiretoriosViaXML
			' 
			Me.menuImportarDiretoriosViaXML.Name = "menuImportarDiretoriosViaXML"
			Me.menuImportarDiretoriosViaXML.Size = New System.Drawing.Size(241, 22)
			Me.menuImportarDiretoriosViaXML.Text = "Importar Diretórios via XML"
			AddHandler Me.menuImportarDiretoriosViaXML.Click, New System.EventHandler(AddressOf Me.MenuImportarDiretoriosViaXMLClick)
			' 
			' menuGravarLogImportacao
			' 
			Me.menuGravarLogImportacao.CheckOnClick = True
			Me.menuGravarLogImportacao.Name = "menuGravarLogImportacao"
			Me.menuGravarLogImportacao.Size = New System.Drawing.Size(241, 22)
			Me.menuGravarLogImportacao.Text = "Gravar Log da Importação"
			' 
			' menuVisao
			' 
			Me.menuVisao.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuMostrarOcultArvoreDirAbaAtiva, Me.menuMostrarOcultarListaItensPesquisados, Me.menuModoExibicao})
			Me.menuVisao.Name = "menuVisao"
			Me.menuVisao.Size = New System.Drawing.Size(47, 20)
			Me.menuVisao.Text = "&Visão"
			' 
			' menuMostrarOcultArvoreDirAbaAtiva
			' 
			Me.menuMostrarOcultArvoreDirAbaAtiva.Name = "menuMostrarOcultArvoreDirAbaAtiva"
			Me.menuMostrarOcultArvoreDirAbaAtiva.Size = New System.Drawing.Size(334, 22)
			Me.menuMostrarOcultArvoreDirAbaAtiva.Text = "Mostrar/Ocultar árvore de diretórios da Aba Ativa"
			AddHandler Me.menuMostrarOcultArvoreDirAbaAtiva.Click, New System.EventHandler(AddressOf Me.MenuMostrarOcultArvoreDirAbaAtivaClick)
			' 
			' menuMostrarOcultarListaItensPesquisados
			' 
			Me.menuMostrarOcultarListaItensPesquisados.Name = "menuMostrarOcultarListaItensPesquisados"
			Me.menuMostrarOcultarListaItensPesquisados.Size = New System.Drawing.Size(334, 22)
			Me.menuMostrarOcultarListaItensPesquisados.Text = "Mostrar/Ocultar lista de itens pesquisados"
			AddHandler Me.menuMostrarOcultarListaItensPesquisados.Click, New System.EventHandler(AddressOf Me.MenuMostrarOcultarListaItensPesquisadosClick)
			' 
			' menuModoExibicao
			' 
			Me.menuModoExibicao.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuIcones, Me.menuLista, Me.menuDetalhes, Me.menuIconesPequenos})
			Me.menuModoExibicao.Name = "menuModoExibicao"
			Me.menuModoExibicao.Size = New System.Drawing.Size(334, 22)
			Me.menuModoExibicao.Text = "Modo de Exibição"
			' 
			' menuIcones
			' 
			Me.menuIcones.Name = "menuIcones"
			Me.menuIcones.Size = New System.Drawing.Size(163, 22)
			Me.menuIcones.Text = "Ícones"
			AddHandler Me.menuIcones.Click, New System.EventHandler(AddressOf Me.MenuIconesClick)
			' 
			' menuLista
			' 
			Me.menuLista.Name = "menuLista"
			Me.menuLista.Size = New System.Drawing.Size(163, 22)
			Me.menuLista.Text = "Lista"
			AddHandler Me.menuLista.Click, New System.EventHandler(AddressOf Me.MenuListaClick)
			' 
			' menuDetalhes
			' 
			Me.menuDetalhes.Name = "menuDetalhes"
			Me.menuDetalhes.Size = New System.Drawing.Size(163, 22)
			Me.menuDetalhes.Text = "Detalhes"
			AddHandler Me.menuDetalhes.Click, New System.EventHandler(AddressOf Me.MenuDetalhesClick)
			' 
			' menuIconesPequenos
			' 
			Me.menuIconesPequenos.Name = "menuIconesPequenos"
			Me.menuIconesPequenos.Size = New System.Drawing.Size(163, 22)
			Me.menuIconesPequenos.Text = "Ícones Pequenos"
			AddHandler Me.menuIconesPequenos.Click, New System.EventHandler(AddressOf Me.MenuIconesPequenosClick)
			' 
			' menuSobre
			' 
			Me.menuSobre.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuSobreCatalogador})
			Me.menuSobre.Name = "menuSobre"
			Me.menuSobre.Size = New System.Drawing.Size(49, 20)
			Me.menuSobre.Text = "&Sobre"
			' 
			' menuSobreCatalogador
			' 
			Me.menuSobreCatalogador.Name = "menuSobreCatalogador"
			Me.menuSobreCatalogador.Size = New System.Drawing.Size(182, 22)
			Me.menuSobreCatalogador.Text = "Sobre o Catalogador"
			AddHandler Me.menuSobreCatalogador.Click, New System.EventHandler(AddressOf Me.MenuSobreCatalogadorClick)
			' 
			' barraFerra
			' 
			Me.barraFerra.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden
			Me.barraFerra.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.btnImportarDiretorio, Me.pb, Me.edtPesquisa, Me.btnPesquisar})
			Me.barraFerra.Location = New System.Drawing.Point(0, 24)
			Me.barraFerra.Name = "barraFerra"
			Me.barraFerra.Size = New System.Drawing.Size(884, 25)
			Me.barraFerra.Stretch = True
			Me.barraFerra.TabIndex = 1
			' 
			' btnImportarDiretorio
			' 
			Me.btnImportarDiretorio.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.btnImportarDiretorio.Image = DirectCast(resources.GetObject("btnImportarDiretorio.Image"), System.Drawing.Image)
			Me.btnImportarDiretorio.ImageTransparentColor = System.Drawing.Color.Magenta
			Me.btnImportarDiretorio.Name = "btnImportarDiretorio"
			Me.btnImportarDiretorio.Size = New System.Drawing.Size(106, 22)
			Me.btnImportarDiretorio.Text = "&Importar Diretório"
			AddHandler Me.btnImportarDiretorio.Click, New System.EventHandler(AddressOf Me.BtnImportarDiretorioClick)
			' 
			' pb
			' 
			Me.pb.AutoSize = False
			Me.pb.Name = "pb"
			Me.pb.Size = New System.Drawing.Size(385, 22)
			Me.pb.[Step] = 0
			' 
			' edtPesquisa
			' 
			Me.edtPesquisa.AutoSize = False
			Me.edtPesquisa.MaxLength = 255
			Me.edtPesquisa.Name = "edtPesquisa"
			Me.edtPesquisa.Size = New System.Drawing.Size(288, 25)
			Me.edtPesquisa.ToolTipText = "Digite aqui para pesquisar"
			' 
			' btnPesquisar
			' 
			Me.btnPesquisar.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.btnPesquisar.Image = DirectCast(resources.GetObject("btnPesquisar.Image"), System.Drawing.Image)
			Me.btnPesquisar.ImageTransparentColor = System.Drawing.Color.Magenta
			Me.btnPesquisar.Name = "btnPesquisar"
			Me.btnPesquisar.Size = New System.Drawing.Size(61, 22)
			Me.btnPesquisar.Text = "&Pesquisar"
			AddHandler Me.btnPesquisar.Click, New System.EventHandler(AddressOf Me.BtnPesquisarClick)
			' 
			' spPesquisa
			' 
			Me.spPesquisa.Dock = System.Windows.Forms.DockStyle.Fill
			Me.spPesquisa.Location = New System.Drawing.Point(0, 49)
			Me.spPesquisa.Name = "spPesquisa"
			Me.spPesquisa.Orientation = System.Windows.Forms.Orientation.Horizontal
			' 
			' spPesquisa.Panel1
			' 
			Me.spPesquisa.Panel1.Controls.Add(Me.tabControl1)
			' 
			' spPesquisa.Panel2
			' 
			Me.spPesquisa.Panel2.Controls.Add(Me.lvPesquisa)
			Me.spPesquisa.Size = New System.Drawing.Size(884, 413)
			Me.spPesquisa.SplitterDistance = 294
			Me.spPesquisa.TabIndex = 2
			' 
			' tabControl1
			' 
			Me.tabControl1.ContextMenuStrip = Me.popupMenu
			Me.tabControl1.Controls.Add(Me.tabPage1)
			Me.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill
			Me.tabControl1.ImageList = Me.imageList3
			Me.tabControl1.Location = New System.Drawing.Point(0, 0)
			Me.tabControl1.Name = "tabControl1"
			Me.tabControl1.SelectedIndex = 0
			Me.tabControl1.Size = New System.Drawing.Size(884, 294)
			Me.tabControl1.TabIndex = 0
			AddHandler Me.tabControl1.SelectedIndexChanged, New System.EventHandler(AddressOf Me.TabControl1SelectedIndexChanged)
			' 
			' popupMenu
			' 
			Me.popupMenu.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuInformacoesDiretorioArquivo, Me.menuExcluirDiretorioSelecionado, Me.menuExpandirDiretorios2, Me.menuColapsarDiretorios2, Me.toolStripSeparator2, Me.menuIncluirNovaAba2, _
				Me.menuAlterarNomeAbaAtiva2, Me.menuExcluirAbaAtiva2})
			Me.popupMenu.Name = "popupMenu"
			Me.popupMenu.Size = New System.Drawing.Size(260, 164)
			' 
			' menuInformacoesDiretorioArquivo
			' 
			Me.menuInformacoesDiretorioArquivo.Name = "menuInformacoesDiretorioArquivo"
			Me.menuInformacoesDiretorioArquivo.Size = New System.Drawing.Size(259, 22)
			Me.menuInformacoesDiretorioArquivo.Text = "Informações do Diretório / Arquivo"
			AddHandler Me.menuInformacoesDiretorioArquivo.Click, New System.EventHandler(AddressOf Me.MenuInformacoesDiretorioArquivoClick)
			' 
			' menuExcluirDiretorioSelecionado
			' 
			Me.menuExcluirDiretorioSelecionado.Name = "menuExcluirDiretorioSelecionado"
			Me.menuExcluirDiretorioSelecionado.Size = New System.Drawing.Size(259, 22)
			Me.menuExcluirDiretorioSelecionado.Text = "Excluir Diretório Selecionado"
			AddHandler Me.menuExcluirDiretorioSelecionado.Click, New System.EventHandler(AddressOf Me.MenuExcluirDiretorioSelecionadoClick)
			' 
			' menuExpandirDiretorios2
			' 
			Me.menuExpandirDiretorios2.Name = "menuExpandirDiretorios2"
			Me.menuExpandirDiretorios2.Size = New System.Drawing.Size(259, 22)
			Me.menuExpandirDiretorios2.Text = "Expandir Diretórios"
			AddHandler Me.menuExpandirDiretorios2.Click, New System.EventHandler(AddressOf Me.MenuExpandirDiretorios2Click)
			' 
			' menuColapsarDiretorios2
			' 
			Me.menuColapsarDiretorios2.Name = "menuColapsarDiretorios2"
			Me.menuColapsarDiretorios2.Size = New System.Drawing.Size(259, 22)
			Me.menuColapsarDiretorios2.Text = "Colapsar Diretórios"
			AddHandler Me.menuColapsarDiretorios2.Click, New System.EventHandler(AddressOf Me.MenuColapsarDiretorios2Click)
			' 
			' toolStripSeparator2
			' 
			Me.toolStripSeparator2.Name = "toolStripSeparator2"
			Me.toolStripSeparator2.Size = New System.Drawing.Size(256, 6)
			' 
			' menuIncluirNovaAba2
			' 
			Me.menuIncluirNovaAba2.Name = "menuIncluirNovaAba2"
			Me.menuIncluirNovaAba2.Size = New System.Drawing.Size(259, 22)
			Me.menuIncluirNovaAba2.Text = "Incluir nova aba"
			AddHandler Me.menuIncluirNovaAba2.Click, New System.EventHandler(AddressOf Me.MenuIncluirNovaAba2Click)
			' 
			' menuAlterarNomeAbaAtiva2
			' 
			Me.menuAlterarNomeAbaAtiva2.Name = "menuAlterarNomeAbaAtiva2"
			Me.menuAlterarNomeAbaAtiva2.Size = New System.Drawing.Size(259, 22)
			Me.menuAlterarNomeAbaAtiva2.Text = "Alterar nome da aba ativa"
			AddHandler Me.menuAlterarNomeAbaAtiva2.Click, New System.EventHandler(AddressOf Me.MenuAlterarNomeAbaAtiva2Click)
			' 
			' menuExcluirAbaAtiva2
			' 
			Me.menuExcluirAbaAtiva2.Name = "menuExcluirAbaAtiva2"
			Me.menuExcluirAbaAtiva2.Size = New System.Drawing.Size(259, 22)
			Me.menuExcluirAbaAtiva2.Text = "Excluir aba ativa"
			AddHandler Me.menuExcluirAbaAtiva2.Click, New System.EventHandler(AddressOf Me.MenuExcluirAbaAtiva2Click)
			' 
			' tabPage1
			' 
			Me.tabPage1.Controls.Add(Me.sp)
			Me.tabPage1.ImageIndex = 0
			Me.tabPage1.Location = New System.Drawing.Point(4, 23)
			Me.tabPage1.Name = "tabPage1"
			Me.tabPage1.Padding = New System.Windows.Forms.Padding(3)
			Me.tabPage1.Size = New System.Drawing.Size(876, 267)
			Me.tabPage1.TabIndex = 0
			Me.tabPage1.Text = "DISCO1"
			Me.tabPage1.UseVisualStyleBackColor = True
			' 
			' sp
			' 
			Me.sp.Dock = System.Windows.Forms.DockStyle.Fill
			Me.sp.Location = New System.Drawing.Point(3, 3)
			Me.sp.Name = "sp"
			' 
			' sp.Panel1
			' 
			Me.sp.Panel1.Controls.Add(Me.tvFixa)
			' 
			' sp.Panel2
			' 
			Me.sp.Panel2.Controls.Add(Me.lvFixa)
			Me.sp.Size = New System.Drawing.Size(870, 261)
			Me.sp.SplitterDistance = 290
			Me.sp.TabIndex = 0
			' 
			' tvFixa
			' 
			Me.tvFixa.Dock = System.Windows.Forms.DockStyle.Fill
			Me.tvFixa.FullRowSelect = True
			Me.tvFixa.HideSelection = False
			Me.tvFixa.ImageIndex = 0
			Me.tvFixa.ImageList = Me.imageList1
			Me.tvFixa.Location = New System.Drawing.Point(0, 0)
			Me.tvFixa.Name = "tvFixa"
			Me.tvFixa.SelectedImageIndex = 1
			Me.tvFixa.Size = New System.Drawing.Size(290, 261)
			Me.tvFixa.TabIndex = 0
			AddHandler Me.tvFixa.AfterSelect, New System.Windows.Forms.TreeViewEventHandler(AddressOf Me.TvFixaAfterSelect)
			' 
			' imageList1
			' 
			Me.imageList1.ImageStream = DirectCast(resources.GetObject("imageList1.ImageStream"), System.Windows.Forms.ImageListStreamer)
			Me.imageList1.TransparentColor = System.Drawing.Color.Transparent
			Me.imageList1.Images.SetKeyName(0, "Fechar.bmp")
			Me.imageList1.Images.SetKeyName(1, "Abrir.bmp")
			Me.imageList1.Images.SetKeyName(2, "Arquivo.bmp")
			' 
			' lvFixa
			' 
			Me.lvFixa.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader10, Me.columnHeader11, Me.columnHeader12, Me.columnHeader13, Me.columnHeader14, Me.columnHeader15})
			Me.lvFixa.Dock = System.Windows.Forms.DockStyle.Fill
			Me.lvFixa.FullRowSelect = True
			Me.lvFixa.GridLines = True
			Me.lvFixa.LargeImageList = Me.imageList2
			Me.lvFixa.Location = New System.Drawing.Point(0, 0)
			Me.lvFixa.MultiSelect = False
			Me.lvFixa.Name = "lvFixa"
			Me.lvFixa.Size = New System.Drawing.Size(576, 261)
			Me.lvFixa.SmallImageList = Me.imageList1
			Me.lvFixa.TabIndex = 1
			Me.lvFixa.UseCompatibleStateImageBehavior = False
			Me.lvFixa.View = System.Windows.Forms.View.Details
			AddHandler Me.lvFixa.ColumnClick, New System.Windows.Forms.ColumnClickEventHandler(AddressOf Me.LvFixaColumnClick)
			AddHandler Me.lvFixa.DoubleClick, New System.EventHandler(AddressOf Me.LvFixaDoubleClick)
			' 
			' columnHeader10
			' 
			Me.columnHeader10.Text = "Nome"
			Me.columnHeader10.Width = 300
			' 
			' columnHeader11
			' 
			Me.columnHeader11.Text = "Tamanho"
			Me.columnHeader11.Width = 100
			' 
			' columnHeader12
			' 
			Me.columnHeader12.Text = "Tipo"
			Me.columnHeader12.Width = 70
			' 
			' columnHeader13
			' 
			Me.columnHeader13.Text = "Modificado"
			Me.columnHeader13.Width = 120
			' 
			' columnHeader14
			' 
			Me.columnHeader14.Text = "Atributos"
			Me.columnHeader14.Width = 90
			' 
			' columnHeader15
			' 
			Me.columnHeader15.Text = "Caminho"
			Me.columnHeader15.Width = 300
			' 
			' imageList2
			' 
			Me.imageList2.ImageStream = DirectCast(resources.GetObject("imageList2.ImageStream"), System.Windows.Forms.ImageListStreamer)
			Me.imageList2.TransparentColor = System.Drawing.Color.Transparent
			Me.imageList2.Images.SetKeyName(0, "Fechar32.bmp")
			Me.imageList2.Images.SetKeyName(1, "Abrir32.bmp")
			Me.imageList2.Images.SetKeyName(2, "Arquivo32.bmp")
			' 
			' imageList3
			' 
			Me.imageList3.ImageStream = DirectCast(resources.GetObject("imageList3.ImageStream"), System.Windows.Forms.ImageListStreamer)
			Me.imageList3.TransparentColor = System.Drawing.Color.Magenta
			Me.imageList3.Images.SetKeyName(0, "cdouro.bmp")
			Me.imageList3.Images.SetKeyName(1, "cdprata.bmp")
			' 
			' lvPesquisa
			' 
			Me.lvPesquisa.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader1, Me.columnHeader2, Me.columnHeader3, Me.columnHeader4, Me.columnHeader5, Me.columnHeader6, _
				Me.columnHeader7})
			Me.lvPesquisa.Dock = System.Windows.Forms.DockStyle.Fill
			Me.lvPesquisa.FullRowSelect = True
			Me.lvPesquisa.GridLines = True
			Me.lvPesquisa.LargeImageList = Me.imageList2
			Me.lvPesquisa.Location = New System.Drawing.Point(0, 0)
			Me.lvPesquisa.MultiSelect = False
			Me.lvPesquisa.Name = "lvPesquisa"
			Me.lvPesquisa.Size = New System.Drawing.Size(884, 115)
			Me.lvPesquisa.SmallImageList = Me.imageList1
			Me.lvPesquisa.TabIndex = 0
			Me.lvPesquisa.UseCompatibleStateImageBehavior = False
			Me.lvPesquisa.View = System.Windows.Forms.View.Details
			AddHandler Me.lvPesquisa.ColumnClick, New System.Windows.Forms.ColumnClickEventHandler(AddressOf Me.LvPesquisaColumnClick)
			AddHandler Me.lvPesquisa.Click, New System.EventHandler(AddressOf Me.LvPesquisaClick)
			' 
			' columnHeader1
			' 
			Me.columnHeader1.Text = "Nome"
			Me.columnHeader1.Width = 300
			' 
			' columnHeader2
			' 
			Me.columnHeader2.Text = "Tamanho"
			Me.columnHeader2.Width = 100
			' 
			' columnHeader3
			' 
			Me.columnHeader3.Text = "Tipo"
			Me.columnHeader3.Width = 70
			' 
			' columnHeader4
			' 
			Me.columnHeader4.Text = "Modificado"
			Me.columnHeader4.Width = 120
			' 
			' columnHeader5
			' 
			Me.columnHeader5.Text = "Atributos"
			Me.columnHeader5.Width = 90
			' 
			' columnHeader6
			' 
			Me.columnHeader6.Text = "Caminho"
			Me.columnHeader6.Width = 300
			' 
			' columnHeader7
			' 
			Me.columnHeader7.Text = "Aba"
			Me.columnHeader7.Width = 150
			' 
			' barraStatus
			' 
			Me.barraStatus.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.labStatus1, Me.labStatus2})
			Me.barraStatus.Location = New System.Drawing.Point(0, 440)
			Me.barraStatus.Name = "barraStatus"
			Me.barraStatus.Size = New System.Drawing.Size(884, 22)
			Me.barraStatus.TabIndex = 3
			Me.barraStatus.Text = "statusStrip1"
			' 
			' labStatus1
			' 
			Me.labStatus1.AutoSize = False
			Me.labStatus1.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
			Me.labStatus1.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner
			Me.labStatus1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.labStatus1.Name = "labStatus1"
			Me.labStatus1.Size = New System.Drawing.Size(300, 17)
			Me.labStatus1.Text = "Quantidade Total: , Tamanho Total:"
			Me.labStatus1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' labStatus2
			' 
			Me.labStatus2.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
			Me.labStatus2.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner
			Me.labStatus2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.labStatus2.Name = "labStatus2"
			Me.labStatus2.Size = New System.Drawing.Size(569, 17)
			Me.labStatus2.Spring = True
			Me.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' odImportar
			' 
			Me.odImportar.DefaultExt = "xml"
			Me.odImportar.Filter = "Arquivos XML (*.xml)|*.xml"
			' 
			' FrmPrincipal
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(884, 462)
			Me.Controls.Add(Me.barraStatus)
			Me.Controls.Add(Me.spPesquisa)
			Me.Controls.Add(Me.barraFerra)
			Me.Controls.Add(Me.barraMenu)
			Me.MainMenuStrip = Me.barraMenu
			Me.Name = "FrmPrincipal"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "HFSGuardaDiretorio 2.0 - Catalogador de Diretórios"
			AddHandler Me.FormClosed, New System.Windows.Forms.FormClosedEventHandler(AddressOf Me.FrmPrincipalFormClosed)
			Me.barraMenu.ResumeLayout(False)
			Me.barraMenu.PerformLayout()
			Me.barraFerra.ResumeLayout(False)
			Me.barraFerra.PerformLayout()
			Me.spPesquisa.Panel1.ResumeLayout(False)
			Me.spPesquisa.Panel2.ResumeLayout(False)
			DirectCast(Me.spPesquisa, System.ComponentModel.ISupportInitialize).EndInit()
			Me.spPesquisa.ResumeLayout(False)
			Me.tabControl1.ResumeLayout(False)
			Me.popupMenu.ResumeLayout(False)
			Me.tabPage1.ResumeLayout(False)
			Me.sp.Panel1.ResumeLayout(False)
			Me.sp.Panel2.ResumeLayout(False)
			DirectCast(Me.sp, System.ComponentModel.ISupportInitialize).EndInit()
			Me.sp.ResumeLayout(False)
			Me.barraStatus.ResumeLayout(False)
			Me.barraStatus.PerformLayout()
			Me.ResumeLayout(False)
			Me.PerformLayout()
		End Sub
		Public escolherDir As System.Windows.Forms.FolderBrowserDialog
		Public sdExportar As System.Windows.Forms.SaveFileDialog
		Public odImportar As System.Windows.Forms.OpenFileDialog
		Private menuExcluirAbaAtiva2 As System.Windows.Forms.ToolStripMenuItem
		Private menuAlterarNomeAbaAtiva2 As System.Windows.Forms.ToolStripMenuItem
		Private menuIncluirNovaAba2 As System.Windows.Forms.ToolStripMenuItem
		Private toolStripSeparator2 As System.Windows.Forms.ToolStripSeparator
		Private menuColapsarDiretorios2 As System.Windows.Forms.ToolStripMenuItem
		Private menuExpandirDiretorios2 As System.Windows.Forms.ToolStripMenuItem
		Private menuExcluirDiretorioSelecionado As System.Windows.Forms.ToolStripMenuItem
		Private menuInformacoesDiretorioArquivo As System.Windows.Forms.ToolStripMenuItem
		Private popupMenu As System.Windows.Forms.ContextMenuStrip
		Private labStatus2 As System.Windows.Forms.ToolStripStatusLabel
		Private labStatus1 As System.Windows.Forms.ToolStripStatusLabel
		Public barraStatus As System.Windows.Forms.StatusStrip
		Private imageList3 As System.Windows.Forms.ImageList
		Public imageList2 As System.Windows.Forms.ImageList
		Public imageList1 As System.Windows.Forms.ImageList
		Private columnHeader15 As System.Windows.Forms.ColumnHeader
		Private columnHeader14 As System.Windows.Forms.ColumnHeader
		Private columnHeader13 As System.Windows.Forms.ColumnHeader
		Private columnHeader12 As System.Windows.Forms.ColumnHeader
		Private columnHeader11 As System.Windows.Forms.ColumnHeader
		Private columnHeader10 As System.Windows.Forms.ColumnHeader
		Public lvFixa As System.Windows.Forms.ListView
		Public tvFixa As System.Windows.Forms.TreeView
		Private sp As System.Windows.Forms.SplitContainer
		Private columnHeader7 As System.Windows.Forms.ColumnHeader
		Private columnHeader6 As System.Windows.Forms.ColumnHeader
		Private columnHeader5 As System.Windows.Forms.ColumnHeader
		Private columnHeader4 As System.Windows.Forms.ColumnHeader
		Private columnHeader3 As System.Windows.Forms.ColumnHeader
		Private columnHeader2 As System.Windows.Forms.ColumnHeader
		Private columnHeader1 As System.Windows.Forms.ColumnHeader
		Public lvPesquisa As System.Windows.Forms.ListView
		Private tabPage1 As System.Windows.Forms.TabPage
		Public tabControl1 As System.Windows.Forms.TabControl
		Public spPesquisa As System.Windows.Forms.SplitContainer
		Private btnPesquisar As System.Windows.Forms.ToolStripButton
		Public edtPesquisa As System.Windows.Forms.ToolStripTextBox
		Public pb As System.Windows.Forms.ToolStripProgressBar
		Private btnImportarDiretorio As System.Windows.Forms.ToolStripButton
		Private barraFerra As System.Windows.Forms.ToolStrip
		Private menuSobreCatalogador As System.Windows.Forms.ToolStripMenuItem
		Private menuIconesPequenos As System.Windows.Forms.ToolStripMenuItem
		Private menuDetalhes As System.Windows.Forms.ToolStripMenuItem
		Private menuLista As System.Windows.Forms.ToolStripMenuItem
		Private menuIcones As System.Windows.Forms.ToolStripMenuItem
		Private menuModoExibicao As System.Windows.Forms.ToolStripMenuItem
		Private menuMostrarOcultarListaItensPesquisados As System.Windows.Forms.ToolStripMenuItem
		Private menuMostrarOcultArvoreDirAbaAtiva As System.Windows.Forms.ToolStripMenuItem
		Public menuGravarLogImportacao As System.Windows.Forms.ToolStripMenuItem
		Private menuImportarDiretoriosViaXML As System.Windows.Forms.ToolStripMenuItem
		Private menuSQL As System.Windows.Forms.ToolStripMenuItem
		Private menuXML As System.Windows.Forms.ToolStripMenuItem
		Private menuHTML As System.Windows.Forms.ToolStripMenuItem
		Private menuCSV As System.Windows.Forms.ToolStripMenuItem
		Private menuTXT As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarDiretoriosAbaAtiva As System.Windows.Forms.ToolStripMenuItem
		Private menuColapsarDiretorios As System.Windows.Forms.ToolStripMenuItem
		Private menuExpandirDiretorios As System.Windows.Forms.ToolStripMenuItem
		Private toolStripSeparator1 As System.Windows.Forms.ToolStripSeparator
		Private menuCadastrarExtensaoArquivo As System.Windows.Forms.ToolStripMenuItem
		Private menuCompararDiretorios As System.Windows.Forms.ToolStripMenuItem
		Private menuImportarSubDiretorios As System.Windows.Forms.ToolStripMenuItem
		Private menuImportarDiretorio As System.Windows.Forms.ToolStripMenuItem
		Private menuExcluirAbaAtiva As System.Windows.Forms.ToolStripMenuItem
		Private menuAlterarNomeAbaAtiva As System.Windows.Forms.ToolStripMenuItem
		Private menuIncluirNovaAba As System.Windows.Forms.ToolStripMenuItem
		Private menuSobre As System.Windows.Forms.ToolStripMenuItem
		Private menuVisao As System.Windows.Forms.ToolStripMenuItem
		Private menuDiretorio As System.Windows.Forms.ToolStripMenuItem
		Private menuAba As System.Windows.Forms.ToolStripMenuItem
		Private barraMenu As System.Windows.Forms.MenuStrip
	End Class
End Namespace
