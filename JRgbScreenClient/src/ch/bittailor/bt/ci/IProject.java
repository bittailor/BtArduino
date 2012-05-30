package ch.bittailor.bt.ci;

import java.util.Collection;


public interface IProject {
	public void update();
	public Collection<IBuild> getHistrory();
}
