
public class QueensPuzzle implements Runnable {
	
	private int x;
	private int y;
	private int size;
	private State[][] table;
	private int queenCounter;
	public int id[];
	
	
	public QueensPuzzle(int x, int y, int n, int id1, int id2){
		this.table = new State[n][n];
		this.size = n;
		this.x = x;
		this.y = y;
		this.queenCounter = 1;
		this.id = new int[2];
		this.id[0] = id1;
		this.id[1] = id2;
		
		//laço para inicializar a matriz
		
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++){
				this.table[i][j] = State.EMPTY;
			}
		}
		this.table[x][y] = State.QUEEN;
		markVertical(y);
		markHorizontal(x);
		markDiagonal(x,y);

	}
	
	private void markVertical(int x)
	{
		for (int i = 0 ; i < this.size ; i++){
			if(this.table[i][x] == State.EMPTY){
				this.table[i][x] = State.USED;
			}
		}
	}
	
	private void markHorizontal(int y) {
		for (int i = 0 ; i < this.size ; i++){
			if(this.table[y][i] == State.EMPTY){
				this.table[y][i] = State.USED;
			}
		}		
	}
	private void markDiagonal(int x, int y) {
		for (int i = x, j = y; i >= 0 && j >= 0 ; i--, j--){
			if(this.table[i][j] == State.EMPTY){
				this.table[i][j] = State.USED;
			}
		}
		for (int i = x, j = y; i < this.size && j < this.size ; i++, j++){
			if(this.table[i][j] == State.EMPTY){
				this.table[i][j] = State.USED;
			}	
		}
		for (int i = x, j = y; i >= 0 && j < this.size ; i--, j++){
			if(this.table[i][j] == State.EMPTY){
				this.table[i][j] = State.USED;
			}	
		}
		for (int i = x, j = y; i < this.size && j >= 0 ; i++, j--){
			if(this.table[i][j] == State.EMPTY){
				this.table[i][j] = State.USED;
			}	
		}
	}

	@Override
	public void run() {
		//laço rudimentar para setar rainha e marcar posições de ataque
		for(int i = 0; i < this.size; i++){
			for (int j = 0; j < this.size; j++){
				if (this.table[i][j] == State.EMPTY){
					this.table[i][j] = State.QUEEN;
					this.queenCounter++;
					markHorizontal(i);
					markVertical(j);
					markDiagonal(i,j);
				}
			}
		}
		if(this.queenCounter == this.size){
			System.out.print(this.id[0]+ "," + this.id[1] + "\n" + this.queenCounter + "\n" + this.toString() + "\n");
		}
	}
	
	@Override
	public String toString(){
		String matrix = new String();
		for (int i = 0; i < this.size ; i++){
			for (int j = 0; j < this.size ; j++){
				if(table[i][j] == State.QUEEN){
					matrix += "R ";
				}
				else{
					matrix += "X ";
				}
			}
			matrix += "\n";
		}
		return matrix;		
	}
}
