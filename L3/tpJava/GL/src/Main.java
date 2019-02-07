
public class Main {

	public static void main(String[] args) {
		Liste l = new Liste(new Integer(5));
		while(l.getSuivant() != null) {
			System.out.println(l.getElem());
		}
		

	}

}
