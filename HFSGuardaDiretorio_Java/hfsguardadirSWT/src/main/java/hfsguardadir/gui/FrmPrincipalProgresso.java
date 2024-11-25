package hfsguardadir.gui;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;

public class FrmPrincipalProgresso implements IProgressoLog {

    FrmPrincipal form;

    public FrmPrincipalProgresso(FrmPrincipal form) {
        this.form = form;
    }

    @Override
    public void ProgressoLog(Progresso progresso) {
        if (progresso.getPosicao() == 0) {
            this.form.pb.setMinimum(progresso.getMinimo());
            this.form.pb.setMaximum(progresso.getMaximo());
        }
        this.form.pb.setSelection(progresso.getPosicao());
        //this.form.pb.update();
    }

}
