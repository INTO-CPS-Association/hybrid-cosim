package be.uantwerpen.ansymo.semanticadaptation.ui.wizard;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

import org.apache.commons.io.IOUtils;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.IWorkbench;
import org.eclipse.ui.IWorkbenchWizard;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.dialogs.WizardNewFileCreationPage;
import org.eclipse.ui.ide.IDE;

import be.uantwerpen.ansymo.semanticadaptation.semanticAdaptation.SemanticAdaptation;

public class SaNewFileWizard extends Wizard implements IWorkbenchWizard {

	private static final String WIZARD_NAME = "VDM New File Wizard";

	private WizardNewFileCreationPage _pageOne;
	private String fPageName;
	private String fPageTitle;
	private String fPageDescription;
	private IStructuredSelection fStructuredSelection;

	public SaNewFileWizard() {
		setWindowTitle(WIZARD_NAME);
		this.fPageName = getPageName();
		this.fPageTitle = getPageTitle();
		this.fPageDescription = getPageDescription();
	}

	@Override
	public void addPages() {
		super.addPages();
		_pageOne = new WizardNewFileCreationPage(this.fPageName, this.fStructuredSelection);
		_pageOne.setFileExtension(getFileExtension());
		_pageOne.setTitle(this.fPageTitle);
		_pageOne.setDescription(this.fPageDescription);

		addPage(_pageOne);

	}

	/*
	 * Gets the main page name
	 */
	protected String getPageName() {
		return "New Semantic Adaptation";
	}

	/*
	 * Gets the main page title to be displayed
	 */
	protected String getPageTitle() {
		return getPageName();
	}

	/*
	 * Gets the main page description
	 */
	protected String getPageDescription() {
		return "Create a new basic semantic adaptation";
	}

	/*
	 * Gets the file extension of the file to create
	 */
	protected String getFileExtension() {
		return "sa";
	}

	/*
	 * Gets the file template or null if none is provided
	 */
	protected String getFileTemplate(String fileName) {
		InputStream stream = null;
		try {
			stream = SemanticAdaptation.class.getResourceAsStream("/templates/new_file_template.sa");
			return IOUtils.toString(stream);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		} finally {
			IOUtils.closeQuietly(stream);
		}
	}

	@Override
	public boolean canFinish() {
		return super.canFinish() && _pageOne.getErrorMessage() == null;
	}

	@Override
	public boolean performFinish() {
		IFile file = _pageOne.createNewFile();
		if (file.exists()) {
			String fileName = file.getName();
			if (fileName.contains(".")) {
				fileName = fileName.substring(0, fileName.indexOf("."));
			}

			boolean isClean = false;
			InputStream in = null;
			try {
				in = file.getContents();
				if (file.getContents().read() == -1) {
					isClean = true;
				}
			} catch (IOException e) {
			} catch (CoreException e) {
			} finally {
				if (in != null) {
					try {
						in.close();
					} catch (IOException e) {
					}
				}
			}

			if (isClean) {
				String fileTemplate = getFileTemplate(fileName);
				if (fileTemplate != null) {
					applyTemplate(file, fileTemplate);
				}
			}

		}
		try {
			IDE.openEditor(PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage(), file, true);
			file.touch(null);
			file.refreshLocal(IResource.DEPTH_ONE, null);
		} catch (CoreException e) {
			e.printStackTrace();
		}
		return true;
	}

	private void applyTemplate(IFile file, String fileTemplate) {
		InputStream stream;
		try {
			stream = new ByteArrayInputStream(fileTemplate.getBytes());
			file.setContents(stream, IFile.FORCE, null);
		} catch (CoreException e) {
			e.printStackTrace();

		}

	}

	public void init(IWorkbench workbench, IStructuredSelection selection) {
		this.fStructuredSelection = selection;
	}

}
