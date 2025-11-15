using System;
using System.Collections.Generic;

namespace Manger_Banca
{
    public enum TipCont
    {
        Persoana,
        Companie
    }

    public class Cont
    {
        public string titularCont { get; }
        public TipCont tipCont { get; }
        public string iban { get; }
        public float Suma { get; private set; }

        public Cont(string titularCont, TipCont tipCont, string iban, float sumaInitiala = 0)
        {
            this.titularCont = titularCont;
            this.tipCont = tipCont;
            this.iban = iban;
            this.Suma = sumaInitiala;
        }

        public void DepunereBani(float suma)
        {
            Suma = Suma + suma;
            Console.WriteLine($"Depunere: {suma}. Sold nou: {Suma}");
        }

        public void RetragereBani(float suma)
        {
            Suma = Suma - suma;
            if(Suma < 0)
            Console.WriteLine("Nu se pot retrage toti bani din acest cont");
            Console.WriteLine($"Retragere: {suma}. Sold nou: {Suma}");
        }

        public override string ToString()
        {
            return $"IBAN: {iban}, Titular: {titularCont}, Tip: {tipCont}, Sold: {Suma}";
        }
    }

    public class Banca
    {
        public string Nume { get; }
        public string Swift { get; }
        public List<Cont> Conturi { get; }

        public Banca(string nume, string swift)
        {
            this.Nume = nume;
            this.Swift = swift;
            this.Conturi = new List<Cont>();
        }

        public void DeschidereCont(string titular, TipCont tip, string iban, float sumaInitiala = 0)
        {
            var cont = new Cont(titular, tip, iban, sumaInitiala);
            Conturi.Add(cont);
            Console.WriteLine($"Cont nou deschis: {iban}");
        }

        public void GasesteCont(string iban)
        {
            var cont = GetAccount(iban);
            if (cont != null)
                Console.WriteLine(cont.ToString());
            else
                Console.WriteLine("Contul nu a fost găsit");
        }

        public void DepunereBani(string iban, float suma)
        {
            var cont = GetAccount(iban);
            if (cont != null)
            {
            cont.DepunereBani(suma);
            }
            else
            {
            Console.WriteLine("Contul cu IBAN-ul specificat nu a fost găsit.");
            }
        }

        public void RetragereBani(string iban, float suma)
        {
            var cont = GetAccount(iban);
            if(cont != null)
            {
                cont.RetragereBani(suma);
            }else
            {
                Console.WriteLine("Contul cu IBAN-ul specificat nu a fost gasit");
            }
        }

        public void Transfer(string ibanSursa, string ibanDestinatie, float suma)
        {
            var contSursa = GetAccount(ibanSursa);
            var contDestinatie = GetAccount(ibanDestinatie);
            
            if (contSursa != null && contDestinatie != null)
            {
                contSursa.RetragereBani(suma);
                contDestinatie.DepunereBani(suma);
                Console.WriteLine($"Transfer de {suma} de la {ibanSursa} la {ibanDestinatie}");
            }else{
                Console.WriteLine("Nu se pot transfera bani");
            }
        }

        private Cont? GetAccount(string iban)
        {
            foreach (Cont cont in Conturi)
            {
                if (cont.iban == iban)
                {
                    return cont;
                }
            }
            return null; 
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

            var banca = new Banca("BRD", "BRDGROBU");
            
            banca.DeschidereCont("Rosca Albert", TipCont.Persoana, "RO49AAAA1B31007593840123", 1000);
            banca.DeschidereCont("SC Resita SRL", TipCont.Companie, "RO49AAAA1B31008093840001", 5000);
            
            Console.WriteLine("\n=== Detalii conturi ===");
            banca.GasesteCont("RO49AAAA1B31007593840123");
            banca.GasesteCont("RO49AAAA1B31008093840001");

            Console.WriteLine("\n=== Operatiuni ===");

            banca.DepunereBani("RO49AAAA1B31007593840123", 500);
            
            banca.RetragereBani("RO49AAAA1B31007593840123", 1600);
            
            banca.Transfer("RO49AAAA1B31007593840001", "RO49AAAA1B31007593840123", 300);
            
            Console.WriteLine("\n=== Solduri finale ===");
            banca.GasesteCont("RO49AAAA1B31007593840123");
            banca.GasesteCont("RO49AAAA1B31008093840001");
        }
    }
}
