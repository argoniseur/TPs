package bataille;

import java.util.LinkedList;

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
