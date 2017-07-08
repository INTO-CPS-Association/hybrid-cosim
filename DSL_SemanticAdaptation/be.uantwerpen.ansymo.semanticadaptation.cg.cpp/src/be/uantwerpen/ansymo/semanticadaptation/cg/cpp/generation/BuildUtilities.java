package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;

import be.uantwerpen.ansymo.semanticadaptation.log.Log;

public class BuildUtilities {
//	public List<File> copyNativeLibFiles(File outfolder) {
//		List<File> libFiles;
//		File outputFile = null;
//		InputStream jarfile = null;
//		FileOutputStream fos = null;
//		JarInputStream jarstream = null;
//		JarEntry filejarentry = null;
//
//		if (!outfolder.exists()) {
//			outfolder.mkdir();
//		}
//
//		libFiles = new LinkedList<>();
//
//		try {
//			jarfile = new FileInputStream(new File("jars/cppFramework.jar"));
//			jarstream = new JarInputStream(jarfile);
//			filejarentry = jarstream.getNextJarEntry();
//
//			// Extract the framework files
//			while (filejarentry != null) {
//				System.out.println("Extracting file: " + filejarentry.getName());
//				if (!filejarentry.getName().contains("hybridCosimulation-framework") || filejarentry.isDirectory()) {
//					filejarentry = jarstream.getNextJarEntry();
//					continue;
//				}
//
//				// Ignore these files
//				if (filejarentry.getName().contains(".gitignore") || filejarentry.getName().contains(".gitmodules")
//						/*|| filejarentry.getName().contains("README.md")*/ || filejarentry.getName().contains("LICENSE")) {
//					filejarentry = jarstream.getNextJarEntry();
//					continue;
//				}
//				String tmpFileName = filejarentry.getName().replace("hybridCosimulation-framework/", "");
//
//				outputFile = new File(outfolder.toString() + File.separator + tmpFileName);
//
//				libFiles.add(new File(outfolder.getName() + File.separator + tmpFileName));
//
//				outputFile.getParentFile().mkdirs();
//				fos = new FileOutputStream(outputFile);
//
//				while (jarstream.available() > 0) {
//					int b = jarstream.read();
//					if (b >= 0) {
//						fos.write(b);
//					}
//				}
//				fos.flush();
//				fos.close();
//				jarstream.closeEntry();
//				filejarentry = jarstream.getNextJarEntry();
//			}
//			jarstream.close();
//			jarfile.close();
//		} catch (IOException e) {
//			e.printStackTrace();
//		}
//
//		return libFiles;
//	}

	public static void writeToFile(File file, String content) throws IOException
	{
		FileWriter writer = new FileWriter(file);
		writer.write(content);
		writer.close();
		Log.println("Stored file: " + file);
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
