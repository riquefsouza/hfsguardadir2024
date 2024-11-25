'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 07/07/2015
' * Time: 14:01
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Drawing
Imports System.Windows.Forms

Namespace objetosgui
	''' <summary>
	''' Description of Dialogo.
	''' </summary>
	Public Class Dialogo
		Public Sub New()
		End Sub

		Public Shared Sub mensagemErro(texto As [String])
			MessageBox.Show(texto, "Erro", MessageBoxButtons.OK, MessageBoxIcon.[Error])
		End Sub

		Public Shared Sub mensagemInfo(texto As [String])
			MessageBox.Show(texto, "Informação", MessageBoxButtons.OK, MessageBoxIcon.Information)
		End Sub

		Public Shared Function confirma(texto As [String]) As Boolean
			Dim res As DialogResult = MessageBox.Show(texto, "Confirma", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
			Return (res = DialogResult.Yes)
		End Function

		Public Shared Function entrada(texto As [String], valorInicial As [String]) As [String]
			Dim form As New Form()
			Dim label As New Label()
			Dim textBox As New TextBox()
			Dim buttonOk As New Button()
			Dim buttonCancel As New Button()

			form.Text = "Informa"
			label.Text = texto
			textBox.Text = valorInicial
			textBox.MaxLength = 10

			buttonOk.Text = "OK"
			buttonCancel.Text = "Cancel"
			buttonOk.DialogResult = DialogResult.OK
			buttonCancel.DialogResult = DialogResult.Cancel

			label.SetBounds(9, 20, 372, 13)
			textBox.SetBounds(12, 36, 372, 20)
			buttonOk.SetBounds(228, 72, 75, 23)
			buttonCancel.SetBounds(309, 72, 75, 23)

			label.AutoSize = True
			textBox.Anchor = textBox.Anchor Or AnchorStyles.Right
			buttonOk.Anchor = AnchorStyles.Bottom Or AnchorStyles.Right
			buttonCancel.Anchor = AnchorStyles.Bottom Or AnchorStyles.Right

			form.ClientSize = New Size(396, 107)
			form.Controls.AddRange(New Control() {label, textBox, buttonOk, buttonCancel})
			form.ClientSize = New Size(Math.Max(300, label.Right + 10), form.ClientSize.Height)
			form.FormBorderStyle = FormBorderStyle.FixedDialog
			form.StartPosition = FormStartPosition.CenterScreen
			form.MinimizeBox = False
			form.MaximizeBox = False
			form.AcceptButton = buttonOk
			form.CancelButton = buttonCancel

			Dim res As DialogResult = form.ShowDialog()

			If res = DialogResult.OK Then
				Return textBox.Text
			Else
				Return ""
			End If
		End Function

		Public Shared Function entrada(texto As [String]) As [String]
			Return entrada(texto, "")
		End Function

	End Class
End Namespace
