import java.util.*;
import java.io.*;
class MyStack {
    private Stack<Integer> mStack;
    private RandomAccessFile file;
    private int result;

    MyStack(String fileName){
        result = 0;

        mStack = new Stack<Integer>();
        try{
            File currentDirectory = new File(new File(".").getAbsolutePath());

            String path = (currentDirectory.getCanonicalPath());

            path = path + "/" + fileName;


            System.out.println(path);
            file = new RandomAccessFile(new File(path), "r");
            //System.out.println(file.readLine());

        }catch(FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");
        }
        catch(IOException ex) {
            System.out.println("Error reading file '" + fileName + "'");
        }
    }
    void stackUp () throws IOException{
        if (mStack.empty()){
            file.seek(0);
            String line;
            while ((line = file.readLine()) != null){
                //System.out.println(line);
                //mStack.push(line);
            }

        }else{
            System.out.println("Pilha já existente");
        }

    }

    void process () throws IOException{
        if (mStack.empty()){
            file.seek(0);
            String line;
            while ((line = file.readLine()) != null){
                //System.out.println(line);
                if (line.contains("PUSH ")){
                    line = line.replace("PUSH ","");
                    mStack.push(Integer.parseInt(line));
                }

                if ((line.equalsIgnoreCase("SUM")) && ( mStack.size() > 1)){
                    int left = mStack.pop();
                    int right = mStack.pop();

                    result = left + right;
                    System.out.println("Resultado Parcial: " + result);
                    mStack.push(result);
                }

                if ((line.equalsIgnoreCase("SUB")) && ( mStack.size() > 1)){
                    int left = mStack.pop();
                    int right = mStack.pop();

                    result = left - right;

                    System.out.println("Resultado Parcial: " + result);
                    mStack.push(result);
                }

                if ((line.equalsIgnoreCase("MULT")) && ( mStack.size() > 1)){
                    int left = mStack.pop();
                    int right = mStack.pop();

                    result = left * right;
                    System.out.println("Resultado Parcial: " + result);
                    mStack.push(result);
                }

                if ((line.equalsIgnoreCase("DIV")) && ( mStack.size() > 1)){
                    int left = mStack.pop();
                    int right = mStack.pop();

                    result = left / right;
                    System.out.println("Resultado Parcial: " + result);
                    mStack.push(result);
                }
            }



        }else{
            System.out.println("Pilha já existente");
        }


    }

    Stack getStack(){
        return mStack;
    }

    void getResult(){


        if (mStack.size() == 1){
            System.out.println("Resultado final: " + mStack.pop());


        }else{
            System.out.println("Erro na pilha: ");
            System.out.println("Stack: " + mStack);
        }
    }




}
