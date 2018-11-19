package bataille;

import java.util.LinkedList;
import java.util.Random;

import protagoniste.EtreVivant;

public class Camp<T extends EtreVivant> {
	private LinkedList<T> liste = new LinkedList<>();
	
	public void ajouter(T etreVivant) {
			if(!liste.contains(etreVivant)) {
				liste.add(etreVivant);
			}
	}
	
	public void eliminer(T etreVivant) {
		if(liste.contains(etreVivant))
			liste.remove(etreVivant);
	}
	
	public LinkedList<T> donnercombattants(){
		return liste;
	}
	
	public int nbCombattants() {
		  return liste.size();
	}
	
	public T selectionner() {
		  Random randomGenerateur = new Random();
		  int numeroCombattant = randomGenerateur.nextInt(liste.size());
		  return liste.get(numeroCombattant);
	}

		
	/*
	@Override
	public String toString() {
		StringBuilder retour = new StringBuilder("Le camp contient: ");
		for(int i = 0; i<liste.size();i++) {
			retour.append(liste.get(i).getNom());
			if(i != liste.size()-1)
				retour.append(", ");
		}
		return retour.toString();		
	}*/
}
