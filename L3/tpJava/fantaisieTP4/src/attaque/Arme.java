package attaque;

import java.util.HashSet;

import protagoniste.ZoneDeCombat;

public abstract class Arme extends ForceDeCombat implements Comparable<Arme>{
	private HashSet<ZoneDeCombat> zoneDeCombat;
	public Arme(int pointDeDegat, String nom, ZoneDeCombat... zoneDeCombats){
		super(pointDeDegat, nom);
		for(ZoneDeCombat z : zoneDeCombats) {
			zoneDeCombat.add(z);
		}
	}
	
	public HashSet<ZoneDeCombat> getZoneDeCombat() {
		return zoneDeCombat;
	}
	
	public int compareTo(Arme o) {
		if(o.operationnel && this.operationnel){
			Integer i = Integer.valueOf(o.getPointDeDegat());
			Integer j = Integer.valueOf(this.getPointDeDegat());
			if(i.compareTo(j) == 0) {
				return o.getNom().compareTo(this.getNom());
			}else {
				return i.compareTo(j);
			}
		}else if(o.operationnel && !this.operationnel) {
			return -1;
		}else if(!o.operationnel && this.operationnel){
			return 1;
		}else {
			return o.getNom().compareTo(this.getNom());
		}
	};
}
