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
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;

/**
 *
 * @author ufabc
 */
public class TemperaturaFuzzy {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException, InterruptedException {
        // TODO code application logic here
        // Load from 'FCL' file
        String fileName = "fcl/temperatura.fcl";
        FIS fis = FIS.load(fileName, true);

        File arquivo = new File("files/saida.csv");

        //Cria rquivo para escrita
        FileWriter fw = new FileWriter(arquivo, false);
        BufferedWriter bw = new BufferedWriter(fw);

        if (fis == null) { // Error while loading
            System.err.println("Can't load file: '" + fileName + "'");
            return;
        }

        // Show variables
        FunctionBlock functionBlock = fis.getFunctionBlock(null);
        JFuzzyChart.get().chart(functionBlock);

        // variaveis de entrada HARDCODED
        double target = 30;
        double updated_temperatura = 5;
        // Set inputs
        functionBlock.setVariable("temperatura", updated_temperatura);
        functionBlock.setVariable("target", target);
        int volume = 100; // comprimento * largura * altura
        double delta_t = (10000 * 0.000293071) / (1.060 * volume);
        // tempo para alcancar a temperatura
        int time = 0;

        // para de atuar quando a diferença for menor que 0.01
        while (Math.abs(target - updated_temperatura) > 0.01) {
            fis.evaluate();
            time++;
            double pwm = (fis.getVariable("pwm").getValue() / 100);
            // nova temperatura da sala apos 1 segundo
            updated_temperatura += delta_t * pwm;
            try {
                // grava os dados em uma arquivo
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
            // seta novamente a variavel de entrada temperatura com a nova temperatura
            functionBlock.setVariable("temperatura", updated_temperatura);
            functionBlock.setVariable("target", target);
            //Thread.sleep(50);
        }

        bw.close();
        fw.close();
        System.out.println("Seu sistema demorou " + time + " segundos para alcançar a temperatura.");

    }

}
