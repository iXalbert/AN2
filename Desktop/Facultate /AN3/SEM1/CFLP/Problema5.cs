using System;
using System.Collections.Generic;

public class Program
{
    public static void RemoveAt(int[] array, ref int length, int n)
    {
        if (n < 0 || n >= length)
        {
            Console.WriteLine("Index nu se afla in dimensiune");
            return;
        }

        for (int i = n; i < length - 1; i++)
        {
            array[i] = array[i + 1];
        }

        length--;

    }

    public static List<int> Intersection(List<int> l1, List<int> l2)
    {

        List<int> result = new List<int>();

        foreach (int item in l1)
        {
            if (l2.Contains(item) && !result.Contains(item))
            {
                result.Add(item);
            }
        }

        return result;
    }


    public static void Main(string[] args)
    {

        int[] array = { 4, 7, 9, 2, 6, 1 };
        int length = array.Length;

        Console.WriteLine("array = " + string.Join(",", array));
        RemoveAt(array, ref length, 4);
        Console.WriteLine("array dupa eliminarea elementului de pe pozitia 4 = " + string.Join(",", array[length]));

        List<int> l1 = new List<int> { 1, 5, 4, 3, 6, 7 };
        List<int> l2 = new List<int> { 6, 3, 8, 7, 6, 1 };

        List<int> Intersectie = Intersection(l1, l2);
        Console.WriteLine("Intersectia celor doua liste este : " + string.Join(",", Intersectie));

        Stack<string> stack = new Stack<string>();
        stack.Push("1");
        stack.Push("2");
        stack.Push("3");

        Console.WriteLine("Primul element din stiva este : " + stack.Peek());
        Console.WriteLine("Pop din stiva : " + stack.Pop());

        stack.Push("4");

        if (stack.TryPop(out string item))
        {
            Console.WriteLine("Element scos cu TryPop : " + item);
        }
        else
        {
            Console.WriteLine("Stiva este goala");
        }
        
                
        stack.Pop();
        stack.Pop();
        stack.Pop();
    }
}

public class Stack<T>
    {
        private List<T> items = new List<T>();

        public void Push(T item)
        {
            items.Add(item);
        }

        public T Pop()
        {
            if (items.Count == 0)
            {
                Console.WriteLine("Stiva este goala");
                return default(T);
            }

        T top = items[items.Count - 1];
        items.RemoveAt(items.Count - 1);

        return top;
        }

        public bool TryPop(out T item)
        {
            if (items.Count == 0)
            {
                item = default(T);
                return false;
            }
            else
            {
                item = items[items.Count - 1];
                items.RemoveAt(items.Count - 1);
                return true;
            }
        }

        public T Peek()
        {
            if (items.Count == 0)
            {
                Console.WriteLine("Stiva este goala");
                return default(T);
            }

            return items[items.Count - 1];
        }
    }