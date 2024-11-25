package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;

public final class Aba {

    private int codigo;
    private String nome;
    private int ordem;

    public Aba() {
        this.limparDados();
    }

    public Aba(int codigo, String nome, int ordem) {
        this.codigo = codigo;
        this.nome = nome;
        this.ordem = ordem;
    }

    public int getCodigo() {
        return codigo;
    }

    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getOrdem() {
        return ordem;
    }

    public void setOrdem(int ordem) {
        this.ordem = ordem;
    }

    public void limparDados() {
        this.codigo = 0;
        this.nome = "";
        this.ordem = 0;
    }

    public boolean equals(Aba obj) {
        return (obj.getCodigo() == this.getCodigo()
                && obj.getNome().equals(this.getNome())
                && obj.getOrdem() == this.getOrdem());
    }

    @Override
    public String toString() {
        return this.nome;
    }

    public String toString2() {
        return Rotinas.getRecurso("Aba.codigo") + " " + this.codigo + ", "
                + Rotinas.getRecurso("Aba.nome") + " " + this.nome;
    }

}
