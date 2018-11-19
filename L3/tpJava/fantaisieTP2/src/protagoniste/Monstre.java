package protagoniste;
import java.util.Iterator;

import attaque.Pouvoir;
import bataille.Bataille;
import protagoniste.ZoneDeCombat;
import java.util.Random;

public class Monstre<P extends Pouvoir> extends EtreVivant implements Iterable<P>{
	private ZoneDeCombat zoneDeCombat;
	private Domaine domaine;
	@SuppressWarnings("unused")
	private P[] attaques;
	private Iterator<P> gestionAttaque;
	
	@SafeVarargs
	public Monstre(String nom, int forceDeVie, ZoneDeCombat zoneDeCombat, Domaine domaine, P... attaques){
		super(nom, forceDeVie);
		this.zoneDeCombat = zoneDeCombat;
		this.domaine = domaine;
		this.attaques = attaques;
		this.gestionAttaque = iterator();
	}
	
	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}
	
	public Domaine getDomaine() {
		return domaine;
	}
	
	@Override
	public String toString() {
		return getNom() + " de type " + getZoneDeCombat() + " avec un pouvoir " + getDomaine();
	}
	
	public void entreEnCombat(){
		for(P x: attaques) {
			x.regenererPouvoir();
		}
		gestionAttaque = iterator();
	}
	
	public P attaque() {
		if (gestionAttaque.hasNext()) {
			return gestionAttaque.next();
		}else 
			return null;
	}
	
	public Iterator<P> iterator(){
		return new GestionAttaque();
	}
	
	public void rejointBataille(Bataille bataille) {
		super.rejointBataille(bataille);
		this.bataille.ajouter(this);
	}
	
	public void mourir() {
		this.bataille.eliminer(this);
	}
	
	/* ***************************** CLASSE INTERNE *************************************** */
	private class GestionAttaque implements Iterator<P>{
		private P[] attaquesPossibles;
		private int nbAttaquesPossibles;
		
		public GestionAttaque() {
			this.attaquesPossibles = attaques;
			this.nbAttaquesPossibles = attaques.length;
		}
		
		@Override
		public boolean hasNext() {
			for(int i = 0; i<nbAttaquesPossibles; i++) {
				if (!attaquesPossibles[i].isOperationnel()) {
					attaquesPossibles[i] = attaquesPossibles[nbAttaquesPossibles-1];
					nbAttaquesPossibles = nbAttaquesPossibles - 1;
				}
			}
			if (nbAttaquesPossibles == 0)
				return false;
			else
				return true;
		}
		
		@Override
		public P next() {
			Random rand = new Random();
			int x = rand.nextInt(nbAttaquesPossibles);			
			return attaquesPossibles[x];
		}
	}
}