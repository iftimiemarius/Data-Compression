import java.util.ArrayList;
import java.util.Random;

import java.nio.file.Files;
import java.nio.file.Paths;

import java.io.FileWriter;
import java.io.IOException;

public class TestGenerator {
  public static void main(String[] args) {
    try {
      ArrayList<String> lines = new ArrayList<>(Files.readAllLines(Paths.get("words.txt")));
      if (args.length != 2) {
        System.out.println("Please enter the number of words and the file path");
        return;
      }
      int words = Integer.parseInt(args[0]);
      Random random = new Random();
      StringBuilder currentRow = new StringBuilder();
      FileWriter fileWriter = new FileWriter(args[1]);
      for (int i = 0; i < words; i++) {
        int index = random.nextInt(lines.size());
        currentRow.append(lines.get(index));
        currentRow.append(" ");
        if (currentRow.length() > 100) {
          currentRow.deleteCharAt(currentRow.length() - 1);
          fileWriter.write(currentRow.toString());
          fileWriter.write("\n");
          currentRow.delete(0, currentRow.length() - 1);
        }
      }
      fileWriter.close();
    }
    catch (IOException e) {
      e.printStackTrace();
    }
  }
}
