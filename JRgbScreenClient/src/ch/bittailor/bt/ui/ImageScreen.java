package ch.bittailor.bt.ui;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.image.BufferedImage;

public class ImageScreen {

	private BufferedImage mImage;
	private BufferedImage mImageMirror;
	private IRgbScreen mScreen;
	private Graphics2D mGraphics;
	private Graphics2D mGraphicsMirror;
	
	public ImageScreen(IRgbScreen iScreen) {
		this.mScreen = iScreen;
		
		mImage = new BufferedImage(iScreen.width(), iScreen.height(), BufferedImage.TYPE_INT_RGB);
		mImageMirror = new BufferedImage(iScreen.width(), iScreen.height(), BufferedImage.TYPE_INT_RGB);
		
		mGraphics = asGraphics(mImage);
		mGraphicsMirror = asGraphics(mImageMirror);
		
		init(mGraphics);
		init(mGraphicsMirror);
		
		mScreen.fill(Color.BLACK);
		mScreen.repaint();	
	}
	
	public Image getImage() {
		return mImage;
	}
	
	public Graphics2D getGraphics() {
		return mGraphics;
	}
	
	public void repaint() {
		for (int x = 0; x < mImage.getWidth(); x++) {
			for (int y = 0; y < mImage.getHeight(); y++) {
				int rgb = mImage.getRGB(x, y);
				if (rgb != mImageMirror.getRGB(x, y)) {
					mScreen.setPixel(x, y,new Color(rgb) );	
					mImageMirror.setRGB(x, y, rgb);
				}
			}
		}
		mScreen.repaint();
	}

	private Graphics2D asGraphics(BufferedImage iImage) {
		return (Graphics2D)iImage.getGraphics();
	}
	
	private void init(Graphics2D iGraphics) {
		iGraphics.setColor(Color.BLACK);
		iGraphics.fillRect(0, 0, mScreen.width(), mScreen.height());
	}
	
}
