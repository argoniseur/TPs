package testsfonctionnels;
import protagoniste.*;
import bataille.*;
import attaque.*;

public class TestGestionGrotte {

	public static void main(String[] args) {
		Monstre<Feu> dragotenebre = new Monstre<>("dragotenebre", 200, ZoneDeCombat.aérien, Domaine.feu, new BouleDeFeu(4), new Lave(1), new Eclair(3));
		@SuppressWarnings("unchecked")
		Monstre<Tranchant>[] tableauVampirien = new Monstre[10];
		for (int i = 0; i < 10; i++) {
		  tableauVampirien[i] = new Monstre<>("vampirien", 10, ZoneDeCombat.aérien, Domaine.tranchant, new Morsure(10));
		}
		Monstre<Glace> marinsangant = new Monstre<>("marinsangant", 150, ZoneDeCombat.aquatique, Domaine.glace, new PicsDeGlace(10), new Tornade(1));
		Monstre<Tranchant> guillotimort = new Monstre<>("guillotimort", 80, ZoneDeCombat.terrestre, Domaine.tranchant, new LameAcier(10), new Griffe());
		Monstre<Glace> givrogolem = new Monstre<>("givrogolem", 200, ZoneDeCombat.terrestre, Domaine.glace, new PicsDeGlace(10), new Tornade(1));
		Monstre<Feu> aqualave = new Monstre<>("aqualave", 30, ZoneDeCombat.aquatique, Domaine.feu, new Lave(5));
		Monstre<Tranchant> requispectre = new Monstre<>("requispectre", 200, ZoneDeCombat.aquatique, Domaine.tranchant, new Griffe());
		Monstre<Glace> soufflemort = new Monstre<>("soufflemort", 120, ZoneDeCombat.aérien, Domaine.glace, new Tornade(8));
		Monstre<Feu> cramombre = new Monstre<>("cramombre", 80, ZoneDeCombat.terrestre, Domaine.feu, new BouleDeFeu(2), new Lave(1), new Eclair(1));
		
		Grotte grotte = new Grotte();

		grotte.ajouterSalle(ZoneDeCombat.terrestre, guillotimort);
		grotte.ajouterSalle(ZoneDeCombat.aérien, dragotenebre);
		grotte.ajouterSalle(ZoneDeCombat.terrestre, cramombre);
		grotte.ajouterSalle(ZoneDeCombat.terrestre, givrogolem);
		grotte.ajouterSalle(ZoneDeCombat.aérien, tableauVampirien);
		grotte.ajouterSalle(ZoneDeCombat.aquatique, aqualave);
		grotte.ajouterSalle(ZoneDeCombat.aquatique, marinsangant);
		grotte.ajouterSalle(ZoneDeCombat.aquatique, requispectre);
		grotte.ajouterSalle(ZoneDeCombat.aérien, soufflemort);

		grotte.configurerAcces(1, 2, 6);
		grotte.configurerAcces(2, 1, 3, 5);
		grotte.configurerAcces(3, 2, 4);
		grotte.configurerAcces(4, 3, 5, 9);
		grotte.configurerAcces(5, 2, 4, 6, 8);
		grotte.configurerAcces(6, 1, 5, 7);
		grotte.configurerAcces(7, 6, 8);
		grotte.configurerAcces(8, 5, 7, 9);
		grotte.configurerAcces(9, 4, 8);

		System.out.println("\n**** TP4 ****");
		grotte.setNumeroSalleDecisive(9);
		System.out.println("Plan de la grotte\n" + grotte.afficherPlanGrotte());
		System.out.println("\nParcours de la grotte\n");
		Salle salle = grotte.premiereSalle();
		System.out.println(salle + "\n");
		if (!grotte.salleDecisive(salle)) {
			do {
				salle = grotte.salleSuivante(salle);
				System.out.println(salle + "\n");

			} while (!grotte.salleDecisive(salle));
			System.out.println("C'est la salle contenant la Pierre de Sang");
		}

	}
//		RESULTAT ATTENDU
//		**** TP4 ****
//		Plan de la grotte
//		La Salle n°1 de type combat TERRESTRE.
//		elle possede 2 acces :  vers la salle Salle n°2 de type combat AERIEN vers la salle Salle n°6 de type combat AQUATIQUE
//		Un monstre de type guillotimort la protege.
//
//		La Salle n°2 de type combat AERIEN.
//		elle possede 3 acces :  vers la salle Salle n°1 de type combat TERRESTRE vers la salle Salle n°3 de type combat TERRESTRE vers la salle Salle n°5 de type combat AERIEN
//		Un monstre de type dragotenebre la protege.
//
//		La Salle n°3 de type combat TERRESTRE.
//		elle possede 2 acces :  vers la salle Salle n°2 de type combat AERIEN vers la salle Salle n°4 de type combat TERRESTRE
//		Un monstre de type cramombre la protege.
//
//		La Salle n°4 de type combat TERRESTRE.
//		elle possede 3 acces :  vers la salle Salle n°3 de type combat TERRESTRE vers la salle Salle n°5 de type combat AERIEN vers la salle Salle n°9 de type combat AERIEN
//		Un monstre de type givrogolem la protege.
//
//		La Salle n°5 de type combat AERIEN.
//		elle possede 4 acces :  vers la salle Salle n°2 de type combat AERIEN vers la salle Salle n°4 de type combat TERRESTRE vers la salle Salle n°6 de type combat AQUATIQUE vers la salle Salle n°8 de type combat AQUATIQUE
//		10 monstres de type vampirien la protege.
//
//		La Salle n°6 de type combat AQUATIQUE.
//		elle possede 3 acces :  vers la salle Salle n°1 de type combat TERRESTRE vers la salle Salle n°5 de type combat AERIEN vers la salle Salle n°7 de type combat AQUATIQUE
//		Un monstre de type aqualave la protege.
//
//		La Salle n°7 de type combat AQUATIQUE.
//		elle possede 2 acces :  vers la salle Salle n°6 de type combat AQUATIQUE vers la salle Salle n°8 de type combat AQUATIQUE
//		Un monstre de type marinsangant la protege.
//
//		La Salle n°8 de type combat AQUATIQUE.
//		elle possede 3 acces :  vers la salle Salle n°5 de type combat AERIEN vers la salle Salle n°7 de type combat AQUATIQUE vers la salle Salle n°9 de type combat AERIEN
//		Un monstre de type requispectre la protege.
//
//		La Salle n°9 de type combat AERIEN.
//		elle possede 2 acces :  vers la salle Salle n°4 de type combat TERRESTRE vers la salle Salle n°8 de type combat AQUATIQUE
//		Un monstre de type soufflemort la protege.
//		C'est dans cette salle que se trouve la pierre de sang.
//
//

		
		//UNE POSSIBILITE DE RESULTAT PARMI D AUTRE
		
//		Parcours de la grotte
//
//		Salle n°1 de type combat TERRESTRE
//
//		Salle n°2 de type combat AERIEN
//
//		Salle n°5 de type combat AERIEN
//
//		Salle n°4 de type combat TERRESTRE
//
//		Salle n°3 de type combat TERRESTRE
//
//		Salle n°2 de type combat AERIEN
//
//		Salle n°3 de type combat TERRESTRE
//
//		Salle n°4 de type combat TERRESTRE
//
//		Salle n°9 de type combat AERIEN
//
//		C'est la salle contenant la Pierre de Sang

}
