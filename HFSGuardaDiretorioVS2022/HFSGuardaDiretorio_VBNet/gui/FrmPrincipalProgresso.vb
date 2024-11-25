'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/07/2015
' * Time: 11:33
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.comum

Namespace gui
	''' <summary>
	''' Description of FrmPrincipalProgresso.
	''' </summary>
	Public Class FrmPrincipalProgresso
		Implements IProgressoLog
		Private form As FrmPrincipal

		Public Sub New(form As FrmPrincipal)
			Me.form = form
		End Sub

		Public Sub ProgressoLog(progresso As Progresso) Implements IProgressoLog.ProgressoLog
			If progresso.Posicao = 0 Then
				Me.form.pb.Minimum = progresso.Minimo
				Me.form.pb.Maximum = progresso.Maximo
				Me.form.pb.[Step] = progresso.Passo
			End If
			Me.form.pb.Value = progresso.Posicao
		End Sub

	End Class
End Namespace
