using System;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;

class Lab3
{
    public static void Interschimba(ref int a, ref int b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    public static Coord MijlocSegmentului(Coord a, Coord b)
    {
        float Xmij = (a.X + b.X) / 2;
        float Ymij = (a.Y + b.Y) / 2;
        return new Coord(Xmij, Ymij);
    }

    static void Lab3Main()
    {
        int x = 5;
        int y = 10;
        Interschimba(ref x, ref y);
        Console.WriteLine($"Dupa interschimbare : x = {x}, y = {y}");

        Coord p1 = new Coord(2, 4);
        Coord p2 = new Coord(6, 8);

        Coord mijloc = MijlocSegmentului(p1, p2);
        Console.WriteLine($"Mijlcoul segentului dintre p1 si p2 este {mijloc}");

        Cont cont = new Cont("Rosca Albert", 10402);
        Console.WriteLine(cont);
        if (cont.Retragere(250, out double soldRamas))
            Console.WriteLine($"Retragere reusita. Sold ramas : {soldRamas} lei");
        else
            Console.WriteLine($"Retragere nereusita. Sold-ul a ramas neschimmbat ");

    }
}

public struct Coord
{
    public float X { get; set; }
    public float Y { get; set; }

    public Coord(float x, float y)
    {
        X = x;
        Y = y;
    }

    public override string ToString()
    {
        return $"({X},{Y})";
    }

}

public class Cont
{
    public string Nume { get; set; }
    public double Sold { get; set; }

    public Cont(string Nume, double Slot)
    {
        this.Nume = Nume;
        this.Sold = Slot;
    }

    public bool Retragere(double suma, out double soldRamas)
    {
        if (suma <= Sold)
        {
            Sold = Sold - suma;
            soldRamas = Sold;
            return true;
        }
        else
        {
            soldRamas = Sold;
            return false;
        }
    }

    public override string ToString()
    {
        return $"{Nume} - Sold current : {Sold} lei";
    }
}