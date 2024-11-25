'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 10/12/2014
' * Time: 17:39
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.Windows.Forms
Imports HFSGuardaDiretorio.gui
Imports HFSGuardaDiretorio.catalogador

''' <summary>
''' Class with program entry point.
''' </summary>
Friend NotInheritable Class Program
	''' <summary>
	''' Program entry point.
	''' </summary>
	<STAThread> _
	Friend Shared Sub Main(args As String())
		HFSGuardaDiretorio.catalogador.Catalogador.iniciarSistema()
		'Rotinas.iniciarLogArquivo(log);

		Application.EnableVisualStyles()
		Application.SetCompatibleTextRenderingDefault(False)
		Application.Run(New FrmPrincipal())
	End Sub
End Class
