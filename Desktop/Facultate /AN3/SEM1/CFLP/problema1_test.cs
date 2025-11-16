using System;
using System.Collections.Generic;

public delegate bool Conditie(float x);

class problema1_test{

    public bool ConvertTemperature(float tempK, out float tempC){
        tempC = tempK - 273.15f;
        return tempK > 0;
    }

    public bool All(List<float> lista, Conditie conditie){

        foreach(float item in lista){

            if(!conditie(item)){
                return false;
            }
        }

        return true;
    }

    public static void Main(string[] args){

        List<float> numere = new List<float>{3.4f,1.6f,3.4f,8.8f};

        float tempK = 289.56f;

        Conditie conditie = delegate(float x){
            return x % 2 == 0;
        };

        flaot tempC;

        bool pozitiva = ConvertTemperature(tempK,out tempC);

        Console.WriteLine("Temperatura in Celsius: " + tempC + " si aceasta este valida ? " + pozitiva);

        bool validation = All(numere,conditie);

        Console.WriteLine("Toate numerele din lista sunt apre? " + validation);

        List<Appliance> appliances = new List<Appliance>();
        appliances.Add(new WashingMachine("gbfegs",4563,0));
        appliances.Add(new WashingMachine("gwbgeiu",3554,1));
        appliances.Add(new Refrigerator("gweg",2345,2,50));
        appliances.Add(new Refrigerator("gweg",2345,2,60));

        foreach(Appliance app in appliances)
        {
            app.Activate();
            Console.WriteLine(app.ToString());
        }

        foreach(Appliance app in appliances)
        {
            app.Dezactivate();
            Console.WriteLine(app.ToString());
        }
    }
}

abstract class Appliance{

    public string brand;
    public float MaxPower;
    public float CurrentPower;

    public Appliance(string brand, float MaxPower, float CurrentPower)
    {
        this.brand = brand;
        this.MaxPower = MaxPower;
        this.CurrentPower = CurrentPower;
    }

    public abstract void Activate();
    public abstract void Dezactivate();

    public override string ToString()
    {
        return "Brand : " + brand + " Max Power : " + MaxPower + " Current Power : " + CurrentPower;
    }

}

class WashingMachine : Applicance
{
    public WashingMachine(float brand, float MaxPower, float CurrentPower) : base(brand,MaxPower,CurrentPower){}

    public override void Activate()
    {
        CurrentPower = MaxPower;
    }

    public override void Dezactivate()
    {
        CurrentPower = 0;
    }

    public string ToString()
    {
        
        return "Washing Machine : " + base.ToString();
    }
}

class Refrigerator : Appliance
{
    public int IdlePower;
    public Refrigerator(float brand, float MaxPower, float CurrentPower, float IdlePower) : base(brand, MaxPower, CurrentPower)
    {
        this.IdlePower = IdlePower;
    }

    public override void Activate()
    {
        CurrentPower = MaxPower/2;
    }

    public override void Dezactivate()
    {
        CurrentPower = IdlePower;
    }

    public string ToString()
    {
        return "Refrigerator : " + base.ToString() + " Idle Power : " + IdlePower;
    }

}
