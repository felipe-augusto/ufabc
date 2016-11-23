/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package temperaturafuzzy;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.math.BigDecimal;
import java.math.RoundingMode;
import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.rule.Variable;
import net.sourceforge.jFuzzyLogic.rule.Rule;
import net.sourceforge.jFuzzyLogic.rule.RuleBlock;
import net.sourceforge.jFuzzyLogic.rule.RuleExpression;
import net.sourceforge.jFuzzyLogic.rule.RuleTerm;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;

import java.util.HashMap;
import java.util.List;

/**
 *
 * @author ufabc
 */
public class TemperaturaFuzzy {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
      // TODO code application logic here
      // Load from 'FCL' file
      String fileName = "fcl/temperatura.fcl";
      FIS fis = FIS.load(fileName, true);
      
      File arquivo = new File("files/saida.csv");
 
       //Cria rquivo para escrita
       FileWriter fw = new FileWriter(arquivo, false);
       BufferedWriter bw = new BufferedWriter(fw);
      
      if (fis == null) 
      { // Error while loading
         System.err.println("Can't load file: '" + fileName + "'");
         return;
      }
      
      // Show variables
      FunctionBlock functionBlock = fis.getFunctionBlock(null);
      JFuzzyChart.get().chart(functionBlock);
 
      int target = 35;
      double updated_temperatura = 10;
      // Set inputs
      functionBlock.setVariable("temperatura", updated_temperatura);
      functionBlock.setVariable("target", target);
      double delta_t = 4 / (1.06 * 45.68); // 1 s -> 0.4C
   
   int time = 0;
      
    while(target - updated_temperatura > 0.001) { 
        fis.evaluate();

        time++;
        double pwm = (fis.getVariable("pwm").getValue() / 100);
        updated_temperatura += delta_t * pwm;
        try 
            {
                String gravar;
                gravar = String.valueOf(time).replace('.', ',');
                bw.write(gravar);
                bw.write(";");
                BigDecimal bdTemperatura = new BigDecimal(updated_temperatura).setScale(3, RoundingMode.HALF_EVEN);
                double valTemperatura = bdTemperatura.doubleValue();
                gravar = String.valueOf(valTemperatura).replace('.', ',');
                bw.write(gravar);
                bw.write(";");
                BigDecimal bdVariacao = new BigDecimal(delta_t * pwm).setScale(5, RoundingMode.HALF_EVEN);
                double valVariacao = bdVariacao.doubleValue();
                gravar = String.valueOf(valVariacao).replace('.', ',');
                bw.write(gravar);
                bw.newLine();

            } catch (IOException ex) {
            ex.printStackTrace();
            }
        //System.out.println("Temperatura : " + updated_temperatura + ", pwm" + pwm);
        functionBlock.setVariable("temperatura", updated_temperatura);
    }
    
    System.out.println(time);
    
    }
    
}
