package hfsguardadir.objetos;

import hfsguardadir.comum.Rotinas;

public class ConexaoParams {
	private String nome;

	private String driver;

	private String url;

	private String login;

	private String senha;

	public ConexaoParams() {
		this.nome = "SQLITE";
		this.driver = "org.sqlite.JDBC";
		this.url = "jdbc:sqlite:GuardaDir.db";
		this.login = "";
		this.senha = "";
	}

	public String getDriver() {
		return driver;
	}

	public void setDriver(String driver) {
		this.driver = driver;
	}

	public String getLogin() {
		return login;
	}

	public void setLogin(String login) {
		this.login = login;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public String getSenha() {
		return senha;
	}

	public void setSenha(String senha) {
		this.senha = senha;
	}

	public String getUrl() {
		return url;
	}

	public void setUrl(String url) {
		this.url = url;
	}
	
	public String toString() {
		return this.nome;
	}

	public String toString2() {
		return Rotinas.getRecurso("ConexaoParams.nome") + " " + nome + ", "
				+ Rotinas.getRecurso("ConexaoParams.driver") + " " + driver
				+ ", " + Rotinas.getRecurso("ConexaoParams.url") + " " + url
				+ ", " + Rotinas.getRecurso("ConexaoParams.login") + " "
				+ login + ", " + Rotinas.getRecurso("ConexaoParams.senha")
				+ " " + senha;
	}
}
