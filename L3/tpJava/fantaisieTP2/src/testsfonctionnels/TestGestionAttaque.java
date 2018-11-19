package testsfonctionnels;
import attaque.*;
import protagoniste.*;

public class TestGestionAttaque {

	public static void main(String[] args) {
		Monstre<Feu> dragotenebre = new Monstre<>("dragotenebre", 200, ZoneDeCombat.aérien, Domaine.feu, new Lave(1), new Eclair(1), new BouleDeFeu(1));
		System.out.println(dragotenebre.toString());
		
		dragotenebre.attaque();
		dragotenebre.attaque();
		dragotenebre.attaque();
		dragotenebre.attaque();
	}

}
