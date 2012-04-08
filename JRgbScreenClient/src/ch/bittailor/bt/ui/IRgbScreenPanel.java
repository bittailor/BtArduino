package ch.bittailor.bt.ui;

import java.awt.event.MouseListener;

public interface IRgbScreenPanel {

	public abstract void addListener(MouseListener iListener);

	public abstract void removeListener(MouseListener iListener);

}