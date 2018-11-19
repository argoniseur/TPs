package attaque;

public abstract class ForceDeCombat {
	private int pointDeDegat;
	private String nom;
	protected boolean operationnel;
	
	public ForceDeCombat(int pointDeDegat, String nom) {
		this.pointDeDegat = pointDeDegat;
		this.nom = nom;
	}
	
	public int getPointDeDegat() {
		return pointDeDegat;
	}
	
	public String getNom() {
		return nom;
	}
	
	public boolean isOperationnel() {
		return operationnel;
	}
	
	@Override
	public String toString() {
		return getNom() + ": Dégats = " + getPointDeDegat();
	}
}
