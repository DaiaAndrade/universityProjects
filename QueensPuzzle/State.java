
public enum State {
	EMPTY(0), QUEEN(1), USED(-1);
    private int value;
    
    private State(int value){
    	this.value = value;
    }
}
