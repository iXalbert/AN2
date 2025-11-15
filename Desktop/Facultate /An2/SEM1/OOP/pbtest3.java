import java.util.ArrayList;

interface GreutateCalculabila {
    double calculeazaGreutateTotala();
}

class Autoturism implements GreutateCalculabila {
    private String numarInmatriculare;
    private double greutateAutovehicul;
    private double greutatePasageri;

    public Autoturism(String numarInmatriculare, double greutateAutovehicul, double greutatePasageri) {
        this.numarInmatriculare = numarInmatriculare;
        this.greutateAutovehicul = greutateAutovehicul;
        this.greutatePasageri = greutatePasageri;
    }

    public double calculeazaGreutateTotala() {
        return greutateAutovehicul + greutatePasageri;
    }

    public String toString() {
        return "Numar inmatriculare: " + numarInmatriculare +
               ", Greutate autovehicul: " + greutateAutovehicul +
               ", Greutate pasageri: " + greutatePasageri;
    }
}

class Camion implements GreutateCalculabila {
    private String numarInmatriculare;
    private double greutateAutovehicul;
    private ArrayList<Autoturism> autoturisme;

    public Camion(String numarInmatriculare, double greutateAutovehicul) {
        this.numarInmatriculare = numarInmatriculare;
        this.greutateAutovehicul = greutateAutovehicul;
        this.autoturisme = new ArrayList<>();
    }

    public void adaugaAutoturism(Autoturism autoturism) {
        autoturisme.add(autoturism);
    }

    @Override
    public double calculeazaGreutateTotala() {
        double totalGreutate = greutateAutovehicul;
        for (Autoturism autoturism : autoturisme) {
            totalGreutate += autoturism.calculeazaGreutateTotala();
        }
        return totalGreutate;
    }

    public String toString() {
        StringBuilder result = new StringBuilder("Numar inmatriculare: " + numarInmatriculare +
                ", Greutate camion: " + greutateAutovehicul + " Transporta autoturisme: ");

        for (Autoturism autoturism : autoturisme) {
            result.append("	").append(autoturism.toString()).append(" ");
        }
        return result.toString();
    }
}

class Transportor {
    private double greutateMaxima;
    private ArrayList<GreutateCalculabila> autovehicule;

    public Transportor(double greutateMaxima) {
        this.greutateMaxima = greutateMaxima;
        this.autovehicule = new ArrayList<>();
    }

    public boolean adaugaAutovehicul(GreutateCalculabila autovehicul) {
        double greutateTotala = calculeazaGreutateTotala() + autovehicul.calculeazaGreutateTotala();
        if (greutateTotala <= greutateMaxima) {
            autovehicule.add(autovehicul);
            return true;
        }
        return false;
    }

    public double calculeazaGreutateTotala() {
        double totalGreutate = 0;
        for (GreutateCalculabila autovehicul : autovehicule) {
            totalGreutate += autovehicul.calculeazaGreutateTotala();
        }
        return totalGreutate;
    }

    public String toString() {
        StringBuilder result = new StringBuilder("Transportor: Greutate maxima: " + greutateMaxima +
                ", Greutate curenta: " + calculeazaGreutateTotala() + " Autovehicule transportate: ");
        for (GreutateCalculabila autovehicul : autovehicule) {
            result.append("	").append(autovehicul.toString()).append(" ");
        }
        return result.toString();
    }
}

public class pbtest3 {
    public static void main(String[] args) {
	
        Autoturism a1 = new Autoturism("MS01ABC", 4.5, 0.3);
        Autoturism a2 = new Autoturism("MS02DEF", 2.5, 0.25);
        Autoturism a3 = new Autoturism("MS03XYZ", 3.0, 0.2);

        Camion camion1 = new Camion("MS10CAM", 8.0);
        camion1.adaugaAutoturism(a1);
        camion1.adaugaAutoturism(a2);

        Camion camion2 = new Camion("MS20CAM", 10.0);
        camion2.adaugaAutoturism(a3);

        Transportor transportor = new Transportor(20.0);
        System.out.println("Adaugare camion1: " + transportor.adaugaAutovehicul(camion1));
        System.out.println("Adaugare camion2: " + transportor.adaugaAutovehicul(camion2));

        System.out.println(transportor);
    }
}
