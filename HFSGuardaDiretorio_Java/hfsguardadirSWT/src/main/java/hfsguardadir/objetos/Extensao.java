package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;
import java.util.Arrays;

public final class Extensao {

    private int codigo;
    private String nome;
    private int ordem;
    private byte[] bmp16;
    private byte[] bmp32;
    private byte[] gif16;
    private byte[] gif32;

    public Extensao() {
        this.limparDados();
    }

    public Extensao(int codigo, String nome, int ordem,
            byte[] bmp16, byte[] bmp32) {
        this.codigo = codigo;
        this.nome = nome;
        this.ordem = ordem;
        this.bmp16 = bmp16;
        this.bmp32 = bmp32;
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

    public byte[] getBmp16() {
        return bmp16;
    }

    public void setBmp16(byte[] bmp16) {
        this.bmp16 = bmp16;
    }

    public byte[] getBmp32() {
        return bmp32;
    }

    public void setBmp32(byte[] bmp32) {
        this.bmp32 = bmp32;
    }

    /**
     * @return the gif16
     */
    public byte[] getGif16() {
        return gif16;
    }

    /**
     * @param gif16 the gif16 to set
     */
    public void setGif16(byte[] gif16) {
        this.gif16 = gif16;
    }

    /**
     * @return the gif32
     */
    public byte[] getGif32() {
        return gif32;
    }

    /**
     * @param gif32 the gif32 to set
     */
    public void setGif32(byte[] gif32) {
        this.gif32 = gif32;
    }

    public void limparDados() {
        this.codigo = 0;
        this.nome = "";
        this.ordem = 0;
        this.bmp16 = null;
        this.bmp32 = null;
    }

    public boolean equals(Extensao obj) {
        return (obj.getCodigo() == this.getCodigo()
                && obj.getNome().equals(this.getNome())
                && obj.getOrdem() == this.getOrdem());
    }

    @Override
    public String toString() {
        return Rotinas.getRecurso("Extensao.codigo") + " " + this.codigo + ", "
                + Rotinas.getRecurso("Extensao.nome") + " " + this.nome + ", "
                + Rotinas.getRecurso("Extensao.bmp16") + " "
                + Arrays.toString(this.bmp16) + ", "
                + Rotinas.getRecurso("Extensao.bmp32") + " "
                + Arrays.toString(this.bmp32);
    }
    
}
