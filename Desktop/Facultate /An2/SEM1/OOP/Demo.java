import java.util.*;

interface UnitateLupta{
    public boolean esteVie();
    public void loveste(UnitateLupta u);
    public void ranire(int d);
}

abstract class UnitateLuptaSimpla implements UnitateLupta{
    private int viata,putere;
    public UnitateLuptaSimpla(int d,int p){
	viata = d;
	putere = p;
    }

    public boolean esteVie(){
	return viata > 0;
    }

    public void ranire(int d){
	if(this.esteVie()){
	    viata = viata-d;
	    if(!this.esteVie()){
		tocmaiUrmeazaSaMor();
	    }
	}
    }

    public void loveste(UnitateLupta u){
	if(this.esteVie()){
	    u.ranire(putere);
	}
	else{
	    u.ranire(0);
	}
    }

    protected void tocmaiUrmeazaSaMor(){}
    
}

class Arcas extends UnitateLuptaSimpla{
    public Arcas(){
	super(100,10);
    }
}

class Calaret extends UnitateLuptaSimpla{

    private static int nrCai = 0;

    public Calaret(){
	super(200,15);
    }

    public static int nrCai(){
	return nrCai;
    }

    protected void tocmaiUrmeazaSaMor(){
	nrCai++;
    }
}

class Pluton implements UnitateLupta{

    private UnitateLupta u[] = new UnitateLupta[10];
    private int k;
    
    public boolean adauga(UnitateLupta u ){
	if(!u.esteVie() || !this.esteVie()){
	    return false;
	}
	if(k == this.u.length){
	    this.u = Arrays.copyOf(this.u, 2*this.u.length);
	}
	this.u[k++] = u;
	return true;
    }

    public boolean esteVie(){
	if(k==0)
	    return true;

	for(int i=0;i<k;i++)
	    if(this.u[i].esteVie())
		return true;
	return false;
    }
    
    public void ranire(int d){

	for(int i=0;i<k;i++)
	    if(this.u[i].esteVie()){
		this.u[i].ranire(d);
		return;
	    }
	
    }

    public void loveste(UnitateLupta u){

	for(int i=0;i<k;i++)
	    if(this.u[i].esteVie()){
		this.u[i].loveste(u);
	    }
    }
    
}

class Main{
    public static void main(String argv[]){
	Pluton p1 = new Pluton();

	p1.adauga(new Arcas());
	p1.adauga(new Arcas());
	p1.adauga(new Arcas());
	p1.adauga(new Arcas());

	Pluton p2 = new Pluton();

	p2.adauga(new Calaret());

	Pluton p21 = new Pluton();

	p21.adauga(new Arcas());
	p21.adauga(new Arcas());

	p2.adauga(p21);

	new Fir(p1,p2).start();
	new Fir(p1,p2).start();
    }
}

class Fir extends Thread{


    /*

      public Patrat p;
      public Fir(Patrat x){
      p=x;
      }

      public static void main(String argv[]){
      Patrat p = new Patrat();
      new Fir(p).start();
      new Fir(p).start();
      }
      
     */
    
    private UnitateLupta u1,u2;

    public Fir(UnitateLupta a, UnitateLupta b){
	u1 = a;
	u2 = b;
    }
    
    public void run(){
	while(true){
	    u1.loveste(u2);
	    System.out.println(this.hashCode() + "  loveste " + u2.hashCode());
	    try{
		Thread.sleep(1000);
	    }catch(Exception e){}
    }
    }

}

/*

  class Patrat {
  private int l,L;

  public void set(int a){
  l=a;
  L=a;
  if(l!=L)
  System.out.println("?!??!?!?!?!!!??");
  }
  }
  
 */
