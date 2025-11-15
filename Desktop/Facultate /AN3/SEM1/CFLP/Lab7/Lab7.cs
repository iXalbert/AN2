using System;
using System.Collections.Generic;

public delegate bool MyBoolDelegate(int x);
public delegate float MyFloatDelegate(float x);
public delegate int MyFunction(int x);

public class Lab7
{
    public static void Main(string[] args)
    {
        List<int> lista = new List<int> { 1, 5, 6, 3, 7, 9, 12, 4, 11, 2, 10, 8 };

        Console.WriteLine("Lista cu cond este : " + string.Join(", ", lista));

        MyBoolDelegate conditie = new MyBoolDelegate(Mic_de_7);
        List<int> Lista_finala = Filtru(conditie, lista);

        Console.WriteLine("Lista cu cond este : " + string.Join(", ", Lista_finala));

        MyFloatDelegate conditie1 = new MyFloatDelegate(f);
        MyFloatDelegate conditie2 = new MyFloatDelegate(g);

        float rezultat = FGX(conditie2, conditie1, 5);
        Console.WriteLine("Rezultatul FGX este : " + rezultat);

        MyFunction f2 = delegate (int x) 
        { 
            return x - 2; 
        };
        MyFunction g2 = delegate (int x) 
        { 
            return x * 3; 
            
        };

        MyFunction h = COMP(f2, g2);

        float h_rezultat = h(5);
        Console.WriteLine("Rezultatul cu MyFunction este : " + h_rezultat);
    }

    public static List<int> Filtru(MyBoolDelegate conditie, List<int> lista)
    {
        List<int> Lista_finala = new List<int>();
        foreach (int elem in lista)
        {
            if (conditie(elem))
            {
                Lista_finala.Add(elem);
            }
        }

        return Lista_finala;
    }

    public static bool Mic_de_7(int x)
    {
        return x < 7;
    }

    public static float f(float x)
    {
        return x * 3;
    }

    public static float g(float x)
    {
        return x - 2;
    }

    public static float FGX(MyFloatDelegate conditie1, MyFloatDelegate conditie2, float x)
    {
        return conditie2(conditie1(x));
    }

    public static MyFunction COMP(MyFunction f, MyFunction g)
    {
        return delegate (int x)
        {
            return f(g(x));
        };
    }
}
