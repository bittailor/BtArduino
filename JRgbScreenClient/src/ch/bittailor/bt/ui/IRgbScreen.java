package ch.bittailor.bt.ui;

import java.awt.Color;

public interface IRgbScreen {
	
	public boolean isDisposed();

	public int width();

	public int height();

	public void setPixel(int iX, int iY, Color iColor);

	public void fill(Color iColor);

	public void repaint();
	
	public int numberOfSegments();

    public Color whiteBalance(int iSegment);

    public void setWhiteBalance(Color iColor, int iSegment);

    public void persistWhiteBalance(int iSegment);

}