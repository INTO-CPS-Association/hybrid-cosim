package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.util.LinkedList;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;

public class BuildUtilities {
	public void copyNativeLibFiles(File outfolder) {
		List<File> libFiles;
		File outputFile = null;
		InputStream jarfile = null;
		FileOutputStream fos = null;
		JarInputStream jarstream = null;
		JarEntry filejarentry = null;

		if (!outfolder.exists()) {
			outfolder.mkdir();
		}
		else
		{
			return;
		}

		libFiles = new LinkedList<>();

		try {
			jarfile = new FileInputStream(new File("jars/cppFramework.jar"));
			jarstream = new JarInputStream(jarfile);
			filejarentry = jarstream.getNextJarEntry();

			// Extract the framework files
			while (filejarentry != null) {
				System.out.println("Extracting file: " + filejarentry.getName());
				if (!filejarentry.getName().contains("hybridCosimulation-framework") || filejarentry.isDirectory()) {
					filejarentry = jarstream.getNextJarEntry();
					continue;
				}

				// Ignore these files
				if (filejarentry.getName().contains(".gitignore") || filejarentry.getName().contains(".gitmodules")
						/*|| filejarentry.getName().contains("README.md")*/ || filejarentry.getName().contains("LICENSE")) {
					filejarentry = jarstream.getNextJarEntry();
					continue;
				}
				String tmpFileName = filejarentry.getName().replace("hybridCosimulation-framework/", "");

				outputFile = new File(outfolder.toString() + File.separator + tmpFileName);

				libFiles.add(new File(outfolder.getName() + File.separator + tmpFileName));

				outputFile.getParentFile().mkdirs();
				fos = new FileOutputStream(outputFile);

				while (jarstream.available() > 0) {
					int b = jarstream.read();
					if (b >= 0) {
						fos.write(b);
					}
				}
				fos.flush();
				fos.close();
				jarstream.closeEntry();
				filejarentry = jarstream.getNextJarEntry();
			}
			jarstream.close();
			jarfile.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

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
