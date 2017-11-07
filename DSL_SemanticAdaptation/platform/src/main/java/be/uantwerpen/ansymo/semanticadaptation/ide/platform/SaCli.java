package be.uantwerpen.ansymo.semanticadaptation.ide.platform;

import org.apache.commons.lang.StringUtils;
import org.eclipse.core.runtime.Platform;
import org.eclipse.equinox.app.IApplication;
import org.eclipse.equinox.app.IApplicationContext;

public class SaCli implements IApplication {

	@Override
	public Object start(IApplicationContext arg0) throws Exception {
		System.out.println("Argument context is: "+arg0);
		System.out.println("Arguments is: "+arg0.getArguments());
		System.out.println("Arguments is: "+StringUtils.join(Platform.getApplicationArgs(),","));
		return IApplication.EXIT_OK;
	}

	@Override
	public void stop() {
		
	}

}
