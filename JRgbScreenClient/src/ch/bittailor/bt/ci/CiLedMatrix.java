package ch.bittailor.bt.ci;

import java.awt.Image;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;

import ch.bittailor.bt.ui.IRgbScreen;
import ch.bittailor.bt.ui.ImageScreen;

public class CiLedMatrix implements Runnable {
	
	private ImageScreen mMatrixScreen;
	private List<ProjectLedMatrix> mProjects;
	
	public CiLedMatrix(IRgbScreen iMatrixScreen, List<IProject> projects) {
		mProjects = new ArrayList<ProjectLedMatrix>(projects.size());
		mMatrixScreen = new ImageScreen(iMatrixScreen);
		for (IProject project : projects) {
			Image image = new BufferedImage(8, 16, BufferedImage.TYPE_INT_RGB);
			ProjectLedMatrix projectLedMatrix = new ProjectLedMatrix(project, image);
			mProjects.add(projectLedMatrix);
		}	
	}
	
	public void update() {
		int offset = 0;
		for (ProjectLedMatrix project : mProjects) {
			project.update();
			mMatrixScreen.getGraphics().drawImage(project.getImage(), offset, 0, null);
			offset += 8;			
		}
		mMatrixScreen.repaint();
	}

	@Override
	public void run() {
		update();	
	}	
}
