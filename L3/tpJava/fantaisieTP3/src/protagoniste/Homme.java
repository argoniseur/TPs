package protagoniste;

import bataille.Bataille;

public class Homme extends EtreVivant{
	public Homme(String nom) {
		super(nom, 70);
	}

	public void rejointBataille(Bataille bataille) {
		super.rejointBataille(bataille);
		this.bataille.ajouter(this);
	}
	
	public void mourir() {
		this.bataille.eliminer(this);
	}
	
	@Override
	public String toString() {
		return "Homme: " + this.nom + " ayant " + this.forceDeVie + " points de vie";
	}
}
