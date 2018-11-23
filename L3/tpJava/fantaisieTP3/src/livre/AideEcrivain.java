package livre;


import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.NavigableSet;
import java.util.TreeSet;

import attaque.Morsure;
import attaque.Tranchant;
import bataille.Bataille;
import protagoniste.Domaine;
import protagoniste.Heros;
import protagoniste.Homme;
import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class AideEcrivain {
	private Bataille bataille;
	private NavigableSet<Monstre<?>> monstresDomaineSet = new TreeSet<Monstre<?>>(
			new Comparator<Monstre<?>>() {
				public int compare(Monstre<?> m1, Monstre<?> m2) {
					if (m1.getDomaine().equals(m2.getDomaine())){
						return m1.compareTo(m2);
					}
					return m1.getDomaine().compareTo(m2.getDomaine());
				};
			}
	);
	private NavigableSet<Monstre<?>> monstresZoneSet = new TreeSet<Monstre<?>>(
			new Comparator<Monstre<?>>() {
				public int compare(Monstre<?> m1, Monstre<?> m2 ) {
					if (m1.getZoneDeCombat().equals(m2.getZoneDeCombat())) {
						if (m1.getForceDeVie() == m2.getForceDeVie()) {
							return m1.compareTo(m2);
						}
						return m2.getForceDeVie()-m1.getForceDeVie();
					}
					return m1.getZoneDeCombat().compareTo(m2.getZoneDeCombat());
				}
			}
	);
	
	private NavigableSet<Monstre<?>> monstresDeFeu;
	private NavigableSet<Monstre<?>> monstresDeGlace;
	private NavigableSet<Monstre<?>> monstresTranchants;
	
	public AideEcrivain(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public String visualiserForcesHumaines() {
		List<Homme> listeCamp = bataille.getCampHumains().donnercombattants();
		LinkedList<Homme> listeTriee = new LinkedList<>();
		
		int b1 = 0;
		int b2 = 0;
		for(Homme h : listeCamp){
			if(h instanceof Heros) {
				listeTriee.add(b1, h);
				b1 = b1 + 1;
				b2 = b2 + 1;
			}else {
				listeTriee.add(b2, h);
				b2 = b2 + 1;
			}
		}
		
		return listeTriee.toString();
	}
	
	public String ordreNaturelMonstre() {
		StringBuilder x = new StringBuilder();
		int z = 0;
		NavigableSet<Monstre<?>> set = new TreeSet<>();
		List<Monstre<?>> list = bataille.getCampMonstres().donnercombattants();
		
		for(Monstre<?> m : list) {
			set.add(m);
		}
		
		for(Monstre<?> m : set) {
			if (z != 0) {
				x.append(", ");
			}
			z++;
			x.append(m.getNom());
		}
		return x.toString();
	}
	
	public void updateMonstresDomaine() {
		for(Monstre<?> m : bataille.getCampMonstres().donnercombattants()) {
			monstresDomaineSet.add(m);
		}
	}
	
	public void updateMonstresZone() {
		for(Monstre<?> m : bataille.getCampMonstres().donnercombattants()) {
			monstresZoneSet.add(m);
		}
	}
	
	public String ordreMonstreDomaine() {
		StringBuilder x = new StringBuilder();
		updateMonstresDomaine();
		Monstre<Tranchant> m1 = new Monstre<>("!", 10, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		Monstre<Tranchant> m2 = new Monstre<>("~", 10, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		NavigableSet<Monstre<?>> vueMonstre = monstresDomaineSet.subSet(m1, true, m2, true);
		
		x.append("FEU : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(", ");
		}
		x.append("\n");
		m1 = new Monstre<>("!", 10, ZoneDeCombat.aérien, Domaine.glace, new Morsure(10));
		m2 = new Monstre<>("~", 10, ZoneDeCombat.aérien, Domaine.glace, new Morsure(10));
		vueMonstre = monstresDomaineSet.subSet(m1, true, m2, true);
		
		x.append("GLACE : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(", ");
		}
		x.append("\n");
		m1 = new Monstre<>("!", 10, ZoneDeCombat.aérien, Domaine.tranchant, new Morsure(10));
		m2 = new Monstre<>("~", 10, ZoneDeCombat.aérien, Domaine.tranchant, new Morsure(10));
		vueMonstre = monstresDomaineSet.subSet(m1, true, m2, true);
				
		x.append("TRANCHANT : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(", ");
		}

		return x.toString();
	}
	
	public String ordreMonstreZone() {
		StringBuilder x = new StringBuilder();
		updateMonstresZone();
		Monstre<Tranchant> m1 = new Monstre<>("!", 2000, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		Monstre<Tranchant> m2 = new Monstre<>("~", 0, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		NavigableSet<Monstre<?>> vueMonstre = monstresZoneSet.subSet(m1, true, m2, true);
		
		x.append("AERIEN : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(" : ");
			x.append(m.getForceDeVie());
			x.append(", ");
		}
		x.append("\n");
		m1 = new Monstre<>("!", 2000, ZoneDeCombat.aquatique, Domaine.glace, new Morsure(10));
		m2 = new Monstre<>("~", 0, ZoneDeCombat.aquatique, Domaine.glace, new Morsure(10));
		vueMonstre = monstresZoneSet.subSet(m1, true, m2, true);
		
		x.append("AQUATIQUE : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(" : ");
			x.append(m.getForceDeVie());
			x.append(", ");
		}
		x.append("\n");
		m1 = new Monstre<>("!", 2000, ZoneDeCombat.terrestre, Domaine.tranchant, new Morsure(10));
		m2 = new Monstre<>("~", 0, ZoneDeCombat.terrestre, Domaine.tranchant, new Morsure(10));
		vueMonstre = monstresZoneSet.subSet(m1, true, m2, true);
				
		x.append("TERRESTRE : \n");
		for(Monstre<?> m : vueMonstre) {
			x.append(m.getNom());
			x.append(" : ");
			x.append(m.getForceDeVie());
			x.append(", ");
		}

		return x.toString();
	}
	
	public NavigableSet<Monstre<?>> getMonstresDeFeu() {
		initMonstresDeFeu();
		return monstresDeFeu;
	}
	
	public NavigableSet<Monstre<?>> getMonstresDeGlace() {
		initMonstresDeGlace();
		return monstresDeGlace;
	}
	
	public NavigableSet<Monstre<?>> getMonstresTranchants() {
		initMonstresTranchant();
		return monstresTranchants;
	}
	
//	public Monstre<?> firstMonstreDomaine(Domaine d){
//		this.updateMonstresDomaine();
//		for(Monstre<?> m : monstresDomaineSet) {
//			if(d == m.getDomaine()) {
//				return m;
//			}
//		}
//		return null;
//	}
//	
//	public void initMonstresDeFeu() {
//		this.updateMonstresDomaine();
//		Monstre<?> m1 = firstMonstreDomaine(Domaine.glace);
//		Monstre<?> m2 = monstresDomaineSet.first();
//		monstresDeFeu = monstresDomaineSet.subSet(m2, true, m1, false);
//	}
	
	public void initMonstresDeFeu() {
		Monstre<Tranchant> m1 = new Monstre<>("!", 2000, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		Monstre<Tranchant> m2 = new Monstre<>("~", 0, ZoneDeCombat.aérien, Domaine.feu, new Morsure(10));
		monstresDeFeu = monstresDomaineSet.subSet(m1, true, m2, false);
	}
	
	public void initMonstresDeGlace() {
		Monstre<Tranchant> m1 = new Monstre<>("!", 2000, ZoneDeCombat.aérien, Domaine.glace, new Morsure(10));
		Monstre<Tranchant> m2 = new Monstre<>("~", 0, ZoneDeCombat.aérien, Domaine.glace, new Morsure(10));
		monstresDeGlace = monstresDomaineSet.subSet(m1, true, m2, false);
	}
	
	public void initMonstresTranchant() {
		Monstre<Tranchant> m1 = new Monstre<>("!", 2000, ZoneDeCombat.aérien, Domaine.tranchant, new Morsure(10));
		Monstre<Tranchant> m2 = new Monstre<>("~", 0, ZoneDeCombat.aérien, Domaine.tranchant, new Morsure(10));
		monstresTranchants = monstresDomaineSet.subSet(m1, true, m2, false);
	}
}
