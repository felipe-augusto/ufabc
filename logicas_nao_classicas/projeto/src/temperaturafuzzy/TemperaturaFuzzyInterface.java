/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temperaturafuzzy;

import java.io.IOException;
import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;

/**
 *
 * @author ufabc
 */
public class TemperaturaFuzzyInterface {
    public static void main(String[] args) {
        Interface tela = new Interface();
        tela.setVisible(true);
    }

    public static void calculaFuzzy(int volume, int potencia, double temperatura, double target ) throws IOException{
        // TODO code application logic here
        // Load from 'FCL' file
        String fileName = "fcl/temperatura.fcl";
        FIS fis = FIS.load(fileName, true);
        
        if (fis == null) { // Error while loading
            System.err.println("Can't load file: '" + fileName + "'");
            return;
        }
        
        FunctionBlock functionBlock = fis.getFunctionBlock(null);
        
        functionBlock.setVariable("temperatura", temperatura);
        functionBlock.setVariable("target", target);
        
        // variacao temperatura por segundo
        double delta_t = (potencia * 0.000293071) / (1.060 * volume);
        int time = 0;
        
        while (Math.abs(target - temperatura) > 0.01) {
            fis.evaluate();
            time++;
            double pwm = (fis.getVariable("pwm").getValue() / 100);
            // nova temperatura da sala apos 1 segundo
            temperatura += delta_t * pwm;
            // seta novamente a variavel de entrada temperatura com a nova temperatura
            functionBlock.setVariable("temperatura", temperatura);
        }
        
        System.out.println("Seu sistema demorou " + time + " segundos para alcançar a temperatura.");
    }
}
