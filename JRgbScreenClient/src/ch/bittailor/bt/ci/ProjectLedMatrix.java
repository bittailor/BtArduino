package ch.bittailor.bt.ci;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.util.Iterator;

import ch.bittailor.bt.ci.IBuild.Status;

public class ProjectLedMatrix {
	
	private IProject mProject;
	private Image mImage;
	private Graphics2D mGraphics;

	public ProjectLedMatrix(IProject iProject, Image iImage) {
		mProject = iProject;
		mImage = iImage;
		mGraphics = (Graphics2D)mImage.getGraphics();
	}
	
	public void update() {
		mProject.update();	
		clear();
		if(mProject.getHistrory().isEmpty()) {
			drawEmpty();
			return;
		}
		draw();
	}
	
	public Image getImage() {
		return mImage;
	}

	private void clear() {
		mGraphics.setColor(Color.BLACK);
		mGraphics.fillRect(0, 0, mImage.getWidth(null), mImage.getHeight(null));	
	}
	
	private void draw() {
		Iterator<IBuild> iterator = mProject.getHistrory().iterator();	
		iterator.hasNext();
		IBuild currentBuild = iterator.next();
		drawCurrentBuild(currentBuild);
		int counter = 0;
		while (iterator.hasNext() && counter < 8) {
			drawHistory(iterator.next(),counter);
			counter++;
		}
		
	}

	private void drawHistory(IBuild iBuild, int iCounter) {
		if(iBuild.getStatus() == Status.GOOD) {
			mGraphics.setColor(Color.GREEN);
		} else {			
			mGraphics.setColor(Color.RED);
		}
		int line = iCounter + 8;
		mGraphics.drawLine(1, line, 6, line);	
	}
	
	private void drawCurrentBuild(IBuild iCurrentBuild) {
		if(iCurrentBuild.getStatus() == Status.GOOD) {
			drawGoodBuild();
			return;
		}
		drawFailedBuild();
		
	}

	private void drawFailedBuild() {
		mGraphics.setColor(Color.RED);
		drawRawFace();
		mGraphics.drawLine(3 ,4, 4, 4);
		mGraphics.drawLine(2 ,5, 2, 5);
		mGraphics.drawLine(5 ,5, 5, 5);	
	}

	private void drawGoodBuild() {
		mGraphics.setColor(Color.GREEN);
		drawRawFace();
		mGraphics.drawLine(3 ,5, 4, 5);
		mGraphics.drawLine(2 ,4, 2, 4);
		mGraphics.drawLine(5 ,4, 5, 4);
	}
	
	

	private void drawRawFace() {
		mGraphics.drawLine(1, 0, 6, 0);
		mGraphics.drawLine(1, 7, 6, 7);
		mGraphics.drawLine(0, 1, 0, 6);
		mGraphics.drawLine(7, 1, 7, 6);
		
		mGraphics.drawLine(2 ,2, 2, 2);
		mGraphics.drawLine(5 ,2, 5, 2);
	}

	private void drawEmpty() {
		
	
	}

	
	
}
