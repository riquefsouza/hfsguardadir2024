'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 10:59
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmSobre
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
			Me.label1 = New System.Windows.Forms.Label()
			Me.label2 = New System.Windows.Forms.Label()
			Me.label3 = New System.Windows.Forms.Label()
			Me.label4 = New System.Windows.Forms.Label()
			Me.btnOk = New System.Windows.Forms.Button()
			Me.SuspendLayout
			'
			'label1
			'
			Me.label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 8.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0,Byte))
			Me.label1.Location = New System.Drawing.Point(12, 9)
			Me.label1.Name = "label1"
			Me.label1.Size = New System.Drawing.Size(268, 21)
			Me.label1.TabIndex = 0
			Me.label1.Text = "HFSGuardaDir 2.0 - Catalogador de Diretórios"
			Me.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
			'
			'label2
			'
			Me.label2.Location = New System.Drawing.Point(12, 30)
			Me.label2.Name = "label2"
			Me.label2.Size = New System.Drawing.Size(268, 18)
			Me.label2.TabIndex = 1
			Me.label2.Text = "Desenvolvido em VB.Net, Versão: 2.0"
			Me.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
			'
			'label3
			'
			Me.label3.Location = New System.Drawing.Point(12, 48)
			Me.label3.Name = "label3"
			Me.label3.Size = New System.Drawing.Size(268, 18)
			Me.label3.TabIndex = 2
			Me.label3.Text = "Por Henrique Figueiredo de Souza"
			Me.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
			'
			'label4
			'
			Me.label4.Location = New System.Drawing.Point(12, 66)
			Me.label4.Name = "label4"
			Me.label4.Size = New System.Drawing.Size(268, 18)
			Me.label4.TabIndex = 3
			Me.label4.Text = "Todos os direitos reservados, 2024"
			Me.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
			'
			'btnOk
			'
			Me.btnOk.Location = New System.Drawing.Point(108, 96)
			Me.btnOk.Name = "btnOk"
			Me.btnOk.Size = New System.Drawing.Size(75, 23)
			Me.btnOk.TabIndex = 4
			Me.btnOk.Text = "&Ok"
			Me.btnOk.UseVisualStyleBackColor = true
			AddHandler Me.btnOk.Click, AddressOf Me.BtnOkClick
			'
			'FrmSobre
			'
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6!, 13!)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(292, 125)
			Me.Controls.Add(Me.btnOk)
			Me.Controls.Add(Me.label4)
			Me.Controls.Add(Me.label3)
			Me.Controls.Add(Me.label2)
			Me.Controls.Add(Me.label1)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
			Me.MaximizeBox = false
			Me.MinimizeBox = false
			Me.Name = "FrmSobre"
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "Sobre o Catalogador"
			Me.ResumeLayout(false)
		End Sub
		Private btnOk As System.Windows.Forms.Button
		Private label4 As System.Windows.Forms.Label
		Private label3 As System.Windows.Forms.Label
		Private label2 As System.Windows.Forms.Label
		Private label1 As System.Windows.Forms.Label
	End Class
End Namespace
