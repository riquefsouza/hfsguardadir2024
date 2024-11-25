'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/07/2015
' * Time: 11:26
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports HFSGuardaDiretorio.comum

Namespace gui
	''' <summary>
	''' Description of FrmImportarDiretorioProgresso.
	''' </summary>
	Public Class FrmImportarDiretorioProgresso
		Implements IProgressoLog
		Private form As FrmImportarDiretorio

		Public Sub New(form As FrmImportarDiretorio)
			Me.form = form
		End Sub

		Public Sub ProgressoLog(progresso As Progresso) Implements IProgressoLog.ProgressoLog
			If progresso.Posicao = 0 Then
				Me.form.pbImportar.Minimum = progresso.Minimo
				Me.form.pbImportar.Maximum = progresso.Maximo
				Me.form.pbImportar.[Step] = progresso.Passo
			End If
			Me.form.pbImportar.Value = progresso.Posicao

			If progresso.Log.Length > 0 Then
				Dim pos As Integer = form.memoImportaDir.TextLength
				form.memoImportaDir.AppendText(progresso.Log & vbLf)
				form.memoImportaDir.[Select](pos, pos)
				form.barraStatus.Items(1).Text = Convert.ToString(pos)
				form.barraStatus.Update()
			End If

		End Sub

	End Class
End Namespace
