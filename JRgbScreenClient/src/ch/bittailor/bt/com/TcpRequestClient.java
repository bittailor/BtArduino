package ch.bittailor.bt.com;

import java.io.IOException;

public class TcpRequestClient implements IRequestClient {

	static final int TCP_SERVER_BUFFER_LENGHT = 32;
	static final int TCP_SERVER_START_REQUEST = 0xAF;
	static final int TCP_SERVER_QUIT = 0xAA;
	
	private IConnection mConnection;	
	private PackageBuffer mOutputBuffer;
	private IOutputPackage mOutputPackage;
	private PackageBuffer mInputBuffer;
	private IInputPackage mInputPackage;
	
		
	public TcpRequestClient(IConnectionFactory iConnectionFactory) {
		mConnection = iConnectionFactory.createConnection();
		mOutputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mOutputPackage = new BinaryOutputPackage(mOutputBuffer);
		mInputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mInputPackage = new BinaryInputPackage(mInputBuffer);
	}

	public TcpRequestClient(IConnection iConnection) {
		mConnection = iConnection;
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
			receive();
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
	
	@Override
	public void close() {
		try {
			mConnection.getOutputStream().write(TCP_SERVER_QUIT);
			mConnection.getOutputStream().flush();
			Thread.sleep(100);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		mConnection.close();
		
	}

	private void send() throws IOException {
		mConnection.getOutputStream().write(TCP_SERVER_START_REQUEST);
		mConnection.getOutputStream().write(mOutputBuffer.length());
		mConnection.getOutputStream().write(mOutputBuffer.raw(), 0, mOutputBuffer.length());
		mConnection.getOutputStream().flush();
	}
	
	private void clearBuffers() {
		mOutputBuffer.clear();
		mInputBuffer.clear();
	}
	
	private void receive() throws IOException {
		int checkByte = mConnection.getInputStream().read();
		if ( checkByte != TCP_SERVER_START_REQUEST) {
			System.out.println("wrong check byte " + checkByte + " != " + TCP_SERVER_START_REQUEST);
			throw new RuntimeException("wrong check byte " + checkByte + " != " + TCP_SERVER_START_REQUEST);
		}

		int length = mConnection.getInputStream().read();
		int read = 0;
		while (read < length) {
			read += mConnection.getInputStream().read(mInputBuffer.raw(), read, (length-read));
		}
		mInputBuffer.filled(length);
	}

}
