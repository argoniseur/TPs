
public class Liste {
	private Integer elem;
	private Liste suivant;
	public Liste(Integer x) {
		this.elem = x;
	}
	
	public Integer getElem() {
		return elem;
	}
	
	public Liste getSuivant() {
		return suivant;
	}
	
	public void setElem(Integer elem) {
		this.elem = elem;
	}
	
	public void setSuivant(Liste suivant) {
		this.suivant = suivant;
	}
	
	public Liste insertion(Integer x) {
		Boolean continu = true;
		Liste courant = this;
		Liste precedent = null;
		while (continu && (courant != null)) {
			if(courant.getElem() > x) {
				continu = false;
			}else {
				precedent = courant;
				courant = courant.getSuivant();
			}
		}
		
		Liste l = new Liste(x);
		l.setSuivant(courant);
		
		if(precedent != null) {
			precedent.getSuivant().setSuivant(l);
		}
		return this;
	}
}
