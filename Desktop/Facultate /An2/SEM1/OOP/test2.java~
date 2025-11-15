class Remorca {
    private static int lastCutiCount = 10;
    private String nrInmatriculare;
    private int nrCutiTransport;

    public Remorca(String nrInmatriculare, int nrCutiTransport) {
        this.nrInmatriculare = nrInmatriculare;
        this.nrCutiTransport = nrCutiTransport;
        lastCutiCount = nrCutiTransport;
    }

    public Remorca(String nrInmatriculare) {
        this.nrInmatriculare = nrInmatriculare;
        this.nrCutiTransport = lastCutiCount + 1;
        lastCutiCount = this.nrCutiTransport;
    }

    public int getNrCutiTransport() {
        return nrCutiTransport;
    }

    public String getNrInmatriculare() {
        return nrInmatriculare;
    }

    public String toString() {
        return "R(" + nrInmatriculare + ", " + nrCutiTransport + ")";
    }
}

class Tir {
    private Remorca[] remorci;
    private int nrRemorci;

    public Tir() {
        this.remorci = new Remorca[5];
        this.nrRemorci = 0;
    }

    public boolean adaugaRemorca(int nrCutiTransport, String nrInmatriculare) {
        if (nrRemorci < 5) {
            remorci[nrRemorci++] = new Remorca(nrInmatriculare, nrCutiTransport);
            return true;
        }
        return false;
    }

    public boolean adaugaRemorca(Remorca remorca) {
        if (nrRemorci < 5) {
            remorci[nrRemorci++] = remorca;
            return true;
        }
        return false;
    }

    public Remorca stergeRemorca(String nrInmatriculare) {
        for (int i = 0; i < nrRemorci; i++) {
            if (remorci[i].getNrInmatriculare().equals(nrInmatriculare)) {
                Remorca eliminata = remorci[i];
                for (int j = i; j < nrRemorci - 1; j++) {
                    remorci[j] = remorci[j + 1];
                }
                return eliminata;
            }
        }
        return null;
    }

    public int capacitateTotala() {
        int total = 0;
        for (int i = 0; i < nrRemorci; i++) {
            total += remorci[i].getNrCutiTransport();
        }
        return total;
    }

    public boolean equals(Tir other) {
        return this.capacitateTotala() == other.capacitateTotala();
    }

    public String toString() {
        StringBuilder sb = new StringBuilder("T");
        for (int i = 0; i < nrRemorci; i++) {
            sb.append(" -> ").append(remorci[i]);
        }
        return sb.toString();
    }
}


public class tes2 {
    public static void main(String[] args) {
        Tir tir1 = new Tir();
        Tir tir2 = new Tir();

        tir1.adaugaRemorca(20, "B123XYZ");
        tir1.adaugaRemorca(new Remorca("B456XYZ"));
        tir2.adaugaRemorca(15, "B789XYZ");
        tir2.adaugaRemorca(new Remorca("B101XYZ"));

        System.out.println("Tir 1: " + tir1);
        System.out.println("Tir 2: " + tir2);

        if (tir1.equals(tir2)) {
            System.out.println("Tirurile sunt egale ca și capacitate de transport.");
        } else {
            System.out.println("Tirurile NU sunt egale ca și capacitate de transport.");
        }

        Remorca remEliminata = tir1.stergeRemorca("B123XYZ");
        if (remEliminata != null) {
            System.out.println("Remorca eliminată din tir1: " + remEliminata);
        } else {
            System.out.println("Remorca nu a fost găsită în tir1.");
        }

        System.out.println("Tir 1 după eliminare: " + tir1);
    }
}
