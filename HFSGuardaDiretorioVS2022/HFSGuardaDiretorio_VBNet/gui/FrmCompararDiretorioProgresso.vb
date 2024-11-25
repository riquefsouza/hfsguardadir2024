'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/07/2015
' * Time: 11:24
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.comum

Namespace gui
	''' <summary>
	''' Description of FrmCompararDiretorioProgresso.
	''' </summary>
	Public Class FrmCompararDiretorioProgresso
		Implements IProgressoLog
		Private form As FrmCompararDiretorio

		Public Sub New(form As FrmCompararDiretorio)
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
