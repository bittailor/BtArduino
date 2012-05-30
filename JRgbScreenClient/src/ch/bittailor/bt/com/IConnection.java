package ch.bittailor.bt.com;

import java.io.InputStream;
import java.io.OutputStream;

public interface IConnection {

	public OutputStream getOutputStream();
	public InputStream getInputStream();
	public void close();
	public boolean isClosed();

}
