'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 10:52
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace gui
	Partial Class FrmSplash
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
			Me.pb = New System.Windows.Forms.ProgressBar()
			Me.SuspendLayout()
			' 
			' label1
			' 
			Me.label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CByte(0))
			Me.label1.Location = New System.Drawing.Point(21, 9)
			Me.label1.Name = "label1"
			Me.label1.Size = New System.Drawing.Size(332, 34)
			Me.label1.TabIndex = 0
			Me.label1.Text = "HFSGuardaDiretorio 2.0"
			' 
			' label2
			' 
			Me.label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CByte(0))
			Me.label2.Location = New System.Drawing.Point(47, 53)
			Me.label2.Name = "label2"
			Me.label2.Size = New System.Drawing.Size(267, 29)
			Me.label2.TabIndex = 1
			Me.label2.Text = "Catalogador de Diretórios"
			' 
			' pb
			' 
			Me.pb.Dock = System.Windows.Forms.DockStyle.Bottom
			Me.pb.Location = New System.Drawing.Point(0, 96)
			Me.pb.Name = "pb"
			Me.pb.Size = New System.Drawing.Size(375, 17)
			Me.pb.[Step] = 1
			Me.pb.TabIndex = 2
			' 
			' FrmSplash
			' 
			Me.AutoScaleDimensions = New System.Drawing.SizeF(6F, 13F)
			Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
			Me.ClientSize = New System.Drawing.Size(375, 113)
			Me.ControlBox = False
			Me.Controls.Add(Me.pb)
			Me.Controls.Add(Me.label2)
			Me.Controls.Add(Me.label1)
			Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None
			Me.MaximizeBox = False
			Me.MinimizeBox = False
			Me.Name = "FrmSplash"
			Me.ShowIcon = False
			Me.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide
			Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
			Me.Text = "FrmSplash"
			Me.ResumeLayout(False)
		End Sub
		Public pb As System.Windows.Forms.ProgressBar
		Private label2 As System.Windows.Forms.Label
		Private label1 As System.Windows.Forms.Label
	End Class
End Namespace
