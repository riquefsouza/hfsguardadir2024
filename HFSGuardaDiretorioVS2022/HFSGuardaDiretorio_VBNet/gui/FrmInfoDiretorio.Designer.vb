'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 11:11
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmInfoDiretorio
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
			Dim listViewItem1 As New System.Windows.Forms.ListViewItem("Aba:")
			Dim listViewItem2 As New System.Windows.Forms.ListViewItem("Nome:")
			Dim listViewItem3 As New System.Windows.Forms.ListViewItem("Tamanho:")
			Dim listViewItem4 As New System.Windows.Forms.ListViewItem("Tipo:")
			Dim listViewItem5 As New System.Windows.Forms.ListViewItem("Modificado:")
			Dim listViewItem6 As New System.Windows.Forms.ListViewItem("Atributos:")
			Dim listViewItem7 As New System.Windows.Forms.ListViewItem("Caminho:")
			Me.groupBox1 = New System.Windows.Forms.GroupBox()
			Me.label5 = New System.Windows.Forms.Label()
			Me.label6 = New System.Windows.Forms.Label()
			Me.label3 = New System.Windows.Forms.Label()
			Me.label4 = New System.Windows.Forms.Label()
			Me.label2 = New System.Windows.Forms.Label()
			Me.label1 = New System.Windows.Forms.Label()
			Me.lvInfo = New System.Windows.Forms.ListView()
			Me.columnHeader1 = New System.Windows.Forms.ColumnHeader()
			Me.columnHeader2 = New System.Windows.Forms.ColumnHeader()
			Me.btnOk = New System.Windows.Forms.Button()
			Me.groupBox1.SuspendLayout()
			Me.SuspendLayout()
			' 
			' groupBox1
			' 
			Me.groupBox1.Controls.Add(Me.label5)
			Me.groupBox1.Controls.Add(Me.label6)
			Me.groupBox1.Controls.Add(Me.label3)
			Me.groupBox1.Controls.Add(Me.label4)
			Me.groupBox1.Controls.Add(Me.label2)
			Me.groupBox1.Controls.Add(Me.label1)
			Me.groupBox1.Location = New System.Drawing.Point(12, 12)
			Me.groupBox1.Name = "groupBox1"
			Me.groupBox1.Size = New System.Drawing.Size(340, 96)
			Me.groupBox1.TabIndex = 0
			Me.groupBox1.TabStop = False
			Me.groupBox1.Text = "Legenda dos Atributos"
			' 
			' label5
			' 
			Me.label5.Location = New System.Drawing.Point(166, 62)
			Me.label5.Name = "label5"
			Me.label5.Size = New System.Drawing.Size(168, 23)
			Me.label5.TabIndex = 5
			Me.label5.Text = "[ROL] - Arquivo Somente Leitura"
			Me.label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label6
			' 
			Me.label6.Location = New System.Drawing.Point(6, 62)
			Me.label6.Name = "label6"
			Me.label6.Size = New System.Drawing.Size(154, 23)
			Me.label6.TabIndex = 4
			Me.label6.Text = "[SYS] - Arquivo de Sistema"
			Me.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label3
			' 
			Me.label3.Location = New System.Drawing.Point(166, 39)
			Me.label3.Name = "label3"
			Me.label3.Size = New System.Drawing.Size(168, 23)
			Me.label3.TabIndex = 3
			Me.label3.Text = "[VOL] - Volume ID"
			Me.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label4
			' 
			Me.label4.Location = New System.Drawing.Point(6, 39)
			Me.label4.Name = "label4"
			Me.label4.Size = New System.Drawing.Size(154, 23)
			Me.label4.TabIndex = 2
			Me.label4.Text = "[HID] - Arquivo Oculto"
			Me.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label2
			' 
			Me.label2.Location = New System.Drawing.Point(166, 16)
			Me.label2.Name = "label2"
			Me.label2.Size = New System.Drawing.Size(168, 23)
			Me.label2.TabIndex = 1
			Me.label2.Text = "[DIR] - Diretório"
			Me.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' label1
			' 
			Me.label1.Location = New System.Drawing.Point(6, 16)
			Me.label1.Name = "label1"
			Me.label1.Size = New System.Drawing.Size(154, 23)
			Me.label1.TabIndex = 0
			Me.label1.Text = "[ARQ] - Arquivo comum"
			Me.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft
			' 
			' lvInfo
			' 
			Me.lvInfo.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.columnHeader1, Me.columnHeader2})
			Me.lvInfo.GridLines = True
			Me.lvInfo.Items.AddRange(New System.Windows.Forms.ListViewItem() {listViewItem1, listViewItem2, listViewItem3, listViewItem4, listViewItem5, listViewItem6, _
				listViewItem7})
			Me.lvInfo.Location = New System.Drawing.Point(18, 114)
			Me.lvInfo.MultiSelect = False
			Me.lvInfo.Name = "lvInfo"
			Me.lvInfo.OwnerDraw = True
			Me.lvInfo.Size = New System.Drawing.Size(328, 181)
			Me.lvInfo.TabIndex = 1
			Me.lvInfo.UseCompatibleStateImageBehavior = False
			Me.lvInfo.View = System.Windows.Forms.View.Details
			AddHandler Me.lvInfo.DrawColumnHeader, New System.Windows.Forms.DrawListViewColumnHeaderEventHandler(AddressOf Me.LvInfoDrawColumnHeader)
			AddHandler Me.lvInfo.DrawItem, New System.Windows.Forms.DrawListViewItemEventHandler(AddressOf Me.LvInfoDrawItem)
			AddHandler Me.lvInfo.DrawSubItem, New System.Windows.Forms.DrawListViewSubItemEventHandler(AddressOf Me.LvInfoDrawSubItem)
			' 
			' columnHeader1
			' 
			Me.columnHeader1.Text = "Item"
			Me.columnHeader1.Width = 108
			' 
			' columnHeader2
			' 
			Me.columnHeader2.Text = "Descrição"
			Me.columnHeader2.Width = 214
			' 
			' btnOk
			' 
			Me.btnOk.Location = New System.Drawing.Point(146, 309)
			Me.btnOk.Name = "btnOk"
			Me.btnOk.Size = New System.Drawing.Size(75, 23)
			Me.btnOk.TabIndex = 2
			Me.btnOk.Text = "&Ok"
			Me.btnOk.UseVisualStyleBackColor = True
			AddHandler Me.btnOk.Click, New System.EventHandler(AddressOf Me.BtnOkClick)
			' 
			' FrmInfoDiretorio
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(363, 344)
			Me.Controls.Add(Me.btnOk)
			Me.Controls.Add(Me.lvInfo)
			Me.Controls.Add(Me.groupBox1)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
			Me.MaximizeBox = False
			Me.MinimizeBox = False
			Me.Name = "FrmInfoDiretorio"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
			Me.Text = "Informações do Diretório / Arquivo"
			Me.groupBox1.ResumeLayout(False)
			Me.ResumeLayout(False)
		End Sub
		Private columnHeader2 As System.Windows.Forms.ColumnHeader
		Private columnHeader1 As System.Windows.Forms.ColumnHeader
		Private btnOk As System.Windows.Forms.Button
		Private lvInfo As System.Windows.Forms.ListView
		Private label1 As System.Windows.Forms.Label
		Private label2 As System.Windows.Forms.Label
		Private label4 As System.Windows.Forms.Label
		Private label3 As System.Windows.Forms.Label
		Private label6 As System.Windows.Forms.Label
		Private label5 As System.Windows.Forms.Label
		Private groupBox1 As System.Windows.Forms.GroupBox
	End Class
End Namespace
