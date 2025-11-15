using System;
using System.Collections.Generic;

public interface IRentable
{
    bool IsRented { get; set; }
    double MonthlyRent { get; }
}

class RealEstateAgency
{
    public List<Property> Properties { get; set; } = new List<Property>();

    public void AddProperty(Property property)
    {
        Properties.Add(property);
    }

    public void RentProperty(Property property)
    {
        if (property is IRentable rentableProperty)
        {
            if (rentableProperty.IsRented)
            {
                Console.WriteLine($"Proprietatea este deja inchiriata");
            }
            else
            {
                rentableProperty.IsRented = true;
                Console.WriteLine($"Proprietatea este disponibila pentru inchiriere");
            }
        }
        else
        {
            Console.WriteLine($"Proprietatea nu poate fi inchiriata");
        }
    }
    
    public void afisareProprietati()
    {
        Console.WriteLine("Proprietatile adaugate in agentie:");
        foreach (var property in Properties)
        {
            Console.WriteLine(property.ToString());
        }
    }
}

abstract class Property
{
    public string Address { get; set; }
    public double IndoorArea { get; set; }
    public double PropertyValue { get; set; }

    public Property(String address, double indoorArea, double propertyValue)
    {
        Address = address;
        IndoorArea = indoorArea;
        PropertyValue = propertyValue;
    }
    public override string ToString()
    {
        return $"{Address} - suprafata proprietate {IndoorArea} m^2 - valoare : {PropertyValue} leuti";
    }
}

class House : Property
{
    public double OutdoorArea { get; set; }
    public double TotalArea { get; set; }

    public House(string address, double indoorArea, double propertyValue, double outdoorArea, double totalArea) : base(address, indoorArea, propertyValue)
    {
        OutdoorArea = outdoorArea;
        TotalArea = indoorArea + outdoorArea;
    }
    
    public override string ToString()
    {
        return $"{base.ToString()} - suprafata curte e : {OutdoorArea} m^2 - suprafata totala este : {TotalArea} m^2";
    }
}

class Apartment : Property
{
    public double Floor { get; set; }
    public bool HasElevator { get; set; }

    public Apartment(string address, double indoorArea, double propertyValue, double floor, bool hasElevator) : base(address, indoorArea, propertyValue)
    {
        Floor = floor;
        HasElevator = hasElevator;
    }

    public override string ToString()
    {
        return $"{base.ToString()} - etaj : {Floor} - are lift : {HasElevator}";
    }
}

class RentableApartment : Apartment, IRentable
{
    public bool IsRented { get; set; }
    public double MonthlyRent { get; }

    public RentableApartment(string address, double indoorArea, double propertyValue, double floor, bool hasElevator, bool isRented, double monthlyRent) : base(address, indoorArea, propertyValue, floor, hasElevator)
    {
        IsRented = isRented;
        MonthlyRent = monthlyRent;
    }
    
    public override string ToString()
    {
        return base.ToString() + $" - este inchiriat : {IsRented} - chirie pe luna : {MonthlyRent} leiuti";
    }
}

class lab5_alternative
{
    static void Lab5Main(string[] args)
    {
        var agency = new RealEstateAgency();

        agency.AddProperty(new House("Aleea Studentilor, nr 10", 135.3, 300000, 60.5, 194.8));
        agency.AddProperty(new House("Aleea Studentilor, nr 11", 154, 45300, 45, 34));
        agency.AddProperty(new RentableApartment("Strada Parvan, nr 2", 35.5, 382000, 4, true, false, 3489));
        agency.AddProperty(new Apartment("Strada Crinilor, nr 1", 30.0, 10000, 3, false));

        agency.afisareProprietati();

        agency.RentProperty(agency.Properties[2]);
        agency.RentProperty(agency.Properties[3]);
        agency.RentProperty(agency.Properties[2]);
        agency.RentProperty(agency.Properties[1]);
    }
}
