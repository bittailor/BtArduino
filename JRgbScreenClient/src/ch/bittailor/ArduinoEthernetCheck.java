package ch.bittailor;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class ArduinoEthernetCheck {
	
	public static final int SERVER_DATA    = 0xAF;
	public static final int SERVER_QUIT    = 0xAA;
	
	public static void main(String[] args) {
		try {
			final Socket socket = new Socket("192.168.2.2",2000);
			socket.setTcpNoDelay(true);
			OutputStream outputStream = new BufferedOutputStream(socket.getOutputStream());
			InputStream inputStream = socket.getInputStream();
			int dataLength = 1;
			for (int loop = 0; loop < 1000000 ; loop++) {
				System.out.println("loop " + loop);				
				int counter = 0;
				while(counter < 256) {					
					outputStream.write(SERVER_DATA);
					outputStream.write(dataLength);
					for (int i = 0; i < dataLength; i++) {
						outputStream.write(counter++);
					}
					outputStream.flush();
					int commandByte = inputStream.read();
					if (commandByte == SERVER_DATA) {
						int readDataLength = inputStream.read();
						for (int i = 0; i < readDataLength; i++) {
							int data = inputStream.read();
							// System.out.println("read> " + data);
						}
					} else {
						System.err.println("unknown command " + Integer.toHexString(commandByte));
					}
					dataLength = (dataLength % 64) +1;
					Thread.sleep(10);
				}
			}
			outputStream.write(SERVER_QUIT);
			Thread.sleep(100);
			socket.close();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
