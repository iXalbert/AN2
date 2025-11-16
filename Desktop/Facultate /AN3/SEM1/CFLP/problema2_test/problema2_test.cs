using System;
using System.Collections.Generic;

public delegate bool Conditie2(double x);

class problema2_test
{
    public bool CalculateScore(double basePoints, double multiplier, out double result)
    {
        result = basePoints * multiplier;
        return result > 0;
    }

    public bool Any(List<double> lista, Conditie2 conditie)
    {
        foreach(double item in lista)
        {
            if(conditie(item))
            {
                return true;
            }
        }

        return false;
    }

    public static void Main(string[] args)
    {
        
        double basePoint = 39.2;
        double multiplayer = 2.5;

        List<double> lista = new List<double>();
        lista.Add(35.6);
        lista.Add(32.1);
        lista.Add(14.7);
        lista.Add(20.6);
        lista.Add(27.5);

        Conditie2 conditie = delegate(double x)
        {
            return x > 35.5;
        };

        double finalScore;

        problema2_test p2 = new problema2_test();

        bool validare = p2.CalculateScore(basePoint,multiplayer,out finalScore);
    
        Console.WriteLine("Final Score: " + finalScore + " is valid? " + validare);

        bool validation = p2.Any(lista,conditie);

        Console.WriteLine("E un numar care indeplineste conditia? " + validation );

        List<Storage> storage = new List<Storage>();
        storage.Add(new CloudStorage("AWS",1000,200,100));
        storage.Add(new CloudStorage("Azure",2000,500,200));
        storage.Add(new HardDisk("Seagate",1500,300));
        storage.Add(new HardDisk("Western Digital",2500,600));
    
        foreach(Storage stor in storage)
        {
            stor.Load(100);
            Console.WriteLine(stor.ToString());
        }

        foreach(Storage stor in storage)
        {
            stor.Unload(150);
            Console.WriteLine(stor.ToString());
        }

    }

}

public abstract class Storage{

    public string Manufacture;
    public float MaxCapacity;
    public double CurrentCapacity;

    public Storage(string Manufacture, float MaxCapacity, double CurrentCapacity){

        this.Manufacture = Manufacture;
        this.MaxCapacity = MaxCapacity;
        this.CurrentCapacity = CurrentCapacity;
    }

    public abstract void Load(int x);
    public abstract void Unload(int x);

    public override string ToString(){
        return "Manufacture: " + Manufacture + " Max Capacitate : " + MaxCapacity + " Current Capacitate : " + CurrentCapacity;
    }

}

public class CloudStorage : Storage{

    public float ReservedCapacity;

    public CloudStorage(string Manufacture, float MaxCapacity, double CurrentCapacity,float ReservedCapacity) : base(Manufacture,MaxCapacity,CurrentCapacity){

        this.ReservedCapacity = ReservedCapacity;
    }

    public override void Load(int x){
        
        CurrentCapacity = CurrentCapacity + 1.2 * x;
        if(CurrentCapacity > MaxCapacity){
            CurrentCapacity = MaxCapacity;
        }
    }

    public override void Unload(int x){
        
        CurrentCapacity = CurrentCapacity - x;
        if(CurrentCapacity < 0){
            CurrentCapacity = 0;
        }
    }

    public override string ToString(){
        return "Cloud Storage : " + base.ToString() + " Reserved Capacity : " + ReservedCapacity;
    }
}

public class HardDisk : Storage{

    public HardDisk(string Manufacture, float MaxCapacity, double CurrentCapacity) : base(Manufacture,MaxCapacity,CurrentCapacity){}

    public override void Load(int x){

        CurrentCapacity = CurrentCapacity + x;
        if(CurrentCapacity > MaxCapacity){
            CurrentCapacity = MaxCapacity;
        }
    }

    public override void Unload(int x){

        CurrentCapacity = CurrentCapacity - x;
        if(CurrentCapacity < 0){
            CurrentCapacity = 0;
        }
    }

    public override string ToString(){
        return "Hard Disk : " + base.ToString();
    }
}
