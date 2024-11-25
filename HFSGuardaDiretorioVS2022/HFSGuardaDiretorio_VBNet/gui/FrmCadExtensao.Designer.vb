'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:58
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmCadExtensao
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
			Me.menuStrip1 = New System.Windows.Forms.MenuStrip()
			Me.menuExtensao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuIncluirExtensao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExcluirExtensao = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExcluirTodasExtensoes = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarTodos = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarBitmap = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarIcone = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarGIF = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarJPEG = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarPNG = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExportarTIFF = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuImportarTodos = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuImportarIconesArquivos = New System.Windows.Forms.ToolStripMenuItem()
			Me.menuExtrairIconesArquivos = New System.Windows.Forms.ToolStripMenuItem()
			Me.lvExtensao = New System.Windows.Forms.ListView()
			Me.columnHeader1 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader2 = New System.Windows.Forms.ColumnHeader()
			Me.imgListExtensao = New System.Windows.Forms.ImageList(Me.components)
			Me.panel1 = New System.Windows.Forms.Panel()
			Me.btnExcluir = New System.Windows.Forms.Button()
			Me.btnIncluir = New System.Windows.Forms.Button()
			Me.odEscolhaArquivo = New System.Windows.Forms.OpenFileDialog()
			Me.menuStrip1.SuspendLayout()
			Me.panel1.SuspendLayout()
			Me.SuspendLayout()
			' 
			' menuStrip1
			' 
			Me.menuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuExtensao, Me.menuExportarTodos, Me.menuImportarTodos})
			Me.menuStrip1.Location = New System.Drawing.Point(0, 0)
			Me.menuStrip1.Name = "menuStrip1"
			Me.menuStrip1.Size = New System.Drawing.Size(280, 24)
			Me.menuStrip1.TabIndex = 0
			Me.menuStrip1.Text = "menuStrip1"
			' 
			' menuExtensao
			' 
			Me.menuExtensao.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuIncluirExtensao, Me.menuExcluirExtensao, Me.menuExcluirTodasExtensoes})
			Me.menuExtensao.Name = "menuExtensao"
			Me.menuExtensao.Size = New System.Drawing.Size(65, 20)
			Me.menuExtensao.Text = "&Extensão"
			' 
			' menuIncluirExtensao
			' 
			Me.menuIncluirExtensao.Name = "menuIncluirExtensao"
			Me.menuIncluirExtensao.Size = New System.Drawing.Size(197, 22)
			Me.menuIncluirExtensao.Text = "Incluir Extensão"
			AddHandler Me.menuIncluirExtensao.Click, New System.EventHandler(AddressOf Me.MenuIncluirExtensaoClick)
			' 
			' menuExcluirExtensao
			' 
			Me.menuExcluirExtensao.Name = "menuExcluirExtensao"
			Me.menuExcluirExtensao.Size = New System.Drawing.Size(197, 22)
			Me.menuExcluirExtensao.Text = "Excluir Extensão"
			AddHandler Me.menuExcluirExtensao.Click, New System.EventHandler(AddressOf Me.MenuExcluirExtensaoClick)
			' 
			' menuExcluirTodasExtensoes
			' 
			Me.menuExcluirTodasExtensoes.Name = "menuExcluirTodasExtensoes"
			Me.menuExcluirTodasExtensoes.Size = New System.Drawing.Size(197, 22)
			Me.menuExcluirTodasExtensoes.Text = "Excluir Todas Extensões"
			AddHandler Me.menuExcluirTodasExtensoes.Click, New System.EventHandler(AddressOf Me.MenuExcluirTodasExtensoesClick)
			' 
			' menuExportarTodos
			' 
			Me.menuExportarTodos.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuExportarBitmap, Me.menuExportarIcone, Me.menuExportarGIF, Me.menuExportarJPEG, Me.menuExportarPNG, Me.menuExportarTIFF})
			Me.menuExportarTodos.Name = "menuExportarTodos"
			Me.menuExportarTodos.Size = New System.Drawing.Size(98, 20)
			Me.menuExportarTodos.Text = "Exportar &Todos"
			' 
			' menuExportarBitmap
			' 
			Me.menuExportarBitmap.Name = "menuExportarBitmap"
			Me.menuExportarBitmap.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarBitmap.Text = "Exportar para Bitmap"
			AddHandler Me.menuExportarBitmap.Click, New System.EventHandler(AddressOf Me.MenuExportarBitmapClick)
			' 
			' menuExportarIcone
			' 
			Me.menuExportarIcone.Name = "menuExportarIcone"
			Me.menuExportarIcone.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarIcone.Text = "Exportar para Ícone"
			AddHandler Me.menuExportarIcone.Click, New System.EventHandler(AddressOf Me.MenuExportarIconeClick)
			' 
			' menuExportarGIF
			' 
			Me.menuExportarGIF.Name = "menuExportarGIF"
			Me.menuExportarGIF.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarGIF.Text = "Exportar para GIF"
			AddHandler Me.menuExportarGIF.Click, New System.EventHandler(AddressOf Me.MenuExportarGIFClick)
			' 
			' menuExportarJPEG
			' 
			Me.menuExportarJPEG.Name = "menuExportarJPEG"
			Me.menuExportarJPEG.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarJPEG.Text = "Exportar para JPEG"
			AddHandler Me.menuExportarJPEG.Click, New System.EventHandler(AddressOf Me.MenuExportarJPEGClick)
			' 
			' menuExportarPNG
			' 
			Me.menuExportarPNG.Name = "menuExportarPNG"
			Me.menuExportarPNG.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarPNG.Text = "Exportar para PNG"
			AddHandler Me.menuExportarPNG.Click, New System.EventHandler(AddressOf Me.MenuExportarPNGClick)
			' 
			' menuExportarTIFF
			' 
			Me.menuExportarTIFF.Name = "menuExportarTIFF"
			Me.menuExportarTIFF.Size = New System.Drawing.Size(184, 22)
			Me.menuExportarTIFF.Text = "Exportar para TIFF"
			AddHandler Me.menuExportarTIFF.Click, New System.EventHandler(AddressOf Me.MenuExportarTIFFClick)
			' 
			' menuImportarTodos
			' 
			Me.menuImportarTodos.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.menuImportarIconesArquivos, Me.menuExtrairIconesArquivos})
			Me.menuImportarTodos.Name = "menuImportarTodos"
			Me.menuImportarTodos.Size = New System.Drawing.Size(101, 20)
			Me.menuImportarTodos.Text = "&Importar Todos"
			' 
			' menuImportarIconesArquivos
			' 
			Me.menuImportarIconesArquivos.Name = "menuImportarIconesArquivos"
			Me.menuImportarIconesArquivos.Size = New System.Drawing.Size(229, 22)
			Me.menuImportarIconesArquivos.Text = "Importar Ícones dos Arquivos"
			AddHandler Me.menuImportarIconesArquivos.Click, New System.EventHandler(AddressOf Me.MenuImportarIconesArquivosClick)
			' 
			' menuExtrairIconesArquivos
			' 
			Me.menuExtrairIconesArquivos.Name = "menuExtrairIconesArquivos"
			Me.menuExtrairIconesArquivos.Size = New System.Drawing.Size(229, 22)
			Me.menuExtrairIconesArquivos.Text = "Extrair Ícones dos Arquivos"
			AddHandler Me.menuExtrairIconesArquivos.Click, New System.EventHandler(AddressOf Me.MenuExtrairIconesArquivosClick)
			' 
			' lvExtensao
			' 
			Me.lvExtensao.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader1, Me.columnHeader2})
			Me.lvExtensao.GridLines = True
			Me.lvExtensao.Location = New System.Drawing.Point(0, 24)
			Me.lvExtensao.MultiSelect = False
			Me.lvExtensao.Name = "lvExtensao"
			Me.lvExtensao.OwnerDraw = True
			Me.lvExtensao.Size = New System.Drawing.Size(280, 325)
			Me.lvExtensao.TabIndex = 2
			Me.lvExtensao.UseCompatibleStateImageBehavior = False
			Me.lvExtensao.View = System.Windows.Forms.View.Details
			AddHandler Me.lvExtensao.DrawColumnHeader, New System.Windows.Forms.DrawListViewColumnHeaderEventHandler(AddressOf Me.LvExtensaoDrawColumnHeader)
			AddHandler Me.lvExtensao.DrawItem, New System.Windows.Forms.DrawListViewItemEventHandler(AddressOf Me.LvExtensaoDrawItem)
			AddHandler Me.lvExtensao.DrawSubItem, New System.Windows.Forms.DrawListViewSubItemEventHandler(AddressOf Me.LvExtensaoDrawSubItem)
			' 
			' columnHeader1
			' 
			Me.columnHeader1.Text = "Extensão"
			Me.columnHeader1.Width = 167
			' 
			' columnHeader2
			' 
			Me.columnHeader2.Text = "Ícone"
			Me.columnHeader2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
			Me.columnHeader2.Width = 58
			' 
			' imgListExtensao
			' 
			Me.imgListExtensao.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit
			Me.imgListExtensao.ImageSize = New System.Drawing.Size(16, 16)
			Me.imgListExtensao.TransparentColor = System.Drawing.Color.Transparent
			' 
			' panel1
			' 
			Me.panel1.Controls.Add(Me.btnExcluir)
			Me.panel1.Controls.Add(Me.btnIncluir)
			Me.panel1.Dock = System.Windows.Forms.DockStyle.Bottom
			Me.panel1.Location = New System.Drawing.Point(0, 347)
			Me.panel1.Name = "panel1"
			Me.panel1.Size = New System.Drawing.Size(280, 43)
			Me.panel1.TabIndex = 3
			' 
			' btnExcluir
			' 
			Me.btnExcluir.Location = New System.Drawing.Point(155, 8)
			Me.btnExcluir.Name = "btnExcluir"
			Me.btnExcluir.Size = New System.Drawing.Size(75, 23)
			Me.btnExcluir.TabIndex = 1
			Me.btnExcluir.Text = "&Excluir"
			Me.btnExcluir.UseVisualStyleBackColor = True
			AddHandler Me.btnExcluir.Click, New System.EventHandler(AddressOf Me.BtnExcluirClick)
			' 
			' btnIncluir
			' 
			Me.btnIncluir.Location = New System.Drawing.Point(46, 8)
			Me.btnIncluir.Name = "btnIncluir"
			Me.btnIncluir.Size = New System.Drawing.Size(75, 23)
			Me.btnIncluir.TabIndex = 0
			Me.btnIncluir.Text = "&Incluir"
			Me.btnIncluir.UseVisualStyleBackColor = True
			AddHandler Me.btnIncluir.Click, New System.EventHandler(AddressOf Me.BtnIncluirClick)
			' 
			' odEscolhaArquivo
			' 
			Me.odEscolhaArquivo.Filter = "Todos os Arquivos (*.*)|*.*"
			' 
			' FrmCadExtensao
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(280, 390)
			Me.Controls.Add(Me.lvExtensao)
			Me.Controls.Add(Me.menuStrip1)
			Me.Controls.Add(Me.panel1)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
			Me.MainMenuStrip = Me.menuStrip1
			Me.MaximizeBox = False
			Me.MinimizeBox = False
			Me.Name = "FrmCadExtensao"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "Cadastro de Extensão de Arquivo"
			Me.menuStrip1.ResumeLayout(False)
			Me.menuStrip1.PerformLayout()
			Me.panel1.ResumeLayout(False)
			Me.ResumeLayout(False)
			Me.PerformLayout()
		End Sub
		Private imgListExtensao As System.Windows.Forms.ImageList
		Private odEscolhaArquivo As System.Windows.Forms.OpenFileDialog
		Private btnIncluir As System.Windows.Forms.Button
		Private btnExcluir As System.Windows.Forms.Button
		Private panel1 As System.Windows.Forms.Panel
		Private columnHeader2 As System.Windows.Forms.ColumnHeader
		Private columnHeader1 As System.Windows.Forms.ColumnHeader
		Private lvExtensao As System.Windows.Forms.ListView
		Private menuExtrairIconesArquivos As System.Windows.Forms.ToolStripMenuItem
		Private menuImportarIconesArquivos As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarTIFF As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarPNG As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarJPEG As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarGIF As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarIcone As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarBitmap As System.Windows.Forms.ToolStripMenuItem
		Private menuExcluirTodasExtensoes As System.Windows.Forms.ToolStripMenuItem
		Private menuExcluirExtensao As System.Windows.Forms.ToolStripMenuItem
		Private menuIncluirExtensao As System.Windows.Forms.ToolStripMenuItem
		Private menuImportarTodos As System.Windows.Forms.ToolStripMenuItem
		Private menuExportarTodos As System.Windows.Forms.ToolStripMenuItem
		Private menuExtensao As System.Windows.Forms.ToolStripMenuItem
		Private menuStrip1 As System.Windows.Forms.MenuStrip
	End Class
End Namespace
