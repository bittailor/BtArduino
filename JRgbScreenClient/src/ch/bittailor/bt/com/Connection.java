package ch.bittailor.bt.com;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Connection implements IConnection {

	private Socket mSocket;
	
	public Connection(String iHost, int iPort) {
		try {
			mSocket = new Socket(iHost, iPort);
			mSocket.setTcpNoDelay(true);
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
		try {
			return mSocket.getOutputStream();
		} catch (IOException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		}
	}

	@Override
	public InputStream getInputStream() {
		try {
			return mSocket.getInputStream();
		} catch (IOException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		}
	}

	@Override
	public void close() {
		try {
			mSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
			throw new RuntimeException("Connection Problem",e);
		}
	}

}
