package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;

public class Diretorio extends Arquivo {

    private Aba aba;
    private int codigo;
    private int ordem;
    private int codDirPai;
    private Tipo tipo;
    private String caminho;
    private String nomePai;
    private String caminhoPai;
    private String tamanhoFormatado;
    private String modificadoFormatado;
    private String caminhoOriginal;

    public Diretorio() {
        this.aba = new Aba();
        this.tipo = new Tipo();
        this.limparDados();
    }

    /**
     * @return the aba
     */
    public Aba getAba() {
        return aba;
    }

    /**
     * @param aba the aba to set
     */
    public void setAba(Aba aba) {
        this.aba = aba;
    }

    /**
     * @return the codigo
     */
    public int getCodigo() {
        return codigo;
    }

    /**
     * @param codigo the codigo to set
     */
    public void setCodigo(int codigo) {
        this.codigo = codigo;
    }

    /**
     * @return the ordem
     */
    public int getOrdem() {
        return ordem;
    }

    /**
     * @param ordem the ordem to set
     */
    public void setOrdem(int ordem) {
        this.ordem = ordem;
    }

    /**
     * @return the codDirPai
     */
    public int getCodDirPai() {
        return codDirPai;
    }

    /**
     * @param codDirPai the codDirPai to set
     */
    public void setCodDirPai(int codDirPai) {
        this.codDirPai = codDirPai;
    }

    /**
     * @return the tipo
     */
    public Tipo getTipo() {
        return tipo;
    }

    /**
     * @param tipo the tipo to set
     */
    public void setTipo(Tipo tipo) {
        this.tipo = tipo;
    }

    /**
     * @return the caminho
     */
    public String getCaminho() {
        return caminho;
    }

    /**
     * @param caminho the caminho to set
     */
    public void setCaminho(String caminho) {
        this.caminho = caminho;
    }

    /**
     * @return the nomePai
     */
    public String getNomePai() {
        return nomePai;
    }

    /**
     * @param nomePai the nomePai to set
     */
    public void setNomePai(String nomePai) {
        this.nomePai = nomePai;
    }

    /**
     * @return the caminhoPai
     */
    public String getCaminhoPai() {
        return caminhoPai;
    }

    /**
     * @param caminhoPai the caminhoPai to set
     */
    public void setCaminhoPai(String caminhoPai) {
        this.caminhoPai = caminhoPai;
    }

    /**
     * @return the tamanhoFormatado
     */
    public String getTamanhoFormatado() {
        return tamanhoFormatado;
    }

    /**
     * @param tamanhoFormatado the tamanhoFormatado to set
     */
    public void setTamanhoFormatado(String tamanhoFormatado) {
        this.tamanhoFormatado = tamanhoFormatado;
    }

    /**
     * @return the modificadoFormatado
     */
    public String getModificadoFormatado() {
        return modificadoFormatado;
    }

    /**
     * @param modificadoFormatado the modificadoFormatado to set
     */
    public void setModificadoFormatado(String modificadoFormatado) {
        this.modificadoFormatado = modificadoFormatado;
    }

    /**
     * @return the caminhoOriginal
     */
    public String getCaminhoOriginal() {
        return caminhoOriginal;
    }

    /**
     * @param caminhoOriginal the caminhoOriginal to set
     */
    public void setCaminhoOriginal(String caminhoOriginal) {
        this.caminhoOriginal = caminhoOriginal;
    }

    @Override
    public void limparDados() {
        super.limparDados();
        this.aba.limparDados();
        this.codigo = 0;
        this.ordem = 0;
        this.codDirPai = 0;
        this.tipo.limparDados();
        this.caminho = "";
        this.nomePai = "";
        this.caminhoPai = "";
        this.tamanhoFormatado = "";
        this.modificadoFormatado = "";
        this.caminhoOriginal = "";
    }

    public boolean equals(Diretorio obj) {
        return (obj.getAba().equals(this.getAba())
                && obj.getCodigo() == this.getCodigo()
                && obj.getOrdem() == this.getOrdem()
                && obj.getCodDirPai() == this.getCodDirPai()
                && obj.getNome().equals(this.getNome())
                && obj.getTamanho() == this.getTamanho()
                && obj.getModificado().equals(this.getModificado())
                && obj.getAtributos().equals(this.getAtributos())
                && obj.getTipo().equals(this.getTipo())
                && obj.getCaminho().equals(this.getCaminho())
                && obj.getNomePai().equals(this.getNomePai())
                && obj.getCaminhoPai().equals(this.getCaminhoPai())
                && obj.getTamanhoFormatado().equals(this.getTamanhoFormatado())
                && obj.getModificadoFormatado().equals(this.getModificadoFormatado())
                && obj.getCaminhoOriginal().equals(this.getCaminhoOriginal()));
    }

    @Override
    public String toString() {
        return Rotinas.getRecurso("Diretorio.aba") + " [" + this.aba + "], "
                + Rotinas.getRecurso("Diretorio.codigo") + " " + this.codigo + ", "
                + Rotinas.getRecurso("Diretorio.ordem") + " " + this.ordem + ", "
                + Rotinas.getRecurso("Diretorio.codDirPai") + " " + this.codDirPai + ", "
                + Rotinas.getRecurso("Diretorio.nome") + " " + this.getNome() + ", "
                + Rotinas.getRecurso("Diretorio.tamanho") + " " + this.tamanhoFormatado + ", "
                + Rotinas.getRecurso("Diretorio.modificado") + " " + this.modificadoFormatado + ", "
                + Rotinas.getRecurso("Diretorio.atributos") + " " + this.getAtributos() + ", "
                + Rotinas.getRecurso("Diretorio.tipo") + " [" + this.tipo + "], "
                + Rotinas.getRecurso("Diretorio.caminho") + " " + this.caminho;
    }
}
