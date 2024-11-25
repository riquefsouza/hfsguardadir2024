'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 07/07/2015
' * Time: 13:47
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.comum

Namespace gui
	''' <summary>
	''' Description of FrmSplashProgresso.
	''' </summary>
	Public Class FrmSplashProgresso
		Implements IProgressoLog

		Private form As FrmSplash

		Public Sub New(form As FrmSplash)
			Me.form = form
		End Sub

		Public Sub ProgressoLog(progresso As Progresso) Implements IProgressoLog.ProgressoLog
			If progresso.Posicao = 0 Then
				Me.form.pb.Minimum = progresso.Minimo
				Me.form.pb.Maximum = progresso.Maximo
				Me.form.pb.[Step] = progresso.Passo
			End If
			Me.form.pb.Value = progresso.Posicao
			Me.form.pb.Update()
		End Sub
	End Class
End Namespace
