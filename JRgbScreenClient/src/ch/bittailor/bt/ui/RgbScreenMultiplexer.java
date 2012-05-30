package ch.bittailor.bt.ui;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class RgbScreenMultiplexer implements IRgbScreen {

	private int mWidth;
	private int mHeight;
	private Color[][] mData;
	private List<IRgbScreen> mScreens;
	
	RgbScreenMultiplexer(int iWidth, int iHeight) {
		mWidth = iWidth;
		mHeight = iHeight;
		mData = new Color[iWidth][iHeight];
		
		for (int x = 0; x < mData.length; x++) {
			for (int y = 0; y < mData[x].length; y++) {
				mData[x][y] = Color.BLACK;
			}
		}
		
		mScreens = new ArrayList<IRgbScreen>();
	}
	
	
	
	@Override
	public boolean isDisposed() {
		return false;
	}



	void add(IRgbScreen screen) {
		for (int x = 0; x < mData.length; x++) {
			for (int y = 0; y < mData[x].length; y++) {
				screen.setPixel(x, y, mData[x][y]);
			}
		}
		screen.repaint();
		mScreens.add(screen);
	}
	
	void remove(IRgbScreen screen) {
		mScreens.remove(screen);
	}
	
	@Override
	public int width() {
		return mWidth;
	}

	@Override
	public int height() {
		return mHeight;
	}

	@Override
	public void setPixel(int iX, int iY, Color iColor) {
		check();
		mData[iX][iY] = iColor;
		for (IRgbScreen screen : mScreens) {
			screen.setPixel(iX, iY, iColor);
		}
	}

	@Override
	public void fill(Color iColor) {
		check();
		for (int x = 0; x < mData.length; x++) {
			for (int y = 0; y < mData[x].length; y++) {
				mData[x][y] = iColor;
			}
		}
		for (IRgbScreen screen : mScreens) {
			screen.fill(iColor);
		}

	}

	@Override
	public void repaint() {
		check();
		for (IRgbScreen screen : mScreens) {
			screen.repaint();
		}
	}

	@Override
	public int numberOfSegments() {
		// TODO to implement 
		return 1;
	}

	@Override
	public Color whiteBalance(int iSegment) {
		// TODO to implement 
		return Color.BLACK;
	}

	@Override
	public void setWhiteBalance(Color iColor, int iSegment) {
		// TODO to implement 		
	}

	@Override
	public void persistWhiteBalance(int iSegment) {
		// TODO to implement 		
	}

	private void check() {		
		for (Iterator<IRgbScreen> iterator = mScreens.iterator(); iterator.hasNext();) {
			IRgbScreen screen = iterator.next();
			if (screen.isDisposed()) {
				iterator.remove();
			}
			
		}
	}
	
}
