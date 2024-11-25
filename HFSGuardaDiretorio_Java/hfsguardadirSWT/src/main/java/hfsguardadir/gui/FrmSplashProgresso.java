package hfsguardadir.gui;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;

public class FrmSplashProgresso implements IProgressoLog {

    FrmSplash form;

    public FrmSplashProgresso(FrmSplash form) {
        this.form = form;
    }

    @Override
    public void ProgressoLog(Progresso progresso) {
        if (progresso.getPosicao() == 0) {
            this.form.pb.setMinimum(progresso.getMinimo());
            this.form.pb.setMaximum(progresso.getMaximo());
            //this.form.update();
        }
/*
        try {
			Thread.sleep(5);
		} catch (InterruptedException e) {

			e.printStackTrace();
		}
*/
        this.form.pb.setSelection(progresso.getPosicao());
        //this.form.pb.update();
    }

}
