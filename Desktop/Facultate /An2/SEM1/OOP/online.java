public class Main {
    public static void main(String[] args) {
        int a = 11;
        int b = 0;
        int c = -1;

        MyClass myObj = new MyClass();
   

        try {
            for (int i = 0; i < 20; i++) {
                myObj.doSomething(i);
            }
            //myObj.doSomething(a);           
            //myObj.doSomething(b);
            //myObj.doSomething(c);
           
        } catch(CheckedNegativeNumberException ex) {
            System.out.println("Found NegativeNumberException");
        } 
        catch(Exception ex) {
            System.out.println("Found Exception");
        } finally {
            System.out.println("Finally");
        }

        System.out.println("Final de tot");
        
    }
}

class MyClass {
    public int doSomething(int a) throws CheckedNegativeNumberException {

        if(a >= 10) throw new UncheckedNegativeNumberException(); 

        if(a >= 0) 
        {
            System.out.println(a+1);
            return a + 1;
        }
       

        else {
            throw new CheckedNegativeNumberException("Numar negativ in parametru");
        }
    }
}

class CheckedNegativeNumberException extends Exception {
    public CheckedNegativeNumberException(String msg) {
        super(msg);
    }
}

class UncheckedNegativeNumberException extends RuntimeException {

}
