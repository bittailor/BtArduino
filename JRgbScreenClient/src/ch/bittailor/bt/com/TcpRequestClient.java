package ch.bittailor.bt.com;

import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;

public class TcpRequestClient implements IRequestClient {

	static final int TCP_SERVER_BUFFER_LENGHT = 32;
	static final int CHECK_BYTE = 0xAF;
	
	private Socket mSocket;

	private PackageBuffer mOutputBuffer;
	private IOutputPackage mOutputPackage;
	private PackageBuffer mInputBuffer;
	private IInputPackage mInputPackage;
	
	
	
	public TcpRequestClient(Socket mSocket) {
		this.mSocket = mSocket;
		try {
			mSocket.setTcpNoDelay(true);
		} catch (SocketException e) {
			e.printStackTrace();
		}
		mOutputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mOutputPackage = new BinaryOutputPackage(mOutputBuffer);
		mInputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mInputPackage = new BinaryInputPackage(mInputBuffer);
	}

	@Override
	public IOutputPackage out() {
		return mOutputPackage;
	}

	@Override
	public IInputPackage in() {
		return mInputPackage;
	}

	@Override
	public void sendActionRequest() {
		try {
			send();
			clearBuffers();
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void sendQueryRequest() {
		try {			
			send();
			clearBuffers();	
			receive();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void send() throws IOException {
		mSocket.getOutputStream().write(CHECK_BYTE);
		mSocket.getOutputStream().write(mOutputBuffer.length());
		mSocket.getOutputStream().write(mOutputBuffer.raw(), 0, mOutputBuffer.length());
		mSocket.getOutputStream().flush();
	}
	
	private void clearBuffers() {
		mOutputBuffer.clear();
		mInputBuffer.clear();
	}
	
	private void receive() throws IOException {
		int checkByte = mSocket.getInputStream().read();
		if ( checkByte != CHECK_BYTE) {
			System.out.println("wrong check byte " + checkByte + " != " + CHECK_BYTE);
			throw new RuntimeException("wrong check byte " + checkByte + " != " + CHECK_BYTE);
		}

		int length = mSocket.getInputStream().read();
		int read = 0;
		while (read < length) {
			read += mSocket.getInputStream().read(mInputBuffer.raw(), read, (length-read));
		}
		mInputBuffer.filled(length);
	}

}
