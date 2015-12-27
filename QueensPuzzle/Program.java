
public class Program
{

	public static void main(String[] args){
		int n = 500;
		QueensPuzzle teste;
		Thread t1;
		for (int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				teste = new QueensPuzzle(i,j,n,i,j);
				t1 = new Thread(teste);
				t1.start();
			}
		}

	}

}
