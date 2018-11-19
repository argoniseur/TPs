package bataille;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Set;

import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class Grotte{
	private LinkedHashMap<Salle, List<Salle>> planGrotte = new LinkedHashMap<Salle, List<Salle>>();
	private HashMap<Salle, Bataille> batailles = new HashMap<Salle, Bataille>();
	private HashSet<Salle> sallesExplorees = new HashSet<Salle>();
	private Integer numeroSalleDecisive;
	
	public void ajouterSalle(ZoneDeCombat zoneDeCombat, Monstre<?>... monstres) {
		Salle s = new Salle(planGrotte.size()+1, zoneDeCombat);
		Bataille b = new Bataille();
		for(Monstre<?> m : monstres) {
			b.ajouter(m);
		}
		planGrotte.put(s, new ArrayList<Salle>());
		batailles.put(s, b);
	}
	
	public String afficherPlanGrotte() {
		  StringBuilder affichage = new StringBuilder();
		  
		  for (Map.Entry<Salle, List<Salle>> entry : planGrotte.entrySet()) {
			  Salle salle = entry.getKey();
			  List<Salle> acces = planGrotte.get(salle);
			  affichage.append("La " + salle + ".\nelle possede " + acces.size() + " acces : ");
			  for (Salle access : acces) {
				  affichage.append(" vers la salle " + access);
			  }
			  
			  Bataille bataille = batailles.get(salle);
			  Camp<Monstre<?>> camp = bataille.getCampMonstres();
			  Monstre<?> monstre = camp.selectionner();
			  if (camp.nbCombattants() > 1) {
				  affichage.append("\n" + camp.nbCombattants() + " monstres de type ");
			  }else{
				  affichage.append("\nUn monstre de type ");
			  }
			  
			  affichage.append(monstre.getNom() + " la protege.\n");
			  System.out.println(numeroSalleDecisive + "\n");
			  System.out.println(salle.getNumSalle());
			  if (numeroSalleDecisive.equals(salle.getNumSalle())) {
				  affichage.append("C'est dans cette salle que se trouve la pierre de sang.\n");
			  }
			  affichage.append("\n");
		  }
		  return affichage.toString();
	}
	
	private Salle trouverSalle(int numeroSalle) {

		Set<Salle> setSalle = planGrotte.keySet();
		for(Salle s: setSalle) {

			if(s.getNumSalle() == numeroSalle) {
				return s;
			}
		}
		return null;
	}
	
	public void configurerAcces(int numSalle, Integer... nums) {
		Salle salleOrig = trouverSalle(numSalle);
		List<Salle> listeSalleAccess = planGrotte.get(salleOrig);
		for(int i : nums) {
			listeSalleAccess.add(trouverSalle(i));
		}
		planGrotte.replace(salleOrig, listeSalleAccess);
	}
	
	public void setNumeroSalleDecisive(int numeroSalleDecisive) {
		this.numeroSalleDecisive = numeroSalleDecisive;
	}
	
	public boolean salleDecisive(Salle salle) {
		return numeroSalleDecisive.equals(salle.getNumSalle());
	}
	
	public Salle premiereSalle() {
		Salle salle = new Salle(-1, null);
		Set<Salle> listeSalle = planGrotte.keySet();
		for(Salle s : listeSalle) {
			sallesExplorees.add(s);
			return s;	
		}
		sallesExplorees.add(salle);
		return salle;
	}
	
	public Salle salleSuivante(Salle salle) {
		List<Salle> listeSalle = planGrotte.get(salle);
		listeSalle.removeAll(sallesExplorees);
		Random x = new Random();
		int y;
		if (listeSalle.isEmpty()) {
			sallesExplorees.clear();
			listeSalle = planGrotte.get(salle);
			y = x.nextInt(listeSalle.size());
			sallesExplorees.add(listeSalle.get(y));
			return listeSalle.get(y);
		}
		y = x.nextInt(listeSalle.size());
		sallesExplorees.add(listeSalle.get(y));
		return listeSalle.get(y);
		
	}
}
