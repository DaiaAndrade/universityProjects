import java.io.IOException;
import java.util.*;
public class MaquinaPilha {
    public static void main(String[] args) throws IOException {
        MyStack ms = new MyStack(args[0]);

        ms.process();

        ms.getResult();



    }

}
