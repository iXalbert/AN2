import java.io.*;
import java.util.*;

class Curs
{
    private String denumire;
    private int id, credite, cod;

    public Curs(String d, int id, int credite, int cod)
    {
	this.denumire = d;
	this.id = id;
	this.credite = credite;
	this.cod = cod;
    }

    public boolean equals(Object o)
    {
	if(o instanceof Curs)
	    {
		return this.cod == ((Curs)o).cod;
	    }
	return false;
    }

    public int getId()
    {
	return id;
    }

    public int getCredite()
    {
	return this.credite;
    }

    // public String toString1() -> da aiurea(random)
    public String toString()
    {
	return "Id: " + id + " Denumire: " + denumire + " Credite: " + credite + " Cod: " + cod;
    }
}

class Curricula
{
    private Curs[] cursuri = new Curs[1];
    private int nrCursuri;

    public void add(Curs c)
    {
	if(nrCursuri == cursuri.length)
	    {
		Curs tmp[] = new Curs[2 * cursuri.length];
		for(int i = 0; i < cursuri.length; i++)
		    tmp[i] = cursuri[i];
		cursuri = tmp; 
	    }
	cursuri[nrCursuri++] = c;
    }

    public String toString()
    {
	/*
	String tmp = "";
	for(int i = 0; i < nrCursuri; i++)
	    {
		tmp += cursuri[i] + "\n";
	    }
	return tmp;
	*/

	/*
	  StringBuilder tmp = "";
	  for(int i = 0; i < nrCursuri; i++)
	  {
	       tmp.append(cursuri[i]).append("\n");
	  }
	  return tmp.toString();
	*/

	return Arrays.toString(cursuri); // mergem pana la sfarsitul tabloului, desi nu avem toat elementele setate
    }

    public Curs cauta(int id)
    {
	for(int i = 0; i < nrCursuri; i++)
	    {

		if(id == cursuri[i].getId())
		    return cursuri[i];
	    }
	return null;
    }

    public static Curricula load(String f)
    {
	Curricula c = new Curricula();
	try
	    {
		FileInputStream fis = new FileInputStream(f);
		Scanner s = new Scanner(fis);
		while(s.hasNext())
		    {
			int id;
			String denumire;
			int credite;
			int cod;
			if(s.hasNextInt())
			    id = s.nextInt();
			else
			    break;
			if(s.hasNext())
			    denumire = s.next();
			else
			    break;
			if(s.hasNextInt())
			    cod = s.nextInt();
			else
			    break;
			if(s.hasNextInt())
			    credite = s.nextInt();
			else
			    break;
			c.add(new Curs(denumire, id, credite, cod));
		    }
		s.close();
	    }
	catch(IOException e)
	    {
		System.err.println(e);
	    }
	return c;
    }
}

class Student
{
    private String nume;
    private Curs[] cursuri = new Curs[10]; // de la asociere
    private int[] note = new int[10];
    private int nrCursuri;
    
    public Student(String n)
    {
	nume = n;
    }

    public void inregistreazaNota(Curs c, int n)
    {
	if(n >= 5 && n <= 10)
	    {
		for(int i = 0; i < nrCursuri; i++)
		    {
			if(cursuri[i].equals(c))
			    {
				if(note[i] < n)
				    note[i] = n;
				return;
			    }
		    }
		if(nrCursuri == cursuri.length)
		    {
			cursuri = Arrays.copyOf(cursuri, 2 * cursuri.length);
			note = Arrays.copyOf(note, 2 * note.length);
		    }
		cursuri[nrCursuri] = c;
		note[nrCursuri++] = n;
	    }
    }

    // nu scriem :
    // private int sum = 0;
    // pentru ca nu se reinitializeaza pe 0
    public int calculeazaCredite()
    {
	int sum = 0;
	for(int i = 0; i < nrCursuri; i++)
	    {
		sum += cursuri[i].getCredite();
	    }
	return sum;
    }

    public double calculeazaMedie()
    {
	if(nrCursuri == 0)
	    return 0;
	
	double sum = 0;
	for(int i = 0; i < nrCursuri; i++)
	    sum += note[i];
	return sum / nrCursuri;
    }

    public String toString()
    {
	// fluxurile in java
	return Arrays
	    .stream(cursuri)
	    .map(e -> e + "")
	    .reduce("", (s, e) -> s + e + "\n");
	/*
	String res = nume + "\n";
	
	for(int i = 0; i < nrCursuri; i++)
	    res += cursuri[i] + "-" + note[i] + "\n";
	
	res += "Media: " + this.calculeazaMedie();
	res += "Credite: " + this.calculeazaCredite();

	return res;
	*/
    }
}

class Main
{
    public static void main(String argv[])
    {
	/*
	Curs a = new Curs("SDA", 1, 5, 1);
	Curs b = new Curs("POO", 2, 5, 2);
	Curs d = new Curs("OOP", 3, 5, 2);
	*/
	
	Curricula c = Curricula.load("input.txt");
	// c.add(a);
	// c.add(b);
	// c.add(d);
	System.out.println(c);
	
	Student s1 = new Student("Alin");
	s1.inregistreazaNota(c.cauta(1), 10);
	s1.inregistreazaNota(c.cauta(2), 4);
	System.out.println(s1);
	s1.inregistreazaNota(c.cauta(2), 6);
	System.out.println(s1);
	
	Student s2 = new Student("Alina");
	s2.inregistreazaNota(c.cauta(1), 8);
	s2.inregistreazaNota(c.cauta(2), 7);
	System.out.println(s2);
	s2.inregistreazaNota(c.cauta(1), 10);
	s2.inregistreazaNota(c.cauta(2), 4);
	System.out.println(s2);
    }
}
