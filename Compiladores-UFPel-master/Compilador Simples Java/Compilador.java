class Compilador{
    public static void main(String[]args) {

        ArvoreSintatica arv=null;

        try{
            AnaliseLexica al = new AnaliseLexica(args[0]);

            Parser as = new Parser(al);


            arv = as.parseProg();

            System.out.println("=== BACK END ORIGINAL ===\n");

            CodeGen backend = new CodeGen();
            String codigo = backend.geraCodigo(arv);
            System.out.println(codigo);


            System.out.println("\n=== INTERPRETADOR ===\n");

            Interpretador runner = new Interpretador();
            System.out.println("Resultado Final: " + runner.interpretar(arv));

        }catch(Exception e) {
            System.out.println("Erro de compilação:\n" + e);
        }




    }
}
