package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

public class BuildUtilities {

	public static void writeToFile(File file, String content) throws IOException
	{
		FileWriter writer = new FileWriter(file);
		writer.write(content);
		writer.close();
		System.out.println("Stored file: " + file);
	}

	public static void copyFile(File sourceFile, File sinkFile) throws IOException {
	  Files.copy(sourceFile.toPath(), sinkFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
	}
	
	public static void deleteFolder(File folder) {
		File[] files = folder.listFiles();
		if (files != null) { // some JVMs return null for empty dirs
			for (File f : files) {
				if (f.isDirectory()) {
					deleteFolder(f);
				} else {
					f.delete();
				}
			}
		}
		folder.delete();
	}
}
