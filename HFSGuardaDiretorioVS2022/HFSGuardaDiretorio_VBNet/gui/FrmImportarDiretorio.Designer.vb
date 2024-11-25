'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:24
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmImportarDiretorio
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
			Me.memoImportaDir = New System.Windows.Forms.TextBox()
			Me.barraStatus = New System.Windows.Forms.StatusStrip()
			Me.labStatus1 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.labStatus2 = New System.Windows.Forms.ToolStripStatusLabel()
			Me.pbImportar = New System.Windows.Forms.ProgressBar()
			Me.barraStatus.SuspendLayout()
			Me.SuspendLayout()
			' 
			' memoImportaDir
			' 
			Me.memoImportaDir.Dock = System.Windows.Forms.DockStyle.Top
			Me.memoImportaDir.Location = New System.Drawing.Point(0, 0)
			Me.memoImportaDir.Multiline = True
			Me.memoImportaDir.Name = "memoImportaDir"
			Me.memoImportaDir.ScrollBars = System.Windows.Forms.ScrollBars.Both
			Me.memoImportaDir.Size = New System.Drawing.Size(889, 505)
			Me.memoImportaDir.TabIndex = 0
			' 
			' barraStatus
			' 
			Me.barraStatus.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.labStatus1, Me.labStatus2})
			Me.barraStatus.Location = New System.Drawing.Point(0, 522)
			Me.barraStatus.Name = "barraStatus"
			Me.barraStatus.Size = New System.Drawing.Size(889, 22)
			Me.barraStatus.TabIndex = 9
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
			Me.labStatus1.Text = "Total de linhas sendo processadas:"
			Me.labStatus1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' labStatus2
			' 
			Me.labStatus2.BorderSides = CType((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) Or System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom), System.Windows.Forms.ToolStripStatusLabelBorderSides)
			Me.labStatus2.BorderStyle = System.Windows.Forms.Border3DStyle.SunkenInner
			Me.labStatus2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text
			Me.labStatus2.Name = "labStatus2"
			Me.labStatus2.Size = New System.Drawing.Size(643, 17)
			Me.labStatus2.Spring = True
			Me.labStatus2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' pbImportar
			' 
			Me.pbImportar.Dock = System.Windows.Forms.DockStyle.Bottom
			Me.pbImportar.Location = New System.Drawing.Point(0, 505)
			Me.pbImportar.Name = "pbImportar"
			Me.pbImportar.Size = New System.Drawing.Size(889, 17)
			Me.pbImportar.[Step] = 1
			Me.pbImportar.TabIndex = 10
			' 
			' FrmImportarDiretorio
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(889, 544)
			Me.ControlBox = False
			Me.Controls.Add(Me.pbImportar)
			Me.Controls.Add(Me.barraStatus)
			Me.Controls.Add(Me.memoImportaDir)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
			Me.MaximizeBox = False
			Me.MinimizeBox = False
			Me.Name = "FrmImportarDiretorio"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "Importando Diretório"
			AddHandler Me.Shown, New System.EventHandler(AddressOf Me.FrmImportarDiretorioShown)
			Me.barraStatus.ResumeLayout(False)
			Me.barraStatus.PerformLayout()
			Me.ResumeLayout(False)
			Me.PerformLayout()
		End Sub
		Public labStatus2 As System.Windows.Forms.ToolStripStatusLabel
		Private labStatus1 As System.Windows.Forms.ToolStripStatusLabel
		Public barraStatus As System.Windows.Forms.StatusStrip
		Public pbImportar As System.Windows.Forms.ProgressBar
		Public memoImportaDir As System.Windows.Forms.TextBox
	End Class
End Namespace
