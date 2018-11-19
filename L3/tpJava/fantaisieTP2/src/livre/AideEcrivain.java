package livre;


import java.util.LinkedList;
import java.util.List;

import bataille.Bataille;

import protagoniste.Heros;
import protagoniste.Homme;

public class AideEcrivain {
	private Bataille bataille;
	
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
}
