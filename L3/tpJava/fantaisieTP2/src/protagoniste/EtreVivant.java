package protagoniste;

import bataille.Bataille;

public abstract class EtreVivant {
	protected String nom;
	protected int forceDeVie;
	protected Bataille bataille;
	
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
	
	public void rejointBataille(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public void mourir() {
		
	}
	
	@Override
	public boolean equals(Object arg0) {
		if(arg0 instanceof EtreVivant) {
			EtreVivant x = (EtreVivant)arg0;
			return x.getNom() == this.nom;
		}

		return false;
	}
	
}
