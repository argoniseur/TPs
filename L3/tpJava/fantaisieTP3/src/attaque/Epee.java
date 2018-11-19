package attaque;

public class Epee extends Arme{	
	@SuppressWarnings("unused")
	private String nom;
	
	public Epee(String nomEpee) {
		super(80, nomEpee);
		this.nom = nomEpee;	
	}
}
