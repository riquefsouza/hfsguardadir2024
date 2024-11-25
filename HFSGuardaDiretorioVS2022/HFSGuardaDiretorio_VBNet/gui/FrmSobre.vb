'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 11/12/2014
' * Time: 10:59
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Drawing
Imports System.Windows.Forms

Namespace gui
	''' <summary>
	''' Description of FrmSobre.
	''' </summary>
	Public Partial Class FrmSobre
		Inherits Form
		Public Sub New()
			'
			' The InitializeComponent() call is required for Windows Forms designer support.
			'

				'
				' TODO: Add constructor code after the InitializeComponent() call.
				'
			InitializeComponent()
		End Sub

		Private Sub BtnOkClick(sender As Object, e As EventArgs)
			Me.Close()
		End Sub
	End Class
End Namespace
