package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;
import java.util.Date;

public class Arquivo {

    private String nome;
    private long tamanho;
    private Date modificado;
    private String atributos;

    public Arquivo() {
        super();
    }

    public Arquivo(String nome, long tamanho, Date modificado, String atributos) {
        this.nome = nome;
        this.tamanho = tamanho;
        this.modificado = modificado;
        this.atributos = atributos;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public long getTamanho() {
        return tamanho;
    }

    public void setTamanho(long tamanho) {
        this.tamanho = tamanho;
    }

    public Date getModificado() {
        return modificado;
    }

    public void setModificado(Date modificado) {
        this.modificado = modificado;
    }

    public String getAtributos() {
        return atributos;
    }

    public void setAtributos(String atributos) {
        this.atributos = atributos;
    }

    public void limparDados() {
        this.nome = "";
        this.tamanho = 0;
        this.modificado = new Date();
        this.atributos = "";
    }

    public boolean equals(Arquivo obj) {
        return (obj.getNome().equals(this.getNome())
                && obj.getTamanho() == this.getTamanho()
                && obj.getModificado() == this.getModificado()
                && obj.getAtributos().equals(this.getAtributos()));
    }

    @Override
    public String toString() {
        return this.nome;
    }

    public String toString2() {
        return Rotinas.getRecurso("Arquivo.nome") + " " + this.nome + ", "
                + Rotinas.getRecurso("Arquivo.tamanho") + " " + this.tamanho + ", "
                + Rotinas.getRecurso("Arquivo.tamanho") + " " + this.modificado + ", "
                + Rotinas.getRecurso("Arquivo.tamanho") + " " + this.atributos;
    }
}
