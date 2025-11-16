using System;
using System.Collections.Generic;

public delegate bool Conditie3(int x);

class problema3_test{

    public static void SwapIfGreater(ref int a, ref int b){

        if(a > b){

            int temp = a;
            a = b;
            b = temp;
        }
    }

    public bool AnyTrue(List<int> lista, Conditie3 conditie){

        foreach(int item in lista){

            if(conditie(item)){
                return true;
            }

        }

        return false;
    }

    public static void Main(string[] args){

        problema3_test  p3 = new problema3_test();

        int a1 = 3;
        int b1 = 7;

        int a2 = 6;
        int b2 = 1;

        Console.WriteLine("Before Swap a1 = " + a1 + " b1 = " + b1);
        SwapIfGreater(ref a1, ref b1);
        Console.WriteLine("After Swap a1 = " + a1 + " b1 = " + b1);


        Console.WriteLine("Before Swap a2 = " + a2 + " b2 = " + b2);
        SwapIfGreater(ref a2, ref b2);
        Console.WriteLine("After Swap a2 = " + a2 + " b2 = " + b2);

        List<int> numere = new List<int>();
        numere.Add(3);
        numere.Add(1);
        numere.Add(4);
        numere.Add(5);
        numere.Add(2);

        Conditie3 conditie = delegate(int x){
            return x%2 == 1;
        };

        bool validation = p3.AnyTrue(numere,conditie);

        Console.WriteLine("Exista un numar impar in lista? " + validation); 

        List<Device> devices = new List<Device>();

        devices.Add(new Phone("iPhone",100,20));
        devices.Add(new Phone("Samsung",150,50));
        devices.Add(new Tablet("iPad",200,80));
        devices.Add(new Tablet("Galaxy Tab",250,100));

        foreach(Device dev in devices){
            dev.Charge(30);
            Console.WriteLine(dev.ToString());
        }

        foreach(Device dev in devices){
            dev.Use(50);
            Console.WriteLine(dev.ToString());
        }   


    }
}

public abstract class Device{

    public string Name{get;}
    public int BatteryCapacity{get;set;}
    public int BatteryLevel{get;set;}

    public Device(string Name, int BatteryCapacity, int BatteryLevel){

        this.Name = Name;
        this.BatteryCapacity = BatteryCapacity;
        this.BatteryLevel = BatteryLevel;
    }

    public abstract void Charge(int percentage);
    public abstract void Use(int percentage);

    public override string ToString(){
        return "Nume : " + Name + " Capacitate Bateriei  : " + BatteryCapacity + " Nivel Baterie : " + BatteryLevel ; 
    }
}

public class Phone : Device{

    public Phone(string Name, int BatteryCapacity, int BatteryLevel) : base(Name,BatteryCapacity,BatteryLevel)
    {

    } 

    public override void Charge(int percentage){

        BatteryLevel = BatteryLevel + percentage;
        if(BatteryLevel > BatteryCapacity){
            BatteryLevel = BatteryCapacity;
        }

        Console.WriteLine("Telefonul " + Name + " a fost incarcat la  " + BatteryLevel);

    }

    public override void Use(int percentage){

        BatteryLevel = BatteryLevel - percentage;
        if(BatteryLevel < 0){
            BatteryLevel = 0;
        }

        Console.WriteLine("Telefonul " + Name + " a fost folosit pana la nivelul bateriei de  " + BatteryLevel);
    }

    public override string ToString(){
        return "Phone - " + base.ToString();
    }
}

public class Tablet : Device{

    public Tablet(string Name, int BatteryCapacity, int BatteryLevel) : base(Name,BatteryCapacity,BatteryLevel){}

    public override void Charge(int percentage){

        BatteryLevel = BatteryLevel + percentage;
        if(BatteryLevel > BatteryCapacity){
            BatteryLevel = BatteryCapacity;
        }

        Console.WriteLine("Tableta " + Name + " e incarcata mai lent " + BatteryLevel);

    }

    public override void Use(int percentage){

        BatteryLevel = BatteryLevel - percentage;
        if(BatteryLevel < 0){
            BatteryLevel = 0;
        }

        Console.WriteLine("Tableta " + Name + " a fost folosita. Nivelul bateriei este acum " + BatteryLevel);
    }

    public override string ToString(){
        return "Tableta - " + base.ToString();
    } 
}