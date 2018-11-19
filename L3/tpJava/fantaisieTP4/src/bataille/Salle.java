package bataille;

import protagoniste.ZoneDeCombat;

public class Salle {
	private int numSalle;
	private ZoneDeCombat zoneDeCombat;
	
	public Salle(int numSalle, ZoneDeCombat zoneDeCombat) {
		this.numSalle = numSalle;
		this.zoneDeCombat = zoneDeCombat;
	}
	
	public int getNumSalle() {
		return numSalle;
	}
	
	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}
	
	@Override
	public String toString() {
		return "Salle n°" + getNumSalle() + " de type combat " + getZoneDeCombat(); 
	}
	
	@Override
	public boolean equals(Object arg0) {
		if(arg0 instanceof Salle) {
			Salle x = (Salle)arg0;
			return x.getNumSalle() == this.numSalle;
		}
		return false;
	}
	
	@Override
	public int hashCode() {
		int hash = 1;
		hash = hash * 11 + numSalle;
		return hash;
	}
}
