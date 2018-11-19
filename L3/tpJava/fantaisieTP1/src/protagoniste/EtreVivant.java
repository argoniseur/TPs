package protagoniste;

public abstract class EtreVivant {
	private String nom;
	private int forceDeVie;
	
	public EtreVivant(String nom, int forceDeVie) {
		this.nom = nom;
		this.forceDeVie = forceDeVie;
	}
	
	public int getForceDeVie() {
		return forceDeVie;
	}
	
	public String getNom() {
		return nom;
	}
	
	@Override
	public String toString() {
		return getNom() + " ayant " + getForceDeVie();
	}
}
