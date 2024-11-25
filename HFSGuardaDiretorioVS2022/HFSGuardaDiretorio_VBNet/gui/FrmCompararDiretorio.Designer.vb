'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:44
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmCompararDiretorio
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
			Dim resources As New System.ComponentModel.ComponentResourceManager(GetType(FrmCompararDiretorio))
			Me.panel1 = New System.Windows.Forms.Panel()
			Me.pb = New System.Windows.Forms.ProgressBar()
			Me.btnSalvarLog = New System.Windows.Forms.Button()
			Me.btnCompararDiretorios = New System.Windows.Forms.Button()
			Me.gpDiretorio1 = New System.Windows.Forms.GroupBox()
			Me.tvDiretorio1 = New System.Windows.Forms.TreeView()
			Me.imageList1 = New System.Windows.Forms.ImageList(Me.components)
			Me.cmbAba1 = New System.Windows.Forms.ComboBox()
			Me.gpDiretorio2 = New System.Windows.Forms.GroupBox()
			Me.tvDiretorio2 = New System.Windows.Forms.TreeView()
			Me.cmbAba2 = New System.Windows.Forms.ComboBox()
			Me.barraStatus = New System.Windows.Forms.StatusStrip()
			Me.labStatus1 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.labStatus2 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.label1 = New System.Windows.Forms.Label()
			Me.lvCompara = New System.Windows.Forms.ListView()
			Me.columnHeader10 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader11 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader12 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader13 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader14 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader15 = New System.Windows.Forms.ColumnHeader()
			Me.panel1.SuspendLayout()
			Me.gpDiretorio1.SuspendLayout()
			Me.gpDiretorio2.SuspendLayout()
			Me.barraStatus.SuspendLayout()
			Me.SuspendLayout()
			' 
			' panel1
			' 
			Me.panel1.Controls.Add(Me.pb)
			Me.panel1.Controls.Add(Me.btnSalvarLog)
			Me.panel1.Controls.Add(Me.btnCompararDiretorios)
			Me.panel1.Dock = System.Windows.Forms.DockStyle.Top
			Me.panel1.Location = New System.Drawing.Point(0, 0)
			Me.panel1.Name = "panel1"
			Me.panel1.Size = New System.Drawing.Size(687, 37)
			Me.panel1.TabIndex = 0
			' 
			' pb
			' 
			Me.pb.Location = New System.Drawing.Point(136, 10)
			Me.pb.Name = "pb"
			Me.pb.Size = New System.Drawing.Size(446, 19)
			Me.pb.[Step] = 1
			Me.pb.TabIndex = 2
			' 
			' btnSalvarLog
			' 
			Me.btnSalvarLog.Location = New System.Drawing.Point(588, 8)
			Me.btnSalvarLog.Name = "btnSalvarLog"
			Me.btnSalvarLog.Size = New System.Drawing.Size(87, 23)
			Me.btnSalvarLog.TabIndex = 1
			Me.btnSalvarLog.Text = "&Salvar Log"
			Me.btnSalvarLog.UseVisualStyleBackColor = True
			AddHandler Me.btnSalvarLog.Click, New System.EventHandler(AddressOf Me.BtnSalvarLogClick)
			' 
			' btnCompararDiretorios
			' 
			Me.btnCompararDiretorios.Location = New System.Drawing.Point(12, 8)
			Me.btnCompararDiretorios.Name = "btnCompararDiretorios"
			Me.btnCompararDiretorios.Size = New System.Drawing.Size(118, 23)
			Me.btnCompararDiretorios.TabIndex = 0
			Me.btnCompararDiretorios.Text = "&Comparar Diretórios"
			Me.btnCompararDiretorios.UseVisualStyleBackColor = True
			AddHandler Me.btnCompararDiretorios.Click, New System.EventHandler(AddressOf Me.BtnCompararDiretoriosClick)
			' 
			' gpDiretorio1
			' 
			Me.gpDiretorio1.Controls.Add(Me.tvDiretorio1)
			Me.gpDiretorio1.Controls.Add(Me.cmbAba1)
			Me.gpDiretorio1.Location = New System.Drawing.Point(12, 43)
			Me.gpDiretorio1.Name = "gpDiretorio1"
			Me.gpDiretorio1.Size = New System.Drawing.Size(329, 284)
			Me.gpDiretorio1.TabIndex = 1
			Me.gpDiretorio1.TabStop = False
			Me.gpDiretorio1.Text = "Diretório 1"
			' 
			' tvDiretorio1
			' 
			Me.tvDiretorio1.ImageIndex = 0
			Me.tvDiretorio1.ImageList = Me.imageList1
			Me.tvDiretorio1.Location = New System.Drawing.Point(6, 46)
			Me.tvDiretorio1.Name = "tvDiretorio1"
			Me.tvDiretorio1.SelectedImageIndex = 0
			Me.tvDiretorio1.Size = New System.Drawing.Size(317, 232)
			Me.tvDiretorio1.TabIndex = 1
			' 
			' imageList1
			' 
			Me.imageList1.ImageStream = DirectCast(resources.GetObject("imageList1.ImageStream"), System.Windows.Forms.ImageListStreamer)
			Me.imageList1.TransparentColor = System.Drawing.Color.Transparent
			Me.imageList1.Images.SetKeyName(0, "Fechar.bmp")
			Me.imageList1.Images.SetKeyName(1, "Abrir.bmp")
			' 
			' cmbAba1
			' 
			Me.cmbAba1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
			Me.cmbAba1.FormattingEnabled = True
			Me.cmbAba1.Location = New System.Drawing.Point(6, 19)
			Me.cmbAba1.Name = "cmbAba1"
			Me.cmbAba1.Size = New System.Drawing.Size(317, 21)
			Me.cmbAba1.TabIndex = 0
			AddHandler Me.cmbAba1.SelectedIndexChanged, New System.EventHandler(AddressOf Me.CmbAba1SelectedIndexChanged)
			' 
			' gpDiretorio2
			' 
			Me.gpDiretorio2.Controls.Add(Me.tvDiretorio2)
			Me.gpDiretorio2.Controls.Add(Me.cmbAba2)
			Me.gpDiretorio2.Location = New System.Drawing.Point(347, 43)
			Me.gpDiretorio2.Name = "gpDiretorio2"
			Me.gpDiretorio2.Size = New System.Drawing.Size(329, 284)
			Me.gpDiretorio2.TabIndex = 2
			Me.gpDiretorio2.TabStop = False
			Me.gpDiretorio2.Text = "Diretório 2"
			' 
			' tvDiretorio2
			' 
			Me.tvDiretorio2.ImageIndex = 0
			Me.tvDiretorio2.ImageList = Me.imageList1
			Me.tvDiretorio2.Location = New System.Drawing.Point(6, 46)
			Me.tvDiretorio2.Name = "tvDiretorio2"
			Me.tvDiretorio2.SelectedImageIndex = 0
			Me.tvDiretorio2.Size = New System.Drawing.Size(317, 232)
			Me.tvDiretorio2.TabIndex = 1
			' 
			' cmbAba2
			' 
			Me.cmbAba2.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
			Me.cmbAba2.FormattingEnabled = True
			Me.cmbAba2.Location = New System.Drawing.Point(6, 19)
			Me.cmbAba2.Name = "cmbAba2"
			Me.cmbAba2.Size = New System.Drawing.Size(317, 21)
			Me.cmbAba2.TabIndex = 0
			AddHandler Me.cmbAba2.SelectedIndexChanged, New System.EventHandler(AddressOf Me.CmbAba2SelectedIndexChanged)
			' 
			' barraStatus
			' 
			Me.barraStatus.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.labStatus1, Me.labStatus2})
			Me.barraStatus.Location = New System.Drawing.Point(0, 558)
			Me.barraStatus.Name = "barraStatus"
			Me.barraStatus.Size = New System.Drawing.Size(687, 22)
			Me.barraStatus.TabIndex = 10
			Me.barraStatus.Text = "statusStrip1"
			' 
			' labStatus1
			' 
			Me.labStatus1.AutoSize = False
			Me.labStatus1.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
			Me.labStatus1.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner
			Me.labStatus1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.labStatus1.Name = "labStatus1"
			Me.labStatus1.Size = New System.Drawing.Size(200, 17)
			Me.labStatus1.Text = "Total de diferenças encontradas:"
			Me.labStatus1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' labStatus2
			' 
			Me.labStatus2.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
			Me.labStatus2.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner
			Me.labStatus2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.labStatus2.Name = "labStatus2"
			Me.labStatus2.Size = New System.Drawing.Size(472, 17)
			Me.labStatus2.Spring = True
			Me.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label1
			' 
			Me.label1.Location = New System.Drawing.Point(8, 330)
			Me.label1.Name = "label1"
			Me.label1.Size = New System.Drawing.Size(138, 18)
			Me.label1.TabIndex = 11
			Me.label1.Text = "Diferenças Encontradas"
			' 
			' lvCompara
			' 
			Me.lvCompara.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader10, Me.columnHeader11, Me.columnHeader12, Me.columnHeader13, Me.columnHeader14, Me.columnHeader15})
			Me.lvCompara.FullRowSelect = True
			Me.lvCompara.GridLines = True
			Me.lvCompara.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable
			Me.lvCompara.Location = New System.Drawing.Point(0, 351)
			Me.lvCompara.MultiSelect = False
			Me.lvCompara.Name = "lvCompara"
			Me.lvCompara.Size = New System.Drawing.Size(687, 205)
			Me.lvCompara.SmallImageList = Me.imageList1
			Me.lvCompara.TabIndex = 12
			Me.lvCompara.UseCompatibleStateImageBehavior = False
			Me.lvCompara.View = System.Windows.Forms.View.Details
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
			' FrmCompararDiretorio
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(687, 580)
			Me.Controls.Add(Me.lvCompara)
			Me.Controls.Add(Me.label1)
			Me.Controls.Add(Me.barraStatus)
			Me.Controls.Add(Me.gpDiretorio2)
			Me.Controls.Add(Me.gpDiretorio1)
			Me.Controls.Add(Me.panel1)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
			Me.MaximizeBox = False
			Me.MinimizeBox = False
			Me.Name = "FrmCompararDiretorio"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "Comparar Diretórios"
			Me.panel1.ResumeLayout(False)
			Me.gpDiretorio1.ResumeLayout(False)
			Me.gpDiretorio2.ResumeLayout(False)
			Me.barraStatus.ResumeLayout(False)
			Me.barraStatus.PerformLayout()
			Me.ResumeLayout(False)
			Me.PerformLayout()
		End Sub
		Private columnHeader15 As System.Windows.Forms.ColumnHeader
		Private columnHeader14 As System.Windows.Forms.ColumnHeader
		Private columnHeader13 As System.Windows.Forms.ColumnHeader
		Private columnHeader12 As System.Windows.Forms.ColumnHeader
		Private columnHeader11 As System.Windows.Forms.ColumnHeader
		Private columnHeader10 As System.Windows.Forms.ColumnHeader
		Private lvCompara As System.Windows.Forms.ListView
		Private label1 As System.Windows.Forms.Label
		Private labStatus2 As System.Windows.Forms.ToolStripStatusLabel
		Private labStatus1 As System.Windows.Forms.ToolStripStatusLabel
		Private barraStatus As System.Windows.Forms.StatusStrip
		Private imageList1 As System.Windows.Forms.ImageList
		Private cmbAba2 As System.Windows.Forms.ComboBox
		Private tvDiretorio2 As System.Windows.Forms.TreeView
		Private gpDiretorio2 As System.Windows.Forms.GroupBox
		Private tvDiretorio1 As System.Windows.Forms.TreeView
		Private cmbAba1 As System.Windows.Forms.ComboBox
		Private gpDiretorio1 As System.Windows.Forms.GroupBox
		Public pb As System.Windows.Forms.ProgressBar
		Private btnCompararDiretorios As System.Windows.Forms.Button
		Private btnSalvarLog As System.Windows.Forms.Button
		Private panel1 As System.Windows.Forms.Panel
	End Class
End Namespace
