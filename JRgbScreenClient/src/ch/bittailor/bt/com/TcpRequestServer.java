package ch.bittailor.bt.com;

import java.io.IOException;

public class TcpRequestServer implements Runnable {

	static final int TCP_SERVER_BUFFER_LENGHT = 32;
	static final int TCP_SERVER_START_REQUEST = 0xAF;
	static final int TCP_SERVER_QUIT = 0xAA;
	
	private IConnection mConnection;	
	private PackageBuffer mOutputBuffer;
	private IOutputPackage mOutputPackage;
	private PackageBuffer mInputBuffer;
	private IInputPackage mInputPackage;
	private IRequestServer mHandler;
	
		
	public TcpRequestServer(IConnection iConnection, IRequestServer iHandler) {
		mConnection = iConnection;
		mHandler = iHandler;
		mOutputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mOutputPackage = new BinaryOutputPackage(mOutputBuffer);
		mInputBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mInputPackage = new BinaryInputPackage(mInputBuffer);
	}


	@Override
	public void run() {
		while(true) {
			int commandByte;
			try {
				commandByte = mConnection.getInputStream().read();
				if (commandByte == TCP_SERVER_START_REQUEST) {
					request();					
				}
				if (commandByte == TCP_SERVER_QUIT) {
					return;
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}


	private void request() throws IOException {
		int size = mConnection.getInputStream().read();
		mInputBuffer.clear();
		while(mInputBuffer.length() < size) {
			int read = mConnection.getInputStream().read();
			if (read == -1) {
				throw new IOException("Unexpected end of stream");
			}
			int t = (0xff & read);
			byte b = (byte) t;
			mInputBuffer.put(b);
		}
		mOutputBuffer.clear();
		mHandler.handleRequest(mInputPackage,mOutputPackage);
		mConnection.getOutputStream().write(TCP_SERVER_START_REQUEST);
		mConnection.getOutputStream().flush();
		mConnection.getOutputStream().write(mOutputBuffer.length());
		mConnection.getOutputStream().flush();
		if (mOutputBuffer.length() > 0) {
			mConnection.getOutputStream().write(mOutputBuffer.raw(),0,mOutputBuffer.length());
			mConnection.getOutputStream().flush();
		}	
	}
}
