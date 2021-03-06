package protagoniste;

import java.util.Comparator;
import java.util.EnumMap;
import java.util.LinkedList;
import java.util.List;
import java.util.NavigableSet;
import java.util.TreeSet;

import attaque.Arc;
import attaque.Arme;
import attaque.LancePierre;
import bataille.Bataille;

public class Homme extends EtreVivant{
	private EnumMap<ZoneDeCombat, List<Arme>> armes;
	private Arme armeChoisie;
	
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
	
	public void ajouterArmes(Arme... arme) {
		for(Arme a : arme) {
			for(ZoneDeCombat z : a.getZoneDeCombat()) {
				if(armes.containsKey(z)) {
					armes.get(z).add(a);
				}else {
					List<Arme> x = new LinkedList<Arme>();
					x.add(a);
					armes.put(z, x);
				}
			}
		}
	}
	
	public void supprimerArme(Arme a) {
		for(ZoneDeCombat z : a.getZoneDeCombat()) {
			for (Arme arme : armes.get(z)) {
				if (arme.equals(a)) {
					armes.get(z).remove(a);
				}
			}
		}
	}
	
	public Arme getArmeChoisie() {
		return armeChoisie;
	}
	
	public Arme choisirArme(Monstre<?> m) {
		ZoneDeCombat z = m.getZoneDeCombat();
		List<Arme> listArme = armes.get(z);
		NavigableSet<Arme> armesTriees = new TreeSet<Arme>(
				new Comparator<Arme>() {
					public int compare(Arme o, Arme a ) {
						return o.compareTo(a);
					}
				}
		);
		
		for(Arme a : listArme) {
			armesTriees.add(a);
		}
		Arme a1 = new Arc(1);
		Arme a2 = new LancePierre();
		NavigableSet<Arme> armesAdaptees = armesTriees.subSet(a1, true, a2, true);
		
		
	}
	
}