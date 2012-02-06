package ch.bittailor.bt.com;

public class ConnectionFactory implements IConnectionFactory {

	private String mHost;
	private int mPort;
	
	public ConnectionFactory(String iHost, int iPort) {
		mHost = iHost;
		mPort = iPort;
	}

	@Override
	public IConnection createConnection() {
		return new Connection(mHost, mPort);
	}

}
