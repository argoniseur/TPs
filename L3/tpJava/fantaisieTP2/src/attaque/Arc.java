package attaque;

public class Arc extends Arme {
	@SuppressWarnings("unused")
	private int nbFlechesRestantes;
	
	public Arc(int nbFlechesRestantes) {
		super(50, "arc");
		this.nbFlechesRestantes = nbFlechesRestantes;
	}
	
	int utiliser(){
		if (operationnel) {
			nbFlechesRestantes = nbFlechesRestantes-1;
			if (nbFlechesRestantes == 0) {
				operationnel = false;
			}
			
			return 50;
		}else {
			return 0;
		}
	}
}
