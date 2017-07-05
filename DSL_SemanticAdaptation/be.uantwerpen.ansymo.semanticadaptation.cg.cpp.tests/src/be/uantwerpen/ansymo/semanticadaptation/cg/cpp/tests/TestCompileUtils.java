package be.uantwerpen.ansymo.semanticadaptation.cg.cpp.tests;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;


public class TestCompileUtils {

	private static String OS = System.getProperty("os.name").toLowerCase();

	public static boolean isMac() {
		return OS.indexOf("mac") >= 0;
	}
	
	 public static boolean isUnix() {
	        return (OS.indexOf("nix") >= 0 || OS.indexOf("nux") >= 0 || OS.indexOf("aix") > 0 );
	    }

	protected int runExternalProcess(ProcessBuilder pb) throws IOException, InterruptedException {

		Process p = pb.start();

		final InputStream inStream = p.getInputStream();
		new Thread(new Runnable() {
			public void run() {
				InputStreamReader reader = new InputStreamReader(inStream);
				Scanner scan = new Scanner(reader);
				while (scan.hasNextLine()) {
					System.out.println(scan.nextLine());
				}
				scan.close();
			}
		}).start();

		final InputStream inErrStream = p.getErrorStream();
		new Thread(new Runnable() {
			public void run() {
				InputStreamReader reader = new InputStreamReader(inErrStream);
				Scanner scan = new Scanner(reader);
				while (scan.hasNextLine()) {
					System.out.println(scan.nextLine());
				}
				scan.close();
			}
		}).start();

		if (!p.waitFor(5, TimeUnit.MINUTES)) {
			// timeout - kill the process.
			p.destroy(); // consider using destroyForcibly instead
		}
		return p.exitValue();
	}

	public boolean checkCompile(File destination) throws InterruptedException, IOException {
		System.out.println(destination.getAbsolutePath());
		ProcessBuilder pb = new ProcessBuilder();
		pb.directory(destination);
		String cmake = "cmake";

		if (isMac()) {
			cmake = "/usr/local/bin/cmake";
		}

		pb.command(cmake, ".");

		int exitCode = runExternalProcess(pb);
		if (exitCode != 0)
			return false;

		pb = new ProcessBuilder();
		pb.directory(destination);
		pb.command("make", "-j4");

		exitCode = runExternalProcess(pb);
		if (exitCode != 0)
			return false;
		return true;
	}
}
