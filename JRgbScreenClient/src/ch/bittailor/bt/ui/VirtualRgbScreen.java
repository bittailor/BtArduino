package ch.bittailor.bt.ui;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

public class VirtualRgbScreen extends JPanel implements IRgbScreen, MouseListener, IRgbScreenPanel {
	
	private static final int PIXEL_SIZE = 24;
	private static final int PIXEL_SPACE = 4;
	
	private static final long serialVersionUID = 5144882024279002974L;
	private int mWidth; 
	private int mHeight;
	private Color mWhiteBalance;
	private Color[][] mData;
	private List<MouseListener> mListener;
	
	public VirtualRgbScreen(int iWidth, int iHeight) {
		mWidth = iWidth;
		mHeight = iHeight;
		mWhiteBalance = new Color(63,63,63);
		mData = new Color[mHeight][mWidth];
		mListener = new ArrayList<MouseListener>();
		
		fill(Color.BLACK);
		
		Dimension dimension = new Dimension(mWidth * PIXEL_SIZE + PIXEL_SIZE , mHeight * PIXEL_SIZE  + PIXEL_SIZE);
		this.setMinimumSize(dimension);
		this.setMaximumSize(dimension);
		this.setPreferredSize(dimension);
		
		this.addMouseListener(this);
		
	}
	
	@Override
	public boolean isDisposed() {
		return false;
	}

	/* (non-Javadoc)
	 * @see ch.bittailor.bt.ui.IRgbScreenPanel#addListener(java.awt.event.MouseListener)
	 */
	@Override
	public void addListener(MouseListener iListener) {
		mListener.add(iListener);
	}
	
	/* (non-Javadoc)
	 * @see ch.bittailor.bt.ui.IRgbScreenPanel#removeListener(java.awt.event.MouseListener)
	 */
	@Override
	public void removeListener(MouseListener iListener) {
		mListener.remove(iListener);
	}
	
	public void paintComponent(Graphics g) {
		draw((Graphics2D)g);
	}
	
	private void draw(Graphics2D g) {
		g.setBackground(Color.BLACK);
		g.fillRect(0, 0, mWidth * PIXEL_SIZE + PIXEL_SIZE, mHeight * PIXEL_SIZE + PIXEL_SIZE);
		for (int i = 0; i < mData.length; i++) {
			for (int j = 0; j < mData[i].length; j++) {
				g.setColor(mData[i][j]);
				g.fillOval(j * PIXEL_SIZE + PIXEL_SIZE/2, i * PIXEL_SIZE + PIXEL_SIZE/2, PIXEL_SIZE-PIXEL_SPACE, PIXEL_SIZE-PIXEL_SPACE);
				g.setColor(Color.DARK_GRAY);
				g.drawOval(j * PIXEL_SIZE + PIXEL_SIZE/2, i * PIXEL_SIZE + PIXEL_SIZE/2, PIXEL_SIZE-PIXEL_SPACE, PIXEL_SIZE-PIXEL_SPACE);
			}
		}
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
		mData[iY][iX] = iColor;
	}

	@Override
	public void fill(Color iColor) {
		for (int i = 0; i < mData.length; i++) {
			for (int j = 0; j < mData[i].length; j++) {
				mData[i][j] = iColor;
			}
		}
	}

	@Override
	public void repaint() {
		this.repaint(0, 0, getWidth(), getHeight());

	}

	@Override
	public int numberOfSegments() {
		return 1;
	}

	@Override
	public Color whiteBalance(int iSegment) {
		return mWhiteBalance;
	}

	@Override
	public void setWhiteBalance(Color iColor, int iSegment) {
		mWhiteBalance = iColor;
	}

	@Override
	public void persistWhiteBalance(int iSegment) {
	}

	private void translate(MouseEvent iE) {
		int x = Math.min(mWidth-1 , (iE.getX() - PIXEL_SIZE/2  ) / PIXEL_SIZE);
		int y = Math.min(mHeight-1 , (iE.getY() - PIXEL_SIZE/2  ) / PIXEL_SIZE);
		iE.translatePoint(x - iE.getX(), y - iE.getY());
	}
	
	@Override
	public void mouseClicked(MouseEvent iE) {
		translate(iE);
		for (MouseListener listener : mListener) {
			listener.mouseClicked(iE);
		}

	}

	@Override
	public void mousePressed(MouseEvent iE) {
		translate(iE);
		for (MouseListener listener : mListener) {
			listener.mousePressed(iE);
		}
	}


	@Override
	public void mouseReleased(MouseEvent iE) {
		translate(iE);
		for (MouseListener listener : mListener) {
			listener.mouseReleased(iE);
		}
	}

	@Override
	public void mouseEntered(MouseEvent iE) {
		translate(iE);
		for (MouseListener listener : mListener) {
			listener.mouseEntered(iE);
		}
	}

	@Override
	public void mouseExited(MouseEvent iE) {
		translate(iE);
		for (MouseListener listener : mListener) {
			listener.mouseExited(iE);
		}
	}
	
}
