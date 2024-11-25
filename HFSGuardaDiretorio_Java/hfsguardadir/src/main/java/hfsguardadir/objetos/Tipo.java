package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;

public class Tipo {

    private char codigo;

    private String nome;

    public Tipo() {
        this.limparDados();
    }

    public Tipo(char codigo, String nome) {
        this.codigo = codigo;
        this.nome = nome;
    }

    public char getCodigo() {
        return codigo;
    }

    public void setCodigo(char codigo) {
        this.codigo = codigo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public final void limparDados() {
        this.codigo = ' ';
        this.nome = "";
    }

    public boolean equals(Tipo obj) {
        return obj.getCodigo() == this.getCodigo()
                && obj.getNome().equals(this.getNome());
    }

    @Override
    public String toString() {
        return Rotinas.getRecurso("Tipo.codigo") + " " + this.codigo + ", "
                + Rotinas.getRecurso("Tipo.nome") + " " + this.nome;
    }

}
