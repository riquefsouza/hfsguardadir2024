package hfsguardadir.gui;

import hfsguardadir.comum.IProgressoLog;
import hfsguardadir.comum.Progresso;

public class FrmImportarDiretorioProgresso implements IProgressoLog {

    FrmImportarDiretorio form;

    public FrmImportarDiretorioProgresso(FrmImportarDiretorio form) {
        this.form = form;
    }

    @Override
    public void ProgressoLog(Progresso progresso) {
        if (progresso.getPosicao() == 0) {
            this.form.pbImportar.setMinimum(progresso.getMinimo());
            this.form.pbImportar.setMaximum(progresso.getMaximo());            
        }
        this.form.pbImportar.setSelection(progresso.getPosicao());
        /*
        if (progresso.getPosicao() > 0) {
            if ((progresso.getPosicao() % 30) == 0) {
                //this.form.pbImportar.update(this.form.pbImportar.getGraphics());
                this.form.update();
            }
        }
        */
        if (!progresso.getLog().isEmpty()) {
            int pos = this.form.memoImportaDir.getLista().getItemCount();
            this.form.memoImportaDir.getLista().add(progresso.getLog());
            this.form.memoImportaDir.getLista().setSelection(pos);
            this.form.barraStatus2.setText(String.valueOf(pos));
            /*
            if ((pos % 30) == 0) {
                //this.form.memoImportaDir.update(this.form.memoImportaDir.getGraphics());
                this.form.update(this.form.getGraphics());
            } 
            */           
        }
    }

}
