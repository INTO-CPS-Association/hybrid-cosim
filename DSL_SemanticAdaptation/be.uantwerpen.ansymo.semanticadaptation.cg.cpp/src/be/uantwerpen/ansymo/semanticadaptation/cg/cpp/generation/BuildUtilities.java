package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.generation;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.LinkedList;
import java.util.List;
import java.util.jar.JarEntry;
import java.util.jar.JarInputStream;

public class BuildUtilities {
	public List<File> copyNativeLibFiles(File outfolder) {
		List<File> libFiles;
		File outputFile = null;
		InputStream jarfile = null;
		FileOutputStream fos = null;
		JarInputStream jarstream = null;
		JarEntry filejarentry = null;

		if (!outfolder.exists()) {
			outfolder.mkdir();
		}

		libFiles = new LinkedList<>();

		try {
			jarfile = this.getClass().getClassLoader().getResourceAsStream("jars/cppFramework.jar");
			jarstream = new JarInputStream(jarfile);
			filejarentry = jarstream.getNextJarEntry();

			// Extract the framework files
			while (filejarentry != null) {
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

		return libFiles;
	}
}
