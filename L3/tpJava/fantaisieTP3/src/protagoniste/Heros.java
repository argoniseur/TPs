package protagoniste;

public class Heros extends Homme{
	public Heros(String nom) {
		super(nom);
		forceDeVie = 100;
	}
	
	@Override
	public String toString() {
		return "Heros " + this.nom + " ayant " + this.forceDeVie + " points de vie";
	}
}
