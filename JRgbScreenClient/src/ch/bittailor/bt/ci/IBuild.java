package ch.bittailor.bt.ci;

public interface IBuild extends Comparable<IBuild> {
	
	enum Status {GOOD, FAILED}
	
	public Status getStatus();
	public long getId();
	
}
