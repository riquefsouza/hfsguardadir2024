/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 10/12/2014
 * Time: 17:39
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace HFSGuardaDiretorio.gui
{
	partial class FrmPrincipal
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmPrincipal));
			this.barraMenu = new System.Windows.Forms.MenuStrip();
			this.menuAba = new System.Windows.Forms.ToolStripMenuItem();
			this.menuIncluirNovaAba = new System.Windows.Forms.ToolStripMenuItem();
			this.menuAlterarNomeAbaAtiva = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExcluirAbaAtiva = new System.Windows.Forms.ToolStripMenuItem();
			this.menuDiretorio = new System.Windows.Forms.ToolStripMenuItem();
			this.menuImportarDiretorio = new System.Windows.Forms.ToolStripMenuItem();
			this.menuImportarSubDiretorios = new System.Windows.Forms.ToolStripMenuItem();
			this.menuCompararDiretorios = new System.Windows.Forms.ToolStripMenuItem();
			this.menuCadastrarExtensaoArquivo = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.menuExpandirDiretorios = new System.Windows.Forms.ToolStripMenuItem();
			this.menuColapsarDiretorios = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExportarDiretoriosAbaAtiva = new System.Windows.Forms.ToolStripMenuItem();
			this.menuTXT = new System.Windows.Forms.ToolStripMenuItem();
			this.menuCSV = new System.Windows.Forms.ToolStripMenuItem();
			this.menuHTML = new System.Windows.Forms.ToolStripMenuItem();
			this.menuXML = new System.Windows.Forms.ToolStripMenuItem();
			this.menuSQL = new System.Windows.Forms.ToolStripMenuItem();
			this.menuImportarDiretoriosViaXML = new System.Windows.Forms.ToolStripMenuItem();
			this.menuGravarLogImportacao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuVisao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuMostrarOcultArvoreDirAbaAtiva = new System.Windows.Forms.ToolStripMenuItem();
			this.menuMostrarOcultarListaItensPesquisados = new System.Windows.Forms.ToolStripMenuItem();
			this.menuModoExibicao = new System.Windows.Forms.ToolStripMenuItem();
			this.menuIcones = new System.Windows.Forms.ToolStripMenuItem();
			this.menuLista = new System.Windows.Forms.ToolStripMenuItem();
			this.menuDetalhes = new System.Windows.Forms.ToolStripMenuItem();
			this.menuIconesPequenos = new System.Windows.Forms.ToolStripMenuItem();
			this.menuSobre = new System.Windows.Forms.ToolStripMenuItem();
			this.menuSobreCatalogador = new System.Windows.Forms.ToolStripMenuItem();
			this.barraFerra = new System.Windows.Forms.ToolStrip();
			this.btnImportarDiretorio = new System.Windows.Forms.ToolStripButton();
			this.pb = new System.Windows.Forms.ToolStripProgressBar();
			this.edtPesquisa = new System.Windows.Forms.ToolStripTextBox();
			this.btnPesquisar = new System.Windows.Forms.ToolStripButton();
			this.spPesquisa = new System.Windows.Forms.SplitContainer();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.popupMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.menuInformacoesDiretorioArquivo = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExcluirDiretorioSelecionado = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExpandirDiretorios2 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuColapsarDiretorios2 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.menuIncluirNovaAba2 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuAlterarNomeAbaAtiva2 = new System.Windows.Forms.ToolStripMenuItem();
			this.menuExcluirAbaAtiva2 = new System.Windows.Forms.ToolStripMenuItem();
			this.tabPage1 = new System.Windows.Forms.TabPage();
			this.sp = new System.Windows.Forms.SplitContainer();
			this.tvFixa = new System.Windows.Forms.TreeView();
			this.imageList1 = new System.Windows.Forms.ImageList(this.components);
			this.lvFixa = new System.Windows.Forms.ListView();
			this.columnHeader10 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader11 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader12 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader13 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader14 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader15 = new System.Windows.Forms.ColumnHeader();
			this.imageList2 = new System.Windows.Forms.ImageList(this.components);
			this.imageList3 = new System.Windows.Forms.ImageList(this.components);
			this.lvPesquisa = new System.Windows.Forms.ListView();
			this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader2 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader3 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader4 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader5 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader6 = new System.Windows.Forms.ColumnHeader();
			this.columnHeader7 = new System.Windows.Forms.ColumnHeader();
			this.barraStatus = new System.Windows.Forms.StatusStrip();
			this.labStatus1 = new System.Windows.Forms.ToolStripStatusLabel();
			this.labStatus2 = new System.Windows.Forms.ToolStripStatusLabel();
			this.odImportar = new System.Windows.Forms.OpenFileDialog();
			this.sdExportar = new System.Windows.Forms.SaveFileDialog();
			this.escolherDir = new System.Windows.Forms.FolderBrowserDialog();
			this.barraMenu.SuspendLayout();
			this.barraFerra.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.spPesquisa)).BeginInit();
			this.spPesquisa.Panel1.SuspendLayout();
			this.spPesquisa.Panel2.SuspendLayout();
			this.spPesquisa.SuspendLayout();
			this.tabControl1.SuspendLayout();
			this.popupMenu.SuspendLayout();
			this.tabPage1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.sp)).BeginInit();
			this.sp.Panel1.SuspendLayout();
			this.sp.Panel2.SuspendLayout();
			this.sp.SuspendLayout();
			this.barraStatus.SuspendLayout();
			this.SuspendLayout();
			// 
			// barraMenu
			// 
			this.barraMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuAba,
									this.menuDiretorio,
									this.menuVisao,
									this.menuSobre});
			this.barraMenu.Location = new System.Drawing.Point(0, 0);
			this.barraMenu.Name = "barraMenu";
			this.barraMenu.Size = new System.Drawing.Size(884, 24);
			this.barraMenu.TabIndex = 0;
			this.barraMenu.Text = "menuStrip1";
			// 
			// menuAba
			// 
			this.menuAba.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuIncluirNovaAba,
									this.menuAlterarNomeAbaAtiva,
									this.menuExcluirAbaAtiva});
			this.menuAba.Name = "menuAba";
			this.menuAba.Size = new System.Drawing.Size(40, 20);
			this.menuAba.Text = "&Aba";
			// 
			// menuIncluirNovaAba
			// 
			this.menuIncluirNovaAba.Name = "menuIncluirNovaAba";
			this.menuIncluirNovaAba.Size = new System.Drawing.Size(215, 22);
			this.menuIncluirNovaAba.Text = "Incluir Nova Aba";
			this.menuIncluirNovaAba.Click += new System.EventHandler(this.MenuIncluirNovaAbaClick);
			// 
			// menuAlterarNomeAbaAtiva
			// 
			this.menuAlterarNomeAbaAtiva.Name = "menuAlterarNomeAbaAtiva";
			this.menuAlterarNomeAbaAtiva.Size = new System.Drawing.Size(215, 22);
			this.menuAlterarNomeAbaAtiva.Text = "Alterar Nome da Aba Ativa";
			this.menuAlterarNomeAbaAtiva.Click += new System.EventHandler(this.MenuAlterarNomeAbaAtivaClick);
			// 
			// menuExcluirAbaAtiva
			// 
			this.menuExcluirAbaAtiva.Name = "menuExcluirAbaAtiva";
			this.menuExcluirAbaAtiva.Size = new System.Drawing.Size(215, 22);
			this.menuExcluirAbaAtiva.Text = "Excluir Aba Ativa";
			this.menuExcluirAbaAtiva.Click += new System.EventHandler(this.MenuExcluirAbaAtivaClick);
			// 
			// menuDiretorio
			// 
			this.menuDiretorio.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuImportarDiretorio,
									this.menuImportarSubDiretorios,
									this.menuCompararDiretorios,
									this.menuCadastrarExtensaoArquivo,
									this.toolStripSeparator1,
									this.menuExpandirDiretorios,
									this.menuColapsarDiretorios,
									this.menuExportarDiretoriosAbaAtiva,
									this.menuImportarDiretoriosViaXML,
									this.menuGravarLogImportacao});
			this.menuDiretorio.Name = "menuDiretorio";
			this.menuDiretorio.Size = new System.Drawing.Size(65, 20);
			this.menuDiretorio.Text = "&Diretório";
			// 
			// menuImportarDiretorio
			// 
			this.menuImportarDiretorio.Name = "menuImportarDiretorio";
			this.menuImportarDiretorio.Size = new System.Drawing.Size(241, 22);
			this.menuImportarDiretorio.Text = "Importar Diretório";
			this.menuImportarDiretorio.Click += new System.EventHandler(this.MenuImportarDiretorioClick);
			// 
			// menuImportarSubDiretorios
			// 
			this.menuImportarSubDiretorios.Name = "menuImportarSubDiretorios";
			this.menuImportarSubDiretorios.Size = new System.Drawing.Size(241, 22);
			this.menuImportarSubDiretorios.Text = "Importar SubDiretórios";
			this.menuImportarSubDiretorios.Click += new System.EventHandler(this.MenuImportarSubDiretoriosClick);
			// 
			// menuCompararDiretorios
			// 
			this.menuCompararDiretorios.Name = "menuCompararDiretorios";
			this.menuCompararDiretorios.Size = new System.Drawing.Size(241, 22);
			this.menuCompararDiretorios.Text = "Comparar Diretórios";
			this.menuCompararDiretorios.Click += new System.EventHandler(this.MenuCompararDiretoriosClick);
			// 
			// menuCadastrarExtensaoArquivo
			// 
			this.menuCadastrarExtensaoArquivo.Name = "menuCadastrarExtensaoArquivo";
			this.menuCadastrarExtensaoArquivo.Size = new System.Drawing.Size(241, 22);
			this.menuCadastrarExtensaoArquivo.Text = "Cadastrar Extensão de Arquivo";
			this.menuCadastrarExtensaoArquivo.Click += new System.EventHandler(this.MenuCadastrarExtensaoArquivoClick);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(238, 6);
			// 
			// menuExpandirDiretorios
			// 
			this.menuExpandirDiretorios.Name = "menuExpandirDiretorios";
			this.menuExpandirDiretorios.Size = new System.Drawing.Size(241, 22);
			this.menuExpandirDiretorios.Text = "Expandir Diretórios";
			this.menuExpandirDiretorios.Click += new System.EventHandler(this.MenuExpandirDiretoriosClick);
			// 
			// menuColapsarDiretorios
			// 
			this.menuColapsarDiretorios.Name = "menuColapsarDiretorios";
			this.menuColapsarDiretorios.Size = new System.Drawing.Size(241, 22);
			this.menuColapsarDiretorios.Text = "Colapsar Diretórios";
			this.menuColapsarDiretorios.Click += new System.EventHandler(this.MenuColapsarDiretoriosClick);
			// 
			// menuExportarDiretoriosAbaAtiva
			// 
			this.menuExportarDiretoriosAbaAtiva.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuTXT,
									this.menuCSV,
									this.menuHTML,
									this.menuXML,
									this.menuSQL});
			this.menuExportarDiretoriosAbaAtiva.Name = "menuExportarDiretoriosAbaAtiva";
			this.menuExportarDiretoriosAbaAtiva.Size = new System.Drawing.Size(241, 22);
			this.menuExportarDiretoriosAbaAtiva.Text = "Exportar Diretórios da Aba Ativa";
			// 
			// menuTXT
			// 
			this.menuTXT.Name = "menuTXT";
			this.menuTXT.Size = new System.Drawing.Size(107, 22);
			this.menuTXT.Text = "TXT";
			this.menuTXT.Click += new System.EventHandler(this.MenuTXTClick);
			// 
			// menuCSV
			// 
			this.menuCSV.Name = "menuCSV";
			this.menuCSV.Size = new System.Drawing.Size(107, 22);
			this.menuCSV.Text = "CSV";
			this.menuCSV.Click += new System.EventHandler(this.MenuCSVClick);
			// 
			// menuHTML
			// 
			this.menuHTML.Name = "menuHTML";
			this.menuHTML.Size = new System.Drawing.Size(107, 22);
			this.menuHTML.Text = "HTML";
			this.menuHTML.Click += new System.EventHandler(this.MenuHTMLClick);
			// 
			// menuXML
			// 
			this.menuXML.Name = "menuXML";
			this.menuXML.Size = new System.Drawing.Size(107, 22);
			this.menuXML.Text = "XML";
			this.menuXML.Click += new System.EventHandler(this.MenuXMLClick);
			// 
			// menuSQL
			// 
			this.menuSQL.Name = "menuSQL";
			this.menuSQL.Size = new System.Drawing.Size(107, 22);
			this.menuSQL.Text = "SQL";
			this.menuSQL.Click += new System.EventHandler(this.MenuSQLClick);
			// 
			// menuImportarDiretoriosViaXML
			// 
			this.menuImportarDiretoriosViaXML.Name = "menuImportarDiretoriosViaXML";
			this.menuImportarDiretoriosViaXML.Size = new System.Drawing.Size(241, 22);
			this.menuImportarDiretoriosViaXML.Text = "Importar Diretórios via XML";
			this.menuImportarDiretoriosViaXML.Click += new System.EventHandler(this.MenuImportarDiretoriosViaXMLClick);
			// 
			// menuGravarLogImportacao
			// 
			this.menuGravarLogImportacao.CheckOnClick = true;
			this.menuGravarLogImportacao.Name = "menuGravarLogImportacao";
			this.menuGravarLogImportacao.Size = new System.Drawing.Size(241, 22);
			this.menuGravarLogImportacao.Text = "Gravar Log da Importação";
			// 
			// menuVisao
			// 
			this.menuVisao.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuMostrarOcultArvoreDirAbaAtiva,
									this.menuMostrarOcultarListaItensPesquisados,
									this.menuModoExibicao});
			this.menuVisao.Name = "menuVisao";
			this.menuVisao.Size = new System.Drawing.Size(47, 20);
			this.menuVisao.Text = "&Visão";
			// 
			// menuMostrarOcultArvoreDirAbaAtiva
			// 
			this.menuMostrarOcultArvoreDirAbaAtiva.Name = "menuMostrarOcultArvoreDirAbaAtiva";
			this.menuMostrarOcultArvoreDirAbaAtiva.Size = new System.Drawing.Size(334, 22);
			this.menuMostrarOcultArvoreDirAbaAtiva.Text = "Mostrar/Ocultar árvore de diretórios da Aba Ativa";
			this.menuMostrarOcultArvoreDirAbaAtiva.Click += new System.EventHandler(this.MenuMostrarOcultArvoreDirAbaAtivaClick);
			// 
			// menuMostrarOcultarListaItensPesquisados
			// 
			this.menuMostrarOcultarListaItensPesquisados.Name = "menuMostrarOcultarListaItensPesquisados";
			this.menuMostrarOcultarListaItensPesquisados.Size = new System.Drawing.Size(334, 22);
			this.menuMostrarOcultarListaItensPesquisados.Text = "Mostrar/Ocultar lista de itens pesquisados";
			this.menuMostrarOcultarListaItensPesquisados.Click += new System.EventHandler(this.MenuMostrarOcultarListaItensPesquisadosClick);
			// 
			// menuModoExibicao
			// 
			this.menuModoExibicao.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuIcones,
									this.menuLista,
									this.menuDetalhes,
									this.menuIconesPequenos});
			this.menuModoExibicao.Name = "menuModoExibicao";
			this.menuModoExibicao.Size = new System.Drawing.Size(334, 22);
			this.menuModoExibicao.Text = "Modo de Exibição";
			// 
			// menuIcones
			// 
			this.menuIcones.Name = "menuIcones";
			this.menuIcones.Size = new System.Drawing.Size(163, 22);
			this.menuIcones.Text = "Ícones";
			this.menuIcones.Click += new System.EventHandler(this.MenuIconesClick);
			// 
			// menuLista
			// 
			this.menuLista.Name = "menuLista";
			this.menuLista.Size = new System.Drawing.Size(163, 22);
			this.menuLista.Text = "Lista";
			this.menuLista.Click += new System.EventHandler(this.MenuListaClick);
			// 
			// menuDetalhes
			// 
			this.menuDetalhes.Name = "menuDetalhes";
			this.menuDetalhes.Size = new System.Drawing.Size(163, 22);
			this.menuDetalhes.Text = "Detalhes";
			this.menuDetalhes.Click += new System.EventHandler(this.MenuDetalhesClick);
			// 
			// menuIconesPequenos
			// 
			this.menuIconesPequenos.Name = "menuIconesPequenos";
			this.menuIconesPequenos.Size = new System.Drawing.Size(163, 22);
			this.menuIconesPequenos.Text = "Ícones Pequenos";
			this.menuIconesPequenos.Click += new System.EventHandler(this.MenuIconesPequenosClick);
			// 
			// menuSobre
			// 
			this.menuSobre.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuSobreCatalogador});
			this.menuSobre.Name = "menuSobre";
			this.menuSobre.Size = new System.Drawing.Size(49, 20);
			this.menuSobre.Text = "&Sobre";
			// 
			// menuSobreCatalogador
			// 
			this.menuSobreCatalogador.Name = "menuSobreCatalogador";
			this.menuSobreCatalogador.Size = new System.Drawing.Size(182, 22);
			this.menuSobreCatalogador.Text = "Sobre o Catalogador";
			this.menuSobreCatalogador.Click += new System.EventHandler(this.MenuSobreCatalogadorClick);
			// 
			// barraFerra
			// 
			this.barraFerra.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.barraFerra.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.btnImportarDiretorio,
									this.pb,
									this.edtPesquisa,
									this.btnPesquisar});
			this.barraFerra.Location = new System.Drawing.Point(0, 24);
			this.barraFerra.Name = "barraFerra";
			this.barraFerra.Size = new System.Drawing.Size(884, 25);
			this.barraFerra.Stretch = true;
			this.barraFerra.TabIndex = 1;
			// 
			// btnImportarDiretorio
			// 
			this.btnImportarDiretorio.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.btnImportarDiretorio.Image = ((System.Drawing.Image)(resources.GetObject("btnImportarDiretorio.Image")));
			this.btnImportarDiretorio.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnImportarDiretorio.Name = "btnImportarDiretorio";
			this.btnImportarDiretorio.Size = new System.Drawing.Size(106, 22);
			this.btnImportarDiretorio.Text = "&Importar Diretório";
			this.btnImportarDiretorio.Click += new System.EventHandler(this.BtnImportarDiretorioClick);
			// 
			// pb
			// 
			this.pb.AutoSize = false;
			this.pb.Name = "pb";
			this.pb.Size = new System.Drawing.Size(385, 22);
			this.pb.Step = 0;
			// 
			// edtPesquisa
			// 
			this.edtPesquisa.AutoSize = false;
			this.edtPesquisa.MaxLength = 255;
			this.edtPesquisa.Name = "edtPesquisa";
			this.edtPesquisa.Size = new System.Drawing.Size(288, 25);
			this.edtPesquisa.ToolTipText = "Digite aqui para pesquisar";
			// 
			// btnPesquisar
			// 
			this.btnPesquisar.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.btnPesquisar.Image = ((System.Drawing.Image)(resources.GetObject("btnPesquisar.Image")));
			this.btnPesquisar.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.btnPesquisar.Name = "btnPesquisar";
			this.btnPesquisar.Size = new System.Drawing.Size(61, 22);
			this.btnPesquisar.Text = "&Pesquisar";
			this.btnPesquisar.Click += new System.EventHandler(this.BtnPesquisarClick);
			// 
			// spPesquisa
			// 
			this.spPesquisa.Dock = System.Windows.Forms.DockStyle.Fill;
			this.spPesquisa.Location = new System.Drawing.Point(0, 49);
			this.spPesquisa.Name = "spPesquisa";
			this.spPesquisa.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// spPesquisa.Panel1
			// 
			this.spPesquisa.Panel1.Controls.Add(this.tabControl1);
			// 
			// spPesquisa.Panel2
			// 
			this.spPesquisa.Panel2.Controls.Add(this.lvPesquisa);
			this.spPesquisa.Size = new System.Drawing.Size(884, 413);
			this.spPesquisa.SplitterDistance = 294;
			this.spPesquisa.TabIndex = 2;
			// 
			// tabControl1
			// 
			this.tabControl1.ContextMenuStrip = this.popupMenu;
			this.tabControl1.Controls.Add(this.tabPage1);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.ImageList = this.imageList3;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(884, 294);
			this.tabControl1.TabIndex = 0;
			this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.TabControl1SelectedIndexChanged);
			// 
			// popupMenu
			// 
			this.popupMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.menuInformacoesDiretorioArquivo,
									this.menuExcluirDiretorioSelecionado,
									this.menuExpandirDiretorios2,
									this.menuColapsarDiretorios2,
									this.toolStripSeparator2,
									this.menuIncluirNovaAba2,
									this.menuAlterarNomeAbaAtiva2,
									this.menuExcluirAbaAtiva2});
			this.popupMenu.Name = "popupMenu";
			this.popupMenu.Size = new System.Drawing.Size(260, 164);
			// 
			// menuInformacoesDiretorioArquivo
			// 
			this.menuInformacoesDiretorioArquivo.Name = "menuInformacoesDiretorioArquivo";
			this.menuInformacoesDiretorioArquivo.Size = new System.Drawing.Size(259, 22);
			this.menuInformacoesDiretorioArquivo.Text = "Informações do Diretório / Arquivo";
			this.menuInformacoesDiretorioArquivo.Click += new System.EventHandler(this.MenuInformacoesDiretorioArquivoClick);
			// 
			// menuExcluirDiretorioSelecionado
			// 
			this.menuExcluirDiretorioSelecionado.Name = "menuExcluirDiretorioSelecionado";
			this.menuExcluirDiretorioSelecionado.Size = new System.Drawing.Size(259, 22);
			this.menuExcluirDiretorioSelecionado.Text = "Excluir Diretório Selecionado";
			this.menuExcluirDiretorioSelecionado.Click += new System.EventHandler(this.MenuExcluirDiretorioSelecionadoClick);
			// 
			// menuExpandirDiretorios2
			// 
			this.menuExpandirDiretorios2.Name = "menuExpandirDiretorios2";
			this.menuExpandirDiretorios2.Size = new System.Drawing.Size(259, 22);
			this.menuExpandirDiretorios2.Text = "Expandir Diretórios";
			this.menuExpandirDiretorios2.Click += new System.EventHandler(this.MenuExpandirDiretorios2Click);
			// 
			// menuColapsarDiretorios2
			// 
			this.menuColapsarDiretorios2.Name = "menuColapsarDiretorios2";
			this.menuColapsarDiretorios2.Size = new System.Drawing.Size(259, 22);
			this.menuColapsarDiretorios2.Text = "Colapsar Diretórios";
			this.menuColapsarDiretorios2.Click += new System.EventHandler(this.MenuColapsarDiretorios2Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(256, 6);
			// 
			// menuIncluirNovaAba2
			// 
			this.menuIncluirNovaAba2.Name = "menuIncluirNovaAba2";
			this.menuIncluirNovaAba2.Size = new System.Drawing.Size(259, 22);
			this.menuIncluirNovaAba2.Text = "Incluir nova aba";
			this.menuIncluirNovaAba2.Click += new System.EventHandler(this.MenuIncluirNovaAba2Click);
			// 
			// menuAlterarNomeAbaAtiva2
			// 
			this.menuAlterarNomeAbaAtiva2.Name = "menuAlterarNomeAbaAtiva2";
			this.menuAlterarNomeAbaAtiva2.Size = new System.Drawing.Size(259, 22);
			this.menuAlterarNomeAbaAtiva2.Text = "Alterar nome da aba ativa";
			this.menuAlterarNomeAbaAtiva2.Click += new System.EventHandler(this.MenuAlterarNomeAbaAtiva2Click);
			// 
			// menuExcluirAbaAtiva2
			// 
			this.menuExcluirAbaAtiva2.Name = "menuExcluirAbaAtiva2";
			this.menuExcluirAbaAtiva2.Size = new System.Drawing.Size(259, 22);
			this.menuExcluirAbaAtiva2.Text = "Excluir aba ativa";
			this.menuExcluirAbaAtiva2.Click += new System.EventHandler(this.MenuExcluirAbaAtiva2Click);
			// 
			// tabPage1
			// 
			this.tabPage1.Controls.Add(this.sp);
			this.tabPage1.ImageIndex = 0;
			this.tabPage1.Location = new System.Drawing.Point(4, 23);
			this.tabPage1.Name = "tabPage1";
			this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
			this.tabPage1.Size = new System.Drawing.Size(876, 267);
			this.tabPage1.TabIndex = 0;
			this.tabPage1.Text = "DISCO1";
			this.tabPage1.UseVisualStyleBackColor = true;
			// 
			// sp
			// 
			this.sp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.sp.Location = new System.Drawing.Point(3, 3);
			this.sp.Name = "sp";
			// 
			// sp.Panel1
			// 
			this.sp.Panel1.Controls.Add(this.tvFixa);
			// 
			// sp.Panel2
			// 
			this.sp.Panel2.Controls.Add(this.lvFixa);
			this.sp.Size = new System.Drawing.Size(870, 261);
			this.sp.SplitterDistance = 290;
			this.sp.TabIndex = 0;
			// 
			// tvFixa
			// 
			this.tvFixa.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tvFixa.FullRowSelect = true;
			this.tvFixa.HideSelection = false;
			this.tvFixa.ImageIndex = 0;
			this.tvFixa.ImageList = this.imageList1;
			this.tvFixa.Location = new System.Drawing.Point(0, 0);
			this.tvFixa.Name = "tvFixa";
			this.tvFixa.SelectedImageIndex = 1;
			this.tvFixa.Size = new System.Drawing.Size(290, 261);
			this.tvFixa.TabIndex = 0;
			this.tvFixa.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.TvFixaAfterSelect);
			// 
			// imageList1
			// 
			this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
			this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
			this.imageList1.Images.SetKeyName(0, "Fechar.bmp");
			this.imageList1.Images.SetKeyName(1, "Abrir.bmp");
			this.imageList1.Images.SetKeyName(2, "Arquivo.bmp");
			// 
			// lvFixa
			// 
			this.lvFixa.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader10,
									this.columnHeader11,
									this.columnHeader12,
									this.columnHeader13,
									this.columnHeader14,
									this.columnHeader15});
			this.lvFixa.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lvFixa.FullRowSelect = true;
			this.lvFixa.GridLines = true;
			this.lvFixa.LargeImageList = this.imageList2;
			this.lvFixa.Location = new System.Drawing.Point(0, 0);
			this.lvFixa.MultiSelect = false;
			this.lvFixa.Name = "lvFixa";
			this.lvFixa.Size = new System.Drawing.Size(576, 261);
			this.lvFixa.SmallImageList = this.imageList1;
			this.lvFixa.TabIndex = 1;
			this.lvFixa.UseCompatibleStateImageBehavior = false;
			this.lvFixa.View = System.Windows.Forms.View.Details;
			this.lvFixa.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.LvFixaColumnClick);
			this.lvFixa.DoubleClick += new System.EventHandler(this.LvFixaDoubleClick);
			// 
			// columnHeader10
			// 
			this.columnHeader10.Text = "Nome";
			this.columnHeader10.Width = 300;
			// 
			// columnHeader11
			// 
			this.columnHeader11.Text = "Tamanho";
			this.columnHeader11.Width = 100;
			// 
			// columnHeader12
			// 
			this.columnHeader12.Text = "Tipo";
			this.columnHeader12.Width = 70;
			// 
			// columnHeader13
			// 
			this.columnHeader13.Text = "Modificado";
			this.columnHeader13.Width = 120;
			// 
			// columnHeader14
			// 
			this.columnHeader14.Text = "Atributos";
			this.columnHeader14.Width = 90;
			// 
			// columnHeader15
			// 
			this.columnHeader15.Text = "Caminho";
			this.columnHeader15.Width = 300;
			// 
			// imageList2
			// 
			this.imageList2.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList2.ImageStream")));
			this.imageList2.TransparentColor = System.Drawing.Color.Transparent;
			this.imageList2.Images.SetKeyName(0, "Fechar32.bmp");
			this.imageList2.Images.SetKeyName(1, "Abrir32.bmp");
			this.imageList2.Images.SetKeyName(2, "Arquivo32.bmp");
			// 
			// imageList3
			// 
			this.imageList3.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList3.ImageStream")));
			this.imageList3.TransparentColor = System.Drawing.Color.Magenta;
			this.imageList3.Images.SetKeyName(0, "cdouro.bmp");
			this.imageList3.Images.SetKeyName(1, "cdprata.bmp");
			// 
			// lvPesquisa
			// 
			this.lvPesquisa.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
									this.columnHeader1,
									this.columnHeader2,
									this.columnHeader3,
									this.columnHeader4,
									this.columnHeader5,
									this.columnHeader6,
									this.columnHeader7});
			this.lvPesquisa.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lvPesquisa.FullRowSelect = true;
			this.lvPesquisa.GridLines = true;
			this.lvPesquisa.LargeImageList = this.imageList2;
			this.lvPesquisa.Location = new System.Drawing.Point(0, 0);
			this.lvPesquisa.MultiSelect = false;
			this.lvPesquisa.Name = "lvPesquisa";
			this.lvPesquisa.Size = new System.Drawing.Size(884, 115);
			this.lvPesquisa.SmallImageList = this.imageList1;
			this.lvPesquisa.TabIndex = 0;
			this.lvPesquisa.UseCompatibleStateImageBehavior = false;
			this.lvPesquisa.View = System.Windows.Forms.View.Details;
			this.lvPesquisa.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.LvPesquisaColumnClick);
			this.lvPesquisa.Click += new System.EventHandler(this.LvPesquisaClick);
			// 
			// columnHeader1
			// 
			this.columnHeader1.Text = "Nome";
			this.columnHeader1.Width = 300;
			// 
			// columnHeader2
			// 
			this.columnHeader2.Text = "Tamanho";
			this.columnHeader2.Width = 100;
			// 
			// columnHeader3
			// 
			this.columnHeader3.Text = "Tipo";
			this.columnHeader3.Width = 70;
			// 
			// columnHeader4
			// 
			this.columnHeader4.Text = "Modificado";
			this.columnHeader4.Width = 120;
			// 
			// columnHeader5
			// 
			this.columnHeader5.Text = "Atributos";
			this.columnHeader5.Width = 90;
			// 
			// columnHeader6
			// 
			this.columnHeader6.Text = "Caminho";
			this.columnHeader6.Width = 300;
			// 
			// columnHeader7
			// 
			this.columnHeader7.Text = "Aba";
			this.columnHeader7.Width = 150;
			// 
			// barraStatus
			// 
			this.barraStatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
									this.labStatus1,
									this.labStatus2});
			this.barraStatus.Location = new System.Drawing.Point(0, 440);
			this.barraStatus.Name = "barraStatus";
			this.barraStatus.Size = new System.Drawing.Size(884, 22);
			this.barraStatus.TabIndex = 3;
			this.barraStatus.Text = "statusStrip1";
			// 
			// labStatus1
			// 
			this.labStatus1.AutoSize = false;
			this.labStatus1.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.labStatus1.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.labStatus1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.labStatus1.Name = "labStatus1";
			this.labStatus1.Size = new System.Drawing.Size(300, 17);
			this.labStatus1.Text = "Quantidade Total: , Tamanho Total:";
			this.labStatus1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// labStatus2
			// 
			this.labStatus2.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
									| System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
			this.labStatus2.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner;
			this.labStatus2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
			this.labStatus2.Name = "labStatus2";
			this.labStatus2.Size = new System.Drawing.Size(569, 17);
			this.labStatus2.Spring = true;
			this.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			// 
			// odImportar
			// 
			this.odImportar.DefaultExt = "xml";
			this.odImportar.Filter = "Arquivos XML (*.xml)|*.xml";
			// 
			// FrmPrincipal
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(884, 462);
			this.Controls.Add(this.barraStatus);
			this.Controls.Add(this.spPesquisa);
			this.Controls.Add(this.barraFerra);
			this.Controls.Add(this.barraMenu);
			this.MainMenuStrip = this.barraMenu;
			this.Name = "FrmPrincipal";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "HFSGuardaDiretorio 2.0 - Catalogador de Diretórios";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FrmPrincipalFormClosed);
			this.barraMenu.ResumeLayout(false);
			this.barraMenu.PerformLayout();
			this.barraFerra.ResumeLayout(false);
			this.barraFerra.PerformLayout();
			this.spPesquisa.Panel1.ResumeLayout(false);
			this.spPesquisa.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.spPesquisa)).EndInit();
			this.spPesquisa.ResumeLayout(false);
			this.tabControl1.ResumeLayout(false);
			this.popupMenu.ResumeLayout(false);
			this.tabPage1.ResumeLayout(false);
			this.sp.Panel1.ResumeLayout(false);
			this.sp.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.sp)).EndInit();
			this.sp.ResumeLayout(false);
			this.barraStatus.ResumeLayout(false);
			this.barraStatus.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();
		}
		public System.Windows.Forms.FolderBrowserDialog escolherDir;
		public System.Windows.Forms.SaveFileDialog sdExportar;
		public System.Windows.Forms.OpenFileDialog odImportar;
		private System.Windows.Forms.ToolStripMenuItem menuExcluirAbaAtiva2;
		private System.Windows.Forms.ToolStripMenuItem menuAlterarNomeAbaAtiva2;
		private System.Windows.Forms.ToolStripMenuItem menuIncluirNovaAba2;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem menuColapsarDiretorios2;
		private System.Windows.Forms.ToolStripMenuItem menuExpandirDiretorios2;
		private System.Windows.Forms.ToolStripMenuItem menuExcluirDiretorioSelecionado;
		private System.Windows.Forms.ToolStripMenuItem menuInformacoesDiretorioArquivo;
		private System.Windows.Forms.ContextMenuStrip popupMenu;
		private System.Windows.Forms.ToolStripStatusLabel labStatus2;
		private System.Windows.Forms.ToolStripStatusLabel labStatus1;
		public System.Windows.Forms.StatusStrip barraStatus;
		private System.Windows.Forms.ImageList imageList3;
		public System.Windows.Forms.ImageList imageList2;
		public System.Windows.Forms.ImageList imageList1;
		private System.Windows.Forms.ColumnHeader columnHeader15;
		private System.Windows.Forms.ColumnHeader columnHeader14;
		private System.Windows.Forms.ColumnHeader columnHeader13;
		private System.Windows.Forms.ColumnHeader columnHeader12;
		private System.Windows.Forms.ColumnHeader columnHeader11;
		private System.Windows.Forms.ColumnHeader columnHeader10;
		public System.Windows.Forms.ListView lvFixa;
		public System.Windows.Forms.TreeView tvFixa;
		private System.Windows.Forms.SplitContainer sp;
		private System.Windows.Forms.ColumnHeader columnHeader7;
		private System.Windows.Forms.ColumnHeader columnHeader6;
		private System.Windows.Forms.ColumnHeader columnHeader5;
		private System.Windows.Forms.ColumnHeader columnHeader4;
		private System.Windows.Forms.ColumnHeader columnHeader3;
		private System.Windows.Forms.ColumnHeader columnHeader2;
		private System.Windows.Forms.ColumnHeader columnHeader1;
		public System.Windows.Forms.ListView lvPesquisa;
		private System.Windows.Forms.TabPage tabPage1;
		public System.Windows.Forms.TabControl tabControl1;
		public System.Windows.Forms.SplitContainer spPesquisa;
		private System.Windows.Forms.ToolStripButton btnPesquisar;
		public System.Windows.Forms.ToolStripTextBox edtPesquisa;
		public System.Windows.Forms.ToolStripProgressBar pb;
		private System.Windows.Forms.ToolStripButton btnImportarDiretorio;
		private System.Windows.Forms.ToolStrip barraFerra;
		private System.Windows.Forms.ToolStripMenuItem menuSobreCatalogador;
		private System.Windows.Forms.ToolStripMenuItem menuIconesPequenos;
		private System.Windows.Forms.ToolStripMenuItem menuDetalhes;
		private System.Windows.Forms.ToolStripMenuItem menuLista;
		private System.Windows.Forms.ToolStripMenuItem menuIcones;
		private System.Windows.Forms.ToolStripMenuItem menuModoExibicao;
		private System.Windows.Forms.ToolStripMenuItem menuMostrarOcultarListaItensPesquisados;
		private System.Windows.Forms.ToolStripMenuItem menuMostrarOcultArvoreDirAbaAtiva;
		public System.Windows.Forms.ToolStripMenuItem menuGravarLogImportacao;
		private System.Windows.Forms.ToolStripMenuItem menuImportarDiretoriosViaXML;
		private System.Windows.Forms.ToolStripMenuItem menuSQL;
		private System.Windows.Forms.ToolStripMenuItem menuXML;
		private System.Windows.Forms.ToolStripMenuItem menuHTML;
		private System.Windows.Forms.ToolStripMenuItem menuCSV;
		private System.Windows.Forms.ToolStripMenuItem menuTXT;
		private System.Windows.Forms.ToolStripMenuItem menuExportarDiretoriosAbaAtiva;
		private System.Windows.Forms.ToolStripMenuItem menuColapsarDiretorios;
		private System.Windows.Forms.ToolStripMenuItem menuExpandirDiretorios;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem menuCadastrarExtensaoArquivo;
		private System.Windows.Forms.ToolStripMenuItem menuCompararDiretorios;
		private System.Windows.Forms.ToolStripMenuItem menuImportarSubDiretorios;
		private System.Windows.Forms.ToolStripMenuItem menuImportarDiretorio;
		private System.Windows.Forms.ToolStripMenuItem menuExcluirAbaAtiva;
		private System.Windows.Forms.ToolStripMenuItem menuAlterarNomeAbaAtiva;
		private System.Windows.Forms.ToolStripMenuItem menuIncluirNovaAba;
		private System.Windows.Forms.ToolStripMenuItem menuSobre;
		private System.Windows.Forms.ToolStripMenuItem menuVisao;
		private System.Windows.Forms.ToolStripMenuItem menuDiretorio;
		private System.Windows.Forms.ToolStripMenuItem menuAba;
		private System.Windows.Forms.MenuStrip barraMenu;
	}
}
