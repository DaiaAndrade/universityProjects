class Interpretador{
	Interpretador(){}
	public int interpretar(ArvoreSintatica t){
            int res = 0;
            int arg1 = 0;
            int arg2 = 0;

            if(t instanceof Soma){
                arg1 = interpretar(((Soma)t).arg1);
                arg2 = interpretar(((Soma)t).arg2);
                System.out.println("Resultado Parcial: " + arg1 + "+" + arg2);
                return (arg1 + arg2);
            }

            if(t instanceof Sub){
                arg1 = interpretar(((Sub)t).arg1);
                arg2 = interpretar(((Sub)t).arg2);
                System.out.println("Resultado Parcial: " + arg1 + "-" + arg2);
                return (arg1 - arg2);
            }

            if(t instanceof Mult){
                arg1 = interpretar(((Mult)t).arg1);
                arg2 = interpretar(((Mult)t).arg2);
                System.out.println("Resultado Parcial: " + arg1 + "*" + arg2);
                return (arg1 * arg2);
            }

            if(t instanceof Div){
                arg1 = interpretar(((Div)t).arg1);
                arg2 = interpretar(((Div)t).arg2);
                System.out.println("Resultado Parcial: " + arg1 + "/" + arg2);
                return (arg1 / arg2);
            }

            if(t instanceof Num){
                System.out.println("Reconhece Número: " + ((Num)t).num);
                return (((Num)t).num);
            }
            return res;
	}
}
