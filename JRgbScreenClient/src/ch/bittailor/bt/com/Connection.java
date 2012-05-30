package ch.bittailor.bt.com;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Connection implements IConnection {

	private Socket mSocket;
	private OutputStream mOutput;
	private InputStream mInput;
	
	public Connection(String iHost, int iPort) {
		try {
			mSocket = new Socket(iHost, iPort);
			mSocket.setSoTimeout(5000);
			mSocket.setTcpNoDelay(true);
			mOutput = new BufferedOutputStream(mSocket.getOutputStream());
			mInput = mSocket.getInputStream();
		} catch (SocketException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		} catch (UnknownHostException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		} catch (IOException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		}
	}
	
	@Override
	public OutputStream getOutputStream() {
		return mOutput;
	}

	@Override
	public InputStream getInputStream() {
		return mInput;
	}

	@Override
	public void close() {
		try {
			mOutput.flush();
			mSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		}
	}
	
	@Override
	public boolean isClosed() {
		return mSocket.isClosed();
	}

}
