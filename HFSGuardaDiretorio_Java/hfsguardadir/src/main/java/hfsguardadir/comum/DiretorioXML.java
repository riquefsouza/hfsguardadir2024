package hfsguardadir.comum;

import hfsguardadir.objetos.Diretorio;

public class DiretorioXML {
    private Diretorio diretorio;

    public DiretorioXML() {
        this.diretorio = new Diretorio();
    }
    
    public Diretorio getDiretorio() {
        return diretorio;
    }

    public void setDiretorio(Diretorio diretorio) {
        this.diretorio = diretorio;
    }    
    
}
