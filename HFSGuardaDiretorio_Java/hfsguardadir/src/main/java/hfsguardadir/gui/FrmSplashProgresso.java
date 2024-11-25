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
            this.form.update(this.form.getGraphics());
        }
        this.form.pb.setValue(progresso.getPosicao());
        this.form.pb.update(this.form.pb.getGraphics());
        /*
        try {
                Thread.sleep(25);
            } catch (InterruptedException e) {}
        */
    }

}
