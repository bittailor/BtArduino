package ch.bittailor.bt.com;

import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;

public class TcpRequestClient implements IRequestClient {

	static final int TCP_SERVER_BUFFER_LENGHT = 32;
	static final int CHECK_BYTE = 0xAF;
	
	private Socket mSocket;

	private PackageBuffer mOutBuffer;
	private IOutputPackage mOut;
	private PackageBuffer mInBuffer;
	private IInputPackage mIn;
	
	
	
	public TcpRequestClient(Socket mSocket) {
		this.mSocket = mSocket;
		try {
			mSocket.setTcpNoDelay(true);
		} catch (SocketException e) {
			e.printStackTrace();
		}
		mOutBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mOut = new BinaryOutputPackage(mOutBuffer);
		mInBuffer = new PackageBuffer(TCP_SERVER_BUFFER_LENGHT);
		mIn = new BinaryInputPackage(mInBuffer);
	}

	@Override
	public IOutputPackage out() {
		return mOut;
	}

	@Override
	public IInputPackage in() {
		return mIn;
	}

	@Override
	public void sendRequest() {
		try {
			
			mSocket.getOutputStream().write(CHECK_BYTE);
			mSocket.getOutputStream().write(mOutBuffer.length());
			mSocket.getOutputStream().write(mOutBuffer.raw(), 0, mOutBuffer.length());
			mSocket.getOutputStream().flush();
			
			mOutBuffer.clear();
			mInBuffer.clear();
			
			int checkByte = mSocket.getInputStream().read();
			if ( checkByte != CHECK_BYTE) {
				System.out.println("wrong check byte " + checkByte + " != " + CHECK_BYTE);
				throw new RuntimeException("wrong check byte " + checkByte + " != " + CHECK_BYTE);
			}
			
			int length = mSocket.getInputStream().read();
			int read = 0;
			while (read < length) {
				read += mSocket.getInputStream().read(mInBuffer.raw(), read, (length-read));
			}
			mInBuffer.filled(length);
			// Thread.sleep(1);
						
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
		}
	}

}
