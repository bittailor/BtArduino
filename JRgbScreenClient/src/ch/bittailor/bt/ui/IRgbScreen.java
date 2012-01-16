package ch.bittailor.bt.ui;

import java.awt.Color;

public interface IRgbScreen {

	public int width();

	public int height();

	public void setPixel(int iX, int iY, Color iColor);

	public void fill(Color iColor);

	public void repaint();

}